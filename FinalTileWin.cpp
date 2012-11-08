#include <string>
#include <vector>

#include "FinalTileWin.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool FinalTileTsumo::Check(const WinHand& hand, const Player& player)
{
	return player.GetState() == Player::TsumoWinning || player.GetState() == Player::RinshanTsumoWinning;
}

int FinalTileTsumo::GetRank(bool concealing)
{
	return 1;
}

string FinalTileTsumo::GetName()
{
	return "³¤ÄìÌÎ·î";
}

bool FinalTileRon::Check(const WinHand& hand, const Player& player)
{
	return player.GetState() == Player::RonWinning;
}

int FinalTileRon::GetRank(bool concealing)
{
	return 1;
}

string FinalTileRon::GetName()
{
	return "²ÏÄìÙıµû";
}

