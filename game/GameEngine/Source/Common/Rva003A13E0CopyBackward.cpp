// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: out-of-line STLport copy-backward helper at retail 0x003A13E0.
// Near-twin of the 0x00774860 instantiation (Rva00774860CopyBackward.cpp):
// same shape, element stride 0xb8 (46 dwords) instead of 0xbc, and the
// per-element assignment forwards to the pinned BfmeCopyElementD::bfmeAssign
// (0x00024BA9) instead of Gen_t_00776240_p128pod::operator=.

struct Gen_t_003a24c0_p128pod
{
	int words[46];
	Gen_t_003a24c0_p128pod &operator=(const Gen_t_003a24c0_p128pod &);
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
		*result = *last;
	}
	return result;
}

template Gen_t_003a24c0_p128pod *__copy_backward<
	Gen_t_003a24c0_p128pod *, Gen_t_003a24c0_p128pod *, int>(
	Gen_t_003a24c0_p128pod *, Gen_t_003a24c0_p128pod *,
	Gen_t_003a24c0_p128pod *, const random_access_iterator_tag &, int *);
}
