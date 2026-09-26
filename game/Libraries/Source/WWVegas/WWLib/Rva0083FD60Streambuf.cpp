// cl: /O2 /MD

// An adjacent STLport instantiation emits the same triple-pointer shape, but
// no caller proves this copy's owner.
struct Rva0083FD60Streambuf
{
	void *m_0;
	char *m_04;
	char *m_08;
	char *m_0c;
	void rva0083FD60(char *begin, char *current, char *end);
};

void Rva0083FD60Streambuf::rva0083FD60(char *begin, char *current, char *end)
{
	m_04 = begin;
	m_08 = current;
	m_0c = end;
}
