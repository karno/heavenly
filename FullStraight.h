#ifndef __C_CRITERIA_FULLSTRAIGHT__
#define __C_CRITERIA_FULLSTRAIGHT__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// °ìµ¤ÄÌ´Ó
class FullStraight : public Criteria
{
public:
	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
