#include <string>

#include "Player.h"
#include "WinHand.h"
#include "FirstRound.h"

bool FirstRound::Check(const WinHand& hand,  const Player& player)
{
	// ��ȯ�������������Τ߸ƤФ��Τ�
	// ̵����return true
	return true;
}

int FirstRound::GetRank(bool concealing)
{
	return 1;
}

string FirstRound::GetName()
{
	return "��ȯ";
}

