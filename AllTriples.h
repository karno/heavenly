#ifndef __C_CRITERIA_ALLTRIPLES__
#define __C_CRITERIA_ALLTRIPLES__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ÂÐ¡¹ÏÂ
class AllTriples : public Criteria
{
public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

