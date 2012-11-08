#include <string>
#include <vector>

#include "FullStraight.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// �쵤�̴�
bool FullStraight::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;
	
	int steps[3] = {0};

	// 123 : 001(1) 456 : 010(2) 789 : 100(4)
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ��Ƭ���ʻҤϥХ��Х�
		if ((*iter).size() == 2 || (*iter).size() == 4)
			continue;

		// ���(����)��Х��Х�
		if ((*iter).at(0)->GetValue() == (*iter).at(1)->GetValue())
			continue;

		// �ӥåȱ黻
		steps[(int)(*iter).at(0)->GetType()] |=
			((*iter).at(0)->GetValue() == 1 ? 1 : 0) |
			((*iter).at(0)->GetValue() == 4 ? 2 : 0) |
			((*iter).at(0)->GetValue() == 7 ? 4 : 0);
	}
	
	// steps�Τɤ줫��111(7)�ˤʤäƤ���Ф���
	return steps[0] == 7 || steps[1] == 7 || steps[2] == 7;
}

int FullStraight::GetRank(bool concealing)
{
	return concealing ? 2 : 1;
}

string FullStraight::GetName()
{
	return "�쵤�̴�";
}


