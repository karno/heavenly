#include <string>
#include <vector>

#include "ThreeColorRuns.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

bool ThreeColorRuns::Check(const WinHand& hand, const Player& player)
{
	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	// ThreeColorTriplesからのほぼコピー、お許しください！

	// 値の候補
	int vcand[2] = {0};
	int vcnt[2] = {0};

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		// 雀頭を飛ばす
		if ((*iter).size() < 3)
			continue;

		// 刻子じゃダメ
		if ((*iter).at(0)->GetValue() == (*iter).at(1)->GetValue())
			continue;

		// 字牌は対象ではない
		if ((*iter).at(0)->GetType() == Tile::Honors)
			continue;

		if (vcnt[0] == 0)
		{
			// 刻子値候補1組目保存
			vcand[0] = (*iter).at(0)->GetValue();
			vcnt[0]++;
		}
		else
		{
			if ((*iter).at(0)->GetValue() == vcand[0])
			{
				// 刻子値候補1枚目と合致
				vcnt[0]++;
			}
			else
			{
				if (vcnt[1] == 0)
				{
					// 刻子値候補2組目保存
					vcand[1] = (*iter).at(0)->GetValue();
					vcnt[1]++;
				}
				else
				{
					if ((*iter).at(0)->GetValue() == vcand[1])
					{
						// 刻子値候補2枚目と合致
						vcnt[1]++;
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
	return vcnt[0] == 3 || vcnt[1] == 3;
}

int ThreeColorRuns::GetRank(bool concealing)
{
	return concealing ? 2 : 1;
}

string ThreeColorRuns::GetName()
{
	return "三色同順";
}


