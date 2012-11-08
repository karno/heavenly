#ifndef __C_CRITERIA_FOURQUADS__
#define __C_CRITERIA_FOURQUADS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ªÕ‹ ª“
class FourQuads : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
