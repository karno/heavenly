#ifndef __C_CRITERIA_LITTLEDRAGONS__
#define __C_CRITERIA_LITTLEDRAGONS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ������
class LittleDragons : public Criteria
{
	public:

	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif
