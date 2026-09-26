// ?fillTriplesStrided@@YAXPAXHHHHH@Z
// partial score=0.8 date=2026-09-06
// 49/44 B: retail reloads the three scalar args from the stack each iteration with count in ecx; ours hoists them into ebx/edi.
struct Rva0090FDE0Triple { int m_a; int m_b; int m_c; };
void fillTriplesStrided(void* dst, int stride, int a, int b, int c, int count)
{
	for (; count; --count) {
		((Rva0090FDE0Triple*)dst)->m_a = a;
		((Rva0090FDE0Triple*)dst)->m_b = b;
		((Rva0090FDE0Triple*)dst)->m_c = c;
		dst = (char*)dst + stride;
	}
}
