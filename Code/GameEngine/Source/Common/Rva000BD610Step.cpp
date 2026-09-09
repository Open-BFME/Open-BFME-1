// Address-derived name: real identity not recovered.
// Callee at retail 0x0001E6A5 is the matched thunk j_0001e6a5 (thunks_014.cpp);
// pinned here under this file's own extern name since that call needs real
// arguments the thunk's own void() declaration does not carry.
void * __cdecl Rva0001E6A5Helper(void *first, void *second, void *third, char *status, int flag);

class Rva000BD610Owner
{
public:
	void step(void);

	unsigned char m_head[8];
	void *m_src;
	void *m_cur;
};

void Rva000BD610Owner::step(void)
{
	int flag = 0;
	void *third = m_src;
	void *cur = m_cur;
	char status;
	m_cur = Rva0001E6A5Helper(cur, cur, third, &status, flag);
}
