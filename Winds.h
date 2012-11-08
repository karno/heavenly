#ifndef __C_CRITERIA_WINDS__
#define __C_CRITERIA_WINDS__

#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Player.h"

using namespace std;

// ������
class PrevailingWinds : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

// ������
class MyWinds : public Criteria
{
	public:
		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


