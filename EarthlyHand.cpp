#include "Player.h"
#include "EarthlyHand.h"

// 常にtrueを返します。
bool EarthlyHand::Check(const WinHand& hand, const Player& player)
{
	return !player.IsParent();
}

int EarthlyHand::GetRank(bool concealing)
{
	return 13;
}

string EarthlyHand::GetName()
{
	return "地和";
}

