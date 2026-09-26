// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob0

class Rva001608D0Node
{
public:
	char m_pad00[0xc];
	Rva001608D0Node *m_prev;
	Rva001608D0Node *m_next;
};

class Rva001608D0
{
public:
	void add(register Rva001608D0Node *node);

private:
	char m_pad00[8];
	Rva001608D0Node *volatile m_head;
};

void Rva001608D0::add(register Rva001608D0Node *node)
{
	if (m_head == node)
		return;
	if (*(Rva001608D0Node **)((char *)node + 0xc) != 0)
		return;
	if (*(Rva001608D0Node **)((char *)node + 0x10) != 0)
		return;
	*(Rva001608D0Node **)((char *)node + 0x10) = m_head;
	Rva001608D0Node *head = m_head;
	if (head != 0)
		*(Rva001608D0Node **)((char *)head + 0xc) = node;
	m_head = node;
}
