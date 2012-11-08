#include <string>
#include <vector>
#include <stdexcept>

#include "ConcealedFour.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ConcealedFour::Check(const WinHand& hand, const Player& player)
{
	if (!player.IsConcealing())
		return false;

	// NNNN2 (3<=N<=4) の5 tuples以外は受け付けない
	if (hand.Tiles.size() != 5)
		return false;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		switch ((*iter).size())
		{
		case 2:
			// 雀頭
			break;
		case 3:
			// 順子/刻子
			if ((*iter).at(0)->GetType() != Tile::Honors)
			{
				// 数牌の場合、順子もありうるので精査
				// 1枚目と2枚目の値が違えば順子なので不成立
				if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue())
					return false;
			}
			// 刻子確定
			if (player.GetState() == Player::RonWinning)
			{
				// 栄和なので、雀頭待ちでないと四暗刻不成立
				for (vector<Tile*>::const_iterator init = (*iter).begin();
					init != (*iter).end();
					++init)
				{
					// 三枚の中に待ち牌が存在したらアウト
					if ((*init)->GetGid() == hand.Waiting->GetGid())
						return false;
				}
			}
			break;
		case 4:
			// 槓子 (暗槓確定なので見送り)
			break;
		default:
			cout << "Invalid tuple:" << (*iter).size() << endl;
			// 2,3,4以外の個数を持つ組が存在するのはおかしい
			throw new invalid_argument("winhand contains invalid tuple contents.");
		}
	}
	return true;
}

int ConcealedFour::GetRank(bool concealing)
{
	return 13;
}

string ConcealedFour::GetName()
{
	return "四暗刻";
}

