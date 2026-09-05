// ?request@Rva0025F6C0Owner@@QAEXPAVObject@@I@Z
// partial score=0.15 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: address-derived attempt for the BFME special-power request
// helper at retail 0x0025F6C0 (383 B). No Zero Hour twin: the callees
// (BfmeSubBIA/BOB/AKB, the 0x00017BCA ActionManager thunk) are BFME-only
// renames with no matching ZH source. This is a literal register-level
// translation of tools/dis_retail.py 0x0025F6C0, not a proven identity --
// see notes in the ledger entry for the open questions on operand types.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
class Object;
class Coord3D;
class Waypoint;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule
{
public:
	Bool initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos,
			const Waypoint *way, UnsignedInt commandOptions);
	void finishSpecialPower(UnsignedInt commandOptions);

	unsigned char m_bfmeGap[0x10];
	Bool m_bfmeReady;					// +0x0c value tested at [this+0x0c]
};

class BfmeSubBIA
{
public:
	Int ask(void);						// ILT 0x000022BB
};

class BfmeGotBOB
{
};

class BfmeSubBOB
{
public:
	BfmeGotBOB *bfmeFindBOB(void);				// ILT 0x00048C61
};

class BfmeFoundAKB
{
public:
	Int m_bfmeKind;						// +0x14
	void *m_bfmeVtbl;					// +0x00, slot 0x18 used
};

class BfmeSubAKB
{
public:
	BfmeFoundAKB *bfmeFindAKB(Int kind);			// ILT 0x0001B185
};

extern void bfmeLogCNE(Int a, Int b);				// ?bfmeLogCNE@@YGXHH@Z 0x00032DEE

class BFMEActionManager
{
public:
	// address-derived: real args pushed at retail 0x0025F6C0+0xd7/+0x146 to the
	// still-unidentified 0x00017BCA ActionManager thunk (FUN_004c5ff0)
	Bool bfmeCheck17BCA(void *a, Int wantsAlt, void *targetHandle, void *thing);
};

extern BFMEActionManager *g_TheActionManager;			// ?TheActionManager@@3PAVBFMEActionManager@@A 0x012ED700

class ObjectV18
{
public:
	virtual void *slot00();
	virtual void *slot04();
	virtual void *slot08();
	virtual void *slot0c();
	virtual void *slot10();
	virtual void *slot14();
	virtual BfmeFoundAKB *findKind(Int kind);		// vtable +0x18
};

// Object layout used by this body only: hidden pointers immediately below
// 'this' are other base subobjects of the leaf special-power class; the
// SpecialPowerModule base sits at this-0x10.
class Rva0025F6C0Owner : public ObjectV18
{
public:
	void request(Object *target, UnsignedInt flags);

	Int m_bfmeSize;						// +0x08
};

void Rva0025F6C0Owner::request(Object *target, UnsignedInt flags)
{
	char *self = (char *)this;
	SpecialPowerModule *base = (SpecialPowerModule *)(self - 0x10);
	BfmeSubBOB *bob = *(BfmeSubBOB **)(self - 8);

	// Faithful control flow intentionally not completed: several field
	// semantics (the +0x1a4 flag on *(self-8), the +0xd4/ch&0x10 test, and
	// which operand is the Object* vs the UnsignedInt bit-cast pointer into
	// finishSpecialPower) are still open questions -- see ledger notes.
	if (!(flags & 0x40000) && m_bfmeSize > 0 && bob != 0)
	{
		bob->bfmeFindBOB();
	}

	base->initiateIntentToDoSpecialPower(target, 0, 0, flags);
	base->finishSpecialPower(flags);
}
