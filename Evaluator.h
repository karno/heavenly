#ifndef __C_EVALUATOR__
#define __C_EVALUATOR__

#include <vector>

#include "Tile.h"
#include "GameSystem.h"
#include "Player.h"
#include "WinHand.h"
#include "CriteriaSystem.h"

class Evaluator
{
	private:
		// ��׻�
		static int GetAdditionalPoint(const WinHand& wh, const Player& player);

		// ����ɽ
		static int ChildPointMap[5][10];
		static int ParentPointMap[5][10];

	public:
		// �ݡ����׻������������֤��ޤ�
		static int Evaluate(const vector<WinHand>& gotHand, 
				const Player& player, CriteriaSystem::SpecialWinStyles spw);

		// ���λ���������׻����ޤ���
		// isParentValue : �Ƥμ��Τ�
		// retParentValue = �Ƥλ�ʧ������
		static int SplitTsumo(int base, bool isParentValue, int* retParentValue);
};

#endif


