#ifndef __C_TILE_SYSTEM__
#define __C_TILE_SYSTEM__

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "Tile.h"
#include "WinHand.h"

using namespace std;


// 牌の処理に関するスタティッククラス
class TileSystem
{

public:

	// 役の候補を取得します。
	// listの要素が一つも無い場合は聴牌していません。
	// subsに副露された牌を指定します。
	static vector<WinHand>* GetWinHandCandidates(
		const list<Tile*>& tile, const vector<vector<Tile*> >& subs);

	// 役の候補を取得します。
	// listの要素が一つも無い場合は聴牌していません。
	// subsに副露された牌を指定します。
	static vector<WinHand>* TileSystem::GetWinHandCandidates(
		vector<Tile*>& tile, const vector<vector<Tile*> >& subs);


private:

	// inactiveフラグが立っていない牌オブジェクトの個数を取得します。
	static int GetActivatesCount(const vector<Tile*>& tiles);

	// ワークスタックのアイテムを解放します。
	static void FreeStackItem(vector<Tile*>* item);

	// 役の候補を取得します。
	// 雀頭がすでに設定されている状態で利用します。
	static vector<WinHand>* GetCandidatesInner(
		const vector<Tile*>& sorted,
		const vector<Tile*>& head,
		const vector<vector<Tile*> >& subs);


	// 牌のセット(刻子)を取得します。
	static vector<Tile*>* GetSets(
		const vector<Tile*>& sorted, int& pos);

	// 牌のシーケンス(順子)を取得します。
	static vector<Tile*>* GetSequences(
		const vector<Tile*>& sorted, int& pos);

	// 残留牌で面子を構成可能か判定します。
	// 構成可能な場合、一つ以上の待ち牌とその面子構成が
	// ベクタとして返却されます。
	static vector<pair<Tile*, vector<Tile*> > >* GetRemainHands(
		const vector<Tile*>& sorted);
};

#endif

