// ?rva00190f10@Rva00190F10Owner@@QAE_NPAXPAVRva00190F10Arg@@@Z
// partial score=0.46 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// Retail 0x00190F10, 398 bytes.
//
// After the proven guard at 0x00190700 (Code/gen carved row, still a dump;
// reached through j_00013b10) passes, this allocates and constructs a
// BfmeOwnVVB(id, (void*)4) -- same two-argument constructor landed at
// Code/GameEngine/Source/Common/BfmeOwnVVBConstructors.cpp -- appends four
// BfmeVector3BG values through the already-landed
// Code/GameEngine/Source/Common/Bfme5IndexedVector3Setter.cpp inline
// (reusing one scratch BfmeVector3BG with only the X component overwritten
// for two of the four appends, matching the retail partial-store pattern),
// threads the new node onto this-relative +0xc via its own inherited
// m_nodes field (a singly-linked chain built through each node's own +4
// slot, exactly the tail-cursor idiom BfmeOwnVVBConstructors/Destructor
// already prove), then rescans the +0x10-rooted chain to keep m_id ahead of
// every node's own m_id and republishes that into the global id counter
// g_bfmeBFAE (0x012ACB4C) and the dirty flag g_bfmeDirtyBG (0x012EF418).

typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "string_base.h"

inline void *operator new(unsigned int, void *p) { return p; }

class AsciiString : public StringBase<char>
{
public:
	AsciiString() { }
	~AsciiString() { }
};

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
class Gen_0018F210
{
public:
	void bfmeAppendVector3(const BfmeVector3BG *value);
};

struct Rva006C9270GlobalDataXY
{
	unsigned char m_bfmeHead[0x80];
	float m_x;			// +0x80
	float m_y;			// +0x84
};
extern Rva006C9270GlobalDataXY *TheWritableGlobalData;

// Address-derived: the guard's real class/signature is unproven (its body
// is still a dump), only the call shape (this, argA, argB) -> Bool.
class Rva00190700Guard
{
public:
	Bool guard(void *argA, void *argB);	// retail 0x00190700
};

// The second parameter's own +8 word is gated to ==1 before the append
// logic runs; the owning class is unproven, so only that one field is kept.
class Rva00190F10Arg
{
public:
	unsigned char m_pad00[8];
	unsigned short m_flag;		// +0x8
};

class Rva00190F10Owner : public Rva00190700Guard
{
public:
	Bool rva00190f10(void *argA, Rva00190F10Arg *argB);

private:
	char m_pad00[0xc];
	BfmeOwnVVB **m_tailCursor;	// +0xc
	BfmeOwnVVB **m_scanCursor;	// +0x10
	int m_id;					// +0x14
};

// ?rva00190f10@Rva00190F10Owner@@QAE_NPAXPAURva00190F10Arg@@@Z
Bool Rva00190F10Owner::rva00190f10(void *argA, Rva00190F10Arg *argB)
{
	if (!guard(argA, argB))
		return false;

	const unsigned short one = 1;
	if (argB->m_flag == one)
	{
		BfmeOwnVVB *node = new BfmeOwnVVB(m_id, (void *)4);
		m_id = m_id + 1;

		g_bfmeDirtyBG |= 1;

		BfmeVector3BG vec;
		vec.x = -300;
		vec.y = -300;
		vec.z = 7;
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);

		vec.x = (int)(TheWritableGlobalData->m_x + 300.0f);
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);

		vec.x = (int)(TheWritableGlobalData->m_y + 300.0f);
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);

		vec.x = -300;
		((Gen_0018F210 *)node)->bfmeAppendVector3(&vec);

		*m_tailCursor = node;
		m_tailCursor = &node->m_nodes;
	}

	if (*m_scanCursor != 0)
	{
		do
		{
			BfmeOwnVVB *scanNode = *m_scanCursor;
			if (scanNode != 0)
			{
				int scanId = *(int *)((char *)scanNode + 0xc);
				if (scanId > m_id)
					m_id = scanId;
			}

			m_scanCursor = scanNode ? &scanNode->m_nodes : 0;
		} while (m_scanCursor != 0 && *m_scanCursor != 0);
	}

	if (m_id + 1 > g_bfmeBFAE)
		g_bfmeBFAE = m_id + 1;

	g_bfmeDirtyBG |= one;
	return one != 0;
}
