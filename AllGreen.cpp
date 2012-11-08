#include <string>
#include <vector>

#include "AllGreen.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// 緑一色
// 發なし緑一色も認めます。
bool AllGreen::Check(const WinHand& hand, const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator biter = hand.Tiles.begin();
			biter != hand.Tiles.end();
			++biter)
	{
		for (vector<Tile*>::const_iterator iter = (*biter).begin();
				iter != (*biter).end();
				++iter)
		{
			switch ((*iter)->GetType())
			{

				case Tile::Bamboos:
					// 許容するのは、索子の2,3,4,6,8のみ
					// 1, 5, 7, 9はアウト
					{
						// gccに怒られるのでカッコでくくる
						int v = (*iter)->GetValue();
						if (v == 1 || v == 5 || v == 7 || v == 9)
							return false;
					}
					break;

				case Tile::Honors:
					// 字牌は發のみ可
					if ((*iter)->GetValue() != (int)Tile::Green)
						return false;
					break;

				default:
					// 緑じゃない
					return false;
			}
		}
	}
	return true;
}

int AllGreen::GetRank(bool concealing)
{
	return 13;
}

string AllGreen::GetName()
{
	return "緑一色";
}



