// ?d_003abb80@@YAXXZ
// partial score=0.935 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

struct Rva003AB460Tree
{
	int m_raw[3];
	Rva003AB460Tree(const Rva003AB460Tree &other);
};

class Rva003BA660Record
{
public:
	virtual void slot();
	Rva003BA660Record( const Rva003BA660Record &other )
		: m_04( other.m_04 ), m_08( other.m_08 ), m_tree( other.m_tree )
	{
	}
	int m_04;
	char m_08;
	Rva003AB460Tree m_tree;
};

template _STL::vector<Rva003BA660Record, _STL::allocator<Rva003BA660Record> >::vector(
	const _STL::vector<Rva003BA660Record, _STL::allocator<Rva003BA660Record> > &);
