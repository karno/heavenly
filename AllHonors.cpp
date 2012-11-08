#include <string>
#include <vector>

#include "AllHonors.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool AllHonors::Check(const WinHand& hand, const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator biter = hand.Tiles.begin();
			biter != hand.Tiles.end();
			++biter)
	{
		for (vector<Tile*>::const_iterator iter = (*biter).begin();
				iter != (*biter).end();
				++iter)
		{
			// 字牌のみ
			if ((*iter)->GetType() != Tile::Honors)
				return false;
		}
	}
	return true;
}

int AllHonors::GetRank(bool concealing)
{
	return 13;
}

string AllHonors::GetName()
{
	return "字一色";
}


