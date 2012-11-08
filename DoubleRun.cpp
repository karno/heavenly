#include <string>
#include <vector>

#include "DoubleRun.h"
#include "DoubleRuns.h" // 二盃口判定用
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool DoubleRun::Check(const WinHand& hand, const Player& player)
{
	// 面前役
	if (!player.IsConcealing())
		return false;

	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	DoubleRuns dr;
	if (dr.Check(hand, player))
		return false; // 二盃口とは複合しない

	int pv[3] = { 0 };
	Tile::TileType pt[3] = { Tile::None };
	int cp = 0;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 字牌・雀頭・槓子・刻子を排除
		if ((*iter).at(0)->GetType() == Tile::Honors ||
			(*iter).size() == 2 || (*iter).size() == 4 ||
			(*iter).at(0)->GetValue() == (*iter).at(1)->GetValue()
			)
			continue;

		for (int i = 0; i < 3; i++)
		{
			if (pv[i] == (*iter).at(0)->GetValue() &&
				pt[i] == (*iter).at(0)->GetType())
				return true;

		}

		if (cp < 3)
		{
			// DB登録
			pv[cp] = (*iter).at(0)->GetValue();
			pt[cp] = (*iter).at(0)->GetType();
			cp++;
		}
	}
	return false;
}

int DoubleRun::GetRank(bool concealing)
{
	return 1;
}

string DoubleRun::GetName()
{
	return "一盃口";
}

