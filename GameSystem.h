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

		// ������������ȥ桼�������������
		void Init();

		// Init�ε����
		void Dispose();

		// �ɤ򳫻Ϥ��ޤ���
		// ����ͤ�true�ʤ�ɿ����Ѳ����ޤ���
		bool DoCurrentGame();

		// �������ɤ򳫻Ϥ���
		void InitializeCurrentGame();

		// �פν����
		void InitializeTiles();

		// �ɥ��פ��ɲ�
		// �ͳ��ʤʤ�false���֤�
		void AddBonusTile();

		// ������ʹԤ�ɬ�פ��ѿ��Υ��󥹥���

		// ���ߤζɿ�
		int GameCount;

		// ���å桼�����Υݥ�������
		Player **Players;

		// �פΥݥ�������
		vector<Tile*> Tiles;

		// ���μ��ΰ���
		int CurrentPos;

		// ������弫�ΰ���(��弫�β��)
		int RinshanPos;

		// �ɥ��� (size() - 4 - Bonuses.size()������push_back)
		vector<Tile*> Bonuses;

		// �ΤƤ�줿�פ��Ǽ���ޤ�
		vector<Tile*> Discardeds[4];

		// ����꡼�����С�
		int Carryover;

		// �ܾ�
		int Honba;


	public:
		void GameMain();

		// ���ꤷ���桼�������ΤƤ��פ�������ޤ�
		const vector<Tile*> GetDiscardeds(int player) const;

		// �ɥ�ɽ���װ�����������ޤ�
		const vector<Tile*> GetBonusTiles() const;

		// ����׼���
		// ���ʤǤ����concealed��true�ˤ��Ƥ����������ɥ����ɲä����������Τ���ޤ�
		Tile* PickRinshan(bool concealed);
};

#endif


