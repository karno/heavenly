#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>

#include "PlayerMachine.h"

void PlayerMachine::InitializeGame(GameDefine::Winds wind, GameDefine::Winds prevail, vector<Tile*> tile)
{
	PrevailWind = prevail;
	MyWind = wind;
}

// 牌を引いた時の処理
Tile* PlayerMachine::OnDealingTile(Tile* tile, GameSystem& gsys)
{
	// TODO:Implementation
	return tile;
}

// 捨牌されたとき
// 動作を宣言するだけ、了承されれば
// ActionAcceptedがコールバックされます
Player::Action PlayerMachine::OnDiscarded(Tile* discarded, bool chowable)
{
	return Player::None;
}

// 捨牌時動作が了承されました
Tile* PlayerMachine::ActionAccepted(Tile* discarded, Player::Action accepted, GameSystem& gsys)
{
	throw exception();
}


GameDefine::Winds PlayerMachine::GetWind() const
{
	// TODO:Implementation
	return MyWind;
}


GameDefine::Winds PlayerMachine::GetPrevailingWind() const
{
	// TODO:Implementation
	return PrevailWind;
}

// 現在の状態を取得します
Player::State PlayerMachine::GetState() const
{
	// TODO:Implementation
	return Player::Waiting;
}

// 副露された牌オブジェクトへのリファレンスを取得します
const vector<vector<Tile*> >& PlayerMachine::GetSubTiles() const
{
	// TODO:Implementation
	return SubOpeneds;
}

// 副露を行っていない状態か
bool PlayerMachine::IsConcealing() const
{
	// TODO:Implementation
	return true;
}

// 指定した牌を要素に持つ牌セットが副露されているか確認します
bool PlayerMachine::IsUnconcealedSub(Tile* header) const
{
	// TODO:Implementation
	return false;
}

const vector<WinHand>& PlayerMachine::GetWinHands() const
{
	// TODO:Implementation
	return Winhands;
}

