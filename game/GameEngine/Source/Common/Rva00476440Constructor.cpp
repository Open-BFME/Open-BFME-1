// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Exact scratch reconstruction for the constructor of Rva00476440.
// Retail 0x00476380 is immediately followed by its deleting-destructor
// thunk at 0x00476410, which dispatches through ILT 0x0003C092 to the
// already matched Rva00476440 destructor at 0x00476440.  The latter's
// out-of-line member destructor at ILT 0x0001FD66 is the same red-black tree
// destructor used by this constructor, establishing the class identity.

void *bfmeAllocNode(unsigned int bytes);

class Mem004CRefCounted
{
public:
	void Release_Ref()
	{
		if ((m_refs = m_refs - 1) <= 0)
			Delete_This(1);
	}

protected:
	virtual void Delete_This(unsigned int);
	int m_refs;
};

class Rva00476440RefPtr
{
public:
	Rva00476440RefPtr();
	~Rva00476440RefPtr();

	Mem004CRefCounted *m_ptr;
};

// ??0Rva00476440RefPtr@@QAE@XZ absent-from-retail
Rva00476440RefPtr::Rva00476440RefPtr()
	: m_ptr(0)
{
}

// ??1Rva00476440RefPtr@@QAE@XZ absent-from-retail
Rva00476440RefPtr::~Rva00476440RefPtr()
{
	if (m_ptr)
		m_ptr->Release_Ref();
}

struct Rva00476440Node
{
	char m_color;
	int *m_parent;
	Rva00476440Node *m_left;
	Rva00476440Node *m_right;
};

class Mem0001FD66
{
public:
	Mem0001FD66();
	~Mem0001FD66();

	Rva00476440Node *m_header;
	int m_count;
};

// ??0Mem0001FD66@@QAE@XZ absent-from-retail
Mem0001FD66::Mem0001FD66()
	: m_header(0)
{
	m_header = (Rva00476440Node *)bfmeAllocNode(0x18);
	m_count = 0;
	m_header->m_color = 0;
	m_header->m_parent = 0;
	m_header->m_left = m_header;
	m_header->m_right = m_header;
}

// ??1Mem0001FD66@@QAE@XZ absent-from-retail
Mem0001FD66::~Mem0001FD66()
{
}

class Rva00476440Base
{
public:
	Rva00476440Base();
	virtual ~Rva00476440Base();
	virtual void handle();

	int m_bfme04;
};

// ??0Rva00476440Base@@QAE@XZ absent-from-retail
Rva00476440Base::Rva00476440Base()
	: m_bfme04(0)
{
}

// ??1Rva00476440Base@@UAE@XZ absent-from-retail
Rva00476440Base::~Rva00476440Base()
{
}

// ?handle@Rva00476440Base@@UAEXXZ absent-from-retail
void Rva00476440Base::handle()
{
}

class Rva00476440 : public Rva00476440Base
{
public:
	Rva00476440();
	virtual ~Rva00476440();

	Rva00476440RefPtr m_ref;
	Mem0001FD66 m_tail;
};

Rva00476440::Rva00476440()
{
}
