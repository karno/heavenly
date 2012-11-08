#ifndef __C_CRITERIA_CONCEALEDTSUMO__
#define __C_CRITERIA_CONCEALEDTSUMO__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ÌçÁ°À¶¼«ÌÎÏÂ
class ConcealedTsumo : public Criteria
{
public:
	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

