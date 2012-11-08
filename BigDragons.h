#ifndef __C_CRITERIA_BIGDRAGONS__
#define __C_CRITERIA_BIGDRAGONS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// Âç»°¸µ
class BigDragons : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

