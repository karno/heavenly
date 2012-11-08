#ifndef __C_CRITERIA_KINGSTILE__
#define __C_CRITERIA_KINGSTILE__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// Îæ¾å³«²Ö (King's tile draw)
class KingsTile : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


