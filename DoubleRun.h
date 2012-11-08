#ifndef __C_CRITERIA_DOUBLERUN__
#define __C_CRITERIA_DOUBLERUN__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// °ìÇÖ¸ý
class DoubleRun : public Criteria
{
public:
	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();
};

#endif
