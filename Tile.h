#ifndef __C_TILE__
#define __C_TILE__

#include <vector>
#include <string>

using namespace std;

class Tile
{

private:

	// �����Х� ID �ݻ��ѿ�
	static int gidHolder;

	// �����Х� ID
	int gid;

public:

	// �פμ���
	enum TileType
	{
		// �߻� 
		Characters,
		// ����
		Stones,
		// ����
		Bamboos,
		// ����
		Honors,
		// ̵������
		None = -1
	};

	// ���פμ���
	enum HonorValues
	{
		// ��
		East,
		// ��
		South,
		// ��
		West,
		// ��
		North,
		// ��
		White,
		// �
		Green,
		// ��
		Red
	};

#pragma region �����ͥ졼��

	// ������ʸ������װ��ʬ��ɽ��ʸ���������Ѵ����ޤ���
	// �����˼��Ԥ�������0(NULL)���֤��ޤ���
	static vector<string>* SplitTileArray(const string& str);

	// ʸ�������ץ��֥������ȥ��󥹥��󥹤�������ޤ���
	// �����˼��Ԥ�������0(NULL)���֤��ޤ���
	static Tile* ParseString(const string& parse);

#pragma endregion


	// ID�Υޥåԥ�:
	// �߻�: 0 - 8
	// ����: 10 - 18
	// ����: 20 - 28
	// ����: 30 - 37
	int id;

	// �ޥ͡����� ID
	int manage_id;

	// ��λȽ����
	bool inactive;

	// ���󥹥ȥ饯��
	Tile();

	// �����ͤ�����
	int SetTypeValue(TileType type, int value);

	// ���Υ��󥹥��󥹤η������פ����
	TileType GetType() const;

	// �ͤ����
	int GetValue () const;

	// �䥪���奦�פǤ��뤫����
	bool IsYaochu() const;

	// Ƚ�ɲ�ǽ��ʸ��������
	string ToString() const;

	// �����Х�ID�����
	int GetGid() const;

#pragma region �����ȥإ�ѡ�

	static bool IdSort(const Tile* left, const Tile* right)
	{
		return left->id < right->id;
	}

	static bool IdUnique(const Tile* left, const Tile* right)
	{
		return left->id == right->id;
	}

	static bool GidUnique(const Tile* left, const Tile* right)
	{
		return left->gid == right->gid;
	}

#pragma endregion


};

#endif

