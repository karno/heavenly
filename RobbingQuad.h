#ifndef __C_CRITERIA_ROBBINGQUAD__
#define __C_CRITERIA_ROBBINGQUAD__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// 槍槓
// (現状では利用されません)
class RobbingQuad : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


