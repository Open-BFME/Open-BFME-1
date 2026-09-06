// ??1Rva001B3E60@@UAE@XZ
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x001B3E60, 107 bytes. BfmeBaseVUQ destructor family
// with a genuine VIRTUAL base (see Code/GameEngine/Source/Common/
// VirtualBaseThunks.cpp for the sibling vtordisp thunks at 0x001B3E40 etc.):
// own vtable 0x0109CE94 (offset 0, over BfmeBaseVUQ) and a second direct
// base's vtable 0x0109CE80 (offset 4) are stored at entry; the virtual
// base's own vtable 0x0109CE68 is stored through the vbtable pointer at
// +0x8 (esi + vbtable[1] + 8), and its vtordisp slot (esi + vbtable[1] + 4)
// is refreshed from the same vbtable entry. A member at +0x20
// (ClearanceTestingSlowDeathBehaviorModuleDataMember, retail dtor pinned at
// 0x000309F4, still a dump) is destroyed, then the base vtable 0x01073744
// is restored at the tail (only the first, non-virtual BfmeBaseVUQ slot is
// restored -- the second base and the virtual base have no further base of
// their own to unwind to).
//
// Neither the class nor the second/virtual base names are recovered; all
// three keep address-derived names and pure-interface stand-ins wide enough
// to reach their real vtable slot counts.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class Rva001B3E60SecondBase
{
public:
	virtual void slot00() { }
	virtual void slot04() { }
	virtual void slot08() { }
	virtual void slot0C() { }
};

class Rva001B3E60VBase
{
public:
	virtual ~Rva001B3E60VBase();
	virtual void vslot00() { }
	virtual void vslot04() { }
	virtual void vslot08() { }
	virtual void vslot0C() { }
	virtual void vslot10() { }
};

class ClearanceTestingSlowDeathBehaviorModuleDataMember
{
public:
	~ClearanceTestingSlowDeathBehaviorModuleDataMember();      ///< pinned 0x000309F4
};

class Rva001B3E60
	: public BfmeBaseVUQ
	, public Rva001B3E60SecondBase
	, virtual public Rva001B3E60VBase
{
public:
	~Rva001B3E60();

	virtual void vslot00() = 0;
	virtual void vslot04() = 0;
	virtual void vslot08() = 0;
	virtual void vslot0C() = 0;
	virtual void vslot10() = 0;

private:
	unsigned char m_pad0C[0x20 - 0x0C];                         ///< +0x0C, untouched by this body
	ClearanceTestingSlowDeathBehaviorModuleDataMember m_member; ///< +0x20
};

// @??1Rva001B3E60@@UAE@XZ 0x001B3E60
Rva001B3E60::~Rva001B3E60()
{
}
