#include <string>
#include <vector>

#include "ConcealedThree.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ConcealedThree::Check(const WinHand& hand, const Player& player)
{
	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	int ccs = 0;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 雀頭に用はありませんの
		if ((*iter).size() == 2)
			continue;

		// 刻子・順子
		if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue()) // 順子は不要
			continue;

		// 副露牌であるかをチェック
		if (player.IsUnconcealedSub((*iter).at(0))) // 副露されてたらカウントしない
			continue;

		ccs++;
	}
	return ccs >= 3;
}

int ConcealedThree::GetRank(bool concealing)
{
	return 2;
}

string ConcealedThree::GetName()
{
	return "三暗刻";
}


