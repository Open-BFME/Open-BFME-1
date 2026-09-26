// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 __get_decimal_integer<wchar_t> @ 0x0083B0D0 (205B).
// Its direct call to the exact wide signed-int __get_integer specialization at
// 0x0083B1A0 establishes both iterator width and integer type.

#define __BUILDING_STLPORT
#define __get_decimal_integer __get_decimal_integer_vendor
#include <locale>
#undef __get_decimal_integer

namespace _STL
{
	typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > WideIterator;

	template <class InputIter, class Integer>
	bool __get_decimal_integer(InputIter &first, InputIter &last, Integer &value)
	{
		string grouping;
		__false_type tag;
		*((volatile unsigned char *)&tag) = 0;
		return __get_integer(first, last, 10, value, 0, false, ' ', grouping, tag);
	}

	template bool __get_decimal_integer<WideIterator, int>(
		WideIterator &, WideIterator &, int &);
}
