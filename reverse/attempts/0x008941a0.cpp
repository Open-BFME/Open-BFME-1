// ?find008941A0@Rva00894120Vector@@QAEXPAX@Z
// partial score=0.24 date=2026-09-21
// Clean reconstruction of the find-or-intern method at retail RVA 0x008941A0,
// a sibling of Rva00894120Vector::insert (0x00894120) in the same class: it
// linearly searches the vector for an entry whose key matches *param's first
// field (length then content), and if none matches, interns a new key via
// the pool manager and inserts a fresh entry through the same helper() used
// by insert(). The owning type and the exact semantics of the "second" state
// field and of the caller-owned handle at param are not recovered; names
// keep the address token per the address-derived naming policy.

extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct Rva00894120Item
{
	void *first;
	void *second;
};

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

__declspec(noinline) void bfmeDropA(void *p);		// retail 0x00895320

struct BfmeStringPool3AF0
{
	void *unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva00893030Manager
{
public:
	void *find008941A0(void *outSlot, void *param);
};

extern Rva00893030Manager *g_rva00893030Manager;

class Rva00894120Vector
{
public:
	void find008941A0(void *param);
	void helper(void *, void *, void *);

private:
	unsigned m_count;
	char m_pad04[4];
	Rva00894120Item *m_items;
};

static __forceinline Rva00894120Item *Rva00894120Next(
	Rva00894120Item *item)
{
	return item + 1;
}

// Owner wrapper matching the pool's WORD refCount-at-offset-0 convention
// (EAStringData/BfmeHdrVKI family): construction takes a fresh reference,
// destruction releases it back to the pool. This is what puts an SEH frame
// around the helper() insert call in retail.
class Rva008941A0KeyOwner
{
public:
	Rva008941A0KeyOwner(void *key) : m_key(key)
	{
		++*(unsigned short *)m_key;
	}
	~Rva008941A0KeyOwner()
	{
		if (--*(unsigned short *)m_key == 0)
			g_bfmeStringPool1284->free(m_key);
	}

	void *m_key;
};

// ?find008941A0@Rva00894120Vector@@
void Rva00894120Vector::find008941A0(void *param)
{
	Rva00894120Item *item = m_items;
	Rva00894120Item *end = &m_items[m_count];

	if (item != end)
	{
		void *key = *(void **)param;
		unsigned short keyLen = *(unsigned short *)((char *)key + 2);

		do
		{
			void *itemKey = item->first;
			unsigned short itemLen = *(unsigned short *)((char *)itemKey + 2);
			if (itemLen == keyLen)
			{
				if (itemKey == key ||
					memcmp((char *)itemKey + 8, (char *)key + 8, itemLen) == 0)
				{
					if ((int)item->second == 2)
						item->second = (void *)3;
					return;
				}
			}
			item = Rva00894120Next(item);
		} while (item != end);
	}

	void *outSlot;
	void *found = g_rva00893030Manager->find008941A0(&outSlot, param);
	void *newAssoc = *(void **)found;
	bool haveNew = (newAssoc != 0);

	if (param)
	{
		if (Rva00894D90Accessor::decrement((unsigned int *)param) == 0)
			bfmeDropA(param);
	}

	Rva008941A0KeyOwner owner(*(void **)param);

	if (haveNew)
	{
		Rva00894120Item newItem = { owner.m_key, (void *)3 };
		Rva00894120Item *end2 = &m_items[m_count];
		Rva00894120Item *next2 = Rva00894120Next(&newItem);
		Rva00894120Item *begin2 = &newItem;
		helper(&begin2, &next2, &end2);
	}
	else
	{
		Rva00894120Item newItem = { owner.m_key, (void *)1 };
		Rva00894120Item *end2 = &m_items[m_count];
		Rva00894120Item *next2 = Rva00894120Next(&newItem);
		Rva00894120Item *begin2 = &newItem;
		helper(&begin2, &next2, &end2);
	}
}
