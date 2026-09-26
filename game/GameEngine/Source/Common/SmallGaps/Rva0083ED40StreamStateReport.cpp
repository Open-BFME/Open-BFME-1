// ?setState@Rva0083ED40Stream@@QAEXH@Z
// STLport ios-style stream state setters with exceptions off:
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
	void setState(int state);
	void addState(int state);
	void rva0083ED00(int exceptions);
	void rva0083EDB0(int exceptions);
	void *rva0083EFE0(void *buffer);
	__forceinline void clearState(int state)
	{
		if (!m_buffer)
			state |= 1;
		m_state = state;
		if (m_exceptions & state)
			g_call("ios failure", (char*)g_global + 0x40);
	}
	__forceinline void applyState(int state)
	{
		m_state = state;
		if (m_exceptions & state)
			g_call("ios failure", (char*)g_global + 0x40);
	}
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
	clearState(m_state | state);
}

void Rva0083ED40Stream::rva0083EDB0(int exceptions)
{
	m_exceptions = exceptions;
	clearState(m_state);
}

void Rva0083ED40Stream::rva0083ED00(int exceptions)
{
	m_exceptions = exceptions;
	clearState(m_state);
}

void *Rva0083ED40Stream::rva0083EFE0(void *buffer)
{
	void *old = m_buffer;
	m_buffer = buffer;
	applyState(buffer == 0);
	return old;
}
