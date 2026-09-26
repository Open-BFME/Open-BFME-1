// ?addState@Rva0083ED40Stream@@QAEXH@Z
// partial score=0.9 date=2026-09-06
// Open-BFME7: STLport ios_base state setters with exceptions off (2 x 50 B):
// the failure path reports through the global callback instead of throwing.
extern void* g_global;
extern void (__cdecl* g_call)(const char* what, void* where);
struct Rva0083ED40Stream {
	int m_0; int m_4;
	int m_state;
	int m_c; int m_10;
	int m_exceptions;
	char m_pad[0x58 - 0x18];
	void* m_buffer;
	void addState(int state);
};
void Rva0083ED40Stream::setState(int state)
{
	if (!m_buffer)
		state |= 1;
	m_state = state;
	if (m_exceptions & state)
		g_call("ios failure", (char*)g_global + 0x40);
}
void Rva0083ED40Stream::addState(int state)
{
	state = m_state | state;
	if (!m_buffer)
		state |= 1;
	m_state = state;
	if (m_exceptions & state)
		g_call("ios failure", (char*)g_global + 0x40);
}
