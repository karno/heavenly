#ifndef __S_WINHAND__
#define __S_WINHAND__

#include <vector>

#include "Tile.h"

using namespace std;

// 役のデスクリプタ
struct WinHand
{
	public :
		// 当たり牌
		Tile* Waiting;

		// 面子のコレクション
		vector<vector<Tile*> > Tiles;
};

#endif


