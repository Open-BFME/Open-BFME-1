// cl: /O2 /Ob0

class Rva008D2A80
{
	char m_lead[8];
	Rva008D2A80 *m_next;

public:
	void apply();
};

Rva008D2A80 *g_rva008D2A80;

void Rva008D2A80::apply()
{
	m_next = g_rva008D2A80;
	g_rva008D2A80 = this;
}
