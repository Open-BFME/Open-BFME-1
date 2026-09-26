// cl: /EHsc
// stlport
// Open-BFME5: the out-of-line STLport _Construct<T,T> at retail 0x003ABAD0.
//
// Address-derived anonymous payload: the bytes prove a 36-byte LAYOUT and a
// LIFECYCLE -- a vptr at +0 written as an immediate, a dword at +4 and a byte
// at +8 copied inline, and a 24-byte member at +0xC whose copy constructor is
// called out of line through an incremental-link thunk -- never a class
// identity.

#include <memory>

// 24-byte member with an out-of-line copy constructor (retail: an _Rb_tree).
struct Gen_t_003abad0_m24
{
	int m_raw[6];
	Gen_t_003abad0_m24(const Gen_t_003abad0_m24 &);
};

// 36-byte polymorphic payload: vptr +0, dword +4, byte +8, member above +0xC.
struct Gen_t_003abad0_p36vt
{
	virtual void gen_v0();
	int  m_a;
	char m_b;
	Gen_t_003abad0_m24 m_tree;
};

template void _STL::_Construct<Gen_t_003abad0_p36vt, Gen_t_003abad0_p36vt>(
	Gen_t_003abad0_p36vt *, const Gen_t_003abad0_p36vt &);
