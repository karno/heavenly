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
	// �ե�ƥ󤫤ɤ���
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

	// �жɤΥ��åȥ��å�
	void InitializeGame(GameDefine::Winds wind, GameDefine::Winds prevail, vector<Tile*> tile);

	// �פ���������ν���
	Tile* OnDealingTile(Tile* tile, GameSystem& gsys);

	// ���פ��줿�Ȥ�
	// ư���������������λ��������
	// ActionAccepted��������Хå�����ޤ�
	Action OnDiscarded(Tile* discarded, bool chowable);

	// ���׻�ư�λ������ޤ���
	Tile* ActionAccepted(Tile* discarded, Action accepted, GameSystem& gsys);

	// ���ߤξ��֤�������ޤ�
	State GetState() const;

	// ���Υץ쥤�䡼������������ޤ�
	GameDefine::Winds GetWind() const;

	// ������������ޤ�
	GameDefine::Winds GetPrevailingWind() const;

	// ��Ϫ���줿�ץ��֥������ȤؤΥ�ե���󥹤�������ޤ�
	const vector<vector<Tile*> >& GetSubTiles() const;

	// ��Ϫ��ԤäƤ��ʤ����֤�
	bool IsConcealing() const;

	// ���ꤷ���פ�1���ܤ˻����ץ��åȤ���Ϫ����Ƥ��뤫��ǧ���ޤ�
	bool IsUnconcealedSub(Tile* header) const;

	// ��λ���֤λ�����λã���������ΰ�����������ޤ���
	const vector<WinHand>& GetWinHands() const;
};

#endif

