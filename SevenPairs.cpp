#include <vector>
#include <cassert>
#include <iostream>

#include "Tile.h"
#include "WinHand.h"
#include "TileFactory.h"
#include "SevenPairs.h"


// ���л��Ԥ�Ƚ��
// ɬ��ñ���Ԥ��ʤΤǡ�Tile�ؤΥݥ��󥿤�NULL���֤�

WinHand* SevenPairs::CheckWait(const vector<Tile*>& tiles)
{
	bool odd = true;
	bool identifiedWait = false;
	Tile* waitCandidate = NULL;
	Tile* curTile = NULL;

	WinHand* wh = new WinHand();
	// 13�פ�Ƚ��
	assert(tiles.size() == 13);

	for (vector<Tile*>::const_iterator itr = tiles.begin();
		itr != tiles.end();
		++itr)
	{
		if (odd)
		{
			//cout << "odd:" << (*itr)->ToString() << endl;
			// odd
			if (curTile != NULL)
			{
				// error
				// �ʻ�/��Ҥ�¸�ߤ�����ϼ��лҤˤʤ����ʤ�
				if (curTile->id == (*itr)->id)
				{
					if (waitCandidate != NULL)
					{
						// ���Ǥ˼��������Ԥ��ץ��󥹥��󥹤κ��
						TileFactory::Delete(waitCandidate);
					}
					delete(wh);
					//cout << "failed(0)" << endl;
					return NULL;
				}
			}
			curTile = (*itr);
		}
		else
		{
			//cout << "even:" << (*itr)->ToString() << endl;

			// even
			// 
			if (curTile->id != (*itr)->id)
			{
				if (waitCandidate != NULL)
				{
					// �лҤ���ʤ����䤬�⤦����褿

					// ���Ǥ˼��������Ԥ��ץ��󥹥��󥹤κ��
					TileFactory::Delete(waitCandidate);
					delete(wh);
					//cout << "failed(1)" << endl;
					return NULL;
				}
				else
				{
					// �Ԥ��פϤޤ����ꤷ�Ƥ��ʤ�
					// ����curTile���ؤ��Ƥ����פ�Ʊ����פ��Ԥ���
					waitCandidate = TileFactory::Create(curTile->GetType(), curTile->GetValue());
					
					vector<Tile*> pushvec;
					pushvec.push_back(curTile);
					pushvec.push_back(waitCandidate);
					wh->Tiles.push_back(pushvec);

					// �⤦����even�������̤�
					curTile = (*itr);
					continue;
				}
			}
			else
			{
				// �лҤǤ�ok
				vector<Tile*> pushvec;
				pushvec.push_back(curTile);
				pushvec.push_back(*itr);
				wh->Tiles.push_back(pushvec);
			}
		}
		odd = !odd;
	}
	// 13�פʤΤǡ��Ǹ��odd�ǽ����
	if (waitCandidate == NULL)
	{
		// �Ǹ�������Ԥ���
		waitCandidate = TileFactory::Create(curTile->GetType(), curTile->GetValue());
		vector<Tile*> pushvec;
		pushvec.push_back(curTile);
		pushvec.push_back(waitCandidate);
		wh->Tiles.push_back(pushvec);
	}
	wh->Waiting = waitCandidate;
	return wh;
}

bool SevenPairs::Check(const WinHand& hand, const Player& player)
{
	// ���лҤΤȤ��Τ�hand x 7�Ȥʤ�
	return hand.Tiles.size() == 7;
}

int SevenPairs::GetRank(bool concealing)
{
	return 1;
}

string SevenPairs::GetName()
{
	return "���л�";
}

