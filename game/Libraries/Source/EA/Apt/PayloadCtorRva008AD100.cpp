// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The payload constructor is the secondary-base body at retail 0x008AD100
// (442 bytes).  Its first member is an Apt string, followed by the scalar
// fields written at +4, +8, +0c, +10, +14, +18 and +1c.  The matched derived
// constructor in Rva8CB820PayloadCtor.cpp calls it with this adjusted by +0x20.
// Analyst ABI/layout evidence: docs/analysis/0x008985c0.md sections B/C/E.
// The ret34 and that matched caller prove thirteen dword arguments; unused
// arguments a7/a8/a13 remain present. The opaque pin is not an original name.

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

	bool isUndefined() const { return ((m_flags >> 15) & 1) == 0; }
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

	m_a12 = a12;
	m_a10 = a10;
	m_a11 = a11;
	if (!first->isUndefined())
		first->getName(&m_name);

	if (!alignment->isUndefined())
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

