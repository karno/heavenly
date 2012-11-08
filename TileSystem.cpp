#include <list>
#include <vector>
#include <stack>
#include <stdexcept>
#include <algorithm>
#include <utility>

// for assertion
#include <cassert>

#include "TileSystem.h"
#include "System.h"
#include "WinHand.h"
#include "TileFactory.h"

// 国士無双判定用
#include "ThirteenOrphans.h"

// 七対子判定用
#include "SevenPairs.h"

//#define ___TILESYSTEM_TRACE_PRINT_ENABLED

using namespace std;

vector<WinHand>* TileSystem::GetWinHandCandidates(
	const list<Tile*>& tile, const vector<vector<Tile*> >& subs)
{
	// 受け取った牌のアサーション
	// 13枚で判定(4面子 + 1枚)
	if (tile.size() + subs.size() * 3 != 13)
		throw invalid_argument("argument must have 13 tiles(if you have quadraple, it count as 3 tiles.");

	// 理牌
	vector<Tile*> cache(tile.begin(), tile.end());
	return GetWinHandCandidates(cache, subs);
}

vector<WinHand>* TileSystem::GetWinHandCandidates(
	vector<Tile*>& cache, const vector<vector<Tile*> >& subs)
{
	if (cache.size() + subs.size() * 3 != 13)
		throw invalid_argument("argument must have 13 tiles(if you have quadraple, it count as 3 tiles.");

	sort(cache.begin(), cache.end(), Tile::IdSort);

	// deleteが必要
	vector<WinHand> *rets = new vector<WinHand>;

	// 鳴いていないなら国士無双の可能性もあり。
	if (cache.size() == 13)
	{
		// 国士無双判定
		ThirteenOrphans tho;
		vector<Tile*>* thw = tho.CheckWaits(cache);
		if (thw != NULL)
		{
			// 国士無双聴牌
			// (他の役とは複合しようがない)
			for (vector<Tile*>::const_iterator wi = thw->begin();
				wi != thw->end();
				++wi)
			{
				WinHand temp;
				temp.Tiles.push_back(cache);
				temp.Waiting = (*wi);
				rets->push_back(temp);
			}
			// 国士無双で戻る(確定)
			return rets;
		}

		// 七対子判定
		SevenPairs sp;
		WinHand* wht = sp.CheckWait(cache);
		if (wht != NULL)
		{
			WinHand temp;
			temp.Tiles = wht->Tiles;
			temp.Waiting = wht->Waiting;
			rets->push_back(temp);
			delete(wht);
			// 別のcandidateも無いことは無いのでreturnはしない
		}
	}

	vector<Tile*> heads;

	// 雀頭が存在する条件下で聴牌チェック
	for (int i = 0; i < cache.size() - 1; i++)
	{
		// フラグ消去
		for (int c = 0; c < cache.size(); c++)
			cache.at(c)->inactive = false;

		// 雀頭候補を取得
		Tile* curhead = cache.at(i);

		// 同種の牌は一つしか無いので、雀頭構成不可
		if (cache.at(i + 1)->id != curhead->id) continue;

		// 不要なのでフラグを立てる
		curhead->inactive = true;
		cache.at(i + 1)->inactive = true;

		// 雀頭参照
		heads.push_back(curhead);
		heads.push_back(cache.at(i + 1));

#ifdef ___TILESYSTEM_TRACE_PRINT_ENABLED
		cout << "@head is " << curhead->ToString() << "x2" << endl;
#endif

		const vector<WinHand>* c = GetCandidatesInner(
			cache, heads, subs);

		if (c != NULL)
		{
			for (vector<WinHand>::const_iterator iter = c->begin();
				iter != c->end();
				++iter)
			{
				rets->push_back(*iter);
			}
		}

		delete(c);

		// 参照削除
		heads.pop_back();
		heads.pop_back();

		// 立てたフラグは折る！
		curhead->inactive = false;
		cache.at(i + 1)->inactive = false;

		while ((i + 1) < cache.size() &&
			cache.at(i + 1)->id == curhead->id)
		{
			// 同じ牌を読み飛ばす
			i++;
		}
	}
	// 雀頭待ちの状態で聴牌チェック
	for (int i = 0; i < cache.size(); i++)
	{
		// フラグ消去
		for (int c = 0; c < cache.size(); c++)
			cache.at(c)->inactive = false;

		// 雀頭候補を取得
		Tile* curhead = cache.at(i);

		// 不要なのでフラグを立てる
		curhead->inactive = true;

		heads.push_back(curhead);

#ifdef ___TILESYSTEM_TRACE_PRINT_ENABLED
		cout << endl << "@head is " << curhead->ToString() << endl;
#endif

		const vector<WinHand>* c = GetCandidatesInner(
			cache, heads, subs);

		if (c != NULL)
		{
			for (vector<WinHand>::const_iterator iter = c->begin();
				iter != c->end();
				++iter)
			{
				rets->push_back(*iter);
			}
		}

		delete(c);

		// 参照削除
		heads.pop_back();

		// 立てたフラグは折る！
		curhead->inactive = false;

		// 一枚先まで読んでおく(forループで一つ加算されるので)
		while ((i + 1) < cache.size() &&
			cache.at(i + 1)->id == curhead->id)
		{
			// 同じ牌を読み飛ばす
			i++;
		}
	}
	if (rets->size() == 0)
	{
		delete(rets);
		return NULL;
	}
	else
		return rets;
}

/*
すべてのCandidateを取得する。
(数え上げソート？バックトラック？)

以下の手順に従えば、和了形が重複することなく列挙できるはず・・・。

手順1:
セットスタックをpop、インクリメント
その位置から、セットが取得できるかチェック
→できる:取得開始位置をスタックに2回push
手順1を繰り返す
→できない:シーケンススタックに-1をプッシュ、抜ける


手順2:
シーケンススタックをpop
(-1の場合は)インクリメント
(0以上の場合は)シーケンス読み出し位置が
別種の牌を選択するまでインクリメント
その位置から、シーケンスが取得できるかチェック
→できる:取得開始位置をスタックにpush
インクリメントと逆の手順でデクリメントし、スタックにpush
手順2を繰り返す
→できない:抜ける

手順3:
残存牌が0枚のとき:
→WinHand追加
残存牌が2枚のとき:
面子を構成できるなら→WinHand追加
それ以上なら抜ける

手順4:
シーケンススタックが空でないなら、手順2まで戻る

手順5:
セットスタックが空でないなら、手順1まで戻る

各スタックをpush/popする際は、ついでに対象牌もpushする
(次位置をpushするだけの時は、NULLをプッシュする)
対象牌がpopされる際、その牌のinactiveフラッグをfalseにする
*/

vector<WinHand>* TileSystem::GetCandidatesInner(
	const vector<Tile*>& sorted,
	const vector<Tile*>& head,
	const vector<vector<Tile*> >& subs)
{
	// deleteが必要
	vector<WinHand> *rets = new vector<WinHand>;

	// 作業スタック
	stack<int> setStack;
	stack<int> seqStack;

	// 作業ベクタ(スタックとして使うが、要素走査が必要なのでvectorを用いる)
	vector<vector<Tile*>*> workVector;

	setStack.push(-1);
	workVector.push_back(NULL);

	// 手順の実装

	// 手順1:
	//	セットスタックをpop、インクリメント
	//	その位置から、セットが取得できるかチェック
	//		→できる:取得開始位置を2回スタックにpush
	//			手順1を繰り返す
	//		 →できない:シーケンススタックに-1をプッシュ、抜ける
	//
	while (!setStack.empty())
	{
		int val = setStack.top() + 1;
		setStack.pop();

		// ワークスタックをpop
		assert(!workVector.empty());
		FreeStackItem(workVector.back());
		workVector.pop_back();

		vector<Tile*> *sets = GetSets(sorted, val);
		if (sets != NULL)
		{
			setStack.push(val);
			workVector.push_back(sets);
			setStack.push(val);
			workVector.push_back(NULL);

			continue; // 頭に戻る
		}

		// 取得不可
		seqStack.push(-1);
		workVector.push_back(NULL);
		// 手順2:
		//	シーケンススタックをpop
		//		(-1の場合は)インクリメント
		//		(0以上の場合は)シーケンス読み出し位置が
		//			別種の牌を選択するまでインクリメント
		//	その位置から、シーケンスが取得できるかチェック
		//		→できる:取得開始位置をスタックにpush
		//			インクリメントと逆の手順でデクリメントし、スタックにpush
		//			手順2を繰り返す
		//		→できない:抜ける
		//

		while (!seqStack.empty())
		{
			int val = seqStack.top();
			seqStack.pop();
			// ワークスタックをpop
			assert(!workVector.empty());
			FreeStackItem(workVector.back());
			workVector.pop_back();
			if (val == -1)
			{
				val++;
			}
			else
			{
				int nval = val;
				do
				{
					nval++;
				}
				while (nval < sorted.size() &&
					sorted.at(val)->id == sorted.at(nval)-> id);

				val = nval;
			}

			if (val < sorted.size())
			{
				vector<Tile*> *seqs = GetSequences(sorted, val);
				if (seqs != NULL)
				{
					seqStack.push(val);
					workVector.push_back(seqs);
					int pval = val + 1;
					do
					{
						pval--;
					}
					while (pval > -1 &&
						sorted.at(pval)->id == sorted.at(val + 1)->id);

					seqStack.push(pval);
					workVector.push_back(NULL);
					continue;
				}
			}



			// 手順3:
			//  残存牌が0枚のとき:
			//		→WinHand追加
			//	残存牌が2枚のとき:
			//		面子を構成できるなら→WinHand追加
			//	それ以上なら抜ける
			//	

			switch (GetActivatesCount(sorted))
			{
			case 0: // 0枚残存
				// 必ず雀頭待ち
				{
					assert(head.size() == 1);
					WinHand c;
					c.Waiting = 
						TileFactory::Create(
						head.at(0)->GetType(), head.at(0)->GetValue());

					vector<vector<Tile*> > vt;
					vector<Tile*> headtmp;
					headtmp.push_back(head.at(0));
					headtmp.push_back(c.Waiting);
					vt.push_back(headtmp);

					for (vector<vector<Tile*> >::const_iterator sit = subs.begin();
						sit != subs.end();
						++sit)
						vt.push_back(*sit);

					for (vector<vector<Tile*>*>::const_iterator vit =  workVector.begin();
						vit != workVector.end();
						++vit)
						vt.push_back(**vit);

					c.Tiles = System::CloneVecVec<Tile*>(vt);
					//c.Tiles = vt;
					rets->push_back(c);

#ifdef ___TILESYSTEM_TRACE_PRINT_ENABLED
					cout << "tiles:" << endl; 
					for (vector<vector<Tile*> >::const_iterator vvi = c.Tiles.begin();
						vvi != c.Tiles.end();
						++vvi)
					{
						for (vector<Tile*>::const_iterator vi = vvi->begin();
							vi != vvi->end();
							++vi)
							cout << (*vi)->ToString();
						cout << " ";
					}
					cout << "pushback:" << c.Waiting->ToString() << endl;
#endif
				}
				break;
			case 2: // 二枚残存
				// 面子待ち
				{
					assert(head.size() == 2);
					const vector<pair<Tile*, vector<Tile*> > >* rems = GetRemainHands(sorted);
					if (rems != NULL)
					{
						for (vector<pair<Tile*, vector<Tile*> > >::const_iterator iter = rems->begin();
							iter != rems->end();
							++iter)
						{
							WinHand c;
							c.Waiting = (*iter).first;

							vector<vector<Tile*> > vt;
							vt.push_back(head);

							for (vector<vector<Tile*> >::const_iterator sit = subs.begin();
								sit != subs.end();
								++sit)
								vt.push_back(*sit);


							for (vector<vector<Tile*>*>::const_iterator vit = workVector.begin();
								vit != workVector.end();
								++vit)
								vt.push_back(**vit);

							vt.push_back((*iter).second);

							c.Tiles = System::CloneVecVec<Tile*>(vt);
							//c.Tiles = vt;
							rets->push_back(c);

#ifdef ___TILESYSTEM_TRACE_PRINT_ENABLED
							cout << "tiles:" << endl; 
							for (vector<vector<Tile*> >::const_iterator vvi = c.Tiles.begin();
								vvi != c.Tiles.end();
								++vvi)
							{
								for (vector<Tile*>::const_iterator vi = vvi->begin();
									vi != vvi->end();
									++vi)
									cout << (*vi)->ToString();
								cout << " ";
							}
							cout << "pushback:" << c.Waiting->ToString() << endl;
#endif
						}
					}
					delete(rems);
				}
				break;
			case 1:
				// 処理エラー
				throw range_error("Remaining tile count is invalid(1).");
			default:
				// 役構成不可 (switchを抜けます)

#ifdef ___TILESYSTEM_TRACE_PRINT_ENABLED
				{
					vector<vector<Tile*> > vt;
					vt.push_back(head);

					for (vector<vector<Tile*> >::const_iterator sit = subs.begin();
						sit != subs.end();
						++sit)
						vt.push_back(*sit);

					for (vector<vector<Tile*>*>::const_iterator vit =  workVector.begin();
						vit != workVector.end();
						++vit)
						vt.push_back(**vit);

					cout << "tiles:" << endl; 
					for (vector<vector<Tile*> >::const_iterator vvi = vt.begin();
						vvi != vt.end();
						++vvi)
					{
						for (vector<Tile*>::const_iterator vi = vvi->begin();
							vi != vvi->end();
							++vi)
							cout << (*vi)->ToString();
						cout << " ";
					}
					cout << "::failed" << endl;
				}
#endif
				break;
			}
			// 手順4:
			//	シーケンススタックが空でないなら、シーケンススタックをpop
			//	シーケンススタックが空でないなら、手順2まで戻る
			//

		} // seq whileの終わり

		// 手順5:
		//  セットスタックが空でないなら、セットスタックをpop
		//  セットスタックが空でないなら、手順1まで戻る
		//  

	} // set whileの終わり
	// 各スタックをpush/popする際は、ついでに対象牌もpushする
	// -1以外がpopされた場合、対象牌をpopする
	// 対象牌がpopされる際、その牌のinactiveフラッグをfalseにする

	return rets;
}

int TileSystem::GetActivatesCount(const vector<Tile*>& tiles)
{
	int activates = 0;
	for (vector<Tile*>::const_iterator iter = tiles.begin();
		iter != tiles.end();
		++iter)
	{
		if (!(*iter)->inactive)
			activates++;
	}
	return activates;
}

// スタックアイテムの解放
void TileSystem::FreeStackItem(vector<Tile*>* item)
{
	if (item != NULL)
	{
		for (vector<Tile*>::iterator iter = item->begin();
			iter != item->end();
			++iter)
		{
			(*iter)->inactive = false;
		}
	}
	delete(item);
	item = NULL; // 二重解放安全
}

// 牌のセット(刻子)を取得します。
// ABB'B"B~C と並んでいる場合、BB'B"の刻子ではなく、
// B'B"B~の刻子を取得します。(要するに、右詰めで取得します
vector<Tile*>* TileSystem::GetSets(
	const vector<Tile*>& sorted,
	int& pos)
{
	vector<Tile*>* ret = new vector<Tile*>();
	for (int i = pos; i < sorted.size() - 2; ++i)
	{
		if (sorted.at(i)->inactive)
			// すでに取得された牌
			continue;

		int cid = sorted.at(i)->id;
		if (cid == sorted.at(i + 1)->id &&
			cid == sorted.at(i + 2)->id)
		{
			// 刻子構成可能
			if (i < sorted.size() - 3 &&
				cid == sorted.at(i + 3)->id)
			{
				assert(!sorted.at(i + 1)->inactive);
				assert(!sorted.at(i + 2)->inactive);
				assert(!sorted.at(i + 3)->inactive);
				sorted.at(i + 1)->inactive = true;
				sorted.at(i + 2)->inactive = true;
				sorted.at(i + 3)->inactive = true;
				// 槓子にもなれるので、右側を取る
				ret->push_back(sorted.at(i + 1));
				ret->push_back(sorted.at(i + 2));
				ret->push_back(sorted.at(i + 3));
				pos = i + 1;
				return ret;
			}
			else
			{
				// 槓子にはなれない
				assert(!sorted.at(i)->inactive);
				assert(!sorted.at(i + 1)->inactive);
				assert(!sorted.at(i + 2)->inactive);
				sorted.at(i)->inactive = true;
				sorted.at(i + 1)->inactive = true;
				sorted.at(i + 2)->inactive = true;
				ret->push_back(sorted.at(i));
				ret->push_back(sorted.at(i + 1));
				ret->push_back(sorted.at(i + 2));
				pos = i;
				return ret;
			}
		}
	}
	delete(ret);
	return NULL;
}

// 牌のシーケンス(順子)を取得します。
vector<Tile*>* TileSystem::GetSequences(
	const vector<Tile*>& sorted,
	int& pos)
{
	vector<Tile*>* ret = new vector<Tile*>();
	for (int i = pos; i < sorted.size() - 2; ++i)
	{
		// inactiveならすぐcontinue
		if (sorted.at(i)->inactive)
			continue;

		Tile* t = sorted.at(i);
		Tile::TileType tt = t->GetType();
		int tv = t->GetValue();

		if (tt == Tile::Honors) // 字牌は順子になりません！
			continue;

		int n = i;
		do
		{
			n++;
			// 走査し切っていない状態で、
			// inactiveフラッグが立っているか
			// 一牌目候補と同じ値ならインクリメントを続ける
		}
		while(n < sorted.size() - 1 &&
			(sorted.at(n)->inactive ||
			sorted.at(n)->GetValue() == tv));

		if (n == sorted.size() - 1) // 残牌数が足りない
			break;

		if (sorted.at(n)->GetType() != tt ||
			sorted.at(n)->GetValue() != tv + 1) // 非成立
			continue;

		// 取っておく
		int n2 = n;

		do
		{
			n2++;
		}
		while(n2 < sorted.size() &&
			(sorted.at(n2)->inactive ||
			sorted.at(n2)->GetValue() == tv + 1));

		if (n2 == sorted.size()) // 残牌数が足りない
			break;

		if (sorted.at(n2)->GetType() != tt ||
			sorted.at(n2)->GetValue() != tv + 2) // 非成立
			continue;

		// 成立しました
		pos = i;

		assert(!sorted.at(i)->inactive);
		assert(!sorted.at(n)->inactive);
		assert(!sorted.at(n2)->inactive);
		sorted.at(i)->inactive = true;
		sorted.at(n)->inactive = true;
		sorted.at(n2)->inactive = true;
		ret->push_back(sorted.at(i));
		ret->push_back(sorted.at(n));
		ret->push_back(sorted.at(n2));
		return ret;
	}
	delete(ret);
	return NULL;
}

// 面子を構成可能かどうか判定します。
vector<pair<Tile*, vector<Tile*> > >* TileSystem::GetRemainHands(const vector<Tile*>& sorted)
{
	// 残留牌が2枚であることを確認
	assert(GetActivatesCount(sorted) == 2);

	int i = 0;

	while (i < sorted.size() - 1 && sorted.at(i)->inactive)
		i++;

	if (i == sorted.size() - 1)
		return NULL;

	int i2 = i + 1;

	while (i2 < sorted.size() && sorted.at(i2)->inactive)
		i2++;

	if (i2 == sorted.size())
		return NULL;

	Tile::TileType ttype = sorted.at(i)->GetType();

	// 同じ種類であることを確認しないと始まらない
	if (ttype != sorted.at(i2)->GetType())
		return NULL;

	int vi = sorted.at(i)->GetValue();
	int vi2 = sorted.at(i2)->GetValue();
	// 同じ値であれば、刻子を構成可能(シャンポン待ち)
	if (vi == vi2)
	{
		vector<pair<Tile*, vector<Tile*> > >* ret = new vector<pair<Tile*, vector<Tile*> > >;

		vector<Tile*> set;
		Tile* tile = TileFactory::Create(ttype, vi);

		set.push_back(sorted.at(i));
		set.push_back(sorted.at(i2));
		set.push_back(tile);

		ret->push_back(pair<Tile*, vector<Tile*> >(tile, set));
		return ret;
	}

	// 字牌は刻子以外構成不可
	// 宇宙麻雀ならそんなこともないけど。ｗ
	if (ttype == Tile::Honors)
		return NULL;

	// 必ず vi < vi2 である
	assert(vi < vi2);

	if (vi + 1 == vi2)
	{
		vector<pair<Tile*, vector<Tile*> > >* ret = new vector<pair<Tile*, vector<Tile*> > >;

		// 両面待ちが構成可能 (かもしれない)
		if (vi > 1)
		{
			vector<Tile*> set;
			Tile* tile = TileFactory::Create(ttype, vi - 1);

			set.push_back(tile);
			set.push_back(sorted.at(i));
			set.push_back(sorted.at(i2));


			ret->push_back(pair<Tile*, vector<Tile*> >(tile, set));
		}

		if(vi2 < 9)
		{
			vector<Tile*> set;
			Tile* tile = TileFactory::Create(ttype, vi2 + 1);

			set.push_back(sorted.at(i));
			set.push_back(sorted.at(i2));
			set.push_back(tile);

			ret->push_back(pair<Tile*, vector<Tile*> >(tile, set));
		}
		return ret;
	}
	else if(vi + 2 == vi2)
	{
		// カンチャン待ちが構成可能
		vector<pair<Tile*, vector<Tile*> > >* ret = new vector<pair<Tile*, vector<Tile*> > >;
		vector<Tile*> set;

		Tile* tile = TileFactory::Create(ttype, vi + 1);

		set.push_back(sorted.at(i));
		set.push_back(tile);
		set.push_back(sorted.at(i2));

		return ret;
	}
	else
	{
		return NULL;
	}
}

