// ?setUsed@Rva00882550Buffer@@QAEXH@Z
// partial score=0.9 date=2026-09-06
// 42/42 B, 10 diff bytes: retail loads the guard-word global before storing m_used (load hoisted above an unrelated store); cast-call of the ?d_ dump body emits the direct call.
extern int Rva00882550GuardWords;
void __cdecl d_008823e0();
typedef void (__cdecl* Rva00882550Fill)(void* dst, int pattern, int bytes);
struct Rva00882550Buffer {
	int m_0; int m_4;
	int m_used;
	char m_bytes[1];
	void setUsed(int used);
};
void Rva00882550Buffer::setUsed(int used)
{
	m_used = used;
	if (Rva00882550GuardWords)
		((Rva00882550Fill)d_008823e0)(m_bytes + used, 0xbadf00d, Rva00882550GuardWords * 4);
}
