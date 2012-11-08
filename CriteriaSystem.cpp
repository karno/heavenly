#include <vector>
#include <string>

#include "Criteria.h"
#include "CriteriaSystem.h"
#include "WinHand.h"
#include "GameSystem.h"
#include "Player.h"

// 役表現ファイルのインクルード

#include "AllSimples.h"
#include "ConcealedTsumo.h"
#include "DoubleRun.h"
#include "Peace.h"
#include "Values.h"
#include "Winds.h"

#include "AllTerminalsHonors.h"
#include "ConcealedThree.h"
#include "FullStraight.h"
#include "LittleDragons.h"
#include "MixedOutsides.h"
#include "ThreeColorRuns.h"
#include "ThreeColorTriples.h"
#include "ThreeQuads.h"
#include "AllTriples.h"

#include "DoubleRuns.h"
#include "HalfFlush.h"
#include "PureOutsides.h"

#include "FullFlush.h"

#include "AllGreen.h"
#include "AllHonors.h"
#include "AllTerminals.h"
#include "BigDragons.h"
#include "ConcealedFour.h"
#include "FourQuads.h"
#include "FourWinds.h"
#include "NineGates.h"

#include "DoubleRiichi.h"
#include "EarthlyHand.h"
#include "FirstRound.h"
#include "FinalTileWin.h"
#include "HeavenlyHand.h"
#include "KingsTile.h"
#include "Riichi.h"
#include "RobbingQuad.h"
#include "SevenPairs.h"
#include "ThirteenOrphans.h"


using namespace std;

void CriteriaSystem::Initialize()
{
	GenerateCriterias();
}

void CriteriaSystem::GenerateCriterias()
{
	NormalWins.push_back(new AllSimples());
	NormalWins.push_back(new ConcealedTsumo());
	NormalWins.push_back(new DoubleRun());
	NormalWins.push_back(new Peace());
	NormalWins.push_back(new ValueWhite());
	NormalWins.push_back(new ValueGreen());
	NormalWins.push_back(new ValueRed());
	NormalWins.push_back(new MyWinds());
	NormalWins.push_back(new PrevailingWinds());

	NormalWins.push_back(new AllTerminalsHonors());
	NormalWins.push_back(new AllTriples());
	NormalWins.push_back(new ConcealedThree());
	NormalWins.push_back(new FullStraight());
	NormalWins.push_back(new LittleDragons());
	NormalWins.push_back(new MixedOutsides());
	NormalWins.push_back(new ThreeColorRuns());
	NormalWins.push_back(new ThreeColorTriples());
	NormalWins.push_back(new ThreeQuads());
	NormalWins.push_back(new SevenPairs());

	NormalWins.push_back(new DoubleRuns());
	NormalWins.push_back(new HalfFlush());
	NormalWins.push_back(new PureOutsides());

	NormalWins.push_back(new FullFlush());

	Grandslams.push_back(new AllGreen());
	Grandslams.push_back(new AllHonors());
	Grandslams.push_back(new AllTerminals());
	Grandslams.push_back(new BigDragons());
	Grandslams.push_back(new ConcealedFour());
	Grandslams.push_back(new FourQuads());
	Grandslams.push_back(new FourWinds());
	Grandslams.push_back(new NineGates());
	Grandslams.push_back(new ThirteenOrphans());
}

void CriteriaSystem::Dispose()
{
	for (int i = 0; i < NormalWins.size(); i++)
	{
		delete NormalWins[i];
	}

	for (int i = 0; i < Grandslams.size(); i++)
	{
		delete Grandslams[i];
	}
}

// 役の列挙
vector<Criteria*> CriteriaSystem::CheckCriterias(const WinHand& wh, const Player& player,
	CriteriaSystem::SpecialWinStyles specialStyle)
{
	vector<Criteria*> rets;
	for (vector<Criteria*>::iterator iter = Grandslams.begin();
		iter != Grandslams.end();
		++iter)
	{
		if ((*iter)->Check(wh, player))
			rets.push_back(*iter);
	}
	// 役満がpushされていたらスルーする
	if (rets.size() == 0)
	{
		for (vector<Criteria*>::iterator iter = NormalWins.begin();
			iter != NormalWins.end();
			++iter)
		{
			if ((*iter)->Check(wh, player))
				rets.push_back(*iter);
		}
		// 特殊和了状態
		// 立直
		if (specialStyle & CriteriaSystem::InRiichi)
			rets.push_back(&RiichiCriteria);

		// 両立直
		if (specialStyle & CriteriaSystem::InDoubleRiichi)
			rets.push_back(&DoubleRiichiCriteria);

		// 一発
		if (specialStyle & CriteriaSystem::InFirstRound)
			rets.push_back(&FirstRoundCriteria);

		// 天和/地和
		if (specialStyle & CriteriaSystem::InHeavenlyEarthlyHand)
		{
			rets.push_back(&HeavenlyHandCriteria);
			rets.push_back(&EarthlyHandCriteria);
		}

		// 最終牌
		if (specialStyle & CriteriaSystem::InFinalTile)
		{
			rets.push_back(&FinalTileTsumoCriteria);
			rets.push_back(&FinalTileRonCriteria);
		}

		// 槍槓
		if (specialStyle & CriteriaSystem::InRobbingQuad)
			rets.push_back(&RobbingQuadCriteria);
	}
	// TODO:Implementation
	return rets;
}

vector<Criteria*> CriteriaSystem::NormalWins;
vector<Criteria*> CriteriaSystem::Grandslams;
Riichi CriteriaSystem::RiichiCriteria;
DoubleRiichi CriteriaSystem::DoubleRiichiCriteria;
HeavenlyHand CriteriaSystem::HeavenlyHandCriteria;
EarthlyHand CriteriaSystem::EarthlyHandCriteria;
FinalTileTsumo CriteriaSystem::FinalTileTsumoCriteria;
FinalTileRon CriteriaSystem::FinalTileRonCriteria;
KingsTile CriteriaSystem::KingsTilesCriteria;
RobbingQuad CriteriaSystem::RobbingQuadCriteria;
FirstRound CriteriaSystem::FirstRoundCriteria;

