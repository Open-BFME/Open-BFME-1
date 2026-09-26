// STLport pointer-vector insert at retail 0x003C56F0.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
	void *dest, const void *src, unsigned int count);
#define memmove BfmeMemMove
#define _M_insert_overflow j_000100d7
#include <vector>
#undef _M_insert_overflow
#undef memmove

class Rva003C5890Item
{
};

class Rva003C56F0Vector
{
public:
	_STL::vector<Rva003C5890Item *> m_items;
	Rva003C5890Item **insert( Rva003C5890Item **position,
		Rva003C5890Item *const &value );
};

Rva003C5890Item **Rva003C56F0Vector::insert(
	Rva003C5890Item **position, Rva003C5890Item *const &value )
{
	return m_items.insert( position, value );
}
