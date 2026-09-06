// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
//
// Open-BFME7: STLport vector<BfmeEntVTA>::vector(const vector &), retail
// 0x003AACF0, 194 bytes.  BfmeEntVTA is the 12-byte polymorphic record of
// BfmeConv1605.cpp (vtable 0x010EC77C, an AsciiString at +4 and a byte at +8).
// Two things fix the shape: _STLP_NO_EXCEPTIONS lets the element copy inline
// into the loop (no try/catch in uninitialized_copy), and the string member
// has to be the StringInline forwarder (private StringBase<char> base) so the
// destination member address is materialised before the source is pushed --
// a hand model with an out-of-line string copy transposes those two
// instructions (banked at 0.95 in reverse/attempts/0x003aacf0.cpp).

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

class BfmeEntVTA
{
public:
	virtual void bfmeSlot0VTA();
	AsciiString m_bfme04;
	char m_bfme08;
};

template _STL::vector<BfmeEntVTA, _STL::allocator<BfmeEntVTA> >::vector(
	const _STL::vector<BfmeEntVTA, _STL::allocator<BfmeEntVTA> > &);
