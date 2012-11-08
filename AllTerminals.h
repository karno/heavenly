#ifndef __C_CRITERIA_ALLTERMINALS__
#define __C_CRITERIA_ALLTERMINALS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// À¶Ï·Æ¬
class AllTerminals : public Criteria
{
	public:

		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


