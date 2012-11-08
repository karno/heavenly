#include <string>
#include <vector>

#include "ThreeQuads.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// ���ʻ�
bool ThreeQuads::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ��Ƭ�ʳ���4�פ��Ȥ���ǧ��ʤ�
		if ((*iter).size() != 4 && (*iter).size() != 2)
			return false;
	}
	return true;
}

int ThreeQuads::GetRank(bool concealing)
{
	// ����������ʤ�
	return 2;
}

string ThreeQuads::GetName()
{
	return "���ʻ�";
}
