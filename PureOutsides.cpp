#include <string>
#include <vector>

#include "PureOutsides.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool PureOutsides::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ���פ����ä��饢����
		if ((*iter).at(0)->GetType() == Tile::Honors)
			return false;

		// 1���ܤ��䥪���奦�פǤ��뤫�����å�

		if ((*iter).at(0)->IsYaochu())
			continue; // checked

		if ((*iter).size() == 3)
		{
			// ��Ҥ����
			// 3���ܤ�9�Ǥ��뤫�����å�(789�ν�Ҥ�Ť�������)
			if ((*iter).at(2)->GetValue() == 9)
				continue;
		}

		// �����������Ƥ��ʤ�
		return false;
	}
	return true;
}

int PureOutsides::GetRank(bool concealing)
{
	return concealing ? 3 : 2;
}

string PureOutsides::GetName()
{
	return "�����ӥ䥪��";
}


