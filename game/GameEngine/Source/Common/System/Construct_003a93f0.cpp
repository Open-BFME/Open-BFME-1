// cl: /EHsc
// stlport
// Open-BFME5: the out-of-line STLport _Construct<T,T> at retail 0x003A93F0.
//
// Address-derived anonymous payload: the bytes prove a 16-byte LAYOUT and a
// LIFECYCLE -- a 4-byte member at +0 whose copy constructor is called out of
// line at the retail StringBase<char> copy constructor, followed by three raw
// 4-byte fields at +4/+8/+0xC copied inline -- never a class identity.

#include <memory>

// 4-byte member with an out-of-line copy constructor (retail: StringBase<char>).
struct Gen_t_003a93f0_s4
{
	void *m_rep;
	Gen_t_003a93f0_s4(const Gen_t_003a93f0_s4 &);
};

// 16-byte payload: the member above at +0, three plain dwords after it.
struct Gen_t_003a93f0_p16s
{
	Gen_t_003a93f0_s4 m_str;
	int m_a;
	int m_b;
	int m_c;
};

template void _STL::_Construct<Gen_t_003a93f0_p16s, Gen_t_003a93f0_p16s>(
	Gen_t_003a93f0_p16s *, const Gen_t_003a93f0_p16s &);
