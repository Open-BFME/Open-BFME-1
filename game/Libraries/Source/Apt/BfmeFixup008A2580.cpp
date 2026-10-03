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
	void apply(void *a, BfmeFixupChunk2580 *chunk, void *c);

	char m_pad[0x30];
	int m_flag;
};

// The matched helper dump exports only this no-argument object symbol. The
// typed view keeps this in ECX and the original stack arguments; its spare
// EDX slot repeats `a`, which is already live there.
void d_008a2130(void);

void BfmeFixup2580::apply(void *a, BfmeFixupChunk2580 *chunk, void *c)
{
	BfmeFixupChunk2580 *p = chunk;
	if (p->m_rel != 0)
		p->m_rel += (int)p;
	m_flag = 0;
	typedef void (__fastcall *DumpHelper)(void *, void *,
		void *, BfmeFixupChunk2580 *, void *);
	reinterpret_cast<DumpHelper>(&d_008a2130)(this, a, a, p, c);
	if (p->m_rel != 0)
		p->m_rel -= (int)p;
}
