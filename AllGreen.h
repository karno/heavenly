#ifndef __C_CRITERIA_ALLGREEN__
#define __C_CRITERIA_ALLGREEN__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// �а쿧
class AllGreen : public Criteria
{
	public:

		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


