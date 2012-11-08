#include <list>
#include <stdexcept>
#include <algorithm>

#include "TileFactory.h"
#include "Tile.h"

using namespace std;

// �ץե����ȥꥯ�饹�μ���
list<Tile> TileFactory::tilelist;

// ������ο��������󥹥��󥹤����
Tile* TileFactory::Create()
{
	tilelist.push_back(Tile());
	return &(tilelist.back());
}

// ����ͤ���ꤷ�ƣ��
Tile* TileFactory::Create(Tile::TileType type, int value)
{
	Tile* tile = Create();
	tile->SetTypeValue(type, value);
	return tile;
}

// �����뻲�Ȥ������ޤ�
void TileFactory::Delete(const Tile *del)
{
	tilelist.remove_if(GidUnique(*del));
}

// ���ݤ��줿���٤ƤΥ��������
void TileFactory::Destroy()
{
	tilelist.clear();
}

TileFactory::GidUnique::GidUnique(const Tile& source)
{
	targGid = source.GetGid();
}

