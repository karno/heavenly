#include <string>
#include <vector>

#include "AllTerminals.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool AllTerminals::Check(const WinHand& hand, const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator biter = hand.Tiles.begin();
			biter != hand.Tiles.end();
			++biter)
	{
		for (vector<Tile*>::const_iterator iter = (*biter).begin();
				iter != (*biter).end();
				++iter)
		{
			// ¥ä¥ª¶åÇ×¤Ç¤Ê¤¤¤«¡¢»úÇ×¤Ê¤éÌá¤ë
			if (!(*iter)->IsYaochu() || (*iter)->GetType() == Tile::Honors)
				return false;
		}
	}
	return true;
}

int AllTerminals::GetRank(bool concealing)
{
	return 13;
}

string AllTerminals::GetName()
{
	return "À¶Ï·Æ¬";
}


