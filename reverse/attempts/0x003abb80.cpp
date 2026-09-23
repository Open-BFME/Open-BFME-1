// ?d_003abb80@@YAXXZ
// partial score=0.975 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva003AB460Tree
{
	int m_raw[3];
	Rva003AB460Tree(const Rva003AB460Tree &other);
};

struct Rva003ABB80Prefix
{
	int m_04;
	Rva003ABB80Prefix(const Rva003ABB80Prefix &other)
		: m_04( other.m_04 )
	{
		_ReadWriteBarrier();
	}
};

class Rva003BA660Record
{
public:
	virtual void slot();
	Rva003BA660Record( const Rva003BA660Record &other )
		: m_prefix( other.m_prefix ), m_08( other.m_08 ), m_tree( other.m_tree )
	{
	}
	Rva003ABB80Prefix m_prefix;
	char m_08;
	Rva003AB460Tree m_tree;
};

template _STL::vector<Rva003BA660Record, _STL::allocator<Rva003BA660Record> >::vector(
	const _STL::vector<Rva003BA660Record, _STL::allocator<Rva003BA660Record> > &);
