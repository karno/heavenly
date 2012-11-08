#ifndef __C_CRITERIA_HALFFLUSH__
#define __C_CRITERIA_HALFFLUSH__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// º®°ì¿§
class HalfFlush : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
