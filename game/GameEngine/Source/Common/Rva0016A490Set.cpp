// cl: /O2 /Ob0

class Rva0016A490;

struct Rva0016A490Node
{
	char m_lead[4];
	Rva0016A490 *m_owner;
};

class Rva0016A490
{
	Rva0016A490Node *m_ptr;

public:
	void set(Rva0016A490Node *p);
};

void Rva0016A490::set(Rva0016A490Node *p)
{
	m_ptr = p;
	if (p)
		p->m_owner = this;
}
