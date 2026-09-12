// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00069F00 copies the sixteen-byte records held by the vector
// sub-object copied by Rva0006A980Range at 0x0006A980. The vector base
// constructor at 0x00069CC0 and allocator accessor at 0x000698B0 identify the
// STLport vector copy-constructor family.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Gen_t_00069cc0_Tail
{
	int a[ 3 ];
};

struct Gen_t_00069cc0_p16cd
{
	int a;
	Gen_t_00069cc0_Tail tail;

	Gen_t_00069cc0_p16cd() {}
	Gen_t_00069cc0_p16cd(const Gen_t_00069cc0_p16cd &other)
	{
		a = other.a;
		tail = other.tail;
	}
	~Gen_t_00069cc0_p16cd() {}
};

template _STL::vector<Gen_t_00069cc0_p16cd,
	_STL::allocator<Gen_t_00069cc0_p16cd> >::vector(
	const _STL::vector<Gen_t_00069cc0_p16cd,
	_STL::allocator<Gen_t_00069cc0_p16cd> > &);
