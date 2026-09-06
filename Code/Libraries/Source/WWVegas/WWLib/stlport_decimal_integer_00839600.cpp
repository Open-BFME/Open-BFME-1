// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 __get_decimal_integer<char> near-twin @ 0x00839600 (205B),
// sibling of 0x008391D0 (Code/Libraries/Source/WWVegas/WWLib/stlport_decimal_integer.cpp).
// Byte-identical except the inner __get_integer call lands on a distinct
// template instantiation (still an unclaimed dump at 0x008396D0); the REL32
// is masked by the byte-compare, so any instantiation compiling to the same
// caller shape suffices. Fresh namespace alias to avoid ODR collision with
// the twin TU's own explicit instantiation.

#define __BUILDING_STLPORT
#define __get_decimal_integer __get_decimal_integer_vendor_00839600
#include <locale>
#undef __get_decimal_integer

namespace _STL
{
	typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator00839600;

	template <class InputIter, class Integer>
	bool __get_decimal_integer(InputIter &first, InputIter &last, Integer &value)
	{
		string grouping;
		__false_type tag;
		*((volatile unsigned char *)&tag) = 0;
		return __get_integer(first, last, 10, value, 0, false, ' ', grouping, tag);
	}

	template bool __get_decimal_integer<NarrowIterator00839600, unsigned long>(
		NarrowIterator00839600 &, NarrowIterator00839600 &, unsigned long &);
}
