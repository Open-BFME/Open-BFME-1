struct BfmeNodeABA
{
	unsigned char m_bfmeHeadABA[0x14];
	unsigned int m_bfme14ABA;
};

struct BfmeIterABA
{
	BfmeNodeABA *m_bfmeNodeABA;
};

class BfmeListABA
{
public:
	BfmeNodeABA *m_bfmeHeadABA;
};

// The list-range helper this progress query reaches is an ILT thunk in retail:
// the call at +0x19 of the 0x00224440 body lands on ?j_0001c017@@YAXXZ
// (0x0001C017), whose matched five-byte body lives in
// game/gen_small/thunks_013.cpp.  That decorated symbol is what the call must
// relocate against; VC7.1 reserves __thiscall in a free-function-pointer
// typedef, so the pointer-to-member cast idiom (as BfmeConv1002.cpp uses for
// the same ?j_0003f5da ILT) keeps the proven shape: ECX holds the list and
// the two arguments stay on the stack for the callee to pop.
extern void j_0001c017();
struct BfmeRangeThunkABA
{
	void Call(BfmeIterABA *first, BfmeIterABA *last);
};
typedef void (BfmeRangeThunkABA::*BfmeRangeCallABA)(
	BfmeIterABA *first, BfmeIterABA *last);

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadLABA[0x3c];
	unsigned int m_bfme3CABA;
};

class GameLogic;

// retail 0x012F0898; the TU-local view above is Rva00367E30Logic
extern GameLogic *TheGameLogic;

struct BfmeOwnerABA
{
	unsigned char m_bfmeHeadOABA[0x164];
	unsigned int m_bfme164ABA;
};

class BfmeHostABA
{
public:
	int bfmeProgressABA(BfmeIterABA last);
};

int BfmeHostABA::bfmeProgressABA(BfmeIterABA last)
{
	BfmeOwnerABA *o = *(BfmeOwnerABA **)((char *)this - 0x1c);
	BfmeListABA *l = (BfmeListABA *)((char *)this + 0xa8);
	BfmeIterABA first;

	union { void (*asFunction)(); BfmeRangeCallABA asMember; } fnCast;
	fnCast.asFunction = j_0001c017;
	(reinterpret_cast<BfmeRangeThunkABA *>(l)->*fnCast.asMember)(&first, &last);

	if (first.m_bfmeNodeABA == l->m_bfmeHeadABA)
		return 100;

	unsigned int elapsed =
		((Rva00367E30Logic *)TheGameLogic)->m_bfme3CABA - first.m_bfmeNodeABA->m_bfme14ABA;
	unsigned int limit = o->m_bfme164ABA;

	if (elapsed > limit)
		return 100;

	if (elapsed == 0)
		return 0;

	if (limit != 0)
		return (int)((float)elapsed / (float)limit * 100.0f);

	return 100;
}
