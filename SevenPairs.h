#ifndef __C_CRITERIA_SEVENPAIRS__
#define __C_CRITERIA_SEVENPAIRS__

#include <vector>
#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Tile.h" 

using namespace std;

// 七対子
class SevenPairs : public Criteria
{
	public:
		// 七対子の待ちを検出します。
		// 待ちが無い場合はNULLを返します。
		WinHand* CheckWait(const vector<Tile*>& tiles);

		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};


#endif


