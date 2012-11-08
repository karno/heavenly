#ifndef __C_PLAYER__
#define __C_PLAYER__

#include <stdexcept>
#include <list>
#include <vector>
#include <iostream>
#include <utility>

#include "Tile.h"
#include "GameSystem.h"
#include "GameDefine.h"
#include "WinHand.h"

class GameSystem;

using namespace std;

// プレイヤークラス
// 
class Player
{
	public:
		enum Action
		{
			// なし
			None,
			// チー
			Chow,
			// ポン
			Pong,
			// カン
			Kong,
			// ロン
			Ron,
		};

		enum State
		{
			// 配牌待機状態
			DealWait,
			// 待機状態
			Waiting,
			// 聴牌している状態で待機状態
			TenpaiWaiting,
			// 立直宣言を行った状態
			Riiching,
			// 和了状態(自摸和)
			TsumoWinning,
			// 嶺上開花状態
			RinshanTsumoWinning,
			// 和了状態(栄和)
			RonWinning
		};

	protected:
		// 得点
		int Point;

		// 可能なアクションを列挙
		vector<pair<int, Action> > AvailableAction(vector<Tile*>& ins, Tile* tile, bool chowable);

	public:

		// 対局のセットアップ
		virtual void InitializeGame(GameDefine::Winds wind, GameDefine::Winds prevail, vector<Tile*> tile) = 0;

		// 牌を引いた時の処理
		virtual Tile* OnDealingTile(Tile* tile, GameSystem& gsys) = 0;

		// 捨牌されたとき
		// 動作を宣言するだけ、了承されれば
		// ActionAcceptedがコールバックされます
		virtual Action OnDiscarded(Tile* discarded, bool chowable) = 0;

		// 捨牌時動作が了承されました
		virtual Tile* ActionAccepted(Tile* discarded, Action accepted, GameSystem& gsys) = 0;

		// 現在の状態を取得します
		virtual State GetState() const = 0;

		// このプレイヤーの風を取得します
		virtual GameDefine::Winds GetWind() const = 0;

		// 場風を取得します
		virtual GameDefine::Winds GetPrevailingWind() const = 0;

		// 副露された牌オブジェクトへのリファレンスを取得します
		virtual const vector<vector<Tile*> >& GetSubTiles() const = 0;

		// 副露を行っていない状態か
		virtual bool IsConcealing() const = 0;

		// 指定した牌を要素に持つ牌セットが副露されているか確認します
		virtual bool IsUnconcealedSub(Tile* header) const = 0;

		// 和了状態の時、和了達成した型の一覧を取得します。
		virtual const vector<WinHand>& GetWinHands() const = 0;

		// このプレイヤーが親であるかを取得します
		inline bool IsParent() const
		{
			return GetWind() == GameDefine::East;
		}

		// 得点を取得します。
		inline int GetPoint() const
		{
			return Point;
		}

		// 得点を設定します。
		inline void SetPoint(int point)
		{
			Point = point;
		}

		// 得点の差分を設定します。
		inline void SetDiffPoint(int diff)
		{
			Point += diff;
		}
};

#endif


