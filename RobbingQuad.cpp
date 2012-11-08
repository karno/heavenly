#include <string>
#include <vector>

#include "RobbingQuad.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool RobbingQuad::Check(const WinHand& hand, const Player& player)
{
	return true;
}

int RobbingQuad::GetRank(bool concealing)
{
	return 1;
}

string RobbingQuad::GetName()
{
	return "¡‰‹ ";
}

