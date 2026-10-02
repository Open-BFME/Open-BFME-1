// ?drop@Rva002AFFA0Owner@@QAEXPAX@Z
// Secondary base at this-0x20: check DieMuxData, mark the object's AI dead,
// deselect the object and begin the structure topple.

class Object;
class DamageInfo;

// Retail ILTs 000357D8, 00025BFD, 0001EC2C and 0003EA22 route to the
// ledger-owned methods at 002551F0, 0026EE80, 00382F50 and 002AFD30.
// Keep the local layout views; single-inheritance member pointers below give
// these existing symbols their __thiscall ABI without redeclaring EA classes.
extern "C" void __cdecl __identifier("?isDieApplicable@DieMuxData@@QBE_NPBVObject@@PBVDamageInfo@@@Z")();
extern "C" void __cdecl __identifier("?markAsDead@AIUpdateInterface@@QAEXXZ")();
extern "C" void __cdecl __identifier("?deselectObject@GameLogic@@QAEXPAVObject@@G_N@Z")();
extern "C" void __cdecl __identifier("?beginStructureTopple@StructureToppleUpdate@@IAEXPBVDamageInfo@@@Z")();

class BfmeHookXG
{
};

class BfmeUnitXG
{
public:
	unsigned char m_bfmeHeadXG[0x204];
	BfmeHookXG *m_bfmeHookXG;
};

struct BfmeSubXG
{
};

class Rva002AFFA0Holder
{
public:
	void *m_bfmeFrontXG[2];
	BfmeSubXG m_bfmeSubXG;
};

// TU-local view of the retail GameLogic; the global itself is the canonical
// ?TheGameLogic@@3PAVGameLogic@@A from GameLogic/System/GameLogic.cpp.
class GameLogic;

class BfmeLogicXG
{
};

extern GameLogic *TheGameLogic;

class BfmeOuterXG
{
public:
	unsigned char m_bfmeStartXG[4];
	Rva002AFFA0Holder *m_bfmeHolderXG;
	BfmeUnitXG *m_bfmeUnitXG;
};

class Rva002AFFA0Owner
{
public:
	void drop(void *arg);
};

// The holder and the unit must be named locals so the allocator claims eax for
// the holder and ecx for the unit; the three later unit reads must stay inline
// so deselectObject loads its receiver global after the argument pushes.
void Rva002AFFA0Owner::drop(void *arg)
{
	union {
		void (*address)();
		bool (BfmeSubXG::*member)(const Object *, const DamageInfo *) const;
	} test = { __identifier("?isDieApplicable@DieMuxData@@QBE_NPBVObject@@PBVDamageInfo@@@Z") };
	union {
		void (*address)();
		void (BfmeHookXG::*member)();
	} markAsDead = { __identifier("?markAsDead@AIUpdateInterface@@QAEXXZ") };
	union {
		void (*address)();
		void (BfmeLogicXG::*member)(Object *, unsigned short, bool);
	} deselect = { __identifier("?deselectObject@GameLogic@@QAEXPAVObject@@G_N@Z") };
	union {
		void (*address)();
		void (BfmeOuterXG::*member)(const DamageInfo *);
	} finish = { __identifier("?beginStructureTopple@StructureToppleUpdate@@IAEXPBVDamageInfo@@@Z") };

	Rva002AFFA0Holder *holder = ((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeHolderXG;
	BfmeUnitXG *unit = ((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG;

	if ((holder->m_bfmeSubXG.*test.member)((const Object *)unit, (const DamageInfo *)arg))
	{
		if (((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG->m_bfmeHookXG != 0)
			(((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG->m_bfmeHookXG->*markAsDead.member)();

		(((BfmeLogicXG *)TheGameLogic)->*deselect.member)(
			(Object *)((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG, 0xffff, true);
		(((BfmeOuterXG *)((char *)this - 0x20))->*finish.member)((const DamageInfo *)arg);
	}
}
