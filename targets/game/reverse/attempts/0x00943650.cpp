// ??0Rva00943650Owner@@QAE@XZ
// partial score=0.7 date=2026-09-06
struct Rva00943650Link {
	Rva00943650Link* m_next; Rva00943650Link* m_prev; int m_count; int m_a; int m_b;
	Rva00943650Link()
	{
		m_count = 0; m_prev = 0; m_next = 0; m_a = 0; m_b = 0;
		m_next = this; m_prev = this; m_a = 0; m_count = 0;
	}
};
struct Rva00943650Sub : Rva00943650Link { virtual ~Rva00943650Sub(); };
struct Rva00943650Owner { int m_0; Rva00943650Sub m_sub; Rva00943650Owner(); };
Rva00943650Owner::Rva00943650Owner() : m_0(0) {}
