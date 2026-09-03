// cl: /DNDEBUG /MD /O2
// Open-BFME5: GenBase003BB1E0 constructor. Retail 0x003BB1E0, 81 bytes.
// Vftable, then an inlined 0x2c-byte red-black header at +4, then four dword
// zeros, two bytes and 1.0f. Tree member ctor writes the +0x10..+0x1c zeros
// so add esp stays after them once inlined; outer vtable stays first.

void *bfmeAllocNode(unsigned int bytes);

class GenBase003BB1E0;

struct Rva003BB1E0Node
{
	char color;
	int *parent;
	Rva003BB1E0Node *left;
	Rva003BB1E0Node *right;
};

struct Rva003BB1E0Tree
{
	Rva003BB1E0Node *header;
	int count;
	Rva003BB1E0Tree(GenBase003BB1E0 *outer);
};

class GenBase003BB1E0
{
public:
	GenBase003BB1E0();
	virtual void handle();

	Rva003BB1E0Tree m_tree;
	int m_at0C;
	int m_at10;
	void *m_at14;
	void *m_at18;
	void *m_at1C;
	char m_at20;
	char m_at21;
	float m_at24;
};

Rva003BB1E0Tree::Rva003BB1E0Tree(GenBase003BB1E0 *outer)
{
	header = 0;
	header = (Rva003BB1E0Node *)bfmeAllocNode(0x2c);
	count = 0;
	header->color = 0;
	header->parent = 0;
	header->left = header;
	header->right = header;
	int *z = &outer->m_at10;
	z[0] = 0;
	z[1] = 0;
	z[2] = 0;
	z[3] = 0;
}

// ??0GenBase003BB1E0@@QAE@XZ
GenBase003BB1E0::GenBase003BB1E0()
	: m_tree(this)
	, m_at20(0)
	, m_at21(0)
	, m_at24(1.0f)
{
}
