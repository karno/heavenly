#ifndef __C_GAME_SYSTEM__
#define __C_GAME_SYSTEM__

#include <vector>

#include "Player.h"
#include "GameDefine.h"
#include "Tile.h"

class Player;
using namespace std;

class GameSystem
{
	private:
		GameDefine::Winds PrevailingWind;

		// 牌配列の生成とユーザー配列の生成
		void Init();

		// Initの逆操作
		void Dispose();

		// 局を開始します。
		// 戻り値がtrueなら局数が変化します。
		bool DoCurrentGame();

		// 新しい局を開始する
		void InitializeCurrentGame();

		// 牌の初期化
		void InitializeTiles();

		// ドラ牌を追加
		// 四開槓ならfalseが返る
		void AddBonusTile();

		// ゲーム進行に必要な変数のインスタンス

		// 現在の局数
		int GameCount;

		// 参加ユーザーのポインタ配列
		Player **Players;

		// 牌のポインタ配列
		vector<Tile*> Tiles;

		// 次の自摸位置
		int CurrentPos;

		// 次の嶺上自摸位置(嶺上自摸回数)
		int RinshanPos;

		// ドラ牌 (size() - 4 - Bonuses.size()から随時push_back)
		vector<Tile*> Bonuses;

		// 捨てられた牌を格納します
		vector<Tile*> Discardeds[4];

		// キャリーオーバー
		int Carryover;

		// 本場
		int Honba;


	public:
		void GameMain();

		// 指定したユーザーが捨てた牌を取得します
		const vector<Tile*> GetDiscardeds(int player) const;

		// ドラ表示牌一覧を取得します
		const vector<Tile*> GetBonusTiles() const;

		// 嶺上牌自摸
		// 暗槓であればconcealedをtrueにしてください、ドラ牌追加がすぐに通知されます
		Tile* PickRinshan(bool concealed);
};

#endif


