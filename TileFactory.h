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

#pragma region ���Ҵؿ�

	// remove_if��Predicate
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

	// �ץ��֥������� ���󥹥��󥹤��������ޤ���
	static Tile* Create();

	// ����ͤ���ꤷ�ơ��ץ��֥������� ���󥹥��󥹤��������ޤ���
	static Tile* Create(Tile::TileType type, int value);

	// TileFactory�������������ץ��֥������Ȥ������ޤ���
	static void Delete(const Tile *del);

	// TileFactory�������������ץ��֥������Ȥ򤹤٤ƺ�����ޤ���
	static void Destroy();



};

#endif

