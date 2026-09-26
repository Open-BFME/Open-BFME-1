// cl: /EHsc
// stlport
// Open-BFME5: the out-of-line STLport _Construct<T,T> at retail 0x003A9110.
//
// The payload type is deliberately anonymous and address-derived: the bytes
// prove a LAYOUT and a LIFECYCLE (a vptr at +0 written as an immediate, and a
// 4-byte member at +4 whose copy constructor is called out of line at the
// retail StringBase<char> copy constructor), never a class identity. Its only
// retail caller is the 8-byte-payload vector push_back at 0x003B1000, which
// game/gen_small/tgrid_113.cpp already carries under the same convention.

#include <memory>

// 4-byte member with an out-of-line copy constructor (retail: StringBase<char>).
struct Gen_t_003a9110_s4
{
	void *m_rep;
	Gen_t_003a9110_s4(const Gen_t_003a9110_s4 &);
};

// 8-byte polymorphic payload: vptr at +0, the member above at +4.
struct Gen_t_003a9110_p8vs
{
	virtual void gen_v0();
	Gen_t_003a9110_s4 m_str;
};

template void _STL::_Construct<Gen_t_003a9110_p8vs, Gen_t_003a9110_p8vs>(
	Gen_t_003a9110_p8vs *, const Gen_t_003a9110_p8vs &);
