// ?d_00893b30@@YAXXZ
// partial score=0.72 date=2026-09-07
// cl: /DNDEBUG /MD /EHs-c-

struct BfmeStringData3AF0
{
	unsigned short m_refs;
};

struct BfmeStringPool3AF0
{
	void *m_pad;
	void (__cdecl *m_destroy)(BfmeStringData3AF0 *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct Rva00892640Item
{
	Rva00892640Item();
	~Rva00892640Item();

	BfmeStringData3AF0 *m_handle;
	void *m_extra;
};

// ?Rva00893B30ResizeItems@@YAPAURva00892640Item@@PAU1@HH@Z
Rva00892640Item *Rva00893B30ResizeItems(
	Rva00892640Item *data, int logical_count, int new_capacity)
{
	if (data == 0)
		return new Rva00892640Item[new_capacity];

	Rva00892640Item *replacement = new Rva00892640Item[new_capacity];
	int count = logical_count;
	if (new_capacity < count)
		count = new_capacity;
	if (count != 0)
	{
		Rva00892640Item *source = data;
		Rva00892640Item *destination = replacement;
		do
		{
			BfmeStringData3AF0 *incoming = source->m_handle;
			++incoming->m_refs;
			BfmeStringData3AF0 *old = destination->m_handle;
			--old->m_refs;
			if (old->m_refs == 0)
				g_bfmeStringPool1284->m_destroy(old);
			destination->m_handle = source->m_handle;
			destination->m_extra = source->m_extra;
			++source;
			++destination;
		}
		while (--count != 0);
	}
	delete[] data;
	return replacement;
}
