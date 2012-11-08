#include <string>
#include <vector>
#include <stdexcept>

#include "ConcealedFour.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ConcealedFour::Check(const WinHand& hand, const Player& player)
{
	if (!player.IsConcealing())
		return false;

	// NNNN2 (3<=N<=4) ��5 tuples�ʳ��ϼ����դ��ʤ�
	if (hand.Tiles.size() != 5)
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		switch ((*iter).size())
		{
		case 2:
			// ��Ƭ
			break;
		case 3:
			// ���/���
			if ((*iter).at(0)->GetType() != Tile::Honors)
			{
				// ���פξ�硢��Ҥ⤢�ꤦ��Τ�����
				// 1���ܤ�2���ܤ��ͤ��㤨�н�ҤʤΤ�����Ω
				if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue())
					return false;
			}
			// ��ҳ���
			if (player.GetState() == Player::RonWinning)
			{
				// ���¤ʤΤǡ���Ƭ�Ԥ��Ǥʤ��ȻͰŹ�����Ω
				for (vector<Tile*>::const_iterator init = (*iter).begin();
					init != (*iter).end();
					++init)
				{
					// ���������Ԥ��פ�¸�ߤ����饢����
					if ((*init)->GetGid() == hand.Waiting->GetGid())
						return false;
				}
			}
			break;
		case 4:
			// �ʻ� (���ʳ���ʤΤǸ�����)
			break;
		default:
			cout << "Invalid tuple:" << (*iter).size() << endl;
			// 2,3,4�ʳ��θĿ�������Ȥ�¸�ߤ���ΤϤ�������
			throw new invalid_argument("winhand contains invalid tuple contents.");
		}
	}
	return true;
}

int ConcealedFour::GetRank(bool concealing)
{
	return 13;
}

string ConcealedFour::GetName()
{
	return "�ͰŹ�";
}

