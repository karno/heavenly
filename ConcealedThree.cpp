#include <string>
#include <vector>

#include "ConcealedThree.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ConcealedThree::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	int ccs = 0;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ��Ƭ���ѤϤ���ޤ����
		if ((*iter).size() == 2)
			continue;

		// ��ҡ����
		if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue()) // ��Ҥ�����
			continue;

		// ��Ϫ�פǤ��뤫������å�
		if (player.IsUnconcealedSub((*iter).at(0))) // ��Ϫ����Ƥ��饫����Ȥ��ʤ�
			continue;

		ccs++;
	}
	return ccs >= 3;
}

int ConcealedThree::GetRank(bool concealing)
{
	return 2;
}

string ConcealedThree::GetName()
{
	return "���Ź�";
}


