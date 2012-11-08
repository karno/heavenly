#ifndef __C_CRITERIA_FIRSTROUND__
#define __C_CRITERIA_FIRSTROUND__

#include <string>

#include "Player.h"
#include "WinHand.h"
#include "Criteria.h"

using namespace std;

// ÆÃ¼ìÌò¾ò·ïÎ©Ä¾
class FirstRound : public Criteria
{
public:
	bool Check(const WinHand& hand,  const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif


