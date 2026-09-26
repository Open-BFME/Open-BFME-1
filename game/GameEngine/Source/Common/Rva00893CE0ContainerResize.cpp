// cl: /DNDEBUG /MD /EHsc /Oy

struct BfmeStringData3AF0
{
	unsigned short m_refs;
};

struct BfmeStringPool3AF0
{
	void *m_pad;
	void (__cdecl *m_destroy)(BfmeStringData3AF0 *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct Rva00892640Item
{
	Rva00892640Item();
	Rva00892640Item &operator=(const Rva00892640Item &other);
	~Rva00892640Item();

	BfmeStringData3AF0 *m_handle;
	void *m_extra;
};

Rva00892640Item::Rva00892640Item()
{
	m_handle = &g_bfmeDefaultString1284;
	++m_handle->m_refs;
	m_extra = 0;
}

Rva00892640Item &Rva00892640Item::operator=(const Rva00892640Item &other)
{
	BfmeStringData3AF0 *incoming = other.m_handle;
	++incoming->m_refs;
	BfmeStringData3AF0 *old = m_handle;
	--old->m_refs;
	if (old->m_refs == 0)
		g_bfmeStringPool1284->m_destroy(old);
	m_handle = other.m_handle;
	m_extra = other.m_extra;
	return *this;
}

Rva00892640Item::~Rva00892640Item()
{
	BfmeStringData3AF0 *old = m_handle;
	--old->m_refs;
	if (old->m_refs == 0)
		g_bfmeStringPool1284->m_destroy(old);
}

extern Rva00892640Item *Rva00893B30ResizeItems(
	Rva00892640Item *data, int logical_count, int new_capacity);
extern Rva00892640Item *Rva00892640CopyItems(
	Rva00892640Item *first, Rva00892640Item *last,
	Rva00892640Item *dest);

class Gen_uw_00893e70
{
public:
	void resize(int new_capacity);
	int capacity() const { return m_capacity; }

private:
	unsigned int m_count;
	int m_capacity;
	Rva00892640Item *m_data;
	Rva00892640Item m_inline[2];
};

void Gen_uw_00893e70::resize(int new_capacity)
{
	if (new_capacity <= capacity())
		return;
	if (new_capacity <= 1)
	{
		m_capacity = new_capacity;
		return;
	}

	Rva00892640Item *new_data =
		Rva00893B30ResizeItems(0, 0, new_capacity + 1);
	Rva00892640Item *old_end = m_data + m_count;
	Rva00892640CopyItems(m_data, old_end, new_data);
	m_capacity = new_capacity;
	if (m_data != m_inline)
		Rva00893B30ResizeItems(m_data, 0, 0);
	m_data = new_data;
	m_data[m_count] = Rva00892640Item();
}
