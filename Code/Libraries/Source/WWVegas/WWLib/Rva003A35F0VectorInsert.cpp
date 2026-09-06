// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: near-twin of vector<Gen_t_00776240_p128pod>::insert (twin
// 0x0077CC60, Rva0077CC60VectorInsert.cpp).  Same STLport vector<T>::insert
// shape, but the 184-byte element is Rva003A35A0Element (already landed
// elsewhere as the push_back at 0x003A35A0, RvaVectorPushBack.cpp) instead
// of the twin's 188-byte Gen_t_00776240_p128pod.  Every differing callee in
// this body is already pinned in reverse/symbols.csv: BfmeElementConstruct
// (0x72F2), the element assign (0x24BA9, bfmeAssign@BfmeCopyElementD), the
// element dtor (0x36241, Gen_dtor_002bcca0) and _M_insert_overflow (0x2798F).

#include <vector>

struct Rva003A35A0Element
{
	int words[46];

	Rva003A35A0Element();
	Rva003A35A0Element(const Rva003A35A0Element &);
	~Rva003A35A0Element();
	Rva003A35A0Element &operator=(const Rva003A35A0Element &other);
};

template class _STL::vector<Rva003A35A0Element>;
