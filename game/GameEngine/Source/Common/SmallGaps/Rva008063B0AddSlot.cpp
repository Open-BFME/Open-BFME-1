// ?addSlot@Rva008063B0Owner@@QAEXHH@Z
struct Rva008063B0Diag {
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void report(const char* message, const char* file, int line);
};
Rva008063B0Diag* __cdecl Rva007EB810Get();
extern char g_bfmeMsgUVB[];
struct Rva008063B0Slot { int m_a; int m_b; };
struct Rva008063B0Owner {
	int m_0;
	int m_4;
	Rva008063B0Slot m_slots[8];
	void addSlot(int a, int b);
};
void Rva008063B0Owner::addSlot(int a, int b)
{
	for (Rva008063B0Slot* s = m_slots; s < m_slots + 8; ++s) {
		if (s->m_a == 0) {
			s->m_a = a;
			s->m_b = b;
			return;
		}
	}
	Rva007EB810Get()->report(g_bfmeMsgUVB, "\\views\\feslbuild_main\\jabba\\fesl\\source\\statemachine.cpp", 0x6b);
}
