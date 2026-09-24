// ?helper@Rva00894120Vector@@QAEXPAX00@Z
// partial score=0.97 date=2026-09-24
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

class BfmeG1045
{
public:
	BfmeG1045 *bfmeGo1045G(BfmeG1045 *other);

	BfmeStringData3AF0 *m_handle;
	void *m_extra;
};

Rva00892640Item::Rva00892640Item()
{
	m_handle = &g_bfmeDefaultString1284;
	++m_handle->m_refs;
	m_extra = 0;
}

Rva00892640Item &Rva00892640Item::operator=(
	const Rva00892640Item &other)
{
	reinterpret_cast<BfmeG1045 *>(this)->bfmeGo1045G(
		reinterpret_cast<BfmeG1045 *>(const_cast<Rva00892640Item *>(&other)));
	return *this;
}

Rva00892640Item::~Rva00892640Item()
{
	BfmeStringData3AF0 *old = m_handle;
	--old->m_refs;
	if (old->m_refs == 0)
		g_bfmeStringPool1284->m_destroy(old);
}

extern Rva00892640Item *Rva008926D0CopyItems(
	Rva00892640Item *first, Rva00892640Item *last,
	Rva00892640Item *dest);
extern Rva00892640Item *Rva00892730CopyItems(
	Rva00892640Item *first, Rva00892640Item *last,
	Rva00892640Item *dest);

class Gen_uw_00893e70
{
public:
	void resize(int new_capacity);

protected:
	unsigned m_count;
	int m_capacity;
	Rva00892640Item *m_items;
};

class Rva00894120Vector : public Gen_uw_00893e70
{
public:
	void helper(void *, void *, void *);
};

static inline BfmeG1045 *Rva00893F10Source(const Rva00892640Item &item)
{
	return reinterpret_cast<BfmeG1045 *>(const_cast<Rva00892640Item *>(&item));
}

static inline void *Rva00893F10Address(Rva00892640Item *const &value)
{
	return (void *)&value;
}

// ?helper@Rva00894120Vector@@QAEXPAX00@Z
void Rva00894120Vector::helper(void *first_arg, void *last_arg,
	void *insert_arg)
{
	Rva00892640Item **first_p = static_cast<Rva00892640Item **>(first_arg);
	Rva00892640Item **last_p = static_cast<Rva00892640Item **>(last_arg);
	Rva00892640Item **insert_p = static_cast<Rva00892640Item **>(insert_arg);
	int count = (int)(*last_p - *first_p);
	if (count == 0)
		return;

	int new_count = m_count + count;
	int capacity = m_capacity;
	if (new_count < capacity)
	{
		Rva00892640Item *old_end = m_items + m_count;
		Rva00892640Item *insert = *insert_p;
		if (insert == old_end)
		{
			Rva008926D0CopyItems(*first_p, *last_p, old_end);
			reinterpret_cast<BfmeG1045 *>(&m_items[new_count])->bfmeGo1045G(
				Rva00893F10Source(Rva00892640Item()));
		}
		else
		{
			Rva00892730CopyItems(insert, old_end, m_items + ((insert - m_items) + count));
			Rva008926D0CopyItems(*first_p, *last_p, *insert_p);
			reinterpret_cast<BfmeG1045 *>(&m_items[new_count])->bfmeGo1045G(
				Rva00893F10Source(Rva00892640Item()));
		}
		m_count = new_count;
		return;
	}

	int new_capacity = (int)(capacity * 2.0);
	if (new_capacity < new_count)
		new_capacity = new_count;

	int offset = (int)(*insert_p - m_items);
	resize(new_capacity);
	helper(first_arg, last_arg, Rva00893F10Address(m_items + offset));
}
