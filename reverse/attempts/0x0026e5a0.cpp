// ?probe@Rva0026E5A0ListProbe@@QBE_NXZ
// partial score=0.7 date=2026-09-03
// cl: /O2 /DNDEBUG /MD
// Open-BFME6: 0x0026E5A0 list-tag probe.

struct Rva0026E5A0Node
{
	char m_pad00[8];
	Rva0026E5A0Node *m_next;
	char m_pad0C[0x14];
	unsigned m_tag20;
};

class Rva0026E5A0ListProbe
{
public:
	bool probe() const;

private:
	char m_pad00[4];
	Rva0026E5A0Node *m_head;
	char m_pad08[8];
	void *m_guard10;
};

// ?probe@Rva0026E5A0ListProbe@@QBE_NXZ
bool Rva0026E5A0ListProbe::probe() const
{
	Rva0026E5A0Node *node = m_head;
	if (node == 0)
		return false;
	if (m_guard10 == 0)
		return false;

	unsigned i = 0;
	const unsigned sentinel = 0x7FFFFFFFu;
	for (;;)
	{
		unsigned cur = i;
		++i;
		if (cur >= 100u)
			return false;
		if (node->m_tag20 != sentinel)
			return true;
		node = node->m_next;
		if (node == 0)
			return false;
	}
}
