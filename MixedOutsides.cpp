#include <string>
#include <vector>

#include "MixedOutsides.h"
#include "AllTerminalsHonors.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// 混チャンタ
bool MixedOutsides::Check(const WinHand& hand, const Player& player)
{
	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	// 混老頭と複合しない
	AllTerminalsHonors ath;
	if (ath.Check(hand, player))
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 1牌目が 1 9 字牌であるかチェック
		if ((*iter).at(0)->IsYaochu())
			continue; // checked

		if ((*iter).size() == 3)
		{
			// 刻子か順子
			// 3牌目が9であるかチェック(789の順子を掬いあげる)
			if ((*iter).at(2)->GetValue() == 9)
				continue;
		}
		
		// 残念でした
		return false;
	}
	return true;
}

int MixedOutsides::GetRank(bool concealing)
{
	return concealing ? 2 : 1;
}

string MixedOutsides::GetName()
{
	return "混全帯ヤオ九";
}


