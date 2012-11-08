#include <vector>
#include <string>

#include "Values.h"
#include "Tile.h"
#include "WinHand.h"
#include "Criteria.h"

using namespace std;

// White *******************************************************************************************

bool ValueWhite::Check(const WinHand& hand,  const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).at(0)->GetType() == Tile::Honors &&
			(*iter).at(0)->GetValue() == Tile::White &&
			(*iter).size() == 3) // 刻子であることを要求する
			return true;
	}
	return false;
}

int ValueWhite::GetRank(bool concealing)
{
	return 1;
}

string ValueWhite::GetName()
{
	return "役牌(白)";
}

// Greeb ****************************************************************************************

bool ValueGreen::Check(const WinHand& hand,  const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).at(0)->GetType() == Tile::Honors &&
			(*iter).at(0)->GetValue() == Tile::Green &&
			(*iter).size() == 3) // 刻子であることを要求する
			return true;
	}
	return false;
}

int ValueGreen::GetRank(bool concealing)
{
	return 1;
}

string ValueGreen::GetName()
{
	return "役牌(發)";
}


// Red *******************************************************************************************

bool ValueRed::Check(const WinHand& hand,  const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).at(0)->GetType() == Tile::Honors &&
			(*iter).at(0)->GetValue() == Tile::Red &&
			(*iter).size() == 3) // 刻子であることを要求する
			return true;
	}
	return false;
}

int ValueRed::GetRank(bool concealing)
{
	return 1;
}

string ValueRed::GetName()
{
	return "役牌(中)";
}


