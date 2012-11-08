#include <string>
#include <vector>

#include "ThreeColorRuns.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ThreeColorRuns::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	// ThreeColorTriples����Τۤܥ��ԡ�������������������

	// �ͤθ���
	int vcand[2] = {0};
	int vcnt[2] = {0};

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ��Ƭ�����Ф�
		if ((*iter).size() < 3)
			continue;

		// ��Ҥ������
		if ((*iter).at(0)->GetValue() == (*iter).at(1)->GetValue())
			continue;

		// ���פ��оݤǤϤʤ�
		if ((*iter).at(0)->GetType() == Tile::Honors)
			continue;

		if (vcnt[0] == 0)
		{
			// ����͸���1������¸
			vcand[0] = (*iter).at(0)->GetValue();
			vcnt[0]++;
		}
		else
		{
			if ((*iter).at(0)->GetValue() == vcand[0])
			{
				// ����͸���1���ܤȹ���
				vcnt[0]++;
			}
			else
			{
				if (vcnt[1] == 0)
				{
					// ����͸���2������¸
					vcand[1] = (*iter).at(0)->GetValue();
					vcnt[1]++;
				}
				else
				{
					if ((*iter).at(0)->GetValue() == vcand[1])
					{
						// ����͸���2���ܤȹ���
						vcnt[1]++;
					}
					else
					{
						// �ɤ���Ȥ�㤨�Ф���������
						return false;

					}
				}
			}
		}

	}
	return vcnt[0] == 3 || vcnt[1] == 3;
}

int ThreeColorRuns::GetRank(bool concealing)
{
	return concealing ? 2 : 1;
}

string ThreeColorRuns::GetName()
{
	return "����Ʊ��";
}


