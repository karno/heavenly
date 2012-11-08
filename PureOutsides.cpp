#include <string>
#include <vector>

#include "PureOutsides.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool PureOutsides::Check(const WinHand& hand, const Player& player)
{
	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 字牌があったらアウト
		if ((*iter).at(0)->GetType() == Tile::Honors)
			return false;

		// 1牌目がヤオチュウ牌であるかチェック

		if ((*iter).at(0)->IsYaochu())
			continue; // checked

		if ((*iter).size() == 3)
		{
			// 刻子か順子
			// 3牌目が9であるかチェック(789の順子を掬いあげる)
			if ((*iter).at(2)->GetValue() == 9)
				continue;
		}

		// 条件を満たしていない
		return false;
	}
	return true;
}

int PureOutsides::GetRank(bool concealing)
{
	return concealing ? 3 : 2;
}

string PureOutsides::GetName()
{
	return "清全帯ヤオ九";
}


