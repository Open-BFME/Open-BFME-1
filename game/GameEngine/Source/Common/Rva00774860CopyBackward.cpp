// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: out-of-line STLport copy-backward helper at retail 0x00774860.
// The retail stride is 0xbc and each iteration calls the element assignment.

struct Gen_t_00776240_p128pod
{
	int words[47];
	Gen_t_00776240_p128pod &operator=(const Gen_t_00776240_p128pod &);
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

template Gen_t_00776240_p128pod *__copy_backward<
	Gen_t_00776240_p128pod *, Gen_t_00776240_p128pod *, int>(
	Gen_t_00776240_p128pod *, Gen_t_00776240_p128pod *,
	Gen_t_00776240_p128pod *, const random_access_iterator_tag &, int *);
}
