#ifndef __C_CRITERIA_NINEGATES__
#define __C_CRITERIA_NINEGATES__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ∂Âœ¢ ı≈Ù
class NineGates : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

