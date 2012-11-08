#include <string>

#include "Player.h"
#include "WinHand.h"
#include "FirstRound.h"

bool FirstRound::Check(const WinHand& hand,  const Player& player)
{
	// 一発条件を満たす場合のみ呼ばれるので
	// 無条件にreturn true
	return true;
}

int FirstRound::GetRank(bool concealing)
{
	return 1;
}

string FirstRound::GetName()
{
	return "一発";
}

