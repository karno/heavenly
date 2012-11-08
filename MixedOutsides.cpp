#include <string>
#include <vector>

#include "MixedOutsides.h"
#include "AllTerminalsHonors.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// �������
bool MixedOutsides::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	// ��ϷƬ��ʣ�礷�ʤ�
	AllTerminalsHonors ath;
	if (ath.Check(hand, player))
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 1���ܤ� 1 9 ���פǤ��뤫�����å�
		if ((*iter).at(0)->IsYaochu())
			continue; // checked

		if ((*iter).size() == 3)
		{
			// ��Ҥ����
			// 3���ܤ�9�Ǥ��뤫�����å�(789�ν�Ҥ�Ť�������)
			if ((*iter).at(2)->GetValue() == 9)
				continue;
		}
		
		// ��ǰ�Ǥ���
		return false;
	}
	return true;
}

int MixedOutsides::GetRank(bool concealing)
{
	return concealing ? 2 : 1;
}

string MixedOutsides::GetName()
{
	return "�����ӥ䥪��";
}


