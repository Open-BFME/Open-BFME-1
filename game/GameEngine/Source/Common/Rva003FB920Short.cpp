// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva003FB920Short
{
public:
	void set(short value);

private:
	char m_pad[0x0A];
	short m_value;
};

void Rva003FB920Short::set(short value)
{
	m_value = value;
}

struct Rva003FB9F0Node
{
	int m_pad;
	Rva003FB9F0Node *m_next;
};

class Rva003FB9F0List
{
public:
	void push(Rva003FB9F0Node *node);

private:
	char m_pad[0x3C];
	Rva003FB9F0Node *m_head;
};

void Rva003FB9F0List::push(Rva003FB9F0Node *node)
{
	node->m_next = m_head;
	m_head = node;
}
