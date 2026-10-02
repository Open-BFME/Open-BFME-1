// ?append@Rva008B2EA0Node@@QAEXPAX@Z
// cl: /O2 /DNDEBUG /MD /EHsc

struct BfmeHdrVKI
{
	unsigned short m_count;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool1284
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

// The pool pointer at VA 0x01337A30 has one canonical global; this TU keeps its
// own view type of the {void *unused; void (*free)(void *);} table and casts at
// each use.
struct BfmeStringPool3AF0;

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

static __forceinline BfmeStringPool1284 *localPool()
{
	return (BfmeStringPool1284 *)g_rva01337A30AllocPair;
}

class BfmeStrVKI
{
public:
	BfmeStrVKI() {}
	BfmeStrVKI(const char *s)
	{
		bfmeSetVKI(s);
	}
	BfmeStrVKI(const BfmeStrVKI &other)
	{
		BfmeHdrVKI *data = other.m_data;
		m_data = data;
		++data->m_count;
	}
	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		--data->m_count;
		if (data->m_count == 0)
			localPool()->free(data);
	}
	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->m_count;
		BfmeHdrVKI *old = m_data;
		--old->m_count;
		if (old->m_count == 0)
			localPool()->free(old);
		m_data = other.m_data;
		return *this;
	}
	void bfmeSetVKI(const char *s);
	BfmeHdrVKI *m_data;
};

class Rva008B2EA0Node
{
public:
	virtual void unused();
	unsigned m_flags;
	BfmeStrVKI m_text;
	void append(void *text);
};

void Rva008B2EA0Node::append(void *text)
{
	BfmeStrVKI value((const char *)text);
	m_text = value;
}
