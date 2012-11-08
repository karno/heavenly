#ifndef __C_CRITERIA_RIICHI__
#define __C_CRITERIA_RIICHI__

#include <string>

#include "WinHand.h"
#include "Player.h"
#include "Criteria.h"

using namespace std;

// ÆÃ¼ìÌò¾ò·ïÎ©Ä¾
class Riichi : public Criteria
{
	public:
		bool Check(const WinHand& hand,  const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


