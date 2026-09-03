// ?bfmeCheck1C8A0@@YG_NPAX0@Z
// partial score=0.85 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021C8A0. Flag gate with tail call, 44 bytes: when both
// arguments carry the 0x10 bit at +0x94 answer false, otherwise tail-jump
// to the shared handler at 0x00221960 through the thunk at 0x0002B2D8
// with the same two arguments.

bool __stdcall bfmeHandler1C8A0(void *a1, void *a2);

// ?bfmeCheck@Gen_0021C8A0@@YG_NPAX0@Z
struct BfmeFlags1C8A0
{
	unsigned char m_low : 4;
	unsigned char m_flag : 1;
	unsigned char m_high : 3;
};

struct BfmeObj1C8A0
{
	char m_pad[0x94];
	BfmeFlags1C8A0 m_flags;
};

bool __stdcall bfmeCheck1C8A0(void *a1, void *a2)
{
	BfmeObj1C8A0 *x = (BfmeObj1C8A0 *)a1;
	BfmeObj1C8A0 *y = (BfmeObj1C8A0 *)a2;

	if (x->m_flags.m_flag &&
	    y->m_flags.m_flag)
		return false;
	return bfmeHandler1C8A0(x, y);
}
