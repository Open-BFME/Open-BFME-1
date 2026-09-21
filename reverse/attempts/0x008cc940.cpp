// ?createString@Rva008AE770Stack@@QAEPAVRva00899770@@PAXHPAVBfmeStrVKI@@HHH@Z
// partial score=0.38 date=2026-09-18
// ?createString@Rva008AE770Stack@@QAEPAVRva00899770@@PAXHPAVBfmeStrVKI@@HHH@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

inline void *operator new(unsigned int, void *place)
{
	return place;
}

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_text[1];
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	void **m_items;

	__forceinline void addPooled(void *value)
	{
		int index = m_count;
		if (index >= m_capacity)
		{
			*(unsigned int *)((char *)value + 4) &= 0xbfffffff;
		}
		else
		{
			m_items[index] = value;
			++m_count;
		}
	}
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);

struct Rva008C3B60Node
{
	void *m_vptr;
	unsigned int m_flags;
	BfmeStringData3AF0 *m_data;
	Rva008C3B60Node *m_next;
};

class BfmeStrVKI
{
public:
	BfmeStrVKI()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = other.m_data;
		return *this;
	}

	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

class BfmeStrVKK
{
public:
	void __declspec(nothrow) bfmeTruncVKK(unsigned int length);
};

class Rva00899770
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Rva00899770 *slot10(BfmeStrVKI *name);

	unsigned int m_flags;
	BfmeStringData3AF0 *m_data;
	Rva00899770 *m_next;
};

class Rva008A9B00
{
public:
	static void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	Rva008A9B00();

	void *m_vptr;
	unsigned int m_flags;
	BfmeStringData3AF0 *m_data;
	Rva008A9B00 *m_next;
};

class AptValue
{
public:
	unsigned int m_flags;
};

class BfmeNode1220
{
public:
	Rva00899770 *bfmeTest1220(BfmeStrVKI *name, int unused);
};

class Rva0089CEF0Owner
{
public:
	Rva00899770 *find(BfmeStrVKI *name);
};

class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name,
		int one, int another, int zero);

	char m_gap00[0x0c];
	int m_count;
	char m_gap10[4];
	Rva00899770 **m_values;
};

extern Rva008AE770Stack Rva008AE770TheStack;
extern Rva008C3B60Node *Rva008C3B60Head;
extern AptValue *g_bfmeFallbackDB;

extern void d_008c6320();
extern void d_0089cef0();

typedef unsigned char (__cdecl *PrepareLookup)(void *, void *, BfmeStrVKI *,
	void *&, BfmeStrVKI *);
typedef Rva00899770 *(Rva0089CEF0Owner::*FindString)(BfmeStrVKI *);
typedef void (__cdecl *NotifyString)(const char *);

Rva00899770 *Rva008AE770Stack::createString(void *value, int unused,
	BfmeStrVKI *name, int one, int another, int zero)
{
	BfmeStrVKI key;
	register Rva008AE770Stack *owner = this;
	BfmeStrVKI &input = *name;
	if (input.m_data->m_text[0] == '$')
	{
		Rva008C3B60Node *node = Rva008C3B60Head;
		if (node != 0)
		{
			Rva008C3B60Head = node->m_next;
			g_rva8CD130IdleHook->addPooled(node);
			if (node->m_data != &g_bfmeDefaultString1284)
				((BfmeStrVKK *)&node->m_data)->bfmeTruncVKK(0);
		}
		else
		{
			Rva008A9B00 *fresh = new Rva008A9B00();
			node = (Rva008C3B60Node *)fresh;
		}

		++input.m_data->m_refCount;
		BfmeStringData3AF0 *old = node->m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		node->m_data = input.m_data;
		return (Rva00899770 *)node;
	}

	void *original = value;
	unsigned char prepared = 0;
	if (zero == 0)
	{
		union
		{
			void (*raw)(void);
			PrepareLookup typed;
		} thunk;
		thunk.raw = d_008c6320;
		prepared = thunk.typed(value, (void *)unused, &input, value, &key);
	}
	else
	{
		key = input;
	}

	Rva00899770 *candidate = (Rva00899770 *)value;
	if (key.m_data == &g_bfmeDefaultString1284)
	{
		if (candidate == 0)
			candidate = (Rva00899770 *)g_bfmeFallbackDB;
		return candidate;
	}

	if (prepared == 1 && candidate != 0)
	{
		Rva00899770 *found =
			((BfmeNode1220 *)candidate)->bfmeTest1220(&key, unused);
		if (found != 0)
			return found;
	}

	Rva00899770 *found = 0;
	if (zero != 0 && owner->m_count > 0)
	{
		union
		{
			void (*raw)(void);
			FindString member;
		} thunk;
		thunk.raw = d_0089cef0;
		Rva0089CEF0Owner *stackOwner =
			(Rva0089CEF0Owner *)((char *)owner->m_values[owner->m_count - 1] + 8);
		found = (stackOwner->*thunk.member)(&key);
		if (found != 0)
			return found;
	}

	if (candidate != 0 && ((candidate->m_flags >> 15) & 1) != 0)
	{
		found = candidate->slot10(&key);
		if (found != 0)
			return found;
		found = ((BfmeNode1220 *)candidate)->bfmeTest1220(&key, unused);
		if (found != 0)
			return found;
	}

	if (unused != 0)
	{
		found = owner->createString(original, 0, &input, one, 1, 0);
	}
	else
	{
		NotifyString notify = (*reinterpret_cast<NotifyString *>(0x013378c4));
		if (notify != 0)
		notify((const char *)input.m_data->m_text);
		found = (Rva00899770 *)g_bfmeFallbackDB;
	}
	return found;
}
