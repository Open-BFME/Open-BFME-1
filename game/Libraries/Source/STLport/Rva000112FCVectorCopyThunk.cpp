// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// Retail RVA 0x000112FC is a five-byte jump to the matched 12-byte copy body.

struct Rva00755100Element;

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(
	InputIterator, InputIterator, OutputIterator,
	const random_access_iterator_tag &, Distance *);
}

Rva00755100Element *__cdecl Rva000112FCVectorCopyThunk(
	Rva00755100Element *first, Rva00755100Element *last,
	Rva00755100Element *result,
	const _STL::random_access_iterator_tag &tag, int *count)
{
	return _STL::__copy(first, last, result, tag, count);
}
