// cl: /DNDEBUG /MD /EHsc
// The exact caller at 0x00895340 passes another Gen_uw_00893e70 object to
// this member.  Both objects use the established 28-byte layout: two header
// words, a data pointer, and two inline refcounted string records.

struct BfmeStringData3AF0
{
	unsigned short m_refs;
};

// The Apt allocator-hook pair pointer at VA 0x01337A30, defined once by
// game/Libraries/Source/Apt/Apt.cpp.  Slot +4 is the deallocator this TU calls;
// the view below is the TU-local spelling of that second slot.
struct BfmeStringPool3AF0;
extern struct BfmeStringPool3AF0 *g_rva01337A30AllocPair;

struct Rva01337A30PoolView
{
	void *m_pad;
	void (__cdecl *m_destroy)(BfmeStringData3AF0 *);
};

class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;	// shared empty string block 0x012D5298

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
	m_handle = (BfmeStringData3AF0 *)&g_rva012D5298Empty;
	++m_handle->m_refs;
	m_extra = 0;
}

// The emitted 53-byte helper also occurs at 0x008924B0, which already has a
// differently named owner. Keep it for inlining without claiming a second row.
// ??4Rva00892640Item@@QAEAAU0@ABU0@@Z present-unmatched
Rva00892640Item &Rva00892640Item::operator=(
	const Rva00892640Item &other)
{
	BfmeStringData3AF0 *incoming = other.m_handle;
	++incoming->m_refs;
	BfmeStringData3AF0 *old = m_handle;
	--old->m_refs;
	if (old->m_refs == 0)
		((Rva01337A30PoolView *)g_rva01337A30AllocPair)->m_destroy(old);
	m_handle = other.m_handle;
	m_extra = other.m_extra;
	return *this;
}

Rva00892640Item::~Rva00892640Item()
{
	BfmeStringData3AF0 *old = m_handle;
	--old->m_refs;
	if (old->m_refs == 0)
		((Rva01337A30PoolView *)g_rva01337A30AllocPair)->m_destroy(old);
}

extern Rva00892640Item *Rva00892640CopyItems(
	Rva00892640Item *first,
	Rva00892640Item *last,
	Rva00892640Item *dest);

class Gen_uw_00893e70
{
public:
	Gen_uw_00893e70();
	~Gen_uw_00893e70();

	void Rva00895050(Gen_uw_00893e70 *other);
	void Rva00895340();

private:
	unsigned int m_count;
	unsigned int m_capacity;
	Rva00892640Item *m_data;
	Rva00892640Item m_inline[2];
};

void Gen_uw_00893e70::Rva00895050(Gen_uw_00893e70 *other)
{
	unsigned int count = other->m_count;
	other->m_count = m_count;
	m_count = count;

	unsigned int capacity = other->m_capacity;
	other->m_capacity = m_capacity;

	Rva00892640Item *data = m_data;
	bool this_inline = data == m_inline;
	m_capacity = capacity;
	bool other_inline = other->m_data == other->m_inline;
	if (other_inline)
		m_data = m_inline;
	else
		m_data = other->m_data;
	if (this_inline)
		other->m_data = other->m_inline;
	else
		other->m_data = data;

	if (!other_inline && !this_inline)
		return;

	Rva00892640Item temporary[2];
	// Retail resets the second scratch record through the value assignment
	// before rotating the three inline buffers, including its refcount effects.
	temporary[1] = Rva00892640Item();
	Rva00892640CopyItems(m_inline, m_inline + 2, temporary);
	Rva00892640CopyItems(other->m_inline, other->m_inline + 2, m_inline);
	Rva00892640CopyItems(temporary, temporary + 2, other->m_inline);
}

// 0x00893B30: reallocate an item array.  A null array gets a fresh one;
// otherwise the first min(count, capacity) items are assigned into a new
// array (none when the capacity is zero) and the old array is deleted.  The
// copy advances the incoming pointer itself, so the delete[] receives the
// advanced pointer whenever items were copied, exactly as retail does.
Rva00892640Item *Rva00893B30ResizeItems(
	Rva00892640Item *data, int logical_count, int new_capacity)
{
	if (data == 0)
		return new Rva00892640Item[new_capacity];

	Rva00892640Item *new_data = 0;
	if (new_capacity != 0)
	{
		new_data = new Rva00892640Item[new_capacity];
		int count = new_capacity < logical_count ? new_capacity : logical_count;
		Rva00892640Item *dest = new_data;
		while (count--)
			*dest++ = *data++;
	}
	delete[] data;
	return new_data;
}
