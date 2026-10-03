// ?insertRva008A9AB0@Rva008C3B60Node@@QAEXXZ
// cl: /O2 /Ob0

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
};

class EAStringC
{
public:
	class StringDataC;
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

// The cell at 0x01338478 is defined once, by its canonical spelling, in
// game/GameEngine/Source/Common/Data/Rva01338478.cpp.  This TU's view of
// Rva008C3B60Node is local, but MSVC mangles only the pointee class name, so
// the spelling below is the same symbol retail's references bind to.
extern Rva008C3B60Node *g_rva01338478NodeHead;

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern EAStringC::StringDataC g_rva012D5298Empty;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

void Rva008C3B60Node::insertRva008A9AB0(void)
{
	m_next = g_rva01338478NodeHead;
	g_rva01338478NodeHead = this;

	if (m_8.cmp(0x21))
	{
		BfmeStringData3AF0 *data = m_8.m_inner;

		if (--data->m_refCount == 0)
			g_rva01337A30AllocPair->free(data);

		m_8.m_inner = (BfmeStringData3AF0 *)&g_rva012D5298Empty;
		++((BfmeStringData3AF0 *)&g_rva012D5298Empty)->m_refCount;
	}
}
