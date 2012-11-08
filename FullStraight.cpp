#include <string>
#include <vector>

#include "FullStraight.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// 一気通貫
bool FullStraight::Check(const WinHand& hand, const Player& player)
{
	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;
	
	int steps[3] = {0};

	// 123 : 001(1) 456 : 010(2) 789 : 100(4)
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 雀頭・槓子はバイバイ
		if ((*iter).size() == 2 || (*iter).size() == 4)
			continue;

		// 順子(字牌)もバイバイ
		if ((*iter).at(0)->GetValue() == (*iter).at(1)->GetValue())
			continue;

		// ビット演算
		steps[(int)(*iter).at(0)->GetType()] |=
			((*iter).at(0)->GetValue() == 1 ? 1 : 0) |
			((*iter).at(0)->GetValue() == 4 ? 2 : 0) |
			((*iter).at(0)->GetValue() == 7 ? 4 : 0);
	}
	
	// stepsのどれかが111(7)になっていればおｋ
	return steps[0] == 7 || steps[1] == 7 || steps[2] == 7;
}

int FullStraight::GetRank(bool concealing)
{
	return concealing ? 2 : 1;
}

string FullStraight::GetName()
{
	return "一気通貫";
}


