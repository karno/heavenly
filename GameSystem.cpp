#include <stdexcept>
#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "GameDefine.h"
#include "Tile.h"
#include "Player.h"
#include "UserPlayer.h"
#include "PlayerMachine.h"
#include "TileFactory.h"
#include "TileSystem.h"
#include "Evaluator.h"
#include "WinHand.h"
#include "System.h"

// ゲーム実行メイン
void GameSystem::GameMain()
{
	Init();
	for (int i = 0; i < 4;)
	{
		if(DoCurrentGame())
			i++;
		cout << "Enterキーを押すと続行します。" << endl;
		System::WaitInput();
	}
	Dispose();
}

const vector<Tile*> GameSystem::GetBonusTiles() const
{
	return Bonuses;
}

Tile* GameSystem::PickRinshan(bool concealed)
{
	if (concealed)
		AddBonusTile();
	return Tiles[Tiles.size() - 1 - RinshanPos++];
}

bool GameSystem::DoCurrentGame()
{
	InitializeCurrentGame();
	int playercnt = 0;
	int winningPlayer = -1;
	int discardingPlayer = -1;
	int inOneTurn[4] = { 0 };

	while (true)
	{
		if (CurrentPos >= Tiles.size() - (12 + RinshanPos))
		{
			// 流局
			break;
		}

		Player *p = Players[playercnt];
		cout << "*********************************************************" << endl;
		cout << "プレイヤー " << playercnt + 1 << " (";
		switch (Players[playercnt]->GetWind())
		{
		case GameDefine::East:
			cout << "東家";
			break;
		case GameDefine::South:
			cout << "南家";
			break;
		case GameDefine::West:
			cout << "西家";
			break;
		case GameDefine::North:
			cout << "北家";
			break;
		}
		cout << ")" << endl;

		if (Players[playercnt]->GetSubTiles().size() > 0)
		{
			cout << "副露:";
			for (vector<vector<Tile*> >::const_iterator cit = Players[playercnt]->GetSubTiles().begin();
				cit != Players[playercnt]->GetSubTiles().end();
				++cit)
			{
				for (vector<Tile*>::const_iterator ctit = (*cit).begin();
					ctit != (*cit).end();
					++ctit)
				{
					cout << (*ctit)->ToString();
				}
				cout << " ";
			}
			cout << endl;
		}
		
		const GameSystem *gsys = this;
		Tile *disc = p->OnDealingTile(Tiles[CurrentPos++], const_cast<GameSystem&>(*gsys));
		
		if (disc == NULL)
		{
			// 自摸和了
			winningPlayer = playercnt;
			break;
		}
		if (p->GetState() == Player::Riiching &&
			inOneTurn[playercnt] < 3)
		{
			if (inOneTurn == 0)
			{
				if (Discardeds[playercnt].size() == 0)
					// ダブリー
					inOneTurn[playercnt] = 1;
				else
					// 立直
					inOneTurn[playercnt] = 2;
			}
			else
			{
				inOneTurn[playercnt] += 2;
			}
		}

		cout << "捨てられた牌:" << disc->ToString() << endl;
		int targetind = -1;
		Player::Action actcand = Player::None;
		for (int i = playercnt + 1; i < playercnt + 4; i++)
		{
			Player::Action act = Players[i % 4]->OnDiscarded(disc, i == playercnt + 1);
			if (act != Player::None)
			{
				// NULLかチーじゃない状態なら上書き
				if (targetind == -1 || act != Player::Chow)
				{
					targetind = i % 4;
					actcand = act;
				}
				if (act != Player::Chow)
				{
					// チーでないなら確定
					if (act == Player::Ron)
						winningPlayer = i % 4;

					break;
				}
			}
		}

		Discardeds[playercnt].push_back(disc);
		cout << "(河:";
		for (vector<Tile*>::const_iterator dit = Discardeds[playercnt].begin();
			dit != Discardeds[playercnt].end();
			++dit)
		{
			cout << (*dit)->ToString();
		}
		cout << ")" << endl;
		if (targetind != -1)
		{
			const GameSystem *gsys = this;
			Tile *t = Players[targetind]->ActionAccepted(disc, actcand, const_cast<GameSystem&>(*gsys));
			if (t == NULL)
			{
				assert(Players[targetind]->GetState() == Player::RonWinning);
				// 栄和
				winningPlayer = targetind;
				break;
			}
			else
			{
				assert(Players[targetind]->GetState() != Player::RonWinning);
				Discardeds[targetind].push_back(t);
				playercnt = targetind;
				// 一発が消える
				for (int od = 0; od < 4; od++)
				{
					if(inOneTurn[od] > 0 && inOneTurn[od] < 3)
						inOneTurn[playercnt] += 2;
				}
			}
		}
		playercnt = (playercnt + 1) % 4;
	}
	if (winningPlayer != -1)
	{
		cout << endl;
		if (Players[winningPlayer]->GetState() == Player::TsumoWinning)
			cout << "→プレイヤー " << winningPlayer + 1 << " : 自摸和" << endl;
		else
			cout << "→プレイヤー " << winningPlayer + 1 << " : 栄和" << endl;
		cout << endl;
		vector<WinHand> hands = Players[winningPlayer]->GetWinHands();
		int point = Evaluator::Evaluate(hands, *(Players[winningPlayer]),
			(CriteriaSystem::SpecialWinStyles)
			(((inOneTurn[winningPlayer] == 2 || inOneTurn[winningPlayer] == 4) ? CriteriaSystem::InRiichi : 0) |
			((inOneTurn[winningPlayer] == 1 || inOneTurn[winningPlayer] == 3) ? CriteriaSystem::InDoubleRiichi : 0) |
			((inOneTurn[winningPlayer] == 1 || inOneTurn[winningPlayer] == 2) ? CriteriaSystem::InFirstRound : 0) |
			((Discardeds[winningPlayer].size() == 0 && Players[winningPlayer]->GetState() == Player::TsumoWinning) ? CriteriaSystem::InHeavenlyEarthlyHand : 0) |
			((Players[winningPlayer]->GetState() == Player::RinshanTsumoWinning) ? CriteriaSystem::InKingsTile : 0)));
		if (Players[winningPlayer]->GetState() == Player::TsumoWinning)
		{
			int pareach = 0;
			int each = Evaluator::SplitTsumo(point, Players[winningPlayer]->IsParent(), &pareach);
			int gp = 0;
			for (int p = 0; p < 4; p++)
			{
				if (p == winningPlayer)
					continue;

				gp += Players[p]->IsParent() ? pareach : each;
				Players[p]->SetDiffPoint(-(Players[p]->IsParent() ? pareach : each));
				cout << "プレイヤー" << p + 1 << " -" << (Players[p]->IsParent() ? pareach : each) << endl;
			}
			cout << "プレイヤー" << winningPlayer + 1 << " +" << gp << endl;
		}
		else
		{
			Players[winningPlayer]->SetDiffPoint(point);
			cout << "プレイヤー" << winningPlayer + 1 << " +" << point << endl;
			Players[playercnt]->SetDiffPoint(-point);
			cout << "プレイヤー" << playercnt + 1 << " -" << point << endl;
		}
		return Players[winningPlayer]->IsParent();
	}
	else
	{
		cout << endl << endl << endl;
		cout << "  流局しました。  " << endl;
		cout << endl << endl << endl;
		// ノーテン罰符
		int tempaicnt = 0;
		for (int i = 0; i < 4; i++)
		{
			if (Players[i]->GetState() == Player::TenpaiWaiting ||
				Players[i]->GetState() == Player::Riiching)
				tempaicnt++;
		}
		bool isParentTempaiing = false;
		if (tempaicnt != 4 && tempaicnt != 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (Players[i]->GetState() == Player::TenpaiWaiting ||
					Players[i]->GetState() == Player::Riiching)
				{
					if (tempaicnt == 2)
					{
						Players[i]->SetDiffPoint(1500);
						cout << "プレイヤー" << i + 1 << " +1500" << endl;
					}
					else
					{
						Players[i]->SetDiffPoint(1000);
						cout << "プレイヤー" << i + 1 << " +1000" << endl;
					}
					if (Players[i]->IsParent())
						isParentTempaiing = true;
				}
				else
				{
					if (tempaicnt == 2)
					{
						Players[i]->SetDiffPoint(-1500);
						cout << "プレイヤー" << i + 1 << " -1500" << endl;
					}
					else
					{
						Players[i]->SetDiffPoint(-1000);
						cout << "プレイヤー" << i + 1 << " +1000" << endl;
					}
				}
			}
		}
		return isParentTempaiing;
	}
}

void GameSystem::InitializeCurrentGame()
{
	InitializeTiles();
	// 配牌
	for (int pc = 0; pc < 4; pc++)
	{
		Players[pc]->InitializeGame(
			(GameDefine::Winds)((pc + GameCount) % 4),
			GameDefine::East,
			vector<Tile*>(Tiles.begin() + CurrentPos, Tiles.begin() + CurrentPos + 13));
		CurrentPos += 13;
		Discardeds[pc].clear();
	}
}

void GameSystem::InitializeTiles()
{
	srand((unsigned)time(NULL));

	// 牌のランダムソート
	for (int i = 0; i < Tiles.size(); i++)
	{
		int orig = rand() % Tiles.size();
		int swap = rand() % Tiles.size();
		Tile* otile = Tiles.at(orig);
		Tiles[orig] = Tiles.at(swap);
		Tiles[swap] = otile;
	}
	CurrentPos = 0;
	RinshanPos = 0;

	// ドラのリセット
	Bonuses.clear();
	AddBonusTile();
}

void GameSystem::AddBonusTile()
{
	if (Bonuses.size() == 0)
		cout << "ドラ表示牌:" << Tiles.at(Tiles.size() - 4 - Bonuses.size())->ToString() << endl;
	else
		cout << "追加ドラ表示牌:" << Tiles.at(Tiles.size() - 4 - Bonuses.size())->ToString() << endl;
	Bonuses.push_back(Tiles.at(Tiles.size() - 4 - Bonuses.size()));
}

void GameSystem::Init()
{
	// プレイヤーの初期化
	Players = new Player*[4];
	Players[0] = new UserPlayer();
	Players[1] = new PlayerMachine();
	Players[2] = new PlayerMachine();
	Players[3] = new PlayerMachine();

	for (int i = 0; i < 4; i++)
	{
		Players[i]->SetPoint(25000);
	}

	// 牌の初期化
	for (int c = 0; c < 4; c++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int v = 1; v < 10; v++)
			{
				Tiles.push_back(TileFactory::Create((Tile::TileType)i, v));
			}
		}

		for (int i = 0; i < 7; i++)
		{
			Tiles.push_back(TileFactory::Create(Tile::Honors, i));
		}
	}
	GameCount = 0;
	Carryover = 0;
	Honba = 0;
}

void GameSystem::Dispose()
{
	// プレイヤーの後始末
	for (int i = 0; i < 4; i++)
	{
		delete Players[i];
	}
	delete[] Players;
}

