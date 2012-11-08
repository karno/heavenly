#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>

#include "Player.h"
#include "PlayerMachine.h"
#include "CriteriaSystem.h"
#include "GameSystem.h"

#include "Evaluator.h"
#include "Tile.h"
#include "TileSystem.h"
#include "TileFactory.h"

using namespace std;

int main()
{
	GameSystem gs;
	gs.GameMain();
	return 0;

	string input;
	cout << "13牌入力してください。" << endl;
	cout << "(入力は (1-9)(pms), nswepgr(TNSPWHC) で行えます)" << endl;
	cout << ":";
	cin >> input;

	list<Tile*> tilev;
	vector<string>* iterptr = Tile::SplitTileArray(input);
	if(iterptr)
	{
		vector<string>::iterator iter = iterptr->begin();
		while(iter != iterptr->end())
		{
			Tile *t = Tile::ParseString(*iter);
			if(t)
			{
				cout << t->ToString();
				tilev.push_back(t);
			}
			else
			{
				cout << "Unknown:" << *iter << endl;
			}
			++iter;
		}
	}
	else
	{
		cout << "Invalid input" << endl;
	}
	cout << endl;
	delete(iterptr);

	vector<Tile*> lisvec(tilev.begin(), tilev.end());
	sort(lisvec.begin(), lisvec.end(), Tile::IdSort);
	vector<WinHand>* c = TileSystem::GetWinHandCandidates(
		tilev, vector<vector<Tile*> >());

	cout << endl << endl << "Candidates:" << endl;
	CriteriaSystem::Initialize();
	if ( c != NULL)
	{
		PlayerMachine p;
		for (vector<WinHand>::iterator iter = c->begin();
			iter != c->end();
			++iter)
		{
			// 面子のイテレーション
			for (vector<vector<Tile*> >::iterator tsit = iter->Tiles.begin();
				tsit != iter->Tiles.end();
				++tsit)
			{
				for(vector<Tile*>::iterator tit = tsit->begin();
					tit != tsit->end();
					++tit)
				{
					if (iter->Waiting->GetGid() == (*tit)->GetGid())
						cout << "[" << (*tit)->ToString() << "]";
					else
						cout << (*tit)->ToString();
				}
				cout << " ";
			}
			// 当たり牌
			cout << endl;
			cout << "Waiting:" << iter->Waiting->ToString() << endl << endl;

			vector<Criteria*> val = CriteriaSystem::CheckCriterias(*iter, p, CriteriaSystem::None);
			for (vector<Criteria*>::iterator cit = val.begin();
				cit != val.end();
				++cit)
			{
				cout << (*cit)->GetName() << ":" << (*cit)->GetRank(true) << endl;
			}
			cout << endl;
		}

		cout << "***********************************************" << endl;
		cout << "あなたの待ちは:" << endl;
		vector<Tile*> waits;
		for (vector<WinHand>::iterator iter = c->begin();
			iter != c->end();
			++iter)
		{
			waits.push_back(iter->Waiting);
		}

		sort(waits.begin(), waits.end(), Tile::IdSort);
		vector<Tile*>::iterator uend = unique(waits.begin(), waits.end(), Tile::IdUnique);
		waits.erase(uend, waits.end());

		for (vector<Tile*>::iterator iter = waits.begin();
			iter != waits.end();
			++iter)
		{
			cout << (*iter)->ToString() << " " << endl;
			cout << "この牌で和了すると(親、自摸) >> " << endl;
			vector<WinHand> twh;
			for (vector<WinHand>::iterator whi = c->begin();
				whi != c->end();
				++whi)
			{
				if ((*whi).Waiting->GetType() == (*iter)->GetType() &&
					(*whi).Waiting->GetValue() == (*iter)->GetValue())
					twh.push_back(*whi);
			}
			PlayerMachine p;
			cout << Evaluator::Evaluate(twh, p, CriteriaSystem::None) << "点" << endl;
			cout << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "待ちが見つかりませんでした。" << endl;
	}
	CriteriaSystem::Dispose();
	delete(c);
	for (list<Tile*>::iterator iter = tilev.begin();
		iter != tilev.end();
		++iter)
	{
		delete(*iter);
	}
	cout << "何か入力すると終了します..." << endl;
	fflush(stdin);
	int i = getchar();
	TileFactory::Destroy();
	return 0;
}

