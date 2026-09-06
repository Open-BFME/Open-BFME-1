// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x006BCE40, 100 bytes. BfmeBaseVUQ destructor family
// (see docs/... none yet -- address-derived). Derived vtable 0x0111D024 is
// stored at +0x0, then the object referenced by the pointer at +0x4 (if any)
// has its vtable slot 0x40 called, then an inline Release_Ref
// (`if (--NumRefs == 0) Delete_This();`, NumRefs at +0x4 of the pointee,
// Delete_This at vtable slot 0) runs, the pointer at +0x4 is zeroed, and
// finally the BfmeBaseVUQ base vtable (0x01073744) is restored by the
// implicit base destructor call.
//
// The pointee's real type/name are not recovered; it is modelled as a
// 17-slot virtual interface purely to reach slot 0 (Delete_This) and slot
// 0x40 (an address-derived "notify" method) at the right vtable offsets.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class Rva006BCE40Member
{
public:
	virtual void Delete_This(void) = 0;                       ///< vtable +0x00
	virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0;
	virtual void slot14() = 0; virtual void slot18() = 0;
	virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0;
	virtual void slot2C() = 0; virtual void slot30() = 0;
	virtual void slot34() = 0; virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void notify(void) = 0;                            ///< vtable +0x40

	int NumRefs;                                              ///< +0x04 of the pointee

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}
};

class Rva006BCE40 : public BfmeBaseVUQ
{
public:
	~Rva006BCE40();

	Rva006BCE40Member *m_member;                              ///< +0x04
};

// @??1Rva006BCE40@@UAEXXZ 0x006BCE40
Rva006BCE40::~Rva006BCE40()
{
	Rva006BCE40Member *member = m_member;

	if (member != 0)
		member->notify();

	member = m_member;
	if (member != 0)
	{
		member->Release_Ref();
		m_member = 0;
	}
}
