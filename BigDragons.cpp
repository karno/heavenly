#include <string>
#include <vector>

#include "BigDragons.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool BigDragons::Check(const WinHand& hand, const Player& player)
{
	bool dragons[3] = { false };
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).size() >= 3 && (*iter).at(0)->GetType() == Tile::Honors)
		{
			switch ((Tile::HonorValues)(*iter).at(0)->GetValue())
			{
			case Tile::White:
				dragons[0] = true;
				break;
			case Tile::Green:
				dragons[1] = true;
				break;
			case Tile::Red:
				dragons[2] = true;
				break;
			}
		}
	}
	return dragons[0] && dragons[1] && dragons[2];
}

int BigDragons::GetRank(bool concealing)
{
	return 13;
}

string BigDragons::GetName()
{
	return "Âç»°¸µ";
}


