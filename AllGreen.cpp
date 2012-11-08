#include <string>
#include <vector>

#include "AllGreen.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// �а쿧
// ⤤ʤ��а쿧��ǧ��ޤ���
bool AllGreen::Check(const WinHand& hand, const Player& player)
{
	for (vector<vector<Tile*> >::const_iterator biter = hand.Tiles.begin();
			biter != hand.Tiles.end();
			++biter)
	{
		for (vector<Tile*>::const_iterator iter = (*biter).begin();
				iter != (*biter).end();
				++iter)
		{
			switch ((*iter)->GetType())
			{

				case Tile::Bamboos:
					// ���Ƥ���Τϡ����Ҥ�2,3,4,6,8�Τ�
					// 1, 5, 7, 9�ϥ�����
					{
						// gcc���ܤ���Τǥ��å��Ǥ�����
						int v = (*iter)->GetValue();
						if (v == 1 || v == 5 || v == 7 || v == 9)
							return false;
					}
					break;

				case Tile::Honors:
					// ���פ�⤤Τ߲�
					if ((*iter)->GetValue() != (int)Tile::Green)
						return false;
					break;

				default:
					// �Ф���ʤ�
					return false;
			}
		}
	}
	return true;
}

int AllGreen::GetRank(bool concealing)
{
	return 13;
}

string AllGreen::GetName()
{
	return "�а쿧";
}



