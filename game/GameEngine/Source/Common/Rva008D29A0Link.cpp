// cl: /O2 /Ob0

class Rva008D29A0
{
	char m_lead[8];
	Rva008D29A0 *m_next;

public:
	void apply();
};

Rva008D29A0 *g_rva008D29A0;

void Rva008D29A0::apply()
{
	m_next = g_rva008D29A0;
	g_rva008D29A0 = this;
}
