// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Open-BFME7: STLport list<AsciiString+int pair>::push_back, four byte twins
// (retail 0x0034DEB0/0x0034DF70/0x0034E030/0x0034E0F0, 144 bytes each) that
// only differ by the this-relative offset of the target list among four
// sibling arrays 0x80 bytes apart and by their own (compiler-generated) SEH
// scope table -- both invisible once relocations are masked.  Each body
// builds an (AsciiString, int) pair on the stack via AsciiString's copy ctor
// (0x00887B60), allocates a 16-byte list node (8 overhead + 8 value) through
// __node_alloc::_M_allocate, copy-constructs the node's value from the pair
// via the shared out-of-line _Construct thunk, links it before the list's
// sentinel, then releases the temporary AsciiString (0x00887940).  The
// owning class is unidentified; each method carries an address-derived tag
// and a padding-only layout out to its own list array.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

struct Rva0034DEB0Elem
{
	Rva0034DEB0Elem( const AsciiString &name, int extra ) : m_name( name ), m_extra( extra ) {}
	AsciiString m_name;
	int m_extra;
};

typedef _STL::list<Rva0034DEB0Elem, _STL::allocator<Rva0034DEB0Elem> > Rva0034DEB0List;

class Rva0034DEB0OwnerA
{
public:
	void insert( int index, const AsciiString &name, int extra );
private:
	char m_pad[ 0x17274 ];
	Rva0034DEB0List m_lists[ 1 ];
};

class Rva0034DEB0OwnerB
{
public:
	void insert( int index, const AsciiString &name, int extra );
private:
	char m_pad[ 0x172F4 ];
	Rva0034DEB0List m_lists[ 1 ];
};

class Rva0034DEB0OwnerC
{
public:
	void insert( int index, const AsciiString &name, int extra );
private:
	char m_pad[ 0x17374 ];
	Rva0034DEB0List m_lists[ 1 ];
};

class Rva0034DEB0OwnerD
{
public:
	void insert( int index, const AsciiString &name, int extra );
private:
	char m_pad[ 0x173F4 ];
	Rva0034DEB0List m_lists[ 1 ];
};

void Rva0034DEB0OwnerA::insert( int index, const AsciiString &name, int extra )
{
	m_lists[ index ].push_back( Rva0034DEB0Elem( name, extra ) );
}

void Rva0034DEB0OwnerB::insert( int index, const AsciiString &name, int extra )
{
	m_lists[ index ].push_back( Rva0034DEB0Elem( name, extra ) );
}

void Rva0034DEB0OwnerC::insert( int index, const AsciiString &name, int extra )
{
	m_lists[ index ].push_back( Rva0034DEB0Elem( name, extra ) );
}

void Rva0034DEB0OwnerD::insert( int index, const AsciiString &name, int extra )
{
	m_lists[ index ].push_back( Rva0034DEB0Elem( name, extra ) );
}
