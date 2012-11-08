#include <string>
#include <vector>

#include "DoubleRuns.h"
#include "Player.h"
#include "WinHand.h"
#include "Tile.h" 

using namespace std;

// 二盃口
bool DoubleRuns::Check(const WinHand& hand, const Player& player)
{
	// 面前役
	if (!player.IsConcealing())
		return false;

	// 七対子誤爆を防ぐ
	if (hand.Tiles.size() != 5)
		return false;

	// 順子の開始値を覚えておく
	int firstInitValue = -1;
	Tile::TileType firstType = Tile::None;
	int secondInitValue = -1;
	Tile::TileType secondType = Tile::None;

	for (vector<vector<Tile*> >::const_iterator iter = hand.Tiles.begin();
		iter != hand.Tiles.end();
		++iter)
	{
		if ((*iter).size() == 2) // 雀頭を読み飛ばす
			continue;

		else if((*iter).size() != 3) // 槓子ならばすぐにアウト
			return false;

		// 順子であることを確認
		if ((*iter).at(0)->GetValue() == (*iter).at(1)->GetValue())
			return false;

		if (firstInitValue == -1)
		{
			// 第一順子
			firstInitValue = (*iter).at(0)->GetValue();
			firstType = (*iter).at(0)->GetType();
			if (firstType == Tile::Honors)
				return false; // 無いとは思う
		}
		else
		{
			// 第一順子判定
			if ((*iter).at(0)->GetValue() == firstInitValue &&
				(*iter).at(0)->GetType() == firstType)
			{
				firstInitValue = 10; // 無効な値を保持しておく
			}
			else
			{
				if (secondInitValue == -1)
				{
					// 第二順子
					secondInitValue = (*iter).at(0)->GetValue();
					secondType = (*iter).at(0)->GetType();
				}
				else
				{
					// 第二順子判定
					if ((*iter).at(0)->GetValue() == secondInitValue &&
						(*iter).at(0)->GetType() == secondType)
					{
						secondInitValue = 10; // 無効な値を保持しておく(予備)
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

int DoubleRuns::GetRank(bool concealing)
{
	return 3;
}

string DoubleRuns::GetName()
{
	return "二盃口";
}


