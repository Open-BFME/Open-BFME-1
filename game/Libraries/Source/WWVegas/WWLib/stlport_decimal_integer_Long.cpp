// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 __get_decimal_integer<char> @ 0x0000837770 (205B): the long instantiation, byte-twin of stlport_decimal_integer.cpp (tools/twin_scan.py); its __get_integer callee is the dump at 0x0000837840.

#define __BUILDING_STLPORT
#define __get_decimal_integer __get_decimal_integer_vendor
#include <locale>
#undef __get_decimal_integer

namespace _STL
{
	typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;

	template <class InputIter, class Integer>
	bool __get_decimal_integer(InputIter &first, InputIter &last, Integer &value)
	{
		string grouping;
		__false_type tag;
		*((volatile unsigned char *)&tag) = 0;
		return __get_integer(first, last, 10, value, 0, false, ' ', grouping, tag);
	}

	template bool __get_decimal_integer<NarrowIterator, long>(
		NarrowIterator &, NarrowIterator &, long &);
}
