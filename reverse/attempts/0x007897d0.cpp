// ?d_007897d0@@YAXXZ
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Retail layout: address-derived (identity unproven; see reverse/re_attempts.log
// for 0x007897D0). Two-level polymorphic layout, mirroring the landed
// Code/GameEngine/Source/Common/Rva0045EF90Destructor.cpp idiom: a trivial
// inline virtual base (BaseSentinel007897D0) whose own vftable is the shared
// sentinel already pinned as ??_7VirtualMinusOneConstructorThunk@@6B@,
// 0x010F6F58, and a derived class (Owner007897D0, vftable 0x01126CCC, 6
// slots -- matching the landed ??0Rva00789900Init@@QAE@E@Z ctor's
// g_Rva00789900Table) adding five more virtual slots. Entering ~Owner007897D0
// automatically re-asserts its own vftable (retail's opening store), and
// returning from it automatically resets to BaseSentinel's vftable before the
// (empty) base dtor runs (retail's closing store) -- neither store needs to
// be written by hand. The dtor releases five guarded ref-counted members
// (+0xc, +0x10, +0x18, +0x20, +0x24, in that exact retail order -- not simple
// reverse-declaration order) and an inline AsciiString at +8 (destroyed last,
// via its own implicit member destructor, matching retail's releaseBuffer()
// call immediately before the closing vftable store).

class BaseSentinel007897D0
{
public:
	virtual ~BaseSentinel007897D0() {}
};

class AsciiStringField007897D0
{
public:
	~AsciiStringField007897D0() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

struct RefCountedThing007897D0
{
	virtual void Delete_This();
	int m_numRefs;
};

class Owner007897D0 : public BaseSentinel007897D0
{
public:
	~Owner007897D0();

	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();

private:
	unsigned int m_04;                    // +0x04
	AsciiStringField007897D0 m_ascii;     // +0x08
	RefCountedThing007897D0 *m_ref0c;     // +0x0c
	RefCountedThing007897D0 *m_ref10;     // +0x10
	unsigned char m_flag14;               // +0x14
	unsigned char m_pad15[3];
	RefCountedThing007897D0 *m_ref18;     // +0x18
	unsigned int m_1c;                    // +0x1c
	RefCountedThing007897D0 *m_ref20;     // +0x20
	RefCountedThing007897D0 *m_ref24;     // +0x24
	unsigned int m_28;                    // +0x28
	unsigned int m_2c;                    // +0x2c
};

// ?d_007897d0@@YAXXZ
Owner007897D0::~Owner007897D0()
{
	RefCountedThing007897D0 *p;

	p = m_ref10;
	if (p) {
		if (--p->m_numRefs == 0)
			p->Delete_This();
		m_ref10 = 0;
	}

	p = m_ref0c;
	if (p) {
		if (--p->m_numRefs == 0)
			p->Delete_This();
		m_ref0c = 0;
	}

	p = m_ref18;
	if (p) {
		if (--p->m_numRefs == 0)
			p->Delete_This();
		m_ref18 = 0;
	}

	p = m_ref20;
	if (p) {
		if (--p->m_numRefs == 0)
			p->Delete_This();
		m_ref20 = 0;
	}

	p = m_ref24;
	if (p) {
		if (--p->m_numRefs == 0)
			p->Delete_This();
		m_ref24 = 0;
	}
}
