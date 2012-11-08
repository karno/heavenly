#ifndef __C_CRITERIA_ALLHONORS__
#define __C_CRITERIA_ALLHONORS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// »ú°ì¿§
class AllHonors : public Criteria
{
	public:

		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


