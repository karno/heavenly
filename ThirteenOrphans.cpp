#include <vector>
#include <string>
#include <cassert>

#include "WinHand.h"
#include "Criteria.h"
#include "Tile.h"
#include "TileFactory.h"

#include "ThirteenOrphans.h"


// tiles: ソートされた牌列挙
vector<Tile*>* ThirteenOrphans::CheckWaits(const vector<Tile*>& tiles)
{
	Tile::TileType ctype = Tile::Characters;
	int cv = 1;
	int wait[13] = {0};
	bool buffer = false;
	for (vector<Tile*>::const_iterator iter = tiles.begin();
		iter != tiles.end();
		++iter)
	{
		//cout << (*iter)->ToString() << endl;
		// 1-9 字牌のみに限定
		if (!(*iter)->IsYaochu())
		{
			return NULL;
		}

		// 対象牌カウントをインクリメント
		switch ((*iter)->GetType())
		{
		case Tile::Characters: // 萬子
		case Tile::Stones: // 筒子
		case Tile::Bamboos: // 索子
			if ((*iter)->GetValue() == 1)
				wait[((int)(*iter)->GetType()) * 2]++;
			else
				wait[((int)(*iter)->GetType()) * 2 + 1]++;
			break;
		case Tile::Honors:
			wait[((int)(*iter)->GetValue()) + 6]++;
			break;
		default:
			// internal error
			throw new exception();
		}
	}

	//cout << "checked" << endl;
	bool ovfcache = false;
	vector<Tile*>* wtiles = new vector<Tile*>();
	for (int i = 0; i < 13; i++)
	{
		if (wait[i] == 0)
		{
			if (i < 6)
			{
				// numerics
				// 0,2,4 : 1
				// 1,3,5 : 9
				if (i % 2 == 0)
				{
					// 1
					wtiles->push_back(TileFactory::Create(((Tile::TileType)(i / 2)), 1));
				}
				else
				{
					// 9
					wtiles->push_back(TileFactory::Create(((Tile::TileType)((i - 1) / 2)), 9));

				}
			}
			else
			{
				// honors
				wtiles->push_back(TileFactory::Create(Tile::Honors, i - 6));
			}
		}
		else if (wait[i] == 2)
		{
			if (ovfcache)
			{
				delete(wtiles);
				return NULL;
			}
			else
			{
				ovfcache = true;
			}
		}
		else if (wait[i] > 2)
		{
			// 一発アウト
			delete(wtiles);
			return NULL;
		}
	}
	if (!ovfcache)
	{
		cout << "kokusi-13" << endl;
		// 十三面待ち
		assert(wtiles->size() == 0);
		wtiles->push_back(TileFactory::Create(Tile::Characters, 1));
		wtiles->push_back(TileFactory::Create(Tile::Characters, 9));
		wtiles->push_back(TileFactory::Create(Tile::Stones, 1));
		wtiles->push_back(TileFactory::Create(Tile::Stones, 9));
		wtiles->push_back(TileFactory::Create(Tile::Bamboos, 1));
		wtiles->push_back(TileFactory::Create(Tile::Bamboos, 9));
		wtiles->push_back(TileFactory::Create(Tile::Honors, 0));
		wtiles->push_back(TileFactory::Create(Tile::Honors, 1));
		wtiles->push_back(TileFactory::Create(Tile::Honors, 2));
		wtiles->push_back(TileFactory::Create(Tile::Honors, 3));
		wtiles->push_back(TileFactory::Create(Tile::Honors, 4));
		wtiles->push_back(TileFactory::Create(Tile::Honors, 5));
		wtiles->push_back(TileFactory::Create(Tile::Honors, 6));
	}
	assert(wtiles->size() != 0);
	return wtiles;
}

bool ThirteenOrphans::Check(const WinHand& hand,  const Player& player)
{
	// 国士無双判定が通った時、面子は1つとして扱われる
	return hand.Tiles.size() == 1;
}

int ThirteenOrphans::GetRank(bool concealing)
{
	return 13;
}

string ThirteenOrphans::GetName()
{
	return "国士無双";
}

