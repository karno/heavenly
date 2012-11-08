#include <string>
#include <vector>

#include "FourQuads.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool FourQuads::Check(const WinHand& hand, const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).size() != 4)
			return false;
	}

	return true;
}

int FourQuads::GetRank(bool concealing)
{
	return 13;
}

string FourQuads::GetName()
{
	return "ªÕ‹ ª“";
}
