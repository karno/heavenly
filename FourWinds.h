#ifndef __C_CRITERIA_FOURWINDS__
#define __C_CRITERIA_FOURWINDS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ╩м╢Ноб
class FourWinds : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

