// cl: /DNDEBUG /MD /G6 /EHsc
// stlport
//
// Retail 0x00927BB0 searches the STLport hashtable prime table
// (_Stl_prime<bool>::_M_list at 0x01075870, 28 entries ending at
// 0x010758E0) with the FXList __lower_bound instantiation at 0x00066E20
// and returns the bound, folding the past-the-end case to -5 (the last
// prime, 4294967291, as an immediate). Sibling of _STL___stl_next_prime.
// IDENTITY IS NOT RECOVERED: the function keeps its address token.
#include <algorithm>
unsigned int __stdcall Rva00927BB0NextSize(unsigned int n)
{
	const unsigned int *first = (const unsigned int *)0x01075870;
	const unsigned int *last = (const unsigned int *)0x010758E0;
	const unsigned int *pos = _STL::lower_bound(first, last, n);
	if (pos == last)
		return -5;
	return *pos;
}
