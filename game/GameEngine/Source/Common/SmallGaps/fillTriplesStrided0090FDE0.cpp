// Retail 0x0090FDE0: fill three integers at each strided destination.
// Volatile by-value arguments preserve retail's per-iteration stack reads.
struct Rva0090FDE0Triple { int m_a; int m_b; int m_c; };
void fillTriplesStrided0090FDE0(void* dst, int stride, volatile int a, volatile int b, volatile int c, int count)
{
	for (; count; --count) {
		((Rva0090FDE0Triple*)dst)->m_a = a;
		((Rva0090FDE0Triple*)dst)->m_b = b;
		((Rva0090FDE0Triple*)dst)->m_c = c;
		dst = (char*)dst + stride;
	}
}
