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

// The two ILT thunks retail calls through.  0x00015E0B is the sub-object
// base call whose chain ends at the no-op UpdateModule::loadPostProcess body
// (0x001EF410; see S3LoadPostProcessChains.cpp), 0x00014506 the thunk to
// Object::kill (0x001C30F0).  Both are thiscall, receiver in ecx, so each is
// reached through the union / pointer-to-member shape the LivingWorld bodies
// use: the thunk address is a compile-time constant, so the call stays direct
// and lands on the thunk retail's own call lands on.
extern void j_00015e0b();
extern void j_00014506();

class BfmeA987
{
public:
	void bfmeGo987A();
	void bfmeGo987B();

	char m_bfmePad[0x20];
	int m_bfmeId;
};

void BfmeA987::bfmeGo987A()
{
	BfmeA987 *owner = this;
	union { void (*raw)(); void (BfmeA987::*member)(); } base;
	base.raw = ::j_00015e0b;
	(owner->*base.member)();

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
	BfmeA987 *owner = this;
	union { void (*raw)(); void (BfmeA987::*member)(); } base;
	base.raw = ::j_00015e0b;
	(owner->*base.member)();

	BfmeX987 *x = reinterpret_cast<BfmeX987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		m_bfmeId = x->m_bfmeId;
		return;
	}

	m_bfmeId = 0;
}

// The receiver of the Object::kill thunk: a thiscall with two int arguments.
class BfmeDrop987
{
public:
	char m_bfmePad[4];
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
	union { void (*raw)(); void (BfmeDrop987::*member)(int, int); } clear;
	BfmeDrop987 *x = reinterpret_cast<BfmeDrop987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		clear.raw = ::j_00014506;
		(x->*clear.member)(8, 0);
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
	union { void (*raw)(); void (BfmeDrop987::*member)(int, int); } clear;
	BfmeDrop987 *x = reinterpret_cast<BfmeDrop987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		clear.raw = ::j_00014506;
		(x->*clear.member)(8, 0);
		m_bfmeId = 0;
	}
}
