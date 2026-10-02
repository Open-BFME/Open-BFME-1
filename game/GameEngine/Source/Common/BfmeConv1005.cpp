// Open-BFME5 conversions.
// cl: /DNDEBUG /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/StateMachine.h"
#define OBJECT_TU_MEMBERS void bfmeWakeAutoPickup(int runFromButtonNumber);
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class BfmeItem1005;

// ILT 0x00007513 routes to the body owned by BfmeConv916.cpp.
class BfmeThing916D
{
public:
	void bfmeGo916D(void *a);
};

struct BfmeNode1005
{
	BfmeNode1005 *m_bfmeNext;
	char m_bfmePad[4];
	BfmeItem1005 *m_bfmeItem;
};

class BfmeList1005
{
public:
	void bfmeGoC1005(int a);
	void bfmeGoD1005(int a);

	char m_bfmePad[4];
	BfmeNode1005 *m_bfmeHead;
};

void BfmeList1005::bfmeGoC1005(int a)
{
	for (BfmeNode1005 *n = m_bfmeHead->m_bfmeNext; n != m_bfmeHead; n = n->m_bfmeNext)
		((Object *)n->m_bfmeItem)->bfmeWakeAutoPickup(a);
}

void BfmeList1005::bfmeGoD1005(int a)
{
	for (BfmeNode1005 *n = m_bfmeHead->m_bfmeNext; n != m_bfmeHead; n = n->m_bfmeNext)
		((BfmeThing916D *)n->m_bfmeItem)->bfmeGo916D((void *)a);
}

class BfmeMgr1005
{
public:
	virtual void bfmeVM01005();
	virtual void bfmeVM11005();
	virtual void bfmeVM21005();
	virtual void bfmeVM31005();
	virtual void bfmeVM41005();
	virtual void bfmeVM51005();
	virtual void bfmeVM61005();
	virtual void bfmeVM71005();
	virtual void bfmeVM81005();
	virtual void bfmeVM91005();
	virtual void bfmeVM101005();
	virtual void bfmeVM111005();
	virtual void bfmeVM121005();
	virtual void bfmeSet1005(int u, int n);
};

struct BfmeGoal1005
{
	char m_bfmePad[0x74];
	int m_bfmeId;
	char m_bfmePad2[0x184];
	BfmeMgr1005 *m_bfmeMgr;
};

class BfmeHold1005
{
public:
	char m_bfmePad[0x10];
	int m_bfmeUnit;
};

class BfmeE1005
{
public:
	int bfmeGoE1005();
	int bfmeGoF1005();

	char m_bfmePad[0x1c];
	BfmeHold1005 *m_bfmeHold;
	char m_bfmePad2[4];
	int m_bfmeSlot;
};

int BfmeE1005::bfmeGoE1005()
{
	BfmeHold1005 *h = m_bfmeHold;

	m_bfmeSlot = 0;

	int u = h->m_bfmeUnit;
	BfmeGoal1005 *g = (BfmeGoal1005 *)((StateMachine *)h)->getGoalObject();

	if (g) {
		BfmeMgr1005 *m = g->m_bfmeMgr;

		if (m) {
			m->bfmeSet1005(u, 1);
			m_bfmeSlot = g->m_bfmeId;
		}

		return 0;
	}

	return -2;
}

int BfmeE1005::bfmeGoF1005()
{
	BfmeHold1005 *h = m_bfmeHold;

	m_bfmeSlot = 0;

	int u = h->m_bfmeUnit;
	BfmeGoal1005 *g = (BfmeGoal1005 *)((StateMachine *)h)->getGoalObject();

	if (g) {
		BfmeMgr1005 *m = g->m_bfmeMgr;

		if (m) {
			m->bfmeSet1005(u, 1);
			m_bfmeSlot = g->m_bfmeId;
		}

		return 0;
	}

	return -2;
}
