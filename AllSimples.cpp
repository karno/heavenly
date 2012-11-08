#include "AllSimples.h"

#include "Player.h"
#include "WinHand.h"
#include "Tile.h"

bool AllSimples::Check(const WinHand& hand,  const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator it = hand.Tiles.begin();
		it != hand.Tiles.end();
		++it)
	{
		for (vector<Tile*>::const_iterator i = it->begin();
			i != it->end();
			++i)
		{
			if ((*i)->IsYaochu())
				return false;
		}
	}
	return true;
}

int AllSimples::GetRank(bool concealing)
{
	return 1;
}

string AllSimples::GetName()
{
	return "�ǥ䥪";
}

