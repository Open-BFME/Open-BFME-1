// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
//
// Retail 0x003AAC20 is the STLport vector copy constructor for the
// 32-byte Gen_003A8910 record. The body calls the allocator accessor at
// 0x003A66D0, the vector base constructor at 0x003A7870, and the record copy
// constructor at 0x003A8910. The record's vtable, three string members, and
// field offsets come from BfmePolyMixedCopyWO.cpp.
//
// STLport needs _STLP_NO_EXCEPTIONS here to inline the element copy loop while
// retaining the constructor's exception frame.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

class AsciiStringWO
{
public:
	AsciiStringWO(const AsciiStringWO &);
	~AsciiStringWO();

private:
	char *m_bfmeData;
};

class BfmeStrWO : private AsciiStringWO
{
public:
	BfmeStrWO(const AsciiStringWO &other) : AsciiStringWO(other) {}
	~BfmeStrWO() {}
};

class Gen_003A8910
{
public:
	Gen_003A8910(const Gen_003A8910 &);
	virtual ~Gen_003A8910();

	BfmeStrWO m_bfmeFirst;
	int m_bfmeA;
	int m_bfmeB;
	bool m_bfmeFlag;
	BfmeStrWO m_bfmeSecond;
	BfmeStrWO m_bfmeThird;
	int m_bfmeC;
};

template _STL::vector<Gen_003A8910, _STL::allocator<Gen_003A8910> >::vector(
	const _STL::vector<Gen_003A8910, _STL::allocator<Gen_003A8910> > &);
