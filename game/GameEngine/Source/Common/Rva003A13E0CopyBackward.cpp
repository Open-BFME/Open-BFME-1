// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

// Open-BFME: out-of-line STLport copy-backward helper at retail 0x003A13E0.
// Near-twin of the 0x00774860 instantiation (Rva00774860CopyBackward.cpp):
// same shape, element stride 0xb8 (46 dwords) instead of 0xbc, and the
// per-element copy uses ILT 0x00024BA9 to the matched copy-constructor body
// Rva003A1120 at 0x003A1120.

struct Gen_t_003a24c0_p128pod
{
	int words[46];
};

class Rva003A1120
{
public:
	__declspec(nothrow) Rva003A1120(const Rva003A1120 &);
	// Only a 0xB8-byte view is needed to call the matched constructor.
	unsigned char m_unmodeled[0xB8];
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count)
	{
		--last;
		--result;
		// A valid non-empty output range has writable storage at result.
		__assume(result != 0);
		::new ((Rva003A1120 *)result)
			Rva003A1120(*(const Rva003A1120 *)last);
	}
	return result;
}

template Gen_t_003a24c0_p128pod *__copy_backward<
	Gen_t_003a24c0_p128pod *, Gen_t_003a24c0_p128pod *, int>(
	Gen_t_003a24c0_p128pod *, Gen_t_003a24c0_p128pod *,
	Gen_t_003a24c0_p128pod *, const random_access_iterator_tag &, int *);
}
