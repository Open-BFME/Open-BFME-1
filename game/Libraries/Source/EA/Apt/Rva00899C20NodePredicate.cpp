// ?rva00899C20@Rva00899C20Node@@QAEHXZ
// Retail 0x00899C20: address-derived Apt/node predicate.  The receiver and
// linked records use the existing +0x18 virtual slot; this TU declares that
// interface only and emits no vtable or constructor.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00899C20Node;

class Rva00899C20LookupResult
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Rva00899C20Node *slot18();

	unsigned m_pad00;
	unsigned m_pad04;
	unsigned m_pad08;
	unsigned m_flags;
};

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

struct Rva00899C20Registry
{
	char m_pad00[8];
	BfmeTab1024 m_table;
};

extern Rva00899C20Registry *g_Va013387D8;
extern unsigned char g_Va013385F8;
extern char g_rva8D0D80CreateTag;

class Rva00899C20Node
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Rva00899C20Node *slot18();

	unsigned m_kind;
	unsigned m_link;
	unsigned m_flags;

	int rva00899C20();
};

int Rva00899C20Node::rva00899C20()
{
	Rva00899C20Node *first = reinterpret_cast<Rva00899C20Node *>(
		reinterpret_cast<Rva00899C20LookupResult *>(g_Va013387D8->m_table.bfmeFind1024(
			reinterpret_cast<int>(&g_Va013385F8)))->slot18()->m_flags & ~1u);
	Rva00899C20Node *second = reinterpret_cast<Rva00899C20Node *>(
		reinterpret_cast<Rva00899C20LookupResult *>(g_Va013387D8->m_table.bfmeFind1024(
			reinterpret_cast<int>(&g_rva8D0D80CreateTag)))->slot18()->m_flags & ~1u);

	if (this == first)
		return 1;

	Rva00899C20Node *cursor = slot18();
	while (cursor != 0)
	{
		Rva00899C20Node *owner = reinterpret_cast<Rva00899C20Node *>(cursor->m_link & ~1u);
		if (owner == 0)
			return 0;
		if (owner == first)
			return 1;
		if (owner == second)
			return 0;
		cursor = owner->slot18();
	}

	return 0;
}
