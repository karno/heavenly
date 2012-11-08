#include <string>
#include <vector>

#include "HalfFlush.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool HalfFlush::Check(const WinHand& hand, const Player& player)
{
	// ���ܤȤʤ��׼�����
	Tile::TileType type = Tile::None;

	// ���פ򸫤Ĥ�����
	bool honorEncd = false;

	// �̻ҤΥ��ƥ졼�����
	for (vector<vector<Tile*> >::const_iterator hiter = hand.Tiles.begin();
		hiter != hand.Tiles.end();
		++hiter)
	{
		// ���ץ֥�å�����Υ��ƥ졼�����
		for (vector<Tile*>::const_iterator iter = (*hiter).begin();
			iter != (*hiter).end();
			++iter)
		{
			if ((*iter)->GetType() != type)
			{
				// ¾���פ�ȯ��
				if ((*iter)->GetType() == Tile::Honors) // ����ȯ��
					honorEncd = true;
				else
					if (type == Tile::None)
					{
						type = (*iter)->GetType();
					}
					else
					{
						return false;
					}
			}
		}
	}
	// ���פ�ޤ�Ǥ��ʤ��������쿧�Ȥʤ�(������ʣ�礷�ʤ�)
	return honorEncd;
}

int HalfFlush::GetRank(bool concealing)
{
	return concealing ? 3 : 2;
}

string HalfFlush::GetName()
{
	return "���쿧";
}

