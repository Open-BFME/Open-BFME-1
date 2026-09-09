// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 money_get wide long-double decimal parser at 0x00839600
// (205B).  Its callee at 0x008396D0 is the matching
// __get_integer<unsigned short *, long double> body; the retail callee
// advances the mutable wide-string iterator by two bytes and stores a qword
// result.  Fresh namespace alias avoids ODR collision with integer facets.

#define __BUILDING_STLPORT
#define __get_decimal_integer __get_decimal_integer_vendor_00839600
#include <locale>
#undef __get_decimal_integer

namespace _STL
{
	typedef unsigned short * WidePointer00839600;

	template <class InputIter, class Integer>
	bool __get_decimal_integer(InputIter &first, InputIter &last, Integer &value)
	{
		string grouping;
		__false_type tag;
		*((volatile unsigned char *)&tag) = 0;
		return __get_integer(first, last, 10, value, 0, false, ' ', grouping, tag);
	}

	template bool __get_decimal_integer<WidePointer00839600, long double>(
		WidePointer00839600 &, WidePointer00839600 &, long double &);
}
