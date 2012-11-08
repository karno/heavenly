#include <vector>
#include <algorithm>
#include <utility>

#include "Player.h"

vector<pair<int, Player::Action> >  Player::AvailableAction(vector<Tile*>& ins, Tile* tile, bool chowable)
{
	vector<pair<int, Player::Action> > ret;
	for (int i = 0; i < ins.size() - 1; i++)
	{
		// 同じ種類の牌であることが大前提
		if(ins.at(i)->GetType() == ins.at(i + 1)->GetType() &&
			ins.at(i)->GetType() == tile->GetType())
		{
			// チー
			if (chowable && ins.at(i)->GetType() != Tile::Honors)
			{
				if(ins.at(i)->GetValue() + 1 == ins.at(i + 1)->GetValue())
				{
					// 隣接牌
					if (ins.at(i)->GetValue() - 1 == tile->GetValue() ||
						ins.at(i)->GetValue() + 2 == tile->GetValue())
					{
						ret.push_back(make_pair(i, Player::Chow));
					}
				}
				else if (ins.at(i)->GetValue() + 2 == ins.at(i + 1)->GetValue())
				{
					// 一枚置きで隣接
					if (ins.at(i)->GetValue() + 1 == tile->GetValue())
					{
						ret.push_back(make_pair(i, Player::Chow));
					}
				}
			}
			
			// ポン
			if (ins.at(i)->GetValue() == ins.at(i + 1)->GetValue() &&
				ins.at(i)->GetValue() == tile->GetValue())
			{
				ret.push_back(make_pair(i, Player::Pong));
			}
			
			// カン
			if (i < ins.size() - 2 &&
				ins.at(i)->GetType() == ins.at(i + 2)->GetType() &&
				ins.at(i)->GetValue() == ins.at(i + 1)->GetValue() &&
				ins.at(i)->GetValue() == ins.at(i + 2)->GetValue() &&
				ins.at(i)->GetValue() == tile->GetValue())
			{
				ret.push_back(make_pair(i, Player::Kong));
			}
		}
	}
	return ret;
}

