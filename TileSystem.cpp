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

// ���̵��Ƚ����
#include "ThirteenOrphans.h"

// ���л�Ƚ����
#include "SevenPairs.h"

//#define ___TILESYSTEM_TRACE_PRINT_ENABLED

using namespace std;

vector<WinHand>* TileSystem::GetWinHandCandidates(
	const list<Tile*>& tile, const vector<vector<Tile*> >& subs)
{
	// ������ä��פΥ����������
	// 13���Ƚ��(4�̻� + 1��)
	if (tile.size() + subs.size() * 3 != 13)
		throw invalid_argument("argument must have 13 tiles(if you have quadraple, it count as 3 tiles.");

	// ����
	vector<Tile*> cache(tile.begin(), tile.end());
	return GetWinHandCandidates(cache, subs);
}

vector<WinHand>* TileSystem::GetWinHandCandidates(
	vector<Tile*>& cache, const vector<vector<Tile*> >& subs)
{
	if (cache.size() + subs.size() * 3 != 13)
		throw invalid_argument("argument must have 13 tiles(if you have quadraple, it count as 3 tiles.");

	sort(cache.begin(), cache.end(), Tile::IdSort);

	// delete��ɬ��
	vector<WinHand> *rets = new vector<WinHand>;

	// �Ĥ��Ƥ��ʤ��ʤ���̵�Фβ�ǽ���⤢�ꡣ
	if (cache.size() == 13)
	{
		// ���̵��Ƚ��
		ThirteenOrphans tho;
		vector<Tile*>* thw = tho.CheckWaits(cache);
		if (thw != NULL)
		{
			// ���̵��İ��
			// (¾����Ȥ�ʣ�礷�褦���ʤ�)
			for (vector<Tile*>::const_iterator wi = thw->begin();
				wi != thw->end();
				++wi)
			{
				WinHand temp;
				temp.Tiles.push_back(cache);
				temp.Waiting = (*wi);
				rets->push_back(temp);
			}
			// ���̵�Ф����(����)
			return rets;
		}

		// ���л�Ƚ��
		SevenPairs sp;
		WinHand* wht = sp.CheckWait(cache);
		if (wht != NULL)
		{
			WinHand temp;
			temp.Tiles = wht->Tiles;
			temp.Waiting = wht->Waiting;
			rets->push_back(temp);
			delete(wht);
			// �̤�candidate��̵�����Ȥ�̵���Τ�return�Ϥ��ʤ�
		}
	}

	vector<Tile*> heads;

	// ��Ƭ��¸�ߤ����ﲼ��İ�ץ����å�
	for (int i = 0; i < cache.size() - 1; i++)
	{
		// �ե饰�õ�
		for (int c = 0; c < cache.size(); c++)
			cache.at(c)->inactive = false;

		// ��Ƭ��������
		Tile* curhead = cache.at(i);

		// Ʊ����פϰ�Ĥ���̵���Τǡ���Ƭ�����Բ�
		if (cache.at(i + 1)->id != curhead->id) continue;

		// ���פʤΤǥե饰��Ω�Ƥ�
		curhead->inactive = true;
		cache.at(i + 1)->inactive = true;

		// ��Ƭ����
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

		// ���Ⱥ��
		heads.pop_back();
		heads.pop_back();

		// Ω�Ƥ��ե饰���ޤ롪
		curhead->inactive = false;
		cache.at(i + 1)->inactive = false;

		while ((i + 1) < cache.size() &&
			cache.at(i + 1)->id == curhead->id)
		{
			// Ʊ���פ��ɤ����Ф�
			i++;
		}
	}
	// ��Ƭ�Ԥ��ξ��֤�İ�ץ����å�
	for (int i = 0; i < cache.size(); i++)
	{
		// �ե饰�õ�
		for (int c = 0; c < cache.size(); c++)
			cache.at(c)->inactive = false;

		// ��Ƭ��������
		Tile* curhead = cache.at(i);

		// ���פʤΤǥե饰��Ω�Ƥ�
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

		// ���Ⱥ��
		heads.pop_back();

		// Ω�Ƥ��ե饰���ޤ롪
		curhead->inactive = false;

		// ������ޤ��ɤ�Ǥ���(for�롼�פǰ�Ĳû������Τ�)
		while ((i + 1) < cache.size() &&
			cache.at(i + 1)->id == curhead->id)
		{
			// Ʊ���פ��ɤ����Ф�
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
���٤Ƥ�Candidate��������롣
(�����夲�����ȡ��Хå��ȥ�å���)

�ʲ��μ��˽����С���λ������ʣ���뤳�Ȥʤ����Ǥ���Ϥ���������

���1:
���åȥ����å���pop�����󥯥����
���ΰ��֤��顢���åȤ������Ǥ��뤫�����å�
���Ǥ���:�������ϰ��֤򥹥��å���2��push
���1�򷫤��֤�
���Ǥ��ʤ�:�������󥹥����å���-1��ץå��塢ȴ����


���2:
�������󥹥����å���pop
(-1�ξ���)���󥯥����
(0�ʾ�ξ���)���������ɤ߽Ф����֤�
�̼���פ����򤹤�ޤǥ��󥯥����
���ΰ��֤��顢�������󥹤������Ǥ��뤫�����å�
���Ǥ���:�������ϰ��֤򥹥��å���push
���󥯥���Ȥȵդμ��ǥǥ�����Ȥ��������å���push
���2�򷫤��֤�
���Ǥ��ʤ�:ȴ����

���3:
��¸�פ�0��ΤȤ�:
��WinHand�ɲ�
��¸�פ�2��ΤȤ�:
�̻Ҥ����Ǥ���ʤ颪WinHand�ɲ�
����ʾ�ʤ�ȴ����

���4:
�������󥹥����å������Ǥʤ��ʤ顢���2�ޤ����

���5:
���åȥ����å������Ǥʤ��ʤ顢���1�ޤ����

�ƥ����å���push/pop����ݤϡ��Ĥ��Ǥ��о��פ�push����
(�����֤�push��������λ��ϡ�NULL��ץå��夹��)
�о��פ�pop�����ݡ������פ�inactive�ե�å���false�ˤ���
*/

vector<WinHand>* TileSystem::GetCandidatesInner(
	const vector<Tile*>& sorted,
	const vector<Tile*>& head,
	const vector<vector<Tile*> >& subs)
{
	// delete��ɬ��
	vector<WinHand> *rets = new vector<WinHand>;

	// ��ȥ����å�
	stack<int> setStack;
	stack<int> seqStack;

	// ��ȥ٥���(�����å��Ȥ��ƻȤ���������������ɬ�פʤΤ�vector���Ѥ���)
	vector<vector<Tile*>*> workVector;

	setStack.push(-1);
	workVector.push_back(NULL);

	// ���μ���

	// ���1:
	//	���åȥ����å���pop�����󥯥����
	//	���ΰ��֤��顢���åȤ������Ǥ��뤫�����å�
	//		���Ǥ���:�������ϰ��֤�2�󥹥��å���push
	//			���1�򷫤��֤�
	//		 ���Ǥ��ʤ�:�������󥹥����å���-1��ץå��塢ȴ����
	//
	while (!setStack.empty())
	{
		int val = setStack.top() + 1;
		setStack.pop();

		// ��������å���pop
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

			continue; // Ƭ�����
		}

		// �����Բ�
		seqStack.push(-1);
		workVector.push_back(NULL);
		// ���2:
		//	�������󥹥����å���pop
		//		(-1�ξ���)���󥯥����
		//		(0�ʾ�ξ���)���������ɤ߽Ф����֤�
		//			�̼���פ����򤹤�ޤǥ��󥯥����
		//	���ΰ��֤��顢�������󥹤������Ǥ��뤫�����å�
		//		���Ǥ���:�������ϰ��֤򥹥��å���push
		//			���󥯥���Ȥȵդμ��ǥǥ�����Ȥ��������å���push
		//			���2�򷫤��֤�
		//		���Ǥ��ʤ�:ȴ����
		//

		while (!seqStack.empty())
		{
			int val = seqStack.top();
			seqStack.pop();
			// ��������å���pop
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



			// ���3:
			//  ��¸�פ�0��ΤȤ�:
			//		��WinHand�ɲ�
			//	��¸�פ�2��ΤȤ�:
			//		�̻Ҥ����Ǥ���ʤ颪WinHand�ɲ�
			//	����ʾ�ʤ�ȴ����
			//	

			switch (GetActivatesCount(sorted))
			{
			case 0: // 0���¸
				// ɬ����Ƭ�Ԥ�
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
			case 2: // �����¸
				// �̻��Ԥ�
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
				// �������顼
				throw range_error("Remaining tile count is invalid(1).");
			default:
				// �����Բ� (switch��ȴ���ޤ�)

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
			// ���4:
			//	�������󥹥����å������Ǥʤ��ʤ顢�������󥹥����å���pop
			//	�������󥹥����å������Ǥʤ��ʤ顢���2�ޤ����
			//

		} // seq while�ν����

		// ���5:
		//  ���åȥ����å������Ǥʤ��ʤ顢���åȥ����å���pop
		//  ���åȥ����å������Ǥʤ��ʤ顢���1�ޤ����
		//  

	} // set while�ν����
	// �ƥ����å���push/pop����ݤϡ��Ĥ��Ǥ��о��פ�push����
	// -1�ʳ���pop���줿��硢�о��פ�pop����
	// �о��פ�pop�����ݡ������פ�inactive�ե�å���false�ˤ���

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

// �����å������ƥ�β���
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
	item = NULL; // ��Ų�������
}

// �פΥ��å�(���)��������ޤ���
// ABB'B"B~C ���¤�Ǥ����硢BB'B"�ι�ҤǤϤʤ���
// B'B"B~�ι�Ҥ�������ޤ���(�פ���ˡ����ͤ�Ǽ������ޤ�
vector<Tile*>* TileSystem::GetSets(
	const vector<Tile*>& sorted,
	int& pos)
{
	vector<Tile*>* ret = new vector<Tile*>();
	for (int i = pos; i < sorted.size() - 2; ++i)
	{
		if (sorted.at(i)->inactive)
			// ���Ǥ˼������줿��
			continue;

		int cid = sorted.at(i)->id;
		if (cid == sorted.at(i + 1)->id &&
			cid == sorted.at(i + 2)->id)
		{
			// ��ҹ�����ǽ
			if (i < sorted.size() - 3 &&
				cid == sorted.at(i + 3)->id)
			{
				assert(!sorted.at(i + 1)->inactive);
				assert(!sorted.at(i + 2)->inactive);
				assert(!sorted.at(i + 3)->inactive);
				sorted.at(i + 1)->inactive = true;
				sorted.at(i + 2)->inactive = true;
				sorted.at(i + 3)->inactive = true;
				// �ʻҤˤ�ʤ��Τǡ���¦����
				ret->push_back(sorted.at(i + 1));
				ret->push_back(sorted.at(i + 2));
				ret->push_back(sorted.at(i + 3));
				pos = i + 1;
				return ret;
			}
			else
			{
				// �ʻҤˤϤʤ�ʤ�
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

// �פΥ�������(���)��������ޤ���
vector<Tile*>* TileSystem::GetSequences(
	const vector<Tile*>& sorted,
	int& pos)
{
	vector<Tile*>* ret = new vector<Tile*>();
	for (int i = pos; i < sorted.size() - 2; ++i)
	{
		// inactive�ʤ餹��continue
		if (sorted.at(i)->inactive)
			continue;

		Tile* t = sorted.at(i);
		Tile::TileType tt = t->GetType();
		int tv = t->GetValue();

		if (tt == Tile::Honors) // ���פϽ�Ҥˤʤ�ޤ���
			continue;

		int n = i;
		do
		{
			n++;
			// �������ڤäƤ��ʤ����֤ǡ�
			// inactive�ե�å���Ω�äƤ��뤫
			// �����ܸ����Ʊ���ͤʤ饤�󥯥���Ȥ�³����
		}
		while(n < sorted.size() - 1 &&
			(sorted.at(n)->inactive ||
			sorted.at(n)->GetValue() == tv));

		if (n == sorted.size() - 1) // ���׿���­��ʤ�
			break;

		if (sorted.at(n)->GetType() != tt ||
			sorted.at(n)->GetValue() != tv + 1) // ����Ω
			continue;

		// ��äƤ���
		int n2 = n;

		do
		{
			n2++;
		}
		while(n2 < sorted.size() &&
			(sorted.at(n2)->inactive ||
			sorted.at(n2)->GetValue() == tv + 1));

		if (n2 == sorted.size()) // ���׿���­��ʤ�
			break;

		if (sorted.at(n2)->GetType() != tt ||
			sorted.at(n2)->GetValue() != tv + 2) // ����Ω
			continue;

		// ��Ω���ޤ���
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

// �̻Ҥ�����ǽ���ɤ���Ƚ�ꤷ�ޤ���
vector<pair<Tile*, vector<Tile*> > >* TileSystem::GetRemainHands(const vector<Tile*>& sorted)
{
	// ��α�פ�2��Ǥ��뤳�Ȥ��ǧ
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

	// Ʊ������Ǥ��뤳�Ȥ��ǧ���ʤ��ȻϤޤ�ʤ�
	if (ttype != sorted.at(i2)->GetType())
		return NULL;

	int vi = sorted.at(i)->GetValue();
	int vi2 = sorted.at(i2)->GetValue();
	// Ʊ���ͤǤ���С���Ҥ�����ǽ(�����ݥ��Ԥ�)
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

	// ���פϹ�Ұʳ������Բ�
	// ��������ʤ餽��ʤ��Ȥ�ʤ����ɡ���
	if (ttype == Tile::Honors)
		return NULL;

	// ɬ�� vi < vi2 �Ǥ���
	assert(vi < vi2);

	if (vi + 1 == vi2)
	{
		vector<pair<Tile*, vector<Tile*> > >* ret = new vector<pair<Tile*, vector<Tile*> > >;

		// ξ���Ԥ���������ǽ (���⤷��ʤ�)
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
		// ���������Ԥ���������ǽ
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

