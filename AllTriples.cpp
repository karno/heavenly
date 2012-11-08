#include <string>
#include <vector>

#include "AllTriples.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h"

using namespace std;

// �ȥ��ȥ�
bool AllTriples::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ��ҥ�����
		if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue())
			return false;
	}
	return true;
}

int AllTriples::GetRank(bool concealing)
{
	return 2;
}

string AllTriples::GetName()
{
	return "�С���";
}

