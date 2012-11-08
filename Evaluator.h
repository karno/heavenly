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
		// 符計算
		static int GetAdditionalPoint(const WinHand& wh, const Player& player);

		// 点数表
		static int ChildPointMap[5][10];
		static int ParentPointMap[5][10];

	public:
		// 翻・符を計算し、得点を返します
		static int Evaluate(const vector<WinHand>& gotHand, 
				const Player& player, CriteriaSystem::SpecialWinStyles spw);

		// 自摸時の得点を計算します。
		// isParentValue : 親の自摸か
		// retParentValue = 親の支払い得点
		static int SplitTsumo(int base, bool isParentValue, int* retParentValue);
};

#endif


