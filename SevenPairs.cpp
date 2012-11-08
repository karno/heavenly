#include <vector>
#include <cassert>
#include <iostream>

#include "Tile.h"
#include "WinHand.h"
#include "TileFactory.h"
#include "SevenPairs.h"


// 七対子待ち判定
// 必ず単騎待ちなので、TileへのポインタかNULLを返す

WinHand* SevenPairs::CheckWait(const vector<Tile*>& tiles)
{
	bool odd = true;
	bool identifiedWait = false;
	Tile* waitCandidate = NULL;
	Tile* curTile = NULL;

	WinHand* wh = new WinHand();
	// 13牌で判定
	assert(tiles.size() == 13);

	for (vector<Tile*>::const_iterator itr = tiles.begin();
		itr != tiles.end();
		++itr)
	{
		if (odd)
		{
			//cout << "odd:" << (*itr)->ToString() << endl;
			// odd
			if (curTile != NULL)
			{
				// error
				// 槓子/刻子が存在する場合は七対子になり得ない
				if (curTile->id == (*itr)->id)
				{
					if (waitCandidate != NULL)
					{
						// すでに取得した待ち牌インスタンスの削除
						TileFactory::Delete(waitCandidate);
					}
					delete(wh);
					//cout << "failed(0)" << endl;
					return NULL;
				}
			}
			curTile = (*itr);
		}
		else
		{
			//cout << "even:" << (*itr)->ToString() << endl;

			// even
			// 
			if (curTile->id != (*itr)->id)
			{
				if (waitCandidate != NULL)
				{
					// 対子じゃない候補がもう一つ来た

					// すでに取得した待ち牌インスタンスの削除
					TileFactory::Delete(waitCandidate);
					delete(wh);
					//cout << "failed(1)" << endl;
					return NULL;
				}
				else
				{
					// 待ち牌はまだ確定していない
					// 現在curTileが指している牌と同種の牌が待ち牌
					waitCandidate = TileFactory::Create(curTile->GetType(), curTile->GetValue());
					
					vector<Tile*> pushvec;
					pushvec.push_back(curTile);
					pushvec.push_back(waitCandidate);
					wh->Tiles.push_back(pushvec);

					// もう一度even処理を通す
					curTile = (*itr);
					continue;
				}
			}
			else
			{
				// 対子ですok
				vector<Tile*> pushvec;
				pushvec.push_back(curTile);
				pushvec.push_back(*itr);
				wh->Tiles.push_back(pushvec);
			}
		}
		odd = !odd;
	}
	// 13牌なので、最後はoddで終わる
	if (waitCandidate == NULL)
	{
		// 最後の選択が待ち牌
		waitCandidate = TileFactory::Create(curTile->GetType(), curTile->GetValue());
		vector<Tile*> pushvec;
		pushvec.push_back(curTile);
		pushvec.push_back(waitCandidate);
		wh->Tiles.push_back(pushvec);
	}
	wh->Waiting = waitCandidate;
	return wh;
}

bool SevenPairs::Check(const WinHand& hand, const Player& player)
{
	// 七対子のときのみhand x 7となる
	return hand.Tiles.size() == 7;
}

int SevenPairs::GetRank(bool concealing)
{
	return 1;
}

string SevenPairs::GetName()
{
	return "七対子";
}

