// cl: /DNDEBUG /MD /O2
// Open-BFME5: thiscall constructor storing a 2-slot vftable, a dword, a byte,
// then inlining a 0x2c-byte red-black header allocate. Retail 0x003BA5F0, 62
// bytes. The tree is a member so push 0x2c sits after the byte store.

void *bfmeAllocNode(unsigned int bytes);

struct Rva003BA5F0Node
{
	char color;
	int *parent;
	Rva003BA5F0Node *left;
	Rva003BA5F0Node *right;
};

struct Rva003BA5F0TreeBase
{
	Rva003BA5F0Node *header;
	Rva003BA5F0TreeBase()
	{
		header = 0;
		header = (Rva003BA5F0Node *)bfmeAllocNode(0x2c);
	}
};

struct Rva003BA5F0Tree : Rva003BA5F0TreeBase
{
	int count;
	Rva003BA5F0Tree()
		: count(0)
	{
		header->color = 0;
		header->parent = 0;
		header->left = header;
		header->right = header;
	}
};

class Rva003BA5F0
{
public:
	Rva003BA5F0();
	virtual void slot00();
	virtual void slot04();

private:
	int m_at04;
	char m_at08;
	Rva003BA5F0Tree m_tree;
};

Rva003BA5F0::Rva003BA5F0()
	: m_at04(0)
	, m_at08(0)
{
}
