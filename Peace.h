#ifndef __C_CRITERIA_PEACE__
#define __C_CRITERIA_PEACE__

#include <vector>
#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Tile.h" 

using namespace std;

// ¥¿¥ó¥ä¥ª
class Peace : public Criteria
{
	bool Check(const WinHand& hand,  const Player& player);

	int GetRank(bool concealing);

	string GetName();

};


#endif
