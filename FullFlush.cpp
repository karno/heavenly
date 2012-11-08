#include <string>
#include <vector>

#include "FullFlush.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool FullFlush::Check(const WinHand& hand, const Player& player)
{
	// 清一色でなければならないので、全て同じ種類であることを確認
	Tile::TileType type = hand.Waiting->GetType();

	// 字牌が混じったら混一色となります
	if (type == Tile::Honors)
		return false;

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
			// 牌種が違う
			if ((*iter)->GetType() != type)
				return false;
		}
	}

	return true;
}

int FullFlush::GetRank(bool concealing)
{
	return concealing ? 6 : 5;
}

string FullFlush::GetName()
{
	return "清一色";
}

