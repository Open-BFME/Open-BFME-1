// ?bfmeSet14F0@@YIXPAVGen_002214F0@@HPAUBfmeSub14F0@@H1@Z
// partial score=0.7 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x002214F0. Triple field set, 62 bytes, no calls: store
// max(arg2, 1) at this+0xA4, the +0x74 field of arg1 at this+0x9C, and
// the +0x74 field of arg3 at this+0xA0. The second register argument is
// unused; the callee pops its three stack arguments. The max is spelled
// as a pointer select so the address materializes before the compare.

struct BfmeSub14F0
{
	char m_pad[0x74];
	int m_val;
};

class Gen_002214F0
{
public:
	char m_pad[0x9C];
	int m_9c;				// +0x9C
	int m_a0;				// +0xA0
	int m_a4;				// +0xA4
};

// ?bfmeSet14F0@@YIHPAXHPAUH@@Z
void __fastcall bfmeSet14F0(Gen_002214F0 *o, int unused, BfmeSub14F0 *a1, volatile int a2, BfmeSub14F0 *a3)
{
	int one = 1;
	const volatile int *p = &a2;

	if (!(*p > 1))
		p = &one;

	o->m_a4 = *p;
	o->m_9c = a1->m_val;
	o->m_a0 = a3->m_val;
}
