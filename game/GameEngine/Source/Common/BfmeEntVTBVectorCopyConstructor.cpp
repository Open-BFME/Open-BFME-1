// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
//
// Open-BFME7: STLport vector<BfmeEntVTB>::vector(const vector &), retail
// 0x003AAED0, 206 bytes.  BfmeEntVTB is the 20-byte polymorphic record from
// BfmeConv1607.cpp, with two scalar words, an inline AsciiString, and a byte.
// The vtable at 0x010EC784 identifies the element type, and the copy loop
// calls the inline StringBase<char> copy body for the string member.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

class BfmeEntVTB
{
public:

	virtual void bfmeSlot0VTB();
	int m_bfme04;
	int m_bfme08;
	AsciiString m_bfme0c;
	char m_bfme10;
};

template _STL::vector<BfmeEntVTB, _STL::allocator<BfmeEntVTB> >::vector(
	const _STL::vector<BfmeEntVTB, _STL::allocator<BfmeEntVTB> > &);
