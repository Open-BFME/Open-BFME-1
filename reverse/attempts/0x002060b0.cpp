// ?copyAt@Rva002060B0Owner@@QBEXPAURva002060B0Triple@@H@Z
// partial score=0.93 date=2026-09-04
// ?copyAt@Rva002060B0Owner@@QBEXPAURva002060B0Triple@@H@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD
// Open-BFME: 61-byte vector-or-fallback triple copy at retail 0x002060B0.
// Index in range of the pointer vector at +0x24/+0x28 selects vector[i]+8,
// otherwise the pointer at +8 plus 0x38. Copies three dwords to the out slot.
// Residue: MSVC hoists begin and borrows esi (62B) vs retail sub-from-memory (61B).

struct Rva002060B0Triple
{
	void copyTo(Rva002060B0Triple *out) const
	{
		out->m_a = m_a;
		out->m_b = m_b;
		out->m_c = m_c;
	}

	int m_a;
	int m_b;
	int m_c;
};

class Rva002060B0Value
{
public:
	const Rva002060B0Triple &triple() const { return m_triple; }

private:
	char m_pad[8];
	Rva002060B0Triple m_triple;
};

class Rva002060B0Fallback
{
public:
	const Rva002060B0Triple &triple() const { return m_triple; }

private:
	char m_pad[0x38];
	Rva002060B0Triple m_triple;
};

class Rva002060B0Vector
{
public:
	int size() const { return m_end - m_begin; }
	Rva002060B0Value *const &operator[](int index) const { return m_begin[index]; }

private:
	Rva002060B0Value **m_begin;
	Rva002060B0Value **m_end;
};

class Rva002060B0Owner
{
public:
	void copyAt(Rva002060B0Triple *out, int index) const;

private:
	char m_pad0[8];
	Rva002060B0Fallback *m_fallback;
	char m_padC[0x24 - 0x0C];
	Rva002060B0Vector m_values;
};

void Rva002060B0Owner::copyAt(Rva002060B0Triple *out, int index) const
{
	Rva002060B0Triple *dst = out;
	const Rva002060B0Triple &src =
		(index >= 0 && (unsigned int)index < (unsigned int)m_values.size())
		? m_values[index]->triple()
		: m_fallback->triple();
	src.copyTo(dst);
}
