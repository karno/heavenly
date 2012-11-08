#include "Player.h"
#include "HeavenlyHand.h"

// е╥об
bool HeavenlyHand::Check(const WinHand& hand, const Player& player)
{
	return player.IsParent();
}

int HeavenlyHand::GetRank(bool concealing)
{
	return 13;
}

string HeavenlyHand::GetName()
{
	return "е╥об";
}

