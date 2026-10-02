// stlport
// Open-BFME5 conversions.

// The lookup below is GameLogic::findObjectByID; GameLogicObjectLookup.h holds
// the declaration (its body stays in Thing/GameLogicFindObjectByID.cpp).
#include "Thing/GameLogicObjectLookup.h"

struct BfmeX987
{
	char m_bfmePad[0x74];
	int m_bfmeId;
};

// Retail's GameLogic singleton; only GameLogic.cpp defines it.  GameLogic
// comes from the GameLogicObjectLookup.h view included above.
extern GameLogic *TheGameLogic;

class BfmeA987
{
public:
	void bfmeGo987A();
	void bfmeGo987B();
	void bfmeBase987();

	char m_bfmePad[0x20];
	int m_bfmeId;
};

void BfmeA987::bfmeGo987A()
{
	bfmeBase987();

	BfmeX987 *x = reinterpret_cast<BfmeX987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		m_bfmeId = x->m_bfmeId;
		return;
	}

	m_bfmeId = 0;
}

void BfmeA987::bfmeGo987B()
{
	bfmeBase987();

	BfmeX987 *x = reinterpret_cast<BfmeX987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		m_bfmeId = x->m_bfmeId;
		return;
	}

	m_bfmeId = 0;
}

class BfmeDrop987
{
public:
	void bfmeClear987(int a, int b);
};

class BfmeC987
{
public:
	void bfmeGo987C();

	char m_bfmePad[0x24];
	int m_bfmeId;
};

void BfmeC987::bfmeGo987C()
{
	BfmeDrop987 *x = reinterpret_cast<BfmeDrop987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		x->bfmeClear987(8, 0);
		m_bfmeId = 0;
	}
}

class BfmeD987
{
public:
	void bfmeGo987D(int unused);

	char m_bfmePad[4];
	int m_bfmeId;
};

void BfmeD987::bfmeGo987D(int unused)
{
	BfmeDrop987 *x = reinterpret_cast<BfmeDrop987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		x->bfmeClear987(8, 0);
		m_bfmeId = 0;
	}
}
