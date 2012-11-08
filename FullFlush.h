#ifndef __C_CRITERIA_FULLFLUSH__
#define __C_CRITERIA_FULLFLUSH__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// À¶°ì¿§
class FullFlush : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
