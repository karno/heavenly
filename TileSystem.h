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


// �פν����˴ؤ��륹���ƥ��å����饹
class TileSystem
{

public:

	// ��θ����������ޤ���
	// list�����Ǥ���Ĥ�̵������İ�פ��Ƥ��ޤ���
	// subs����Ϫ���줿�פ���ꤷ�ޤ���
	static vector<WinHand>* GetWinHandCandidates(
		const list<Tile*>& tile, const vector<vector<Tile*> >& subs);

	// ��θ����������ޤ���
	// list�����Ǥ���Ĥ�̵������İ�פ��Ƥ��ޤ���
	// subs����Ϫ���줿�פ���ꤷ�ޤ���
	static vector<WinHand>* TileSystem::GetWinHandCandidates(
		vector<Tile*>& tile, const vector<vector<Tile*> >& subs);


private:

	// inactive�ե饰��Ω�äƤ��ʤ��ץ��֥������ȤθĿ���������ޤ���
	static int GetActivatesCount(const vector<Tile*>& tiles);

	// ��������å��Υ����ƥ��������ޤ���
	static void FreeStackItem(vector<Tile*>* item);

	// ��θ����������ޤ���
	// ��Ƭ�����Ǥ����ꤵ��Ƥ�����֤����Ѥ��ޤ���
	static vector<WinHand>* GetCandidatesInner(
		const vector<Tile*>& sorted,
		const vector<Tile*>& head,
		const vector<vector<Tile*> >& subs);


	// �פΥ��å�(���)��������ޤ���
	static vector<Tile*>* GetSets(
		const vector<Tile*>& sorted, int& pos);

	// �פΥ�������(���)��������ޤ���
	static vector<Tile*>* GetSequences(
		const vector<Tile*>& sorted, int& pos);

	// ��α�פ��̻Ҥ�����ǽ��Ƚ�ꤷ�ޤ���
	// ������ǽ�ʾ�硢��İʾ���Ԥ��פȤ����̻ҹ�����
	// �٥����Ȥ����ֵѤ���ޤ���
	static vector<pair<Tile*, vector<Tile*> > >* GetRemainHands(
		const vector<Tile*>& sorted);
};

#endif

