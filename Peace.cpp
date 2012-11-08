#include "Peace.h"
#include "Player.h"

bool Peace::Check(const WinHand& hand,  const Player& player)
{
	// ��Ϫ�������ʿ�¤��դ��ʤ�
	if (!player.IsConcealing())
		return false;

	// 4�Ȥ��̻� + ��Ƭ �Ǥʤ���м�������ʤ�
	// (ȿ��: ���,���л�
	if (hand.Tiles.size() != 5)
		return false;

	// �Ԥ��פ�ޤ��̻ҤؤΥݥ���
	const vector<Tile*>* winWait = NULL;

	// ���٤ƽ�ҤǤ��뤫����Ƚ��
	for (vector<vector<Tile*> >::const_iterator itr = hand.Tiles.begin();
		itr != hand.Tiles.end();
		++itr)
	{
		switch ((*itr).size())
		{
		case 4: // �ʻҤ����ä���̵���Ǥ�
			return false;
		case 3:
			if ((*itr).at(0)->GetType() == Tile::Honors) // ���פϹ�Ҥˤ����ʤ�ʤ�
				return false;

			if ((*itr).at(0)->GetValue() == (*itr).at(1)->GetValue()) // 1����2���ܤ��ͤ�Ʊ���ʤ���
				return false;

			if ((*itr).at(0)->GetGid() == hand.Waiting->GetGid() ||
				(*itr).at(1)->GetGid() == hand.Waiting->GetGid() ||
				(*itr).at(2)->GetGid() == hand.Waiting->GetGid())
				winWait = &(*itr);
			break;
		case 2:
			// ��Ƭ�Ԥ��ˤϤʤ�ʤ�
			if ((*itr).at(0)->GetGid() == hand.Waiting->GetGid() ||
				(*itr).at(1)->GetGid() == hand.Waiting->GetGid())
				return false;
		}
	}


	// ξ���Ԥ����������������å�
	if (winWait->at(0)->GetGid() == hand.Waiting->GetGid())
	{
		// 1����
		if (hand.Waiting->GetValue() == 7)
		{
			// 7-89 �Ǥ���ĥ�Ԥ�
			return false;
		}
	}
	else if (winWait->at(2)->GetGid() == hand.Waiting->GetGid())
	{
		// 3����
		if (hand.Waiting->GetValue() == 3)
		{
			//12-3�Ǥ���ĥ�Ԥ�
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

int Peace::GetRank(bool concealing)
{
	if (!concealing)
		return 0;
	else
		return 1;
}

string Peace::GetName()
{
	return "ʿ��";
}
