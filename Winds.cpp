#include <string>
#include <vector>

#include "Winds.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool PrevailingWinds::Check(const WinHand& hand, const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).size() >= 3 &&
			(*iter).at(0)->GetType() == Tile::Honors &&
			(int)(*iter).at(0)->GetValue() == (int)player.GetPrevailingWind())
			return true;
	}
	return false;
}

int PrevailingWinds::GetRank(bool concealing)
{
	return 1;
}

string PrevailingWinds::GetName()
{
	return "¾ìÉ÷Ç×";
}

bool MyWinds::Check(const WinHand& hand, const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).size() >= 3 &&
			(*iter).at(0)->GetType() == Tile::Honors &&
			(int)(*iter).at(0)->GetValue() == (int)player.GetWind())
			return true;
	}
	return false;
}

int MyWinds::GetRank(bool concealing)
{
	return 1;
}

string MyWinds::GetName()
{
	return "¼«É÷Ç×";
}


