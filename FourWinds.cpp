#include <string>
#include <vector>

#include "FourWinds.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool FourWinds::Check(const WinHand& hand, const Player& player)
{
	bool checked[4] = { false };
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).size() >= 3 && (*iter).at(0)->GetType() == Tile::Honors)
		{
			switch((Tile::HonorValues)(*iter).at(0)->GetValue())
			{
			case Tile::East:
				checked[0] = true;
				break;
			case Tile::South:
				checked[1] = true;
				break;
			case Tile::West:
				checked[2] = true;
				break;
			case Tile::North:
				checked[3] = true;
				break;
			}
		}
	}
	return checked[0] && checked[1] && checked[2] && checked[3];
}

int FourWinds::GetRank(bool concealing)
{
	return 13;
}

string FourWinds::GetName()
{
	return "»Í´îÏÂ";
}
