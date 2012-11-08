#include <string>
#include <vector>

#include "NineGates.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// 負荷が大きいので、清一色判定を先にした方が良いかも。
// もしくは、他の役満が確定した時。
bool NineGates::Check(const WinHand& hand, const Player& player)
{
	// 鳴いたらアウト
	if (!player.IsConcealing()) return false;

	int valuector[9] = {0}; // 1-9の牌の出現数を数える (value - 1でアクセス) (0で初期化)

	// 清一色でなければならないので、全て同じ種類であることを確認
	Tile::TileType type = hand.Waiting->GetType();

	// もちろん字牌では和了できない
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

			valuector[(*iter)->GetValue() - 1]++;
		}
	}

	// 出現枚数を数える
	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
		{
			// 3枚以上(3枚か4枚である必要がある)
			if (valuector[i] < 3)
				return false;
		}
		else
		{
			// 0枚でも、2枚以上でもダメ。
			if (valuector[i] == 0 || valuector[i] > 2)
				return false;
		}
	}

	// おめでとうございます、事故らないように注意してくださいね
	return true;
}

int NineGates::GetRank(bool concealing)
{
	return 13;
}

string NineGates::GetName()
{
	return "九連宝灯";
}

