#ifndef __C_CRITERIA_ALLTERMINALSHONORS__
#define __C_CRITERIA_ALLTERMINALSHONORS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// º®Ï·Æ¬
// (All terminals and honors
class AllTerminalsHonors : public Criteria
{
	public:

		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


