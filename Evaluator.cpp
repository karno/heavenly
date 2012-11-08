#include <vector>
#include <stdexcept>
#include <cmath>

#include "Evaluator.h"
#include "Tile.h"
#include "WinHand.h"
#include "Criteria.h"
#include "CriteriaSystem.h"
#include "GameSystem.h"
#include "GameDefine.h"

int Evaluator::GetAdditionalPoint(const WinHand& wh, const Player& player)
{
	// ����ϸ夫��û������Τǡ������ǤϹ�θ���ʤ�
	if (wh.Tiles.size() != 5)
	{
		// ��Τ����л�
		return 0;
	}

	int val = 0;
	for (vector<vector<Tile*> >::const_iterator iter = wh.Tiles.begin();
		iter != wh.Tiles.end();
		++iter)
	{
		if ((*iter).size() == 2)
		{
			// ��Ƭ
			if ((*iter).at(0)->GetType() != Tile::Honors) // ���׿�Ƭ���䤬�դ��ʤ�
				continue;

			switch((Tile::HonorValues)(*iter).at(0)->GetValue())
			{
			case Tile::East:
			case Tile::South:
			case Tile::West:
			case Tile::North:
				// �����������ʤ� + 2
				if ((*iter).at(0)->GetValue() == (int)player.GetPrevailingWind())
					val += 2;
				if ((*iter).at(0)->GetValue() == (int)player.GetWind())
					val += 2;
				break;
			case Tile::White:
			case Tile::Green:
			case Tile::Red:
				val += 2;
				break;
			}
		}
		else if ((*iter).size() == 3)
		{
			// �̻�
			if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue()) // ��Ҥϥ����
				continue;
			if (player.IsUnconcealedSub((*iter).at(0)))
			{
				// ����
				if ((*iter).at(0)->IsYaochu())
					val += 4;
				else
					val += 2;
			}
			else
			{
				// �Ź�
				if ((*iter).at(0)->IsYaochu())
					val += 4;
				else
					val += 2;
			}
		}
		else if((*iter).size() == 4)
		{
			// �ʻ�
			if (player.IsUnconcealedSub((*iter).at(0)))
			{
				// ����
				if ((*iter).at(0)->IsYaochu())
					val += 16;
				else
					val += 8;
			}
			else
			{
				// �Ź�
				if ((*iter).at(0)->IsYaochu())
					val += 32;
				else
					val += 16;
			}
		}
		else
		{
			cout << "Invalid tuple:" << (*iter).size() << endl;
			throw invalid_argument("Invalid size of tiles tuple.");
		}
	}
	return val;
}

int Evaluator::Evaluate(const vector<WinHand>& gotHand, 
		const Player& player, CriteriaSystem::SpecialWinStyles spw)
{
	// ��η׻�
	int maxCriteriaCount = 0;
	vector<Criteria*> maxCriteriaSets;
	int maxCriteriaContains = 0; // 1:ʿ�¤�ޤ� 2:���лҤ�ޤ�
	const WinHand *maxCriteriaHand = NULL;

	int maxAddPoint = 0;
	for (vector<WinHand>::const_iterator iter = gotHand.begin();
		iter != gotHand.end();
		++iter)
	{
		vector<Criteria*> crts = CriteriaSystem::CheckCriterias(*iter, player, spw);
		if (crts.size() > 0)
		{
			int gross = 0;
			bool pinfu = 0;
			bool seven = 0;
			for (vector<Criteria*>::iterator ceval = crts.begin();
				ceval != crts.end();
				++ceval)
			{
				if ((*ceval)->GetName() == "ʿ��")
					pinfu = true;
				else if ((*ceval)->GetName() == "���л�")
					seven = true;

				gross += (*ceval)->GetRank(player.IsConcealing());
			}

			if (gross > maxCriteriaCount)
			{
				maxCriteriaCount = gross;
				maxCriteriaSets = crts;
				maxCriteriaContains = pinfu ? 1 : seven ? 2 : 0;
				maxCriteriaHand = &(*iter);
			}
		}

		int addp = GetAdditionalPoint(*iter, player);
		if (addp > maxAddPoint)
			maxAddPoint = addp;
	}

	if (maxCriteriaCount == 0)
	{
		cout << "�򤬤���ޤ���" << endl;
		return 0;
	}

	for (vector<vector<Tile*> >::const_iterator mit = maxCriteriaHand->Tiles.begin();
		mit != maxCriteriaHand->Tiles.end();
		++mit)
	{
		for (vector<Tile*>::const_iterator mtit = (*mit).begin();
			mtit != (*mit).end();
			++mtit)
		{
			cout << (*mtit)->ToString();
		}
		cout << " ";
	}
	cout << endl;

	for (vector<Criteria*>::iterator dit = maxCriteriaSets.begin();
		dit != maxCriteriaSets.end();
		++dit)
	{
		cout << (*dit)->GetName() << " - " << (*dit)->GetRank(player.IsConcealing()) << "��" << endl;
	}

	// ʿ�¤�ޤޤʤ����Τʤ�+2
	if ((player.GetState() == Player::TsumoWinning || player.GetState() == Player::RinshanTsumoWinning) &&
		maxCriteriaContains != 1)
		maxAddPoint += 2;
	
	// �������¤ʤ�+10
	if (player.IsConcealing() && player.GetState() == Player::RonWinning)
		maxAddPoint += 10;

	// ������ɲ�
	maxAddPoint += 20;

	// �ڤ�夲
	maxAddPoint = (int)ceil(maxAddPoint / 10.0);
	
	switch (maxCriteriaCount)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		// 1000 - ����
		if (maxCriteriaContains == 2)
		{
			// ���лҤʤΤ�25��
			int retp = player.IsParent() ? 2400: 1600;
			retp *= 2 * (maxCriteriaCount - 1);
			if (!player.IsParent() && retp >= 8000 || retp >= 12000)
				cout << maxCriteriaCount << "�� 25�� - ����" << endl;
			else
				cout << maxCriteriaCount << "�� 25�� - " << retp << "��" <<  endl;
			return retp;
		}
		else
		{
			int retp = player.IsParent() ? ParentPointMap[maxCriteriaCount - 1][maxAddPoint - 2] : ChildPointMap[maxCriteriaCount - 1][maxAddPoint - 2];
			if (!player.IsParent() && retp >= 8000 || retp >= 12000)
				cout << maxCriteriaCount << "�� " << maxAddPoint * 10 << "�� - ����" << endl;
			else
				cout << maxCriteriaCount << "�� " << maxAddPoint * 10 << "�� - " << retp << "��" <<  endl;
			return retp;
		}
	case 6:
	case 7:
		// ķ��
		cout << maxCriteriaCount << "�� ķ��" << endl;
		return player.IsParent() ? 18000 : 12000;
	case 8:
	case 9:
	case 10:
		// ����
		cout << maxCriteriaCount << "�� ����" << endl;
		return player.IsParent() ? 24000 : 16000;
	case 11:
	case 12:
		// ������
		cout << maxCriteriaCount << "�� ������" << endl;
		return player.IsParent() ? 36000 : 24000;
	default:
		// ����
		cout << "����" << endl;
		return (player.IsParent() ? 48000 : 32000) * (int)floor(maxCriteriaCount / 13.0);
	}


	return 0;
}

// 1�ݡ�5�ݤޤǤ������ޥå�
int Evaluator::ChildPointMap[5][10] = 
{
	{   0, 1000, 1300, 1600, 2000, 2300, 2600, 2900, 3200, 3600},
	{1300, 2000, 2600, 3200, 3900, 4500, 5200, 5800, 6400, 7100},
	{2600, 3900, 5200, 6400, 7700, 8000, 8000, 8000, 8000, 8000},
	{5200, 7700, 8000, 8000, 8000, 8000, 8000, 8000, 8000, 8000},
	{8000, 8000, 8000, 8000, 8000, 8000, 8000, 8000, 8000, 8000}
};

int Evaluator::ParentPointMap[5][10] =
{
	{    0,  1500,  2000,  2400,  2900,  3400,  3900,  4400,  4800,  5300},
	{ 2000,  2900,  3900,  4800,  5800,  6800,  7700,  8700,  9600, 10600},
	{ 3900,  5800,  7700,  9600, 11600, 12000, 12000, 12000, 12000, 12000},
	{ 7700, 11600, 12000, 12000, 12000, 12000, 12000, 12000, 12000, 12000},
	{12000, 12000, 12000, 12000, 12000, 12000, 12000, 12000, 12000, 12000}
};

// ����������ʬ�ۤ���
int Evaluator::SplitTsumo(int base, bool isParentValue, int *pretpv)
{
	if (isParentValue)
	{
		// ��
		switch (base)
		{
		case 1500:
			return 500;
		case 200:
			return 700;
		case 2400:
			return 800;
		case 2900:
			return 1000;
		case 3400:
			return 1200;
		case 3900:
			return 1300;
		case 4400:
			return 1500;
		case 4800:
			return 1600;
		case 5300:
			return 1800;
		case 5800:
			return 2000;
		case 6800:
			return 2300;
		case 7700:
			return 2600;
		case 8700:
			return 2900;
		case 9600:
			return 3200;
		case 10600:
			return 3600;
		case 11600:
			return 3900;
		case 12000:
			return 4000;
		default:
			cout << "Invalid split input (parent):" << base << endl;
			throw invalid_argument("invalid base value (parent)");
		}
	}
	else
	{
		switch (base)
		{
		case 1000:
			if (pretpv != NULL) *pretpv = 500;
			return 300;
		case 1300:
			if (pretpv != NULL) *pretpv = 700;
			return 400;
		case 1600:
			if (pretpv != NULL) *pretpv = 800;
			return 400;
		case 2000:
			if (pretpv != NULL) *pretpv = 1000;
			return 500;
		case 2300:
			if (pretpv != NULL) *pretpv = 1200;
			return 600;
		case 2600:
			if (pretpv != NULL) *pretpv = 1300;
			return 700;
		case 2900:
			if (pretpv != NULL) *pretpv = 1500;
			return 800;
		case 3200:
			if (pretpv != NULL) *pretpv = 1600;
			return 800;
		case 3600:
			if (pretpv != NULL) *pretpv = 1800;
			return 900;
		case 3900:
			if (pretpv != NULL) *pretpv = 2000;
			return 1000;
		case 4500:
			if (pretpv != NULL) *pretpv = 2300;
			return 1200;
		case 5200:
			if (pretpv != NULL) *pretpv = 2900;
			return 1500;
		case 5800:
			if (pretpv != NULL) *pretpv = 2900;
			return 1500;
		case 6400:
			if (pretpv != NULL) *pretpv = 3200;
			return 1600;
		case 7100:
			if (pretpv != NULL) *pretpv = 3600;
			return 1800;
		case 7700:
			if (pretpv != NULL) *pretpv = 3900;
			return 2000;
		case 8000:
			if (pretpv != NULL) *pretpv = 4000;
			return 2000;
		default:
			cout << "Invalid split input (child):" << base << endl;
			throw invalid_argument("invalid base value (child)");

		}
	}
}
