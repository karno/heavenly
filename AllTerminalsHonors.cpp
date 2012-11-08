#include <string>
#include <vector>

#include "AllTerminalsHonors.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool AllTerminalsHonors::Check(const WinHand& hand, const Player& player)
{
	// ��ϷƬ�Ȥ�ʣ��ϡ���ϷƬ�������Ǥ��뤿��ͤ��ޤ���
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue())
		{
			// ��ҤϤ��ƤӤǤʤ�
			return false;
		}
		
		// �䥪���פǤʤ��ʤ����
		if (!(*iter).at(0)->IsYaochu())
			return false;
	}
	return true;
}

int AllTerminalsHonors::GetRank(bool concealing)
{
	return 2;
}

string AllTerminalsHonors::GetName()
{
	return "��ϷƬ";
}

