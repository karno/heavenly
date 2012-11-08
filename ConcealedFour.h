#ifndef __C_CRITERIA_CONCEALEDFOUR__
#define __C_CRITERIA_CONCEALEDFOUR__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// »Í°Å¹ï (Four concealed triples)
class ConcealedFour : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

