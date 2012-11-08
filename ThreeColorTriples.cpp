#include <string>
#include <vector>

#include "ThreeColorTriples.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ThreeColorTriples::Check(const WinHand& hand, const Player& player)
{
	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	// 値の候補
	int vcan[2] = {0};
	int vc[2] = {0};

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 雀頭を飛ばす
		if ((*iter).size() < 3)
			continue;

		// 順子でした
		if ((*iter).at(0)->GetValue() != (*iter).at(1)->GetValue())
			continue;

		// 字牌は対象ではない
		if ((*iter).at(0)->GetType() == Tile::Honors)
			continue;

		if (vc[0] == 0)
		{
			// 刻子値候補1組目保存
			vcan[0] = (*iter).at(0)->GetValue();
			vc[0]++;
		}
		else
		{
			if ((*iter).at(0)->GetValue() == vcan[0])
			{
				// 刻子値候補1枚目と合致
				vc[0]++;
			}
			else
			{
				if (vc[1] == 0)
				{
					// 刻子値候補2組目保存
					vcan[1] = (*iter).at(0)->GetValue();
					vc[1]++;
				}
				else
				{
					if ((*iter).at(0)->GetValue() == vcan[1])
					{
						// 刻子値候補2枚目と合致
						vc[1]++;
					}
					else
					{
						// どちらとも違えばすぐアウト
						return false;

					}
				}
			}
		}

	}
	return vc[0] == 3 || vc[1] == 3;
}

int ThreeColorTriples::GetRank(bool concealing)
{
	// 食い下がりなし
	return 2;
}

string ThreeColorTriples::GetName()
{
	return "三色同刻";
}
