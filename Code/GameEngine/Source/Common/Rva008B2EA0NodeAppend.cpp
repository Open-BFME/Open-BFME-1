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

extern BfmeStringPool1284 *g_bfmeStringPool1284;

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
			g_bfmeStringPool1284->free(data);
	}
	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->m_count;
		BfmeHdrVKI *old = m_data;
		--old->m_count;
		if (old->m_count == 0)
			g_bfmeStringPool1284->free(old);
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
