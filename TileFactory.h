#ifndef __C_TILE_FACTORY__
#define __C_TILE_FACTORY__

#include <list>
#include <stdexcept>
#include "Tile.h"

using namespace std;

class TileFactory
{

private:
	
	static list<Tile> tilelist;

#pragma region 叙述関数

	// remove_if用Predicate
	class GidUnique : unary_function<Tile, bool>
	{
	private:
		int targGid;

	public:
		GidUnique(const Tile& source);

		bool operator() (const Tile& tile)
		{
			return tile.GetGid() == targGid;
		}
	};

#pragma endregion

public:

	// 牌オブジェクト インスタンスを生成します。
	static Tile* Create();

	// 初期値を指定して、牌オブジェクト インスタンスを生成します。
	static Tile* Create(Tile::TileType type, int value);

	// TileFactoryから生成した牌オブジェクトを削除します。
	static void Delete(const Tile *del);

	// TileFactoryから生成した牌オブジェクトをすべて削除します。
	static void Destroy();



};

#endif

