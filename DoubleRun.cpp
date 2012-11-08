#include <string>
#include <vector>

#include "DoubleRun.h"
#include "DoubleRuns.h" // ���ָ�Ƚ����
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool DoubleRun::Check(const WinHand& hand, const Player& player)
{
	// ������
	if (!player.IsConcealing())
		return false;

	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	DoubleRuns dr;
	if (dr.Check(hand, player))
		return false; // ���ָ��Ȥ�ʣ�礷�ʤ�

	int pv[3] = { 0 };
	Tile::TileType pt[3] = { Tile::None };
	int cp = 0;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ���ס���Ƭ���ʻҡ���Ҥ��ӽ�
		if ((*iter).at(0)->GetType() == Tile::Honors ||
			(*iter).size() == 2 || (*iter).size() == 4 ||
			(*iter).at(0)->GetValue() == (*iter).at(1)->GetValue()
			)
			continue;

		for (int i = 0; i < 3; i++)
		{
			if (pv[i] == (*iter).at(0)->GetValue() &&
				pt[i] == (*iter).at(0)->GetType())
				return true;

		}

		if (cp < 3)
		{
			// DB��Ͽ
			pv[cp] = (*iter).at(0)->GetValue();
			pt[cp] = (*iter).at(0)->GetType();
			cp++;
		}
	}
	return false;
}

int DoubleRun::GetRank(bool concealing)
{
	return 1;
}

string DoubleRun::GetName()
{
	return "���ָ�";
}

