#include <string.h>
// partial score=0.11 date=2026-09-21
// Retail 0x007AF200: BfmeB1050::bfmeBase1050, the base-field initializer
// called first from BfmeB1050::bfmeGo1050B (BfmeConv1050.cpp) and from
// BfmeB1159::initialize (Rva007B44E0ShadowPair.cpp) before the derived
// fields (m_bfme58/5c/60/64) and vtable pointer are set. Pinned at ILT
// 0x0000AF38 -> 0x007AF200 as ?bfmeBase1050@BfmeB1050@@QAEXXZ.
//
// Field layout (offsets from `this`) is solid: +0 vfptr, +4/+5 bytes (1,0),
// +8..+10 zero triple, +0x14/+0x18 zero pair, +0x1c float 1.0f, +0x20 zero,
// +0x24/+0x28 both -1, +0x2c 0xff, +0x30 byte 1, +0x34 zero. Confirmed by
// the caller (BfmeB1159::initialize) which sets the *derived* siblings right
// after calling this.
//
// UNRESOLVED SHAPE: retail opens with `sub esp,0xc` / `push esi` and reuses
// ESI (not EAX) across BOTH zero-fill groups (lea edx,[ecx+8] / lea
// edx,[ecx+0x14]); a plain per-field or memset()-based C++ body always
// allocator-picks EAX for the fill value and drops the ESI push -- no
// source shape tried (direct stores, indexed loop, real while-loop,
// memset(), struct-value assignment) got the compiler to prefer ESI.
// Retail ALSO carries two dead-looking store pairs `[esp+4]=0;[esp+8]=0`
// immediately before AND after the m_4/m_5 byte stores, with nothing ever
// reading them back -- this looks like leftover argument-staging for a
// (0,0) call that got optimized away, but no such call/inlined-empty-ctor
// candidate was found; declaring m_4/m_5 (or a same-shaped struct) volatile
// is the only lever that reproduces the double stores, and it does so by
// accident (stack-slot placement), not because the fields are genuinely
// volatile in retail. The memset() + float-bitcast-through-a-local-int
// levers below DO reproduce retail's lea+shared-register zero-fill shape
// and the store/reload dance for the 1.0f constant; only the ESI choice and
// the two dead pairs remain open. Needs a genuine register-preference or
// dead-argument-staging lever nobody has documented yet.

class BfmeB1050
{
public:
	void bfmeBase1050(void);

	void *m_bfmeVfptr;
	unsigned char m_4;
	unsigned char m_5;
	int m_grp1[3];
	int m_grp2[3];
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	unsigned char m_30;
	int m_34;
};

void BfmeB1050::bfmeBase1050(void)
{
	volatile int scratch[3];

	memset(m_grp1, 0, sizeof(m_grp1));
	memset(m_grp2, 0, 2 * sizeof(int));

	float f = 1.0f;
	scratch[2] = *(int *)&f;
	m_grp2[2] = scratch[2];

	scratch[0] = 0;
	scratch[1] = 0;
	m_4 = 1;
	m_5 = 0;
	scratch[0] = 0;
	scratch[1] = 0;

	m_20 = 0;
	m_28 = -1;
	m_24 = -1;
	m_2c = 0xff;
	m_30 = 1;
	m_34 = 0;
}
