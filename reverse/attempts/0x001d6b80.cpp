// ??0?$pair@$$CBUGen_t_001d7000_k4@@UGen_t_001d7000_p12cd@@@_STL@@QAE@ABU01@@Z
// partial score=0.96 date=2026-09-02
// cl: /EHsc
// Three-member thiscall copy constructor. Retail copies subobjects at +0,
// +4 and +8 through out-of-line copy ctors, EH states 0 then 1. Adjacent
// swap of `lea ecx,[esi+4]` vs `push eax` on the second copy remains.

class Rva001D6B80Part
{
public:
	Rva001D6B80Part(const Rva001D6B80Part &other);
	~Rva001D6B80Part();

private:
	int m_value;
};

class Rva001D6B80
{
public:
	Rva001D6B80(const Rva001D6B80 &other);

private:
	Rva001D6B80Part m_a;
	Rva001D6B80Part m_b;
	Rva001D6B80Part m_c;
};

Rva001D6B80::Rva001D6B80(const Rva001D6B80 &other)
	: m_a(other.m_a)
	, m_b(other.m_b)
	, m_c(other.m_c)
{
}
