#include <string>
#include <vector>

#include "KingsTile.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool KingsTile::Check(const WinHand& hand, const Player& player)
{
	return true;
}

int KingsTile::GetRank(bool concealing)
{
	return 1;
}

string KingsTile::GetName()
{
	return "Îæ¾å³«²Ö";
}


