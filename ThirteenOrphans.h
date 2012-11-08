#ifndef __C_CRITERIA_THIRTEENORPHANS__
#define __C_CRITERIA_THIRTEENORPHANS__

#include <vector>
#include <string>
#include <cassert>

#include "WinHand.h"
#include "Criteria.h"
#include "Tile.h"
#include "TileFactory.h"

using namespace std;

// ���̵��
class ThirteenOrphans : public Criteria
{
	public:

		// ���̵�Ф��Ԥ��򸡽Ф��ޤ���
		// �Ԥ���̵������NULL���֤��ޤ���
		vector<Tile*>* CheckWaits(const vector<Tile*>& tiles);

		bool Check(const WinHand& hand,  const Player& player);

		int GetRank(bool concealing);

		string GetName();

};

#endif


