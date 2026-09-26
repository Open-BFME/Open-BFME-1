// ?insertRva008A9AB0@Rva008C3B60Node@@QAEXXZ
// cl: /O2 /Ob0

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
};

struct Rva0089E1E0
{
	BfmeStringData3AF0 *m_inner;
	unsigned char cmp(int value);
};

struct Rva008C3B60Node
{
	void *m_vptr;
	int m_4;
	Rva0089E1E0 m_8;
	Rva008C3B60Node *m_next;

	void insertRva008A9AB0(void);
};

extern Rva008C3B60Node *Rva008C3B60Head;

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

void Rva008C3B60Node::insertRva008A9AB0(void)
{
	m_next = Rva008C3B60Head;
	Rva008C3B60Head = this;

	if (m_8.cmp(0x21))
	{
		BfmeStringData3AF0 *data = m_8.m_inner;

		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);

		m_8.m_inner = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
	}
}
