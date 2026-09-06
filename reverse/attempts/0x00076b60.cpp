// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// partial score=0.55 date=2026-09-06

// Open-BFME7: constructor of an unidentified SubsystemInterface-derived class,
// retail 0x00076B60, 105 bytes. Installs vtable 0x01075EE8 (tools/vtable_lookup.py:
// no named slots, only the destructor at 0x00076C80 -- Gen_00076C80 in
// Bfme5ChainedDestructors.cpp -- carries the same constant, member at +0xC).
// Base ctor is SubsystemInterface() (retail 0x009A1A30), which per
// GODupBaseConstructor.cpp we model with a minimal stand-in rather than the
// full engine header. After the base ctor: an int flags member at +0x8 is
// zeroed then OR'd with 0x8 and 0x20 in two separate statements (two
// read-modify-write pairs in the retail body), and a list member at +0xC
// (BfmeDtorMemberF's slot in the dtor family) default-constructs an STLport
// list: allocate a 16-byte sentinel node (8 overhead + 8-byte element) and
// self-link next/prev. Element type/identity of the list is unproven; a
// two-int placeholder reproduces the allocation size, which is all this
// constructor's bytes depend on.

#define _STLP_NO_EXCEPTIONS 0
#include <list>

class SubsystemInterface
{
public:
	SubsystemInterface();					// retail 0x009A1A30
	virtual ~SubsystemInterface();

private:
	int m_bfmeName;
};

struct Rva00076B60Elem
{
	int m_a;
	int m_b;
};

class Gen_00076B60 : public SubsystemInterface
{
public:
	Gen_00076B60();

private:
	unsigned int m_bfmeFlags;												// +0x08
	_STL::list<Rva00076B60Elem, _STL::allocator<Rva00076B60Elem> > m_bfmeList;	// +0x0C
};

static unsigned int Rva00076B60SetFlag( unsigned int v, unsigned int mask )
{
	return v | mask;
}

// ??0Gen_00076B60@@QAE@XZ
Gen_00076B60::Gen_00076B60() : m_bfmeFlags( 0 )
{
	m_bfmeFlags = Rva00076B60SetFlag( m_bfmeFlags, 0x8 );
	m_bfmeFlags = Rva00076B60SetFlag( m_bfmeFlags, 0x20 );
}
