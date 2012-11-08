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

// �ץ쥤�䡼���饹
// 
class Player
{
	public:
		enum Action
		{
			// �ʤ�
			None,
			// ����
			Chow,
			// �ݥ�
			Pong,
			// ����
			Kong,
			// ���
			Ron,
		};

		enum State
		{
			// �����Ե�����
			DealWait,
			// �Ե�����
			Waiting,
			// İ�פ��Ƥ�����֤��Ե�����
			TenpaiWaiting,
			// Ωľ�����Ԥä�����
			Riiching,
			// ��λ����(������)
			TsumoWinning,
			// ��峫�־���
			RinshanTsumoWinning,
			// ��λ����(����)
			RonWinning
		};

	protected:
		// ����
		int Point;

		// ��ǽ�ʥ������������
		vector<pair<int, Action> > AvailableAction(vector<Tile*>& ins, Tile* tile, bool chowable);

	public:

		// �жɤΥ��åȥ��å�
		virtual void InitializeGame(GameDefine::Winds wind, GameDefine::Winds prevail, vector<Tile*> tile) = 0;

		// �פ���������ν���
		virtual Tile* OnDealingTile(Tile* tile, GameSystem& gsys) = 0;

		// ���פ��줿�Ȥ�
		// ư���������������λ��������
		// ActionAccepted��������Хå�����ޤ�
		virtual Action OnDiscarded(Tile* discarded, bool chowable) = 0;

		// ���׻�ư�λ������ޤ���
		virtual Tile* ActionAccepted(Tile* discarded, Action accepted, GameSystem& gsys) = 0;

		// ���ߤξ��֤�������ޤ�
		virtual State GetState() const = 0;

		// ���Υץ쥤�䡼������������ޤ�
		virtual GameDefine::Winds GetWind() const = 0;

		// ������������ޤ�
		virtual GameDefine::Winds GetPrevailingWind() const = 0;

		// ��Ϫ���줿�ץ��֥������ȤؤΥ�ե���󥹤�������ޤ�
		virtual const vector<vector<Tile*> >& GetSubTiles() const = 0;

		// ��Ϫ��ԤäƤ��ʤ����֤�
		virtual bool IsConcealing() const = 0;

		// ���ꤷ���פ����Ǥ˻����ץ��åȤ���Ϫ����Ƥ��뤫��ǧ���ޤ�
		virtual bool IsUnconcealedSub(Tile* header) const = 0;

		// ��λ���֤λ�����λã���������ΰ�����������ޤ���
		virtual const vector<WinHand>& GetWinHands() const = 0;

		// ���Υץ쥤�䡼���ƤǤ��뤫��������ޤ�
		inline bool IsParent() const
		{
			return GetWind() == GameDefine::East;
		}

		// ������������ޤ���
		inline int GetPoint() const
		{
			return Point;
		}

		// ���������ꤷ�ޤ���
		inline void SetPoint(int point)
		{
			Point = point;
		}

		// �����κ�ʬ�����ꤷ�ޤ���
		inline void SetDiffPoint(int diff)
		{
			Point += diff;
		}
};

#endif


