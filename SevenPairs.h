#ifndef __C_CRITERIA_SEVENPAIRS__
#define __C_CRITERIA_SEVENPAIRS__

#include <vector>
#include <string>

#include "WinHand.h"
#include "Criteria.h"
#include "Tile.h" 

using namespace std;

// ���л�
class SevenPairs : public Criteria
{
	public:
		// ���лҤ��Ԥ��򸡽Ф��ޤ���
		// �Ԥ���̵������NULL���֤��ޤ���
		WinHand* CheckWait(const vector<Tile*>& tiles);

		bool Check(const WinHand& hand, const Player& player);

		int GetRank(bool concealing);

		string GetName();

};


#endif


