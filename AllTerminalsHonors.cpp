#include <string>
#include <vector>

#include "AllTerminalsHonors.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool AllTerminalsHonors::Check(const WinHand& hand, const Player& player)
{
	// 清老頭との複合は、清老頭が役満であるため考えません。
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue())
		{
			// 順子はお呼びでない
			return false;
		}
		
		// ヤオ九牌でないなら戻る
		if (!(*iter).at(0)->IsYaochu())
			return false;
	}
	return true;
}

int AllTerminalsHonors::GetRank(bool concealing)
{
	return 2;
}

string AllTerminalsHonors::GetName()
{
	return "混老頭";
}

