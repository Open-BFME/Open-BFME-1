// ??0Rva00476380Owner@@QAE@XZ
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /MD /O2 /EHsc
// FUZZY-TWIN of ??0Rva003C2F40Owner@@QAE@XZ (0x003C2F40, 100B, Code/
// GameEngine/Source/Common/Rva003C2F40TreeCtor.cpp): same EH-framed
// red-black header construction, but this owner zero-initialises two extra
// leading dword members (the twin's Base ctor is empty and never touches
// them) and the header node allocation is 0x18 bytes instead of the twin's
// 0x2c -- a smaller map/set value type. Same already-matched STLport
// allocator callee.

void *bfmeAllocNode(unsigned int bytes);

struct Rva00476380Node
{
	char m_color;
	int *m_parent;
	Rva00476380Node *m_left;
	Rva00476380Node *m_right;
};

struct Rva00476380Tree
{
	int m_extra;
	Rva00476380Node *m_header;
	int m_count;

	Rva00476380Tree();
};

Rva00476380Tree::Rva00476380Tree()
{
	m_extra = 0;
	m_header = 0;
	m_header = (Rva00476380Node *)bfmeAllocNode(0x18);
	m_count = 0;
	m_header->m_color = 0;
	m_header->m_parent = 0;
	m_header->m_left = m_header;
	m_header->m_right = m_header;
}

class Rva00476380Base
{
public:
	Rva00476380Base();
	virtual ~Rva00476380Base();
	virtual void handle();

	int m_bfme04;
};

Rva00476380Base::Rva00476380Base()
	: m_bfme04(0)
{
}

Rva00476380Base::~Rva00476380Base()
{
}

void Rva00476380Base::handle()
{
}

class Rva00476380Owner : public Rva00476380Base
{
public:
	Rva00476380Owner();
	virtual ~Rva00476380Owner();
	Rva00476380Tree m_tree;
};

Rva00476380Owner::Rva00476380Owner()
{
}

Rva00476380Owner::~Rva00476380Owner()
{
}
