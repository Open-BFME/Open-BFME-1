// ?copyPairsStrided@@YAXPAXHPBURva0090FE10Pair@@H@Z
struct Rva0090FE10Pair { int m_a; int m_b; };
void copyPairsStrided(void* dst, int stride, const Rva0090FE10Pair* src, int count)
{
	for (; count; --count) {
		((Rva0090FE10Pair*)dst)->m_a = src->m_a;
		((Rva0090FE10Pair*)dst)->m_b = src->m_b;
		++src;
		dst = (char*)dst + stride;
	}
}
