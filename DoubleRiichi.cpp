#include <string>
#include <vector>

#include "DoubleRiichi.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// �ü���ξΩľ
bool DoubleRiichi::Check(const WinHand& hand, const Player& player)
{
	return true;
}

int DoubleRiichi::GetRank(bool concealing)
{
	return 2;
}

string DoubleRiichi::GetName()
{
	return "ξΩľ";
}

