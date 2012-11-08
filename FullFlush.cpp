#include <string>
#include <vector>

#include "FullFlush.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool FullFlush::Check(const WinHand& hand, const Player& player)
{
	// ���쿧�Ǥʤ���Фʤ�ʤ��Τǡ�����Ʊ������Ǥ��뤳�Ȥ��ǧ
	Tile::TileType type = hand.Waiting->GetType();

	// ���פ������ä��麮�쿧�Ȥʤ�ޤ�
	if (type == Tile::Honors)
		return false;

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
			// �׼郎�㤦
			if ((*iter)->GetType() != type)
				return false;
		}
	}

	return true;
}

int FullFlush::GetRank(bool concealing)
{
	return concealing ? 6 : 5;
}

string FullFlush::GetName()
{
	return "���쿧";
}

