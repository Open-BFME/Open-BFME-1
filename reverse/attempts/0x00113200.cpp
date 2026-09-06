// ??1Rva00113200Derived@@UAE@XZ
// partial score=0.68 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistringsetoutofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Destructor for the family whose constructor is landed in
// S2DualVptrDerivedCtors.cpp as Rva001129B0 / Rva00694E00: a class with TWO
// polymorphic bases (own vtables 0x01089644 at +0 and 0x01089630 at +8) where
// only the FIRST base's constructor is user-written (SubsystemInterface,
// already matched at 0x009A1A30/??0SubsystemInterface@@QAE@XZ) and the
// SECOND base (shared vtable 0x01073744) is trivial/inlined -- see the
// vtable_lookup evidence: 0x01089644 and 0x01089630 are carried ONLY by
// 0x001129B0 (the ctor) and this destructor at 0x00113200, so this is that
// same class's destructor.
//
// Retail order: reset own vtables (+0 and +8), destroy one owned member
// through the ILT thunk at 0x000066E0 (target FUN_00512FF0, still an
// unconverted dump -- only the call site needs to resolve, not that body),
// restore the second base's vtable (0x01073744, inlined -- no separate call,
// consistent with a base that has no user-written destructor), then call the
// first base's real destructor (??1SubsystemInterface@@UAE@XZ, matched at
// 0x00DA1A40). That two-step cleanup (member dtor call, then base dtor call)
// is what produces the SEH frame with the EH-state writes seen in the dump.

#include "PreRTS.h"
#include "Common/SubsystemInterface.h"

// Second, trivial polymorphic base sharing vtable 0x01073744 with the ctor's
// GenBase01073744 (S2DualVptrDerivedCtors.cpp). No user-written destructor,
// so its cleanup is inlined as a plain vtable-restore store, not a call.
class GenBase01073744_113200
{
public:
	virtual void keepSecond() {}
};

// Stand-in for the owned member destroyed through thunk 0x000066E0. The real
// callee (FUN_00512FF0) is an unconverted 416-byte dump; only the call site
// at this address is being matched, so the wrapper's body just reaches it.
class Rva00113200Member
{
public:
	~Rva00113200Member();
};

extern void j_000066e0();

Rva00113200Member::~Rva00113200Member()
{
	j_000066e0();
}

class Rva00113200Derived : public SubsystemInterface, public GenBase01073744_113200
{
public:
	virtual ~Rva00113200Derived();

	// SubsystemInterface's pure virtuals: never called, only need bodies so
	// this derived type is concrete enough to define/emit its own vtable.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	Rva00113200Member m_member;
};

Rva00113200Derived::~Rva00113200Derived()
{
	volatile int unused = 0;
	(void)unused;
}

// TU-local caller so the (non-deleting, complete-object) destructor above is
// emitted; absent from retail. Calling the destructor explicitly -- rather
// than `delete p` -- avoids pulling in the scalar deleting destructor variant,
// which retail's body (no operator-delete call, no deleting flag) does not
// have.
void bfmeInvokeRva00113200Dtor(Rva00113200Derived *p)
{
	p->~Rva00113200Derived();
}
