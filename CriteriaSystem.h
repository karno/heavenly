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

// ���Ƚ����ݥ��饹
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

		// �ü���λ���֤Υǥ�����ץ�
		enum SpecialWinStyles
		{
			// �ʤ�
			None = 0,
			// Ωľ���Ƥ���
			InRiichi = 1,
			// ξΩľ���Ƥ���
			InDoubleRiichi = 2,
			// ��ȯ����λ
			InFirstRound = 4,
			// ŷ��/���¤���λ
			InHeavenlyEarthlyHand = 8,
			// �ǽ��פ���λ
			InFinalTile = 16,
			// ��峫�֤���λ
			InKingsTile = 32,
			// ���ʤ���λ (�󥵥ݡ���)
			InRobbingQuad = 64
		};

		// ���ꤵ�줿�Ԥ��פǼ�����ǽ�ʤ��٤Ƥ������󤷤ޤ���
		static vector<Criteria*> CheckCriterias(const WinHand& wh, const Player& player,
				SpecialWinStyles specialStyle);
};
#endif


