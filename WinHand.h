#ifndef __S_WINHAND__
#define __S_WINHAND__

#include <vector>

#include "Tile.h"

using namespace std;

// ��Υǥ�����ץ�
struct WinHand
{
	public :
		// ��������
		Tile* Waiting;

		// �̻ҤΥ��쥯�����
		vector<vector<Tile*> > Tiles;
};

#endif


