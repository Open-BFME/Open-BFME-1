// Open-BFME: relative-pointer fixup wrapper, retail 0x008A2580.

class BfmeFixupChunk2580
{
public:
	char m_pad[0x1c];
	int m_rel;
};

class BfmeFixup2580
{
public:
	void helper(void *a, BfmeFixupChunk2580 *chunk, void *c);
	void apply(void *a, BfmeFixupChunk2580 *chunk, void *c);

	char m_pad[0x30];
	int m_flag;
};

void BfmeFixup2580::apply(void *a, BfmeFixupChunk2580 *chunk, void *c)
{
	BfmeFixupChunk2580 *p = chunk;
	if (p->m_rel != 0)
		p->m_rel += (int)p;
	m_flag = 0;
	helper(a, p, c);
	if (p->m_rel != 0)
		p->m_rel -= (int)p;
}
