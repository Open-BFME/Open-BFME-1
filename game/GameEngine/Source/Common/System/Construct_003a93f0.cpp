// cl: /EHsc
// stlport
// Open-BFME5: the out-of-line STLport _Construct<T,T> at retail 0x003A93F0.
//
// Address-derived anonymous payload: the bytes prove a 16-byte LAYOUT and a
// LIFECYCLE -- a 4-byte member at +0 whose copy constructor is called out of
// line at the retail StringBase<char> copy constructor, followed by three raw
// 4-byte fields at +4/+8/+0xC copied inline -- never a class identity.

#include <memory>
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// 16-byte payload: the 4-byte string view at +0, then three plain dwords.
struct Gen_t_003a93f0_p16s
{
	// Call view only: AsciiString adds no storage to StringBase<char>, and its
	// inline copy constructor reaches the proven StringBase<char> copy body.
	AsciiString m_str;
	int m_a;
	int m_b;
	int m_c;
};

template void _STL::_Construct<Gen_t_003a93f0_p16s, Gen_t_003a93f0_p16s>(
	Gen_t_003a93f0_p16s *, const Gen_t_003a93f0_p16s &);
