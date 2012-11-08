#ifndef __C_CRITERIA_EARTHLYHAND__
#define __C_CRITERIA_EARTHLYHAND__

#include <vector>
#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"
#include "Tile.h" 

using namespace std;

// ����
class EarthlyHand : public Criteria
{
public:
	// ���true���֤��ޤ���
	bool Check(const WinHand& hand, const Player& player);

	int GetRank(bool concealing);

	string GetName();

};
#endif

