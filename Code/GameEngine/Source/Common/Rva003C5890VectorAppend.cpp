// ?d_003c5890@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _M_insert_overflow j_000100d7
#include <vector>
#undef _M_insert_overflow

class Rva003C5890Item
{
};

class Rva003C5890Owner
{
public:
	void append( const Rva003C5890Item *item );

private:
	_STL::vector<Rva003C5890Item *> m_items;
};

void Rva003C5890Owner::append( const Rva003C5890Item *item )
{
	m_items.push_back( const_cast<Rva003C5890Item *>( item ) );
}
