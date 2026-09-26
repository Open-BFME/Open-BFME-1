// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: STLport vector<T>::insert at retail 0x0077CC60.
// The element is the 0xBC-byte non-POD payload identified by the existing
// 0x00774860 copy-backward helper.

#include <vector>

struct Gen_t_00776240_p128pod
{
	int words[47];

	Gen_t_00776240_p128pod();
	Gen_t_00776240_p128pod(const Gen_t_00776240_p128pod &);
	~Gen_t_00776240_p128pod();
	Gen_t_00776240_p128pod &operator=(
		const Gen_t_00776240_p128pod &other);
};

template class _STL::vector<Gen_t_00776240_p128pod>;
