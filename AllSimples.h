#ifndef __C_CRITERIA_ALLSIMPLES__
#define __C_CRITERIA_ALLSIMPLES__

#include <vector>
#include <string>

#include "WinHand.h"
#include "Criteria.h"

using namespace std;

// ¥¿¥ó¥ä¥ª
class AllSimples : public Criteria
{
	public:
		bool Check(const WinHand& hand,  const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


