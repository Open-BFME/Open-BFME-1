// cl: /Od
// Open-BFME5 conversions.

extern "C" void __cdecl bfmeCopy1152(char *d0, char *d1, char *s0, char *s1);

class BfmeR1152
{
public:
	char *m_begin;
	char *m_end;
};

class BfmeS1152
{
public:
	void bfmeReplace1152(unsigned int pos, unsigned int count, BfmeR1152 *src);
	void bfmeThrow1152(void);
	char *m_begin;
	char *m_end;
};

void BfmeS1152::bfmeReplace1152(unsigned int pos, unsigned int count, BfmeR1152 *src)
{
	// /Od orders frame slots by a name-derived key, so renaming any local here
	// moves every ebp offset in the body. This exact set of names reproduces
	// retail; re-verify with ./build.sh before changing one.
	const unsigned int *chosen;
	// Retail reserved a 0x20-byte frame. These four slots have no live value
	// left in this reconstruction, but dropping them shrinks `sub esp` to 0x10.
	int frameSlot1;
	int frameSlot2;
	int frameSlot3;
	unsigned int tailLen;
	int frameSlot4;

	if (pos > (unsigned int)(m_end - m_begin))
		bfmeThrow1152();

	tailLen = (unsigned int)(m_end - m_begin) - pos;
	// The shorter of the two is taken by address, not by value: retail keeps the
	// pair of `lea`s and the pointer spill that a value-returning min folds away.
	chosen = (tailLen < count) ? &tailLen : &count;
	bfmeCopy1152(m_begin + pos, m_begin + pos + *chosen, src->m_begin, src->m_end);
}
