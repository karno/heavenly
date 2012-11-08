#ifndef __C_CRITERIA_VALUES__
#define __C_CRITERIA_VALUES__

#include <vector>
#include <string>

#include "WinHand.h"
#include "Criteria.h"

using namespace std;

// ���� �
class ValueGreen : public Criteria
{
	bool Check(const WinHand& hand,  const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

// ���� ��
class ValueRed : public Criteria
{
	bool Check(const WinHand& hand,  const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

// ���� ��
class ValueWhite : public Criteria
{
	bool Check(const WinHand& hand,  const Player& player);

	int GetRank(bool concealing);

	string GetName();

};

#endif

