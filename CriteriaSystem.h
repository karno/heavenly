#ifndef __C_CRITERIA_SYSTEM__
#define __C_CRITERIA_SYSTEM__

#include <vector>
#include <string>

#include "Criteria.h"
#include "WinHand.h"
#include "GameSystem.h"
#include "Player.h"

#include "Riichi.h"
#include "DoubleRiichi.h"
#include "FirstRound.h"
#include "HeavenlyHand.h"
#include "EarthlyHand.h"
#include "FinalTileWin.h"
#include "KingsTile.h"
#include "RobbingQuad.h"
#include "Winds.h"


using namespace std;

// 役の判定抽象クラス
class CriteriaSystem
{
	private:
		static vector<Criteria*> NormalWins;
		static vector<Criteria*> Grandslams;

		static Riichi RiichiCriteria;
		static DoubleRiichi DoubleRiichiCriteria;

		static HeavenlyHand HeavenlyHandCriteria;
		static EarthlyHand EarthlyHandCriteria;
		static FirstRound FirstRoundCriteria;
		static FinalTileTsumo FinalTileTsumoCriteria;
		static FinalTileRon FinalTileRonCriteria;
		static KingsTile KingsTilesCriteria;
		static RobbingQuad RobbingQuadCriteria;

		static void GenerateCriterias();

	public:
		static void Initialize();

		static void Dispose();

		// 特殊和了状態のデスクリプタ
		enum SpecialWinStyles
		{
			// なし
			None = 0,
			// 立直している
			InRiichi = 1,
			// 両立直している
			InDoubleRiichi = 2,
			// 一発で和了
			InFirstRound = 4,
			// 天和/地和で和了
			InHeavenlyEarthlyHand = 8,
			// 最終牌で和了
			InFinalTile = 16,
			// 嶺上開花で和了
			InKingsTile = 32,
			// 槍槓で和了 (非サポート)
			InRobbingQuad = 64
		};

		// 指定された待ち牌で取得可能なすべての役を列挙します。
		static vector<Criteria*> CheckCriterias(const WinHand& wh, const Player& player,
				SpecialWinStyles specialStyle);
};
#endif


