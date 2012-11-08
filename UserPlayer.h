#ifndef __C_USER_PLAYER__
#define __C_USER_PLAYER__

#include <vector>
#include <list>

#include "Player.h"
#include "GameDefine.h"
#include "GameSystem.h"
#include "Tile.h"

class UserPlayer : public Player
{
private:
	// フリテンかどうか
	bool IsFriten;

	Action prevAction;

	int prevActionArgument;
	
	vector<Tile*> DiscardedDb;

	vector<vector<Tile*> > SubOpeneds;

	vector<vector<Tile*> > GrossOpeneds;

	vector<Tile*> HandyTiles;

	void UpdateWinHand();

	vector<WinHand> *winHandCache;

	GameDefine::Winds PrevailWind;

	GameDefine::Winds MyWind;

	bool IsConcealingStill;

	void SortAndShowHandy();

	int GetUserOperation(Tile *current);

	State MyState;

public:
	UserPlayer();

	// 対局のセットアップ
	void InitializeGame(GameDefine::Winds wind, GameDefine::Winds prevail, vector<Tile*> tile);

	// 牌を引いた時の処理
	Tile* OnDealingTile(Tile* tile, GameSystem& gsys);

	// 捨牌されたとき
	// 動作を宣言するだけ、了承されれば
	// ActionAcceptedがコールバックされます
	Action OnDiscarded(Tile* discarded, bool chowable);

	// 捨牌時動作が了承されました
	Tile* ActionAccepted(Tile* discarded, Action accepted, GameSystem& gsys);

	// 現在の状態を取得します
	State GetState() const;

	// このプレイヤーの風を取得します
	GameDefine::Winds GetWind() const;

	// 場風を取得します
	GameDefine::Winds GetPrevailingWind() const;

	// 副露された牌オブジェクトへのリファレンスを取得します
	const vector<vector<Tile*> >& GetSubTiles() const;

	// 副露を行っていない状態か
	bool IsConcealing() const;

	// 指定した牌を1枚目に持つ牌セットが副露されているか確認します
	bool IsUnconcealedSub(Tile* header) const;

	// 和了状態の時、和了達成した型の一覧を取得します。
	const vector<WinHand>& GetWinHands() const;
};

#endif

