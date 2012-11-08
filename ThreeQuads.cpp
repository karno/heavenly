#include <string>
#include <vector>

#include "ThreeQuads.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// 三槓子
bool ThreeQuads::Check(const WinHand& hand, const Player& player)
{
	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 雀頭以外は4牌の組しか認めない
		if ((*iter).size() != 4 && (*iter).size() != 2)
			return false;
	}
	return true;
}

int ThreeQuads::GetRank(bool concealing)
{
	// 食い下がりなし
	return 2;
}

string ThreeQuads::GetName()
{
	return "三槓子";
}
