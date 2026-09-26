// cl: /O2 /Ob0

class Rva008D2A10
{
	char m_lead[8];
	Rva008D2A10 *m_next;

public:
	void apply();
};

Rva008D2A10 *g_rva008D2A10;

void Rva008D2A10::apply()
{
	m_next = g_rva008D2A10;
	g_rva008D2A10 = this;
}
