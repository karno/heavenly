#ifndef __C_CRITERIA_THIRTEENORPHANS__
#define __C_CRITERIA_THIRTEENORPHANS__

#include <vector>
#include <string>
#include <cassert>

#include "WinHand.h"
#include "Criteria.h"
#include "Tile.h"
#include "TileFactory.h"

using namespace std;

// 国士無双
class ThirteenOrphans : public Criteria
{
	public:

		// 国士無双の待ちを検出します。
		// 待ちが無い場合はNULLを返します。
		vector<Tile*>* CheckWaits(const vector<Tile*>& tiles);

		bool Check(const WinHand& hand,  const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


