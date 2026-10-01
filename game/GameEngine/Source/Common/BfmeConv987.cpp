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

// Holder for the GameLogic singleton's dir32 spelling in this TU.
class BfmeLook987
{
};

extern BfmeLook987 *g_bfmeLook987;

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
		reinterpret_cast<GameLogic *>(g_bfmeLook987)->findObjectByID(m_bfmeId));

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
		reinterpret_cast<GameLogic *>(g_bfmeLook987)->findObjectByID(m_bfmeId));

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
		reinterpret_cast<GameLogic *>(g_bfmeLook987)->findObjectByID(m_bfmeId));

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
		reinterpret_cast<GameLogic *>(g_bfmeLook987)->findObjectByID(m_bfmeId));

	if (x) {
		x->bfmeClear987(8, 0);
		m_bfmeId = 0;
	}
}
