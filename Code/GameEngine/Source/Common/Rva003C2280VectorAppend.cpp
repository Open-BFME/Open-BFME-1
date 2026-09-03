// ?d_003c2280@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _M_insert_overflow j_00007e96
#include <vector>
#undef _M_insert_overflow

class Rva003C2280Item
{
public:
	char m_pad00[ 8 ];
	bool m_flag;
};

class Rva003C2280Owner
{
public:
	void append( const Rva003C2280Item *item );

private:
	char m_pad00[ 0x50 ];
	_STL::vector<Rva003C2280Item *> m_first;
	_STL::vector<Rva003C2280Item *> m_second;
};

void Rva003C2280Owner::append( const Rva003C2280Item *item )
{
	if ( item->m_flag )
		m_second.push_back( const_cast<Rva003C2280Item *>( item ) );
	else
		m_first.push_back( const_cast<Rva003C2280Item *>( item ) );
}
