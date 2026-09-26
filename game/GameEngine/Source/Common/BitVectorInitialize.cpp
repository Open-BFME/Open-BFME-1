// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<bool>::_M_initialize, retail 0x00526BC0, 120 bytes. The
// name was parked on a 5-byte thunk.
//
// STLport's own bit-vector body out of the real header -- no element to model,
// since vector<bool> stores words.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

void BfmeBitVectorAnchor(_STL::vector<bool> &v, unsigned int n, bool value)
{
	_STL::vector<bool> made(n, value);
	v.swap(made);
	v.insert(v.begin(), n, value);
	v.insert(v.begin(), value);
}
