#ifndef __C_CRITERIA_CONCEALEDTHREE__
#define __C_CRITERIA_CONCEALEDTHREE__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// »°°Å¹ï
// (Three concealed triples)
class ConcealedThree : public Criteria
{
public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
