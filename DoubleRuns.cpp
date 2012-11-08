#include <string>
#include <vector>

#include "DoubleRuns.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// ���ָ�
bool DoubleRuns::Check(const WinHand& hand, const Player& player)
{
	// ������
	if (!player.IsConcealing())
		return false;

	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	// ��Ҥγ����ͤ�Ф��Ƥ���
	int firstInitValue = -1;
	Tile::TileType firstType = Tile::None;
	int secondInitValue = -1;
	Tile::TileType secondType = Tile::None;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).size() == 2) // ��Ƭ���ɤ����Ф�
			continue;

		else if((*iter).size() != 3) // �ʻҤʤ�Ф����˥�����
			return false;

		// ��ҤǤ��뤳�Ȥ��ǧ
		if ((*iter).at(0)->GetValue() == (*iter).at(1)->GetValue())
			return false;

		if (firstInitValue == -1)
		{
			// �����
			firstInitValue = (*iter).at(0)->GetValue();
			firstType = (*iter).at(0)->GetType();
			if (firstType == Tile::Honors)
				return false; // ̵���Ȥϻפ�
		}
		else
		{
			// �����Ƚ��
			if ((*iter).at(0)->GetValue() == firstInitValue &&
				(*iter).at(0)->GetType() == firstType)
			{
				firstInitValue = 10; // ̵�����ͤ��ݻ����Ƥ���
			}
			else
			{
				if (secondInitValue == -1)
				{
					// ������
					secondInitValue = (*iter).at(0)->GetValue();
					secondType = (*iter).at(0)->GetType();
				}
				else
				{
					// ������Ƚ��
					if ((*iter).at(0)->GetValue() == secondInitValue &&
						(*iter).at(0)->GetType() == secondType)
					{
						secondInitValue = 10; // ̵�����ͤ��ݻ����Ƥ���(ͽ��)
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

int DoubleRuns::GetRank(bool concealing)
{
	return 3;
}

string DoubleRuns::GetName()
{
	return "���ָ�";
}


