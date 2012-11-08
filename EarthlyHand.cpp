#include "Player.h"
#include "EarthlyHand.h"

// ���true���֤��ޤ���
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
	return "����";
}

