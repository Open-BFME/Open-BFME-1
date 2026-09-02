// ?copyAt@Rva002060B0Owner@@QBEXPAURva002060B0Triple@@H@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD
// Open-BFME: 61-byte vector-or-fallback triple copy at retail 0x002060B0.
// Index in range of the pointer vector at +0x24/+0x28 selects vector[i]+8,
// otherwise the pointer at +8 plus 0x38. Copies three dwords to the out slot.
// Residue: MSVC hoists begin and borrows esi (62B) vs retail sub-from-memory (61B).

struct Rva002060B0Triple
{
	int m_a;
	int m_b;
	int m_c;
};

class Rva002060B0Owner
{
public:
	void copyAt(Rva002060B0Triple *out, int index) const;

private:
	char m_pad0[8];
	char *m_fallback;
	char m_padC[0x24 - 0x0C];
	char **m_begin;
	char **m_end;
};

void Rva002060B0Owner::copyAt(Rva002060B0Triple *out, int index) const
{
	Rva002060B0Triple *src;
	if (index >= 0)
	{
		if ((unsigned int)index < (unsigned int)(m_end - m_begin))
			src = (Rva002060B0Triple *)(m_begin[index] + 8);
		else
			src = (Rva002060B0Triple *)(m_fallback + 0x38);
	}
	else
		src = (Rva002060B0Triple *)(m_fallback + 0x38);
	*out = *src;
}
