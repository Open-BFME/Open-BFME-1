// RVA 0x007897D0: destructor of the owner constructed at 0x00789900.
// Evidence: targets/game/reverse/identity_evidence/rva007897d0.md
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class VirtualMinusOneConstructorThunk
{
public:
	virtual ~VirtualMinusOneConstructorThunk() {}
};

struct RefCountedThing007897D0
{
	virtual void Delete_This();
	int m_numRefs;
};

// The zero-offset cleanup at 0x00789740 has no entry vptr store.
// This novtable base is an ABI view, not a recovered EA hierarchy.
struct __declspec(novtable) Rva00789740View : VirtualMinusOneConstructorThunk
{
    unsigned int m_04;
    AsciiString m_ascii;
};

struct Rva00789600Pair
{
    RefCountedThing007897D0 *m_ref20;
    RefCountedThing007897D0 *m_ref24;
    ~Rva00789600Pair()
    {
        RefCountedThing007897D0 *p = m_ref20;
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
};

class Rva00789900Init : public Rva00789740View
{
public:
    virtual ~Rva00789900Init();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
private:
    RefCountedThing007897D0 *m_ref0c;
    RefCountedThing007897D0 *m_ref10;
    unsigned m_14;
    RefCountedThing007897D0 *m_ref18;
    unsigned m_1c;
    Rva00789600Pair m_pair;
    unsigned m_28;
    unsigned m_2c;
};

Rva00789900Init::~Rva00789900Init()
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
}
