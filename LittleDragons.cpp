#include <string>
#include <vector>

#include "LittleDragons.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool LittleDragons::Check(const WinHand& hand, const Player& player)
{
	// �绰���Ȥ�ʣ��ϡ��绰���������Ǥ��뤿���θ���ޤ���
	// ������ĤȤ�ʣ���4�ݤȤʤ�ޤ�

	// ���лҸ������ɤ�
	if (hand.Tiles.size() != 5)
		return false;

	bool dragons[3] = { false };
	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// ��Ƭ���ä�OK
		if ((*iter).at(0)->GetType() == Tile::Honors)
		{
			switch ((Tile::HonorValues)(*iter).at(0)->GetValue())
			{
			case Tile::White:
				dragons[0] = true;
				break;
			case Tile::Green:
				dragons[1] = true;
				break;
			case Tile::Red:
				dragons[2] = true;
				break;
			}
		}
	}

	return dragons[0] && dragons[1] && dragons[2];
}

int LittleDragons::GetRank(bool concealing)
{
	return 2;
}

string LittleDragons::GetName()
{
	return "������";
}

