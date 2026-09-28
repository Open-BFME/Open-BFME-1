// ?init@Rva008824E0Block@@QAEXI@Z
// partial score=0.99 date=2026-09-28
// Best candidate for ?init@Rva008824E0Block@@QAEXI@Z at 0x008824E0 (105B).
// Probe: size exact, shape 1.000, 1 non-reloc byte: retail lea eax,[edx+esi+0x0c],
// ours lea eax,[esi+edx+0x0c] at +0x33. Five operand-order variants tried.
// Place inside game/GameEngine/Source/Common/System/memory_pool.cpp after memset32,
// with class Rva008824E0Block { void init(unsigned); void *m_field00; void *m_field04; unsigned m_size08; };
void Rva008824E0Block::init(unsigned int used)
{
	extern int Rva0130EA00GuardWords;
	m_size08 = used;
	unsigned int guardWords = Rva0130EA00GuardWords;
	m_field00 = 0;
	if (guardWords != 0)
	{
		unsigned int guardBytes = guardWords * 4;
		memset32((char *)this - guardBytes, 0x0BADF00D, guardBytes);
		memset32((char *)((unsigned int)this + (m_size08 + 0x0c)), 0x0BADF00D, guardBytes);
	}
	if (*(volatile unsigned int *)0x0130EA04 != 0)
	{
		unsigned int size = m_size08;
		memset32((char *)this + 0x0c, 0xDEADC0DE, size);
	}
}
