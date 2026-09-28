// ?d_000de160@@YAXXZ
// partial score=0.8596 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
struct BfmeSwapTailCJ;
void __cdecl bfmeSwapTailCJ(BfmeSwapTailCJ *first, BfmeSwapTailCJ *second);

struct Rva000DE160
{
	unsigned int volatile m_word00;
	unsigned int volatile m_word04;
	unsigned int volatile m_word08;
	char m_tail[4];

	void swap(Rva000DE160 * volatile other);
};

void Rva000DE160::swap(Rva000DE160 * volatile other)
{
	Rva000DE160 *otherObject = other;
	unsigned int thisValue = m_word00;
	unsigned int otherValue = otherObject->m_word00;
	m_word00 = otherValue;
	otherObject->m_word00 = thisValue;

	otherValue = otherObject->m_word04;
	thisValue = m_word04;
	m_word04 = otherValue;
	otherObject->m_word04 = thisValue;

	otherValue = otherObject->m_word08;
	thisValue = m_word08;
	m_word08 = otherValue;
	otherObject->m_word08 = thisValue;

	bfmeSwapTailCJ(reinterpret_cast<BfmeSwapTailCJ *>(m_tail),
		reinterpret_cast<BfmeSwapTailCJ *>(otherObject->m_tail));
}
