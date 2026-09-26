// Retail 0x0034FB40, 0x0034FBA0 and 0x0034FC00, 72 bytes each.
// These are the three ScriptEngine-owned unlink-and-delete list helpers.

class Rva0034FB40Node
{
public:
	virtual ~Rva0034FB40Node(void);
	Rva0034FB40Node *m_next;
};

class Rva0034FB40Owner
{
public:
	void remove(Rva0034FB40Node *node);

private:
	char m_pad[0x1c];
	Rva0034FB40Node *m_head;
};

void Rva0034FB40Owner::remove(Rva0034FB40Node *node)
{
	Rva0034FB40Node *current = m_head;
	Rva0034FB40Node *previous = 0;
	while (node != current)
	{
		previous = current;
		current = current->m_next;
	}
	if (current != 0)
	{
		if (previous != 0)
			previous->m_next = current->m_next;
		else
			m_head = current->m_next;
		current->m_next = 0;
		delete current;
	}
}

class Rva0034FBA0Node
{
public:
	virtual ~Rva0034FBA0Node(void);
	char m_pad[0x38];
	Rva0034FBA0Node *m_next;
};

class Rva0034FBA0Owner
{
public:
	void remove(Rva0034FBA0Node *node);

private:
	char m_pad[0x20];
	Rva0034FBA0Node *m_head;
};

void Rva0034FBA0Owner::remove(Rva0034FBA0Node *node)
{
	Rva0034FBA0Node *current = m_head;
	Rva0034FBA0Node *previous = 0;
	while (node != current)
	{
		previous = current;
		current = current->m_next;
	}
	if (current != 0)
	{
		if (previous != 0)
			previous->m_next = current->m_next;
		else
			m_head = current->m_next;
		current->m_next = 0;
		delete current;
	}
}

class Rva0034FC00Node
{
public:
	virtual ~Rva0034FC00Node(void);
	char m_pad[0x38];
	Rva0034FC00Node *m_next;
};

class Rva0034FC00Owner
{
public:
	void remove(Rva0034FC00Node *node);

private:
	char m_pad[0x24];
	Rva0034FC00Node *m_head;
};

void Rva0034FC00Owner::remove(Rva0034FC00Node *node)
{
	Rva0034FC00Node *current = m_head;
	Rva0034FC00Node *previous = 0;
	while (node != current)
	{
		previous = current;
		current = current->m_next;
	}
	if (current != 0)
	{
		if (previous != 0)
			previous->m_next = current->m_next;
		else
			m_head = current->m_next;
		current->m_next = 0;
		delete current;
	}
}
