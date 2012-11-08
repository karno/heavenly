#ifndef __C_CRITERIA_DOUBLERIICHI__
#define __C_CRITERIA_DOUBLERIICHI__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ξΩľ
class DoubleRiichi : public Criteria
{
public:
	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

