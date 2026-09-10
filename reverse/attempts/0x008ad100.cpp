// ??0Rva8CB820Payload@@QAE@HHHHHHHHHHHHH@Z
// partial score=0.88 date=2026-09-10
// ??0Rva8CB820Derived@@QAE@HHHHHHHHHHHHH@Z
// ??0Rva8CB820Payload@@QAE@HHHHHHHHHHHHH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The payload constructor is the secondary-base body at retail 0x008AD100
// (442 bytes).  Its first member is an Apt string, followed by the scalar
// fields written at +4, +8, +0c, +10, +14, +18 and +1c.  The matched derived
// constructor below calls it with this adjusted by +0x20.

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

struct Rva8CB820StringData
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_text[1];
};

struct Rva8CB820StringPool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva8CB820StringData g_bfmeDefaultString1284;
extern Rva8CB820StringPool *g_bfmeStringPool1284;

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		m_data = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
	}

	~Rva8CD130String()
	{
		Rva8CB820StringData *data = m_data;
		--data->m_refCount;
		if (data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	Rva8CB820StringData *m_data;
};

class Rva8CD130Value
{
public:
	virtual void addRef();
	virtual void release();
	void getName(Rva8CD130String *name);

	unsigned m_flags;

	bool isUndefined() const
	{
		unsigned char shifted = (unsigned char)(m_flags >> 15);
		shifted = (unsigned char)~shifted;
		return (shifted & 1) != 0;
	}
};

class Rva8CB820Payload
{
public:
	Rva8CB820Payload(int firstValue, int a2, int a3, int a4, int a5,
		int a6, int a7, int a8, int alignmentValue, int a10, int a11,
		int a12, int a13);
	~Rva8CB820Payload();

private:
	Rva8CD130String m_name;
	int m_a2;
	int m_a3;
	int m_alignment;
	int m_flags;
	int m_a12;
	int m_a10;
	int m_a11;
};

Rva8CB820Payload::Rva8CB820Payload(int firstValue, int a2, int a3,
	int a4, int a5, int a6, int a7, int a8, int alignmentValue,
	int a10, int a11, int a12, int a13) :
	m_name()
{
	Rva8CD130Value *first = reinterpret_cast<Rva8CD130Value *>(firstValue);
	Rva8CD130Value *alignment = reinterpret_cast<Rva8CD130Value *>(alignmentValue);
	m_a2 = a2;
	m_a3 = a3;
	m_flags = 0;
	if (a4 == 0)
		m_flags = 0x10000;
	else if (a4 == 1)
		m_flags = 0x10001;

	if (a5 == 0)
		m_flags |= 0x100000;
	else if (a5 == 1)
		m_flags |= 0x100010;

	if (a6 == 0)
		m_flags |= 0x1000000;
	else if (a6 == 1)
		m_flags |= 0x1000100;

	m_a10 = a10;
	m_a12 = a12;
	m_a11 = a11;
	if (!first->isUndefined())
		first->getName(&m_name);

	unsigned int alignmentFlags = alignment->m_flags;
	unsigned char alignmentShifted = (unsigned char)(alignmentFlags >> 15);
	alignmentShifted = (unsigned char)~alignmentShifted;
	if (!(alignmentShifted & 1))
	{
		Rva8CD130String name;
		alignment->getName(&name);
		if (strcmp(name.m_data->m_text, "left") == 0 ||
			strcmp(name.m_data->m_text, "true") == 0)
			m_alignment = 0;
		else if (strcmp(name.m_data->m_text, "center") == 0)
			m_alignment = 2;
		else
			m_alignment = strcmp(name.m_data->m_text, "right") != 0 ? 3 : 1;
	}
	else
	{
		m_alignment = 3;
		return;
	}
}

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	char _bfme_base_slice[0x1c];
};

class Rva8CB820Derived : public Rva899F00Base, public Rva8CB820Payload
{
public:
	Rva8CB820Derived(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		int a8, int a9, int a10, int a11, int a12, int a13);

};

Rva8CB820Derived::Rva8CB820Derived(int a1, int a2, int a3, int a4, int a5,
	int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13) :
	Rva899F00Base(reinterpret_cast<const char *>(0x24), 8),
	Rva8CB820Payload(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12,
		a13)
{
}
