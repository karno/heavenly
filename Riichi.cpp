#include "WinHand.h"
#include "Player.h"
#include "Riichi.h"

bool Riichi::Check(const WinHand& hand,  const Player& player)
{
	// リーチされた場合のみ呼ばれるので
	// 無条件にreturn true
	return true;
}

int Riichi::GetRank(bool concealing)
{
	return 1;
}

string Riichi::GetName()
{
	return "立直";
}

