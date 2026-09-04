// ?d_003c2f40@@YAXXZ
// cl: /DNDEBUG /MD /O2 /EHsc
// The body is the EH-framed construction of the red-black header embedded at
// +0x0c.  Its vtable and the two preceding scalar members are established by
// the surrounding VNI construction path; this constructor only runs the tree
// member's initialization.

void *bfmeAllocNode(unsigned int bytes);

struct Rva003C2F40Node
{
	char m_color;
	int *m_parent;
	Rva003C2F40Node *m_left;
	Rva003C2F40Node *m_right;
};

struct Rva003C2F40Tree
{
	Rva003C2F40Node *m_header;
	int m_count;

	Rva003C2F40Tree();
};

Rva003C2F40Tree::Rva003C2F40Tree()
{
	m_header = 0;
	m_header = (Rva003C2F40Node *)bfmeAllocNode(0x2c);
	m_count = 0;
	m_header->m_color = 0;
	m_header->m_parent = 0;
	m_header->m_left = m_header;
	m_header->m_right = m_header;
}

class Rva003C2F40Base
{
public:
	Rva003C2F40Base();
	virtual ~Rva003C2F40Base();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};

Rva003C2F40Base::Rva003C2F40Base()
{
}

Rva003C2F40Base::~Rva003C2F40Base()
{
}

void Rva003C2F40Base::handle()
{
}

class Rva003C2F40Owner : public Rva003C2F40Base
{
public:
	Rva003C2F40Owner();
	virtual ~Rva003C2F40Owner();
	Rva003C2F40Tree m_tree;
};

Rva003C2F40Owner::Rva003C2F40Owner()
{
}

Rva003C2F40Owner::~Rva003C2F40Owner()
{
}
