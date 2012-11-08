#ifndef __C_TILE__
#define __C_TILE__

#include <vector>
#include <string>

using namespace std;

class Tile
{

private:

	// グローバル ID 保持変数
	static int gidHolder;

	// グローバル ID
	int gid;

public:

	// 牌の種類
	enum TileType
	{
		// 萬子 
		Characters,
		// 筒子
		Stones,
		// 索子
		Bamboos,
		// 字牌
		Honors,
		// 無効な値
		None = -1
	};

	// 字牌の種類
	enum HonorValues
	{
		// 東
		East,
		// 南
		South,
		// 西
		West,
		// 北
		North,
		// 白
		White,
		// 發
		Green,
		// 中
		Red
	};

#pragma region ジェネレータ

	// 牌配列文字列を牌一個分を表す文字の列挙に変換します。
	// 生成に失敗した場合は0(NULL)を返します。
	static vector<string>* SplitTileArray(const string& str);

	// 文字から牌オブジェクトインスタンスを取得します。
	// 生成に失敗した場合は0(NULL)を返します。
	static Tile* ParseString(const string& parse);

#pragma endregion


	// IDのマッピング:
	// 萬子: 0 - 8
	// 筒子: 10 - 18
	// 索子: 20 - 28
	// 字牌: 30 - 37
	int id;

	// マネージング ID
	int manage_id;

	// 和了判定用
	bool inactive;

	// コンストラクタ
	Tile();

	// 型と値を設定
	int SetTypeValue(TileType type, int value);

	// このインスタンスの型タイプを取得
	TileType GetType() const;

	// 値を取得
	int GetValue () const;

	// ヤオチュウ牌であるか取得
	bool IsYaochu() const;

	// 判読可能な文字列を取得
	string ToString() const;

	// グローバルIDを取得
	int GetGid() const;

#pragma region ソートヘルパー

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

