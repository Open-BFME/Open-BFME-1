// ??0Rva00754F70Owner@@QAE@XZ
// partial score=0.79 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Open-BFME7: default constructor zero-initializing nine int members and one
// embedded STLport list<12-byte record>, retail 0x00754F70, 102 bytes.  The
// list's 20-byte sentinel node (8 overhead + 12 value) self-links (next =
// prev = the node itself) through __node_alloc::_M_allocate.  The element is
// only known to be twelve trivially copyable bytes, so it carries an
// address-derived tag; owning class is unidentified.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

struct Rva00754F70Elem
{
	int m_a;
	int m_b;
	int m_c;
};

typedef _STL::list<Rva00754F70Elem, _STL::allocator<Rva00754F70Elem> > Rva00754F70List;

class Rva00754F70Owner
{
public:
	Rva00754F70Owner();
private:
	AsciiString m_f0;
	int m_f4;
	int m_f8;
	Rva00754F70List m_list;
	int m_f10;
	int m_f14;
	int m_f18;
	int m_f1c;
	int m_f20;
	int m_f24;
};

Rva00754F70Owner::Rva00754F70Owner() :
	m_f0(),
	m_f4( 0 ),
	m_f8( 0 )
{
	m_f10 = 0;
	m_f14 = 0;
	m_f18 = 0;
	m_f1c = 0;
	m_f20 = 0;
	m_f24 = 0;
}
