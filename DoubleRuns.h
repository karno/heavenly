#ifndef __C_CRITERIA_DOUBLERUNS__
#define __C_CRITERIA_DOUBLERUNS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ÆóÇÖ¸ý
class DoubleRuns : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

