// ?dispatch@Rva00150ED0Host@@QAEXHH@Z
// Address-derived owner for the exact retail body at RVA 0x00150ED0.

struct RvaC4390Interface
{
	virtual void dispatch(int a, int b) = 0;
};

class RvaC4390First
{
public:
	RvaC4390Interface *getInterface();
};

struct Rva00150ED0Node
{
	Rva00150ED0Node *volatile m_next;
	unsigned char m_pad[4];
	RvaC4390First *m_first;
};

class Rva00150ED0List
{
public:
	bool empty() const { return m_node->m_next == m_node; }
	RvaC4390First *front() const { return m_node->m_next->m_first; }

	Rva00150ED0Node *m_node;
};

class Rva00150ED0Host
{
public:
	void dispatch(int a, int b);

	unsigned char m_head[4];
	Rva00150ED0List m_list;
};

void Rva00150ED0Host::dispatch(int a, int b)
{
	if (m_list.empty())
		return;

	RvaC4390Interface *iface = m_list.front()->getInterface();

	if (iface == 0)
		return;

	iface->dispatch(a, b);
}
