#include <vector>
#include <algorithm>
#include <cassert>

#include "TileSystem.h"
#include "UserPlayer.h"
#include "Player.h"
#include "GameDefine.h"
#include "GameSystem.h"
#include "Tile.h"
#include "TileFactory.h"
#include "System.h"

UserPlayer::UserPlayer()
{
	winHandCache = NULL;
}

void UserPlayer::InitializeGame(GameDefine::Winds wind, GameDefine::Winds prevail, vector<Tile*> tile)
{
	if (winHandCache != NULL)
		delete winHandCache;
	winHandCache = NULL;
	DiscardedDb.clear();
	HandyTiles.clear();
	SubOpeneds.clear();
	GrossOpeneds.clear();
	PrevailWind = prevail;
	MyWind = wind;
	MyState = Player::Waiting;
	IsConcealingStill = true;
	for (vector<Tile*>::const_iterator iter = tile.begin();
			iter != tile.end();
			++iter)
	{
		HandyTiles.push_back(*iter);
	}

	cout << "配牌:";
	SortAndShowHandy();
}

// ツモ和了した時に2 カンした時に1を返します
int UserPlayer::GetUserOperation(Tile *cur)
{
	// operation code - argument
	bool canTsumo = false;

	// 0:External kong 1:internal kong
	vector<pair<int, int> > operations;

	// ツモ判定
	if (winHandCache != NULL && winHandCache->size() > 0)
	{
		for (int i = 0; i < winHandCache->size(); i++)
		{
			if ((*winHandCache)[i].Waiting->GetType() == cur->GetType() &&
					(*winHandCache)[i].Waiting->GetValue() == cur->GetValue())
			{

				canTsumo = true;
				break;
			}
		}
	}
	for (int i = 0; i < HandyTiles.size() - 2; i++)
	{
		if (HandyTiles[i]->GetType() == HandyTiles[i + 1]->GetType() &&
				HandyTiles[i]->GetType() == HandyTiles[i + 2]->GetType() &&
				HandyTiles[i]->GetValue() == HandyTiles[i + 1]->GetValue() &&
				HandyTiles[i]->GetValue() == HandyTiles[i + 2]->GetValue()
		   )
		{
			if (i < HandyTiles.size() - 3 &&
					HandyTiles[i]->GetType() == HandyTiles[i + 3]->GetType() &&
					HandyTiles[i]->GetValue() == HandyTiles[i + 3]->GetValue())
			{
				operations.push_back(make_pair(1, i));
			}
			else if(
					HandyTiles[i]->GetType() == cur->GetType() &&
					HandyTiles[i]->GetValue() == cur->GetValue())
			{
				operations.push_back(make_pair(0, i));
			}
		}
	}
	char code = 'a';
	if (!canTsumo && operations.size() == 0)
	{
		cout << "カン・ツモを行えません。" << endl;
		cout << "(Enterキーを押すと戻ります)" << endl;
		System::WaitInput();
		return 0;
	}
	if (canTsumo)
	{
		cout << "a: 自摸和了" << endl;
		code++;
	}
	for (int i = 0; i < operations.size(); i++)
	{
		cout << code << ": カン";
		cout <<
			HandyTiles[operations[i].second]->ToString() <<
			HandyTiles[operations[i].second + 1]->ToString() <<
			HandyTiles[operations[i].second + 2]->ToString();
		if (operations[i].first == 0)
		{
			cout << " + " << cur->ToString();
		}
		else
		{
			cout << HandyTiles[operations[i].second + 3]->ToString();
		}
		cout << endl;
		code++;
	}
	cout << "ピリオド(.)で戻ります" << endl;
	string in;
	cout << "?";
	while(true)
	{
		fflush(stdin);
		cin >> in;
		if (in.size() == 0)
			continue;
		if (in.at(0) == '.')
			return 0;
		int func = in[0] - 'a';
		if (func == 0 && canTsumo)
		{
			MyState = Player::TsumoWinning;
			return 2;
		}
		else
		{
			if (canTsumo)
				func--;

			if (func < operations.size())
			{
				vector<Tile*> elem;
				if(operations.at(func).first == 0)
				{
					elem.push_back(cur);
				}
				else
				{
					elem.push_back(HandyTiles.at(operations[func].second + 3));
					HandyTiles.erase(
							remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(operations[func].second + 3)),
							HandyTiles.end());
				}
				elem.push_back(HandyTiles.at(operations[func].second + 2));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(operations[func].second + 2)),
						HandyTiles.end());
				elem.push_back(HandyTiles.at(operations[func].second + 1));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(operations[func].second + 1)),
						HandyTiles.end());
				elem.push_back(HandyTiles.at(operations[func].second));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(operations[func].second)),
						HandyTiles.end());
				GrossOpeneds.push_back(elem);
				if (operations.at(func).first == 1)
				{
					HandyTiles.push_back(cur);
				}
				return 1;
			}
			else
			{
				cout << "?";
				continue;
			}
		}
	}
}

void UserPlayer::SortAndShowHandy()
{
	sort(HandyTiles.begin(), HandyTiles.end(), Tile::IdSort);
	for (vector<Tile*>::const_iterator iter = HandyTiles.begin();
			iter != HandyTiles.end();
			++iter)
	{
		cout << (*iter)->ToString();
	}
	cout << endl;
}

Tile *UserPlayer::OnDealingTile(Tile *tile, GameSystem& gsys)
{
	if (MyState == Player::Riiching)
	{
		for (int i = 0; i < winHandCache->size(); i++)
		{
			if ((*winHandCache)[i].Waiting->GetType() == tile->GetType() &&
					(*winHandCache)[i].Waiting->GetValue() == tile->GetValue())
			{
				cout << "自摸できます。(y/n)" << endl;
				string in = "";
				while(true)
				{
					cout << "?";
					fflush(stdin);
					cin >> in;
					if (in.size() > 0 && in[0] == 'y')
					{
						MyState = Player::TsumoWinning;
						return NULL;
					}
					else if (in.size() > 0 && in[0] == 'n')
					{
						IsFriten = true;
						DiscardedDb.push_back(tile);
						return tile;
					}
				}
				break;
			}
		}
		DiscardedDb.push_back(tile);
		return tile;
	}

ShowCommands:
	cout << "切る牌を選択してください。" << endl;
	string showchars = "abcdefghijklmn";
	for (int i = 0; i < HandyTiles.size(); i++)
	{
		cout << showchars.at(i) << " ";
	}
	cout << endl;
	SortAndShowHandy();
	cout << "ツモ牌(" << showchars.at(HandyTiles.size()) << "):" << tile->ToString() << endl;
	cout << "(カン・ツモを行うときは、\".\"(ピリオド)を入力してください)" << endl;
	cout << "?";
	string in = "";
	while(true)
	{
		fflush(stdin);
		cin >> in;
		if (in.size() == 0)
			continue;

		switch(in[0])
		{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
				if (in[0] - 'a' > HandyTiles.size())
					continue;
				else if (in[0] - 'a' == HandyTiles.size())
				{
					UpdateWinHand();
					if (IsConcealing() && winHandCache != NULL && winHandCache->size() > 0)
					{
						// 聴牌状態
						cout << "この牌を切ると聴牌です。立直しますか？(y/n)" << endl;
						string in;
						fflush(stdin);
						cin >> in;
						if (in.size() > 0 && in.at(0) == 'y')
							MyState = Player::Riiching;
					}
					DiscardedDb.push_back(tile);
					return tile;
				}
				else
				{
					Tile* ret = HandyTiles.at(in[0] - 'a');
					HandyTiles[in[0] - 'a'] = tile;
					UpdateWinHand();
					if (IsConcealing() && winHandCache != NULL && winHandCache->size() > 0)
					{
						// 聴牌状態
						cout << "この牌を切ると聴牌です。立直しますか？(y/n)" << endl;
						string in;
						fflush(stdin);
						cin >> in;
						if (in.size() > 0 && in.at(0) == 'y')
							MyState = Player::Riiching;
					}
					DiscardedDb.push_back(ret);
					return ret;
				}

			case '.':
				// 追加オプションの表示
				{
					int op = GetUserOperation(tile);
					if (op == 0)
					{
						goto ShowCommands;
					}
					else if (op == 1)
					{
						Tile* rt = gsys.PickRinshan(true);
						if (rt == NULL)
						{
							// 嶺上牌終了
							cout << "嶺上ツモを行えません。" << endl;
							return NULL;
						}
						cout << "嶺上ツモ牌:" << rt->ToString();
						return OnDealingTile(rt, gsys);
					}
					else if (op == 2)
					{
						// 自摸和了
						return NULL;
					}
				}
			default:
				cout << "?";
				continue;
		}
	}
}

Player::Action UserPlayer::OnDiscarded(Tile *discarded, bool chowable)
{
	if (!IsFriten && winHandCache != NULL)
	{
		for (int i = 0; i < winHandCache->size(); i++)
		{
			if ((*winHandCache)[i].Waiting->GetType() == discarded->GetType() &&
					(*winHandCache)[i].Waiting->GetValue() == discarded->GetValue())
			{
				cout << "栄和できます。" << endl;
				cout << "(あなたの手牌:";
				for (vector<Tile*>::iterator iter = HandyTiles.begin();
						iter != HandyTiles.end();
						++iter)
				{
					cout << (*iter)->ToString();
				}
				cout << ")" << endl;
				cout << "栄和しますか？(y/n)" << endl;
				string in = "";
				while(true)
				{
					cout << "?";
					fflush(stdin);
					cin >> in;
					if (in.size() > 0 && in[0] == 'y')
					{
						MyState = Player::TsumoWinning;
						prevAction = Player::Ron;
						return Player::Ron;
					}
					else if (in.size() > 0 && in[0] == 'n')
					{
						IsFriten = true;
						return Player::None;
					}
				}
				break;
			}
		}
	}

	if (MyState == Player::Riiching)
		return Player::None;
	prevAction = Player::None;
	vector<pair<int, Player::Action> > availables = AvailableAction(HandyTiles, discarded, chowable);
	if (availables.size() == 0)
		return Player::None;
	cout << "<!>鳴くことができる牌が切られました。" << endl;
	cout << "(あなたの手牌:";
	for (vector<Tile*>::iterator iter = HandyTiles.begin();
			iter != HandyTiles.end();
			++iter)
	{
		cout << (*iter)->ToString();
	}
	cout << ")" << endl;
	char cand = 'a';
	for (vector<pair<int, Player::Action> >::iterator ait = availables.begin();
			ait != availables.end();
			++ait)
	{
		cout << cand << ": ";
		switch ((*ait).second)
		{
			case Player::Chow:
				assert((*ait).first >= 0 && (*ait).first < HandyTiles.size() - 1);
				cout << "チー -> " <<
					HandyTiles.at((*ait).first)->ToString() <<
					HandyTiles.at((*ait).first + 1)->ToString() <<
					" + " <<
					discarded->ToString() <<
					endl;
				break;

			case Player::Pong:
				assert((*ait).first >= 0 && (*ait).first < HandyTiles.size() - 1);
				cout << "ポン -> " <<
					HandyTiles.at((*ait).first)->ToString() <<
					HandyTiles.at((*ait).first + 1)->ToString() <<
					" + " <<
					discarded->ToString() <<
					endl;
				break;

			case Player::Kong:
				assert((*ait).first >= 0 && (*ait).first < HandyTiles.size() - 2);
				cout << "カン -> " <<
					HandyTiles.at((*ait).first)->ToString() <<
					HandyTiles.at((*ait).first + 1)->ToString() <<
					HandyTiles.at((*ait).first + 2)->ToString() <<
					" + " <<
					discarded->ToString() <<
					endl;
				break;
		}
		cand++;
	}
	cout << ".(ピリオド): キャンセル" << endl;
	string in = "";
	while (true)
	{
		fflush(stdin);
		cin >> in;
		if (in.size() == 0)
			continue;

		if (in[0] == '.')
			return Player::None;

		int func = in[0] - 'a';
		if (func > availables.size())
			continue;

		prevActionArgument = availables.at(func).first;
		prevAction = availables.at(func).second;
		return prevAction;
	}
}

Tile* UserPlayer::ActionAccepted(Tile *discarded, Action accepted, GameSystem& gsys)
{
	IsConcealingStill = false;
	switch (prevAction)
	{
		case Player::Chow:
			{
				vector<Tile*> elem;
				elem.push_back(HandyTiles.at(prevActionArgument + 1));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(prevActionArgument + 1)),
						HandyTiles.end());
				elem.push_back(HandyTiles.at(prevActionArgument));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(prevActionArgument)),
						HandyTiles.end());
				elem.push_back(discarded);
				sort(elem.begin(), elem.end(), Tile::IdSort);
				SubOpeneds.push_back(elem);
				GrossOpeneds.push_back(elem);
			}
			break;
		case Player::Pong:
			{
				vector<Tile*> elem;
				elem.push_back(HandyTiles.at(prevActionArgument + 1));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(prevActionArgument + 1)),
						HandyTiles.end());
				elem.push_back(HandyTiles.at(prevActionArgument));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(prevActionArgument)),
						HandyTiles.end());
				elem.push_back(discarded);
				SubOpeneds.push_back(elem);
				GrossOpeneds.push_back(elem);
			}
			break;
		case Player::Kong:
			{
				vector<Tile*> elem;
				elem.push_back(HandyTiles.at(prevActionArgument + 2));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(prevActionArgument + 2)),
						HandyTiles.end());
				elem.push_back(HandyTiles.at(prevActionArgument + 1));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(prevActionArgument + 1)),
						HandyTiles.end());
				elem.push_back(HandyTiles.at(prevActionArgument));
				HandyTiles.erase(
						remove(HandyTiles.begin(), HandyTiles.end(), HandyTiles.at(prevActionArgument)),
						HandyTiles.end());
				elem.push_back(discarded);
				SubOpeneds.push_back(elem);
				GrossOpeneds.push_back(elem);
				// 嶺上自摸
				Tile* rst = gsys.PickRinshan(false);
				cout << "嶺上ツモ牌:" << rst->ToString() << endl;
				HandyTiles.push_back(rst);
			}
			break;
		case Player::Ron:
			{
				if (winHandCache == NULL || winHandCache->size() == 0)
				{
					cout << "INVALID CALLBACK!: can't ron op" << endl;
					throw exception();
				}
				vector<WinHand>* wh = new vector<WinHand>();
				for (vector<WinHand>::iterator whci = winHandCache->begin();
						whci != winHandCache->end();
						++whci)
				{
					if ((*whci).Waiting->id == discarded->id)
						wh->push_back(*whci);
				}
				delete winHandCache;
				winHandCache = wh;
				MyState = Player::RonWinning;
				return NULL;
			}
			break;
		default:
			cout << "INVALID CALLBACK!" << endl;
			throw exception();
	}
	cout << "切る牌を選択してください。" << endl;
	string showchars = "abcdefghijklmn";
	for (int i = 0; i < HandyTiles.size(); i++)
	{
		cout << showchars.at(i) << " ";
	}
	cout << endl;
	SortAndShowHandy();
	string in = "";
	while(true)
	{
		cout << "?";
		fflush(stdin);
		cin >> in;
		if (in.size() == 0)
			continue;

		switch(in[0])
		{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
				if (in[0] - 'a' >= HandyTiles.size())
				{
					continue;
				}
				else
				{
					Tile* ret = HandyTiles.at(in[0] - 'a');
					HandyTiles.erase(
							remove(HandyTiles.begin(), HandyTiles.end(), ret),
							HandyTiles.end());
					UpdateWinHand();
					DiscardedDb.push_back(ret);
					return ret;
				}
		}
	}

	prevAction = Player::None;
}

void UserPlayer::UpdateWinHand()
{
	if (winHandCache != NULL)
		delete winHandCache;
	IsFriten = false;
	winHandCache = TileSystem::GetWinHandCandidates(HandyTiles, GrossOpeneds);
	if (winHandCache != NULL)
	{
		for (vector<WinHand>::const_iterator iter = winHandCache->begin();
				iter != winHandCache->end();
				++iter)
		{
			for (vector<Tile*>::const_iterator ddi = DiscardedDb.begin();
					ddi != DiscardedDb.end();
					++ddi)
			{
				if ((*iter).Waiting->id == (*ddi)->id)
					IsFriten = true;
			}
		}
	}
}

Player::State UserPlayer::GetState() const
{
	return MyState;
}

GameDefine::Winds UserPlayer::GetWind() const
{
	return MyWind;
}

GameDefine::Winds UserPlayer::GetPrevailingWind() const
{
	return PrevailWind;
}

const vector<vector<Tile*> >& UserPlayer::GetSubTiles() const
{
	return GrossOpeneds;
}

bool UserPlayer::IsConcealing() const
{
	return IsConcealingStill;
}

bool UserPlayer::IsUnconcealedSub(Tile *header) const
{
	for (vector<vector<Tile*> >::const_iterator iter = SubOpeneds.begin();
			iter != SubOpeneds.end();
			++iter)
	{
		if ((*iter).at(0)->id == header->id)
		{
			return true;
		}
	}
	return false;
}

const vector<WinHand>& UserPlayer::GetWinHands() const
{
	return *winHandCache;
}

