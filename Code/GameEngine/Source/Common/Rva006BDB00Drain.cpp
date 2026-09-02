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
};

class Rva006BDB00
{
public:
	void drain();
	void handleNode(Rva006BDB00Node *node);

private:
	char m_pad10[0x10];
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
