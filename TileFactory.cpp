#include <list>
#include <stdexcept>
#include <algorithm>

#include "TileFactory.h"
#include "Tile.h"

using namespace std;

// 牌ファクトリクラスの実装
list<Tile> TileFactory::tilelist;

// タイルの新しいインスタンスを取得
Tile* TileFactory::Create()
{
	tilelist.push_back(Tile());
	return &(tilelist.back());
}

// 初期値を指定してｒｙ
Tile* TileFactory::Create(Tile::TileType type, int value)
{
	Tile* tile = Create();
	tile->SetTypeValue(type, value);
	return tile;
}

// タイル参照を削除します
void TileFactory::Delete(const Tile *del)
{
	tilelist.remove_if(GidUnique(*del));
}

// 確保されたすべてのタイルを削除
void TileFactory::Destroy()
{
	tilelist.clear();
}

TileFactory::GidUnique::GidUnique(const Tile& source)
{
	targGid = source.GetGid();
}

