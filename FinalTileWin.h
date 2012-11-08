#ifndef __C_CRITERIA_FINALTILE__
#define __C_CRITERIA_FINALTILE__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// �����η�(�ϥ��ƥ��ĥ�)
class FinalTileTsumo : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

// ��������(�ϥ��ƥ����)
class FinalTileRon : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


