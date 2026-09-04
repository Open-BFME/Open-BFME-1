// ?fill@Rva001C6820@@QAEXPAUBits001C6820@@@Z
// partial score=0.72 date=2026-09-04
// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x001C6820 (58B): load m_index first, zero a 6-dword out bitfield via
// esi, then load/or/store the selected bit (not or-mem).

struct Bits001C6820
{
	unsigned m_words[6];
};

class Rva001C6820
{
public:
	void fill(Bits001C6820 *out);

private:
	char m_pad[0x20];
	unsigned m_index;							///< +0x20
};

// ?fill@Rva001C6820@@QAEXPAUBits001C6820@@@Z
void Rva001C6820::fill(Bits001C6820 *out)
{
	unsigned index = m_index;
	unsigned *words = out->m_words;
	unsigned zero = 0;
	words[0] = zero;
	words[1] = zero;
	words[2] = zero;
	words[3] = zero;
	words[4] = zero;
	words[5] = zero;
	unsigned mask = 1u << (index & 31);
	unsigned *slot = &words[index >> 5];
	*slot = *slot | mask;
}
