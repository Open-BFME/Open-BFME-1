// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Drain the node at +0x10. When +0xC is null and +0x7C is set, run
// BfmeThingCDE::bfmeGoCDE on that pointer; otherwise the sibling at 0x006BD1A0.

class BfmeThingCDE
{
public:
	void bfmeGoCDE();
};

class Rva006BDB00Node
{
public:
	char m_pad0C[0xC];
	void *m_alt;
	char m_pad7C[0x7C - 0x10];
	BfmeThingCDE *m_thing;
	char m_pad80[0x110 - 0x80];
	Rva006BDB00Node *m_next;
	Rva006BDB00Node *m_prev;
};

void j_00031d63();

typedef void (__fastcall *Rva006BDB00Process)(Rva006BDB00Node *node);

class Rva006BDB00
{
public:
	void drain();
	void handleNode(Rva006BDB00Node *node);

private:
	char m_pad0C[0xC];
	Rva006BDB00Node *m_tail;
	Rva006BDB00Node *m_head;
};

void Rva006BDB00::drain()
{
	Rva006BDB00Node *node = m_head;
	while (node)
	{
		if (node->m_alt == 0 && node->m_thing != 0)
			node->m_thing->bfmeGoCDE();
		else
			handleNode(node);
		node = m_head;
	}
}

void Rva006BDB00::handleNode(Rva006BDB00Node *node)
{
	if (node == 0)
		return;
	((Rva006BDB00Process)j_00031d63)(node);

	Rva006BDB00Node *current = m_head;
	while (current != 0 && current != node)
		current = current->m_next;
	if (current != 0)
	{
		current = m_tail;
		for (; current != 0; current = current->m_next)
			if (current == node)
				break;
		if (current != 0)
			return;

		if (node->m_next != 0)
			node->m_next->m_prev = node->m_prev;
		if (node->m_prev != 0)
			node->m_prev->m_next = node->m_next;
		else
			m_head = node->m_next;
		node->m_prev = 0;
		node->m_next = m_tail;
		if (m_tail != 0)
			m_tail->m_prev = node;
		m_tail = node;
	}
}
