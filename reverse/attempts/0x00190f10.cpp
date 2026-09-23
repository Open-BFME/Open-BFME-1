// ?rva00190f10@Rva00190F10Owner@@QAE_NPAXPAVRva00190F10Arg@@@Z
// partial score=0.9522613065326633 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// Retail 0x00190F10, 398 bytes.
//
// BFME split of the tail of Zero Hour's
// PolygonTrigger::ParsePolygonTriggersDataChunk (GameLogic/Map/PolygonTrigger.cpp):
// after the proven guard at 0x00190700 (carved, still a dump; reached through
// j_00013b10) passes, a version-1 chunk (DataChunkInfo::version, the word at
// +8) gets the default water-area trigger: BfmeOwnVVB(id, (void*)4) -- the
// two-argument constructor landed in BfmeOwnVVBConstructors.cpp --, the
// inlined bfmeSetA(true) of Bfme5SmallAccessors.cpp (g_bfmeDirtyBG |= 1; byte
// +0x32 = 1), then four bfmeAppendVector3 corner points
// (-300,-300,7) (X+300,-300,7) (X+300,Y+300,7) (-300,Y+300,7) where X/Y are
// GlobalData's m_waterExtentX/m_waterExtentY (+0x80/+0x84). The node is
// threaded on the +0xc tail cursor through its own +4 link, the +0x10-rooted
// chain is rescanned to keep m_id ahead of every node's +0xc id, and m_id+1 is
// republished into the global id counter g_bfmeBFAE.

#include "ascii_string.h"

class BfmeElemBX
{
public:
	BfmeElemBX();
	~BfmeElemBX();
private:
	char m_body[4];
};

class BfmeOwnVVB;

class BfmeOwnVVBNodeList
{
public:
	BfmeOwnVVBNodeList() : m_nodes(0) {}
	BfmeOwnVVB *m_nodes;		// +0x4 (after the implicit vptr)
};

extern int g_bfmeBFAE;

// upstream layout: Code/GameEngine/Source/Common/BfmeOwnVVBConstructors.cpp
class BfmeOwnVVB : public BfmeOwnVVBNodeList
{
public:
	BfmeOwnVVB(int id, void *arg);
	virtual ~BfmeOwnVVB();

	int getID() const { return m_id; }

private:
	void init(void *arg);
	AsciiString m_name;
	int m_id;					// +0xc
	char *m_owned;
	char m_gap1[0x20];
	AsciiString m_description;
	int m_gap38;
	void *m_extra3c;
	char m_gap40[8];
	BfmeElemBX m_elements[6];
	char m_pad_tail[0x28];		// pads sizeof(BfmeOwnVVB) to retail's 0x88 allocation
};

struct BfmeVector3BG
{
	int x;
	int y;
	int z;
};

extern int g_bfmeDirtyBG;

// upstream layout: Code/GameEngine/Source/Common/Bfme5IndexedVector3Setter.cpp
// and Code/GameEngine/Source/Common/Bfme5SmallAccessors.cpp (bfmeSetA, +0x32)
class Gen_0018F210
{
public:
	void bfmeSetA(bool value)
	{
		g_bfmeDirtyBG |= 1;
		m_bfmeA = value;
	}
	void bfmeAppendVector3(const BfmeVector3BG *value);

private:
	char m_bfmeHead[0x32];		// +0x00
	bool m_bfmeA;				// +0x32
};

struct Rva006C9270GlobalDataXY
{
	unsigned char m_bfmeHead[0x80];
	float m_waterExtentX;		// +0x80
	float m_waterExtentY;		// +0x84
};
extern Rva006C9270GlobalDataXY *TheWritableGlobalData;

// Address-derived: the guard's real class/signature is unproven (its body
// is still a dump), only the call shape (this, argA, argB) -> Bool.
class Rva00190700Guard
{
public:
	bool guard(void *argA, void *argB);	// retail 0x00190700
};

// The second parameter's own +8 word is gated to ==1 before the append
// logic runs (the Zero Hour twin tests DataChunkInfo::version ==
// K_TRIGGERS_VERSION_1 there); the class is not proven in BFME, so only
// that one field is kept.
class Rva00190F10Arg
{
public:
	unsigned char m_pad00[8];
	unsigned short m_flag;		// +0x8
};

class Rva00190F10Owner : public Rva00190700Guard
{
public:
	bool rva00190f10(void *argA, Rva00190F10Arg *argB);

private:
	char m_pad00[0xc];
	BfmeOwnVVB **m_tailCursor;	// +0xc
	BfmeOwnVVB **m_scanCursor;	// +0x10
	int m_id;					// +0x14
};

// ?rva00190f10@Rva00190F10Owner@@QAE_NPAXPAVRva00190F10Arg@@@Z
bool Rva00190F10Owner::rva00190f10(void *argA, Rva00190F10Arg *argB)
{
	if (!guard(argA, argB))
		return false;

	if (argB->m_flag == 1)
	{
		BfmeOwnVVB *node = new BfmeOwnVVB(m_id++, (void *)4);
		((Gen_0018F210 *)node)->bfmeSetA(true);

		BfmeVector3BG vec;
		vec.x = -300;
		vec.y = -300;
		vec.z = 7;
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);
		vec.x = 300 + TheWritableGlobalData->m_waterExtentX;
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);
		vec.y = 300 + TheWritableGlobalData->m_waterExtentY;
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);
		vec.x = -300;
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);

		*m_tailCursor = node;
		m_tailCursor = &node->m_nodes;
	}

	while (*m_scanCursor)
	{
		if ((*m_scanCursor)->getID() > m_id)
			m_id = (*m_scanCursor)->getID();
		m_scanCursor = *m_scanCursor ? &(*m_scanCursor)->m_nodes : 0;
	}

	if (m_id + 1 > g_bfmeBFAE)
		g_bfmeBFAE = m_id + 1;

	g_bfmeDirtyBG |= 1;
	return true;
}
