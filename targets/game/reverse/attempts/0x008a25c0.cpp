// ?d_008a25c0@@YAXXZ
// partial score=0.6733 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?run@Rva008A25C0Object@@QAEXPAX@Z -- retail 0x008A25C0, 1454 bytes.
//
// IDENTITY. Address-derived. The pinned name is the one both matched callers
// already use: BfmeDropObjectA::~BfmeDropObjectA (BfmeDtorVBW.cpp) and
// Rva00893030Manager::invoke (Rva00893030ManagerInvoke.cpp) call it on the
// object at +8 of the deferred-run record with the base the forward pass used.
// The forward pass is the pinned BfmeFixup2580::helper at 0x008A2130 (reached
// through BfmeFixup2580::apply, 0x008A2580, which clears the same +0x30 word):
// it turns stored offsets and indices into pointers; this body undoes it.
//
// WHAT THE BYTES SHOW.
//   * +0x0C/+0x10 are a counted table of entry pointers; 0x008A0690
//     (Gen_008A0690::bfmeIndexOf, matched) searches exactly that table, so
//     this class reaches it through that declaration.
//   * +0x20/+0x24 are a counted table of 16-byte records: two relocatable
//     words, the index of the entry they own, and a reference-counted handle
//     whose destructor is 0x00784A70 (the one EH state's cleanup).
//   * +0x28/+0x2C are a counted table of 8-byte records, +0x30 a word cleared
//     before and after the pass and handed by address to the nested passes.
//   * Each entry starts with a kind 1..10; the kinds' layouts below are only
//     the offsets this body touches.
//   * 0x09876543 is stored into every live entry's second word before the
//     entry pointer itself becomes an offset.

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *value);
};

__declspec(noinline) void bfmeDropA(void *value);

void rva008CC540ZeroThirdForwarder(void *a, void *b, void *c);

extern void (__cdecl *g_rva01337880)(void *value);
extern void (__cdecl *g_rva01337890)(void *value);
extern void (__cdecl *g_rva0133789C)(void *value);

// Reference-counted handle held by the +0x24 records.
class Rva008A25C0Handle
{
public:
	Rva008A25C0Handle() : m_item(0) {}

	~Rva008A25C0Handle()
	{
		if (m_item)
		{
			if (Rva00894D90Accessor::decrement((unsigned int *)m_item) == 0)
				bfmeDropA(m_item);
		}
	}

	Rva008A25C0Handle &operator=(const Rva008A25C0Handle &other)
	{
		if (&other != this)
		{
			if (m_item && Rva00894D90Accessor::decrement((unsigned int *)m_item) == 0)
				bfmeDropA(m_item);
			m_item = other.m_item;
			if (m_item)
				Rva00894D80Accessor::increment((unsigned int *)m_item);
		}
		return *this;
	}

	void *m_item;
};

struct Rva008A25C0Import
{
	int m_first;				// +0x00
	int m_second;				// +0x04
	int m_index;				// +0x08
	Rva008A25C0Handle m_handle;	// +0x0C
};

struct Rva008A25C0Pair
{
	int m_offset;				// +0x00
	int m_value;				// +0x04
};

struct Rva008A25C0Entry
{
	int m_kind;					// +0x00
	int m_mark;					// +0x04
};

// Nested object at +8 of kinds 5 and 9: retail 0x008D3610, thiscall, ret 8.
class Rva008D3610Object
{
public:
	void run(void *value, int *flag);
};

struct Rva008A25C0Kind1 : Rva008A25C0Entry
{
	char m_pad08[0x10];
	void *m_resource;			// +0x18
};

struct Rva008A25C0Kind2 : Rva008A25C0Entry
{
	char m_pad08[0x2C];
	int m_offset34;				// +0x34
	int m_offset38;				// +0x38
};

struct Rva008A25C0Kind3 : Rva008A25C0Entry
{
	int m_offset08;				// +0x08
	int m_count;				// +0x0C
	int *m_entries;				// +0x10
};

// Kind 8: two entry references, turned back into entry-table indices.
struct Rva008A25C0Kind8 : Rva008A25C0Entry
{
	int m_first;				// +0x08
	int m_second;				// +0x0C
};

struct Rva008A25C0Kind4Link
{
	void *m_a;					// +0x00
	void *m_b;					// +0x04
	void *m_c;					// +0x08
	void *m_d;					// +0x0C
};

struct Rva008A25C0Kind4Frame
{
	int m_head;					// +0x00
	int m_entry;				// +0x04
	char m_pad08[0x3C];
};

struct Rva008A25C0Kind4 : Rva008A25C0Entry
{
	char m_pad08[0x1C];
	int m_offset24;				// +0x24
	int m_offset28;				// +0x28
	int m_frameCount;			// +0x2C
	Rva008A25C0Kind4Frame *m_frames;	// +0x30
	int m_pairCount;			// +0x34
	Rva008A25C0Pair *m_pairs;	// +0x38
	int m_link;					// +0x3C
};

struct Rva008A25C0Kind5 : Rva008A25C0Entry
{
	Rva008D3610Object m_object;	// +0x08
};

struct Rva008A25C0Kind6 : Rva008A25C0Entry
{
	void *m_resource;			// +0x08
};

struct Rva008A25C0Kind10Item
{
	char m_pad00[0x34];
	int m_offset;				// +0x34
};

struct Rva008A25C0Kind10 : Rva008A25C0Entry
{
	char m_pad08[0x28];
	int m_count;				// +0x30
	Rva008A25C0Kind10Item *m_items;	// +0x34
};

class Gen_008A0690
{
public:
	int bfmeIndexOf(void *key) const;
};

class Rva008A25C0Object : public Gen_008A0690
{
public:
	void run(void *value);

	int findImport(int index) const
	{
		for (int j = 0; j < m_importCount; ++j)
			if (m_imports[j].m_index == index)
				return j;
		return -1;
	}

	int findEntry(int key) const
	{
		for (int j = 0; j < m_count; ++j)
			if ((int)m_entries[j] == key)
				return j;
		return -1;
	}

	char m_pad00[0x0C];
	int m_count;					// +0x0C
	Rva008A25C0Entry **m_entries;	// +0x10
	char m_pad14[0x0C];
	int m_importCount;				// +0x20
	Rva008A25C0Import *m_imports;	// +0x24
	int m_pairCount;				// +0x28
	Rva008A25C0Pair *m_pairs;		// +0x2C
	int m_flag;						// +0x30
};

#define KIND(T, i) ((Rva008A25C0##T *)m_entries[i])

void Rva008A25C0Object::run(void *value)
{
	int *flag = &m_flag;
	*flag = 0;

	int base = (int)value;
	int i;

	for (i = 0; i < m_count; ++i)
	{
		if (m_entries[i] == 0)
			continue;

		if (findImport(i) != -1)
			continue;

		switch (m_entries[i]->m_kind)
		{
		case 8:
			KIND(Kind8, i)->m_first = findEntry(KIND(Kind8, i)->m_first);
			KIND(Kind8, i)->m_second = findEntry(KIND(Kind8, i)->m_second);
			break;

		case 4:
			{
				Rva008A25C0Kind4Link *link = (Rva008A25C0Kind4Link *)KIND(Kind4, i)->m_link;
				if (link)
				{
					if (link->m_b)
						link->m_b = (void *)bfmeIndexOf(link->m_b);
					if (link->m_d)
						link->m_d = (void *)bfmeIndexOf(link->m_d);
					if (link->m_a)
						link->m_a = (void *)bfmeIndexOf(link->m_a);
					if (link->m_c)
						link->m_c = (void *)bfmeIndexOf(link->m_c);
				}
				if (KIND(Kind4, i)->m_link)
					KIND(Kind4, i)->m_link -= base;
			}
			break;
		}
	}

	{
	for (int i = 0; i < m_count; ++i)
	{
		if (m_entries[i] == 0)
			continue;

		if (findImport(i) != -1)
			continue;

		switch (m_entries[i]->m_kind)
		{
		case 5:
		case 9:
			KIND(Kind5, i)->m_object.run(value, flag);
			break;

		case 1:
			g_rva0133789C(KIND(Kind1, i)->m_resource);
			KIND(Kind1, i)->m_resource = (void *)i;
			break;

		case 4:
			{
				if (KIND(Kind4, i)->m_offset24)
					KIND(Kind4, i)->m_offset24 -= base;
				if (KIND(Kind4, i)->m_offset28)
					KIND(Kind4, i)->m_offset28 -= base;
				{
					for (int k = 0; k < KIND(Kind4, i)->m_frameCount; ++k)
						KIND(Kind4, i)->m_frames[k].m_entry = findEntry(KIND(Kind4, i)->m_frames[k].m_entry);
				}
				if (KIND(Kind4, i)->m_frames)
					KIND(Kind4, i)->m_frames = (Rva008A25C0Kind4Frame *)((int)KIND(Kind4, i)->m_frames - base);
				{
					for (int k = 0; k < KIND(Kind4, i)->m_pairCount; ++k)
					{
						rva008CC540ZeroThirdForwarder((void *)KIND(Kind4, i)->m_pairs[k].m_value, value, flag);
						if (KIND(Kind4, i)->m_pairs[k].m_value)
							KIND(Kind4, i)->m_pairs[k].m_value -= base;
					}
				}
				if (KIND(Kind4, i)->m_pairs)
					KIND(Kind4, i)->m_pairs = (Rva008A25C0Pair *)((int)KIND(Kind4, i)->m_pairs - base);
			}
			break;

		case 3:
			{
				if (KIND(Kind3, i)->m_offset08)
					KIND(Kind3, i)->m_offset08 -= base;
				for (int k = 0; k < KIND(Kind3, i)->m_count; ++k)
					KIND(Kind3, i)->m_entries[k] = findEntry(KIND(Kind3, i)->m_entries[k]);
				if (KIND(Kind3, i)->m_entries)
					KIND(Kind3, i)->m_entries = (int *)((int)KIND(Kind3, i)->m_entries - base);
			}
			break;

		case 6:
			g_rva01337880(KIND(Kind6, i)->m_resource);
			KIND(Kind6, i)->m_resource = (void *)i;
			break;

		case 2:
			if (KIND(Kind2, i)->m_offset34)
				KIND(Kind2, i)->m_offset34 -= base;
			if (KIND(Kind2, i)->m_offset38)
				KIND(Kind2, i)->m_offset38 -= base;
			break;

		case 7:
			g_rva01337890(KIND(Kind6, i)->m_resource);
			KIND(Kind6, i)->m_resource = (void *)i;
			break;

		case 10:
			{
				for (int k = 0; k < KIND(Kind10, i)->m_count; ++k)
				{
					if (KIND(Kind10, i)->m_items[k].m_offset)
						KIND(Kind10, i)->m_items[k].m_offset -= base;
				}
				if (KIND(Kind10, i)->m_items)
					KIND(Kind10, i)->m_items = (Rva008A25C0Kind10Item *)((int)KIND(Kind10, i)->m_items - base);
			}
			break;
		}
	}
	}

	for (i = 0; i < m_importCount; ++i)
	{
		m_imports[i].m_handle = Rva008A25C0Handle();
		m_entries[m_imports[i].m_index] = 0;
	}

	for (i = 0; i < m_count; ++i)
	{
		if (m_entries[i])
		{
			m_entries[i]->m_mark = 0x09876543;
			if (m_entries[i])
				m_entries[i] = (Rva008A25C0Entry *)((int)m_entries[i] - base);
		}
	}

	if (m_entries)
		m_entries = (Rva008A25C0Entry **)((int)m_entries - base);

	for (i = 0; i < m_importCount; ++i)
	{
		if (m_imports[i].m_first)
			m_imports[i].m_first -= base;
		if (m_imports[i].m_second)
			m_imports[i].m_second -= base;
	}

	for (i = 0; i < m_pairCount; ++i)
	{
		if (m_pairs[i].m_offset)
			m_pairs[i].m_offset -= base;
	}

	if (m_imports)
		m_imports = (Rva008A25C0Import *)((int)m_imports - base);
	if (m_pairs)
		m_pairs = (Rva008A25C0Pair *)((int)m_pairs - base);

	*flag = 0;
}
