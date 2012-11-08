#ifndef __C_CRITERIA_MIXEDOUTSIDES__
#define __C_CRITERIA_MIXEDOUTSIDES__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// º®Á´ÂÓ¥ä¥ª¶å
class MixedOutsides : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

