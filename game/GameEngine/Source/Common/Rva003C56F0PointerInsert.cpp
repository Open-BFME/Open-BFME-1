// STLport pointer-vector insert at retail 0x003C56F0.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _M_insert_overflow j_000100d7
#include <vector>
#undef _M_insert_overflow

class Rva003C5890Item
{
};

// Only the vector member itself is emitted.
template Rva003C5890Item **_STL::vector<Rva003C5890Item *>::insert(
	Rva003C5890Item **position, Rva003C5890Item *const &value );
