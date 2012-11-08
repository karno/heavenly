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

// �פ���������ν���
Tile* PlayerMachine::OnDealingTile(Tile* tile, GameSystem& gsys)
{
	// TODO:Implementation
	return tile;
}

// ���פ��줿�Ȥ�
// ư���������������λ��������
// ActionAccepted��������Хå�����ޤ�
Player::Action PlayerMachine::OnDiscarded(Tile* discarded, bool chowable)
{
	return Player::None;
}

// ���׻�ư�λ������ޤ���
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

// ���ߤξ��֤�������ޤ�
Player::State PlayerMachine::GetState() const
{
	// TODO:Implementation
	return Player::Waiting;
}

// ��Ϫ���줿�ץ��֥������ȤؤΥ�ե���󥹤�������ޤ�
const vector<vector<Tile*> >& PlayerMachine::GetSubTiles() const
{
	// TODO:Implementation
	return SubOpeneds;
}

// ��Ϫ��ԤäƤ��ʤ����֤�
bool PlayerMachine::IsConcealing() const
{
	// TODO:Implementation
	return true;
}

// ���ꤷ���פ����Ǥ˻����ץ��åȤ���Ϫ����Ƥ��뤫��ǧ���ޤ�
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

