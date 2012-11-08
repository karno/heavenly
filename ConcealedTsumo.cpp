#include <string>
#include <vector>

#include "ConcealedTsumo.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ConcealedTsumo::Check(const WinHand& hand, const Player& player)
{
	return player.IsConcealing() && (player.GetState() == Player::TsumoWinning || player.GetState() == Player::RinshanTsumoWinning);
}

int ConcealedTsumo::GetRank(bool concealing)
{
	return 1;
}

string ConcealedTsumo::GetName()
{
	return "ÌçÁ°À¶¼«ÌÎÏÂ";
}


