#ifndef __C_CRITERIA_THREECOLORTRIPLES__
#define __C_CRITERIA_THREECOLORTRIPLES__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// »°¿§Æ±¹ï
class ThreeColorTriples : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
