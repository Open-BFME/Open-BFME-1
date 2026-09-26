// ?add@Rva8D0D80Table@@QAEXPAVRva8D0D80String@@PAVRva8D0D80Value@@@Z
// partial score=0.28 date=2026-09-23
// ?add@Rva8D0D80Table@@QAEXPAVRva8D0D80String@@PAVRva8D0D80Value@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /FAsc /Fabuild/lane9-0089d890.cod
// The matched addIfAbsent body at 0x0089DBC0 calls this method with the Apt
// table receiver, a refcounted string, and an Apt value.

#include <string.h>

struct BfmeStringData3AF0
{
	unsigned short m_refs;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_hash;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);

struct BfmeStringPool3AF0
{
	void *m_allocate;
	void (__cdecl *m_release)(void *);
};
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

int bfmeCompareVSC(const char *, const char *);

class BfmeKey1279;
class BfmeLookup1279
{
public:
	void bfmeErase1279(BfmeKey1279 &key);
};

class BfmeThing929G
{
public:
	void bfmeInit929G();
};

class BfmeTaggedItem
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual unsigned char isUnique();
};

class Gen_008974C0
{
public:
	void bfmeSet(BfmeTaggedItem *value);
};

class Gen_00897510
{
public:
	void bfmeSet(BfmeTaggedItem *value);
};

class BfmeHeldC680;
class BfmeHeldC6E0;
class BfmeStoreC680
{
public:
	void bfmePutC680(int index, BfmeHeldC680 *value);
};
class BfmeStoreC6E0
{
public:
	void bfmePutC6E0(int index, BfmeHeldC6E0 *value);
};

class Rva8D0D80String
{
public:
	BfmeStringData3AF0 *m_data;
};

static __forceinline bool equalKeys(const Rva8D0D80String *left,
									   const Rva8D0D80String *right)
{
	if (left->m_data == right->m_data)
		return true;
	if (left->m_data->m_hash != right->m_data->m_hash)
		return false;
	bool equal = bfmeCompareVSC((const char *)left->m_data + 8,
								(const char *)right->m_data + 8) == 0;
	return equal;
}

class Rva8D0D80Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual unsigned char isUnique();
};

struct Rva8D0D80Entry
{
	Rva8D0D80String m_key;
	void *m_value;
};

class Rva8D0D80Table
{
public:
	int m_capacity;
	Rva8D0D80Entry *m_entries;

	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
	void rva0089d180();
	void rva0089d5b0(Rva8D0D80String *name, Rva8D0D80Value *value);
};

void Rva8D0D80Table::add(Rva8D0D80String *name, Rva8D0D80Value *value)
{
	if (value == 0)
	{
		((BfmeLookup1279 *)this)->bfmeErase1279(*(BfmeKey1279 *)name);
		return;
	}
	if (name->m_data == &g_bfmeDefaultString1284)
		return;
	if (name->m_data->m_hash == 0)
		((BfmeThing929G *)name)->bfmeInit929G();

	if (name->m_data->m_hash == 0x699
		&& bfmeCompareVSC((const char *)name->m_data + 8, "prototype") == 0)
	{
		((Gen_00897510 *)this)->bfmeSet((BfmeTaggedItem *)value);
		return;
	}
	if (name->m_data->m_hash == 0x6bbd
		&& bfmeCompareVSC((const char *)name->m_data + 8, "__proto__") == 0)
	{
		((Gen_008974C0 *)this)->bfmeSet((BfmeTaggedItem *)value);
		return;
	}

	if (this->m_entries == 0)
	{
		this->m_entries = (Rva8D0D80Entry *)Rva008C5D70Alloc(this->m_capacity * 8);
		memset(this->m_entries, 0, this->m_capacity * 8);
	}

	int index = name->m_data->m_hash & (this->m_capacity - 1);
	Rva8D0D80Entry *entry = this->m_entries + index;
	if (entry->m_key.m_data == 0)
	{
		entry->m_key.m_data = name->m_data;
		++name->m_data->m_refs;
		value->addRef();
		if (value->isUnique() == 1)
			value = (Rva8D0D80Value *)((unsigned)value | 1);
		entry->m_value = value;
		return;
	}

	int empty = -1;
	if (entry->m_key.m_data == &g_bfmeDefaultString1284)
		empty = index;
	else if (equalKeys(&entry->m_key, name))
	{
		((BfmeStoreC680 *)this)->bfmePutC680(index, (BfmeHeldC680 *)value);
		return;
	}

	int low = index - 8;
	int high;
	if (low < 0)
	{
		low = 0;
		high = 16;
		if (this->m_capacity <= high)
			high = this->m_capacity - 1;
	}
	else
	{
		high = index + 8;
		if (high > this->m_capacity - 1)
		{
			high = this->m_capacity - 1;
			low = high - 16;
			if (low < 0)
				low = 0;
		}
	}

	int scan = index;
	int remaining = high - index;
	while (remaining)
	{
		--remaining;
		++scan;
		entry = this->m_entries + scan;
		if (entry->m_key.m_data == 0)
		{
			entry->m_key.m_data = name->m_data;
			++name->m_data->m_refs;
			((BfmeStoreC6E0 *)this)->bfmePutC6E0(scan, (BfmeHeldC6E0 *)value);
			return;
		}
		if (entry->m_key.m_data == &g_bfmeDefaultString1284)
		{
			if (empty != -1)
				empty = scan;
		}
		else if (equalKeys(&entry->m_key, name))
		{
			((BfmeStoreC680 *)this)->bfmePutC680(scan, (BfmeHeldC680 *)value);
			return;
		}
	}

	scan = index;
	remaining = index - low;
	while (remaining)
	{
		--scan;
		--remaining;
		entry = this->m_entries + scan;
		if (entry->m_key.m_data == 0)
		{
			entry->m_key.m_data = name->m_data;
			++name->m_data->m_refs;
			((BfmeStoreC6E0 *)this)->bfmePutC6E0(scan, (BfmeHeldC6E0 *)value);
			return;
		}
		if (entry->m_key.m_data == &g_bfmeDefaultString1284)
		{
			if (empty != -1)
				empty = scan;
		}
		else if (equalKeys(&entry->m_key, name))
		{
			((BfmeStoreC680 *)this)->bfmePutC680(scan, (BfmeHeldC680 *)value);
			return;
		}
	}

	if (empty == -1)
	{
		this->rva0089d180();
		this->rva0089d5b0(name, value);
		return;
	}

	entry = this->m_entries + empty;
	++name->m_data->m_refs;
	BfmeStringData3AF0 *old = entry->m_key.m_data;
	--old->m_refs;
	if (old->m_refs == 0)
		g_bfmeStringPool1284->m_release(old);
	entry->m_key.m_data = name->m_data;
	((BfmeStoreC6E0 *)this)->bfmePutC6E0(empty, (BfmeHeldC6E0 *)value);
}

