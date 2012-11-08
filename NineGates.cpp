#include <string>
#include <vector>

#include "NineGates.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// ��٤��礭���Τǡ����쿧Ƚ�����ˤ��������ɤ����⡣
// �⤷���ϡ�¾�����������ꤷ������
bool NineGates::Check(const WinHand& hand, const Player& player)
{
	// �Ĥ����饢����
	if (!player.IsConcealing()) return false;

	int valuector[9] = {0}; // 1-9���פνи���������� (value - 1�ǥ�������) (0�ǽ����)

	// ���쿧�Ǥʤ���Фʤ�ʤ��Τǡ�����Ʊ������Ǥ��뤳�Ȥ��ǧ
	Tile::TileType type = hand.Waiting->GetType();

	// ���������פǤ���λ�Ǥ��ʤ�
	if (type == Tile::Honors)
		return false;

	// �̻ҤΥ��ƥ졼�����
	for (vector<vector<Tile*> >::const_iterator hiter = hand.Tiles.begin();
		hiter != hand.Tiles.end();
		++hiter)
	{
		// ���ץ֥��å�����Υ��ƥ졼�����
		for (vector<Tile*>::const_iterator iter = (*hiter).begin();
			iter != (*hiter).end();
			++iter)
		{
			// �׼郎�㤦
			if ((*iter)->GetType() != type)
				return false;

			valuector[(*iter)->GetValue() - 1]++;
		}
	}

	// �и�����������
	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
		{
			// 3��ʾ�(3�礫4��Ǥ���ɬ�פ�����)
			if (valuector[i] < 3)
				return false;
		}
		else
		{
			// 0��Ǥ⡢2��ʾ�Ǥ���ᡣ
			if (valuector[i] == 0 || valuector[i] > 2)
				return false;
		}
	}

	// ����ǤȤ��������ޤ������Τ�ʤ��褦�����դ��Ƥ���������
	return true;
}

int NineGates::GetRank(bool concealing)
{
	return 13;
}

string NineGates::GetName()
{
	return "��Ϣ����";
}
