#include <string>
#include <vector>

#include "HalfFlush.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool HalfFlush::Check(const WinHand& hand, const Player& player)
{
	// 基本となる牌種を取得
	Tile::TileType type = Tile::None;

	// 字牌を見つけたか
	bool honorEncd = false;

	// 面子のイテレーション
	for (vector<vector<Tile*> >::const_iterator hiter = hand.Tiles.begin();
		hiter != hand.Tiles.end();
		++hiter)
	{
		// 手牌ブロックの中のイテレーション
		for (vector<Tile*>::const_iterator iter = (*hiter).begin();
			iter != (*hiter).end();
			++iter)
		{
			if ((*iter)->GetType() != type)
			{
				// 他種牌を発見
				if ((*iter)->GetType() == Tile::Honors) // 字牌発見
					honorEncd = true;
				else
					if (type == Tile::None)
					{
						type = (*iter)->GetType();
					}
					else
					{
						return false;
					}
			}
		}
	}
	// 字牌を含んでいない場合は清一色となる(もちろん複合しない)
	return honorEncd;
}

int HalfFlush::GetRank(bool concealing)
{
	return concealing ? 3 : 2;
}

string HalfFlush::GetName()
{
	return "混一色";
}

