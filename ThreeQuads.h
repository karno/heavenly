#ifndef __C_CRITERIA_THREEQUADS__
#define __C_CRITERIA_THREEQUADS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ª∞‹ ª“
class ThreeQuads : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
