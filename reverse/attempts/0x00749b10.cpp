// ?bfmeMarkAX@Rva00749B10MaskAX@@QAEXHH_N@Z
// partial score=0.85 date=2026-09-11
// Guard and index section (x<0||y<0||y>=height||x>=width, idx=stride*y+(x>>3),
// idx>=end-begin) matches retail exactly through +0x31 (score 0.94 stash, this
// candidate). Hoisting the loaded byte into a named local `b`, defined AFTER
// `p` and BEFORE `mask`, with `on` tested via if/else (each arm its own
// return) reproduces retail's push-ebx/dual-pop-epilogue register pattern for
// the byte -- no prior stash reached that structural shape. Two residues
// remain, both proven uncontrollable from clean C++ so far:
// (1) retail reloads begin into ECX (reusing the dead `this` register) and
//     folds the +idx with a single `lea edx,[eax+ecx]`; every variant here
//     (volatile pointer-cast, `begin+idx` vs `idx+begin`, plain pointer add)
//     instead loads begin into EDX and emits a separate `add edx,eax`,
//     costing exactly the one byte this candidate is short (95 of 96).
// (2) the OR/AND that combines `mask` (in AL) and `b` (in BL) always lands
//     with AL as the destination in this compile; retail's binary keeps BL as
//     the destination and stores from BL. Source-level operand order
//     (`b|mask` vs `mask|b`) and in-place mutation (`b |= mask;`) make no
//     difference to the compiled choice.
class Rva00749B10MaskAX
{
public:
	void bfmeMarkAX(int x, int y, unsigned char value);

	unsigned char m_pad00[8];
	int m_width;
	int m_height;
	unsigned char m_pad10[0x34 - 0x10];
	int m_pitch;
	unsigned char m_pad38[0x68 - 0x38];
	unsigned char *m_begin;
	unsigned char *m_end;
};

void Rva00749B10MaskAX::bfmeMarkAX(int x, int y, unsigned char value)
{
	if (x < 0 || y < 0 || y >= m_height || x >= m_width)
		return;

	int idx = m_pitch * y + (x >> 3);

	if ((unsigned int)idx >= (unsigned int)(m_end - m_begin))
		return;

	unsigned char *p = *(unsigned char *volatile *)&m_begin + idx;
	unsigned char b = *(unsigned char volatile *)p;
	unsigned char mask = (unsigned char)(1 << (x & 7));

	if (value)
	{
		*p = (unsigned char)(mask | b);
		return;
	}
	*p = (unsigned char)((unsigned char)~mask & b);
}
