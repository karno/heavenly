#ifndef __C_CRITERIA_FINALTILE__
#define __C_CRITERIA_FINALTILE__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// 海底摸月(ハイテイツモ)
class FinalTileTsumo : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

// 河底撈魚(ハイテイロン)
class FinalTileRon : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


