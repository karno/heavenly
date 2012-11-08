#include <string>
#include <vector>

#include "ThreeColorTriples.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ThreeColorTriples::Check(const WinHand& hand, const Player& player)
{
	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	// �ͤθ���
	int vcan[2] = {0};
	int vc[2] = {0};

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ��Ƭ�����Ф�
		if ((*iter).size() < 3)
			continue;

		// ��ҤǤ���
		if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue())
			continue;

		// ���פ��оݤǤϤʤ�
		if ((*iter).at(0)->GetType() == Tile::Honors)
			continue;

		if (vc[0] == 0)
		{
			// ����͸���1������¸
			vcan[0] = (*iter).at(0)->GetValue();
			vc[0]++;
		}
		else
		{
			if ((*iter).at(0)->GetValue() == vcan[0])
			{
				// ����͸���1���ܤȹ���
				vc[0]++;
			}
			else
			{
				if (vc[1] == 0)
				{
					// ����͸���2������¸
					vcan[1] = (*iter).at(0)->GetValue();
					vc[1]++;
				}
				else
				{
					if ((*iter).at(0)->GetValue() == vcan[1])
					{
						// ����͸���2���ܤȹ���
						vc[1]++;
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
	return vc[0] == 3 || vc[1] == 3;
}

int ThreeColorTriples::GetRank(bool concealing)
{
	// ����������ʤ�
	return 2;
}

string ThreeColorTriples::GetName()
{
	return "����Ʊ��";
}
