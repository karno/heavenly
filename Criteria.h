#ifndef __C_CRITERIA__
#define __C_CRITERIA__

#include <vector>
#include <string>

#include "WinHand.h"
#include "GameSystem.h"
#include "Player.h"

using namespace std;

// ÃÚ§Œ»ΩƒÍ√Íæ›•Ø•È•π
class Criteria
{
	public:
		virtual bool Check(const WinHand& hand, const Player& player) = 0;

		virtual int GetRank(bool concealing) = 0;

		virtual string GetName() = 0;
};
#endif


