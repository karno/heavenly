#include "Peace.h"
#include "Player.h"

bool Peace::Check(const WinHand& hand,  const Player& player)
{
	// 副露があれば平和は付かない
	if (!player.IsConcealing())
		return false;

	// 4組の面子 + 雀頭 でなければ受け入れない
	// (反例: 国士,七対子
	if (hand.Tiles.size() != 5)
		return false;

	// 待ち牌を含む面子へのポインタ
	const vector<Tile*>* winWait = NULL;

	// すべて順子であるか、の判定
	for (vector<vector<Tile*> >::const_iterator itr = hand.Tiles.begin();
		itr != hand.Tiles.end();
		++itr)
	{
		switch ((*itr).size())
		{
		case 4: // 槓子があったら無理です
			return false;
		case 3:
			if ((*itr).at(0)->GetType() == Tile::Honors) // 字牌は刻子にしかならない
				return false;

			if ((*itr).at(0)->GetValue() == (*itr).at(1)->GetValue()) // 1枚目2枚目の値が同じなら刻子
				return false;

			if ((*itr).at(0)->GetGid() == hand.Waiting->GetGid() ||
				(*itr).at(1)->GetGid() == hand.Waiting->GetGid() ||
				(*itr).at(2)->GetGid() == hand.Waiting->GetGid())
				winWait = &(*itr);
			break;
		case 2:
			// 雀頭待ちにはなれない
			if ((*itr).at(0)->GetGid() == hand.Waiting->GetGid() ||
				(*itr).at(1)->GetGid() == hand.Waiting->GetGid())
				return false;
		}
	}


	// 両面待ちを満たすかチェック
	if (winWait->at(0)->GetGid() == hand.Waiting->GetGid())
	{
		// 1枚目
		if (hand.Waiting->GetValue() == 7)
		{
			// 7-89 では辺張待ち
			return false;
		}
	}
	else if (winWait->at(2)->GetGid() == hand.Waiting->GetGid())
	{
		// 3枚目
		if (hand.Waiting->GetValue() == 3)
		{
			//12-3では辺張待ち
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

int Peace::GetRank(bool concealing)
{
	if (!concealing)
		return 0;
	else
		return 1;
}

string Peace::GetName()
{
	return "平和";
}
