#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>

#include "Tile.h"
#include "TileSystem.h"


using namespace std;

int main()
{
	string input;
	cout << "Input 13 tiles" << endl;
	cout << "(you can write (1-9)(pms), nswepgr(TNSPWHC) )" << endl;
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

	vector<Criteria>* c = TileSystem::GetCriteriaCandidates(
		tilev, vector<vector<Tile*> >());

	cout << endl << endl << "Candidates:" << endl;
	if ( c != NULL)
	{
		for (vector<Criteria>::iterator iter = c->begin();
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
					cout << (*tit)->ToString();
				}
				cout << " ";
			}
			// 当たり牌
			cout << endl;
			cout << "Waiting:" << iter->Waiting->ToString() << endl << endl;
		}

		cout << "Your waits:";
		vector<Tile*> waits;
		for (vector<Criteria>::iterator iter = c->begin();
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
			cout << (*iter)->ToString() << " ";
		cout << endl;
	}
	else
	{
		cout << "None." << endl;
	}
	delete(c);
	for (list<Tile*>::iterator iter = tilev.begin();
		iter != tilev.end();
		++iter)
	{
		delete(*iter);
	}
	fflush(stdin);
	cout << "Press enter key to exit..." << endl;
	int i = getchar();
	return 0;
}

