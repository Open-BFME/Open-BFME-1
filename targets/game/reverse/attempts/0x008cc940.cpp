// ?createString@Rva008AE770Stack@@QAEPAVRva00899770@@PAXHPAVBfmeStrVKI@@HHH@Z
// partial score=0.3097 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Boundary: RVA 008CC940, 917 bytes, final ret 18h at +392.
// Analyst source: docs/analysis/0x008cf740.md; 00893380 independently calls
// this six-argument method on the stack global and exports its returned pointer.
// Revised from the old bank: slot +28 takes BOTH receiver and string holder;
// frame-table lookup is controlled by arg5; only a valid candidate's failed
// virtual/recursive lookup invokes the callback when arg2 is zero.
// EH unwind 0105A158 independently proves sized delete at RVA 00891A80.
// 008C6320 returns only AL (do not change to int); typed declarations below
// describe the proved call ABI, and are not new semantic-identity pins.
// Provisional aggregate preserves a byte flag but still allocates 12 rather
// than retail's 8 local bytes; register allocation and return-tail merging differ.

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

	__forceinline BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = other.m_data;
		return *this;
	}

	__forceinline ~BfmeStrVKI()
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
	virtual Rva00899770 *slot10(Rva00899770 *receiver, BfmeStrVKI *name);

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

	static void operator delete(void *, unsigned int); // EH-only RVA 00891A80: storage and size16, cdecl
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

extern unsigned char __cdecl parse008C6320(void *, void *, BfmeStrVKI *, void *&, BfmeStrVKI *);

typedef void (__cdecl *NotifyString)(const char *);
extern NotifyString g_Va013378C4Notify;

Rva00899770 *Rva008AE770Stack::createString(void *value, int unused,
	BfmeStrVKI *name, int one, int another, int zero)
{
	struct LookupState008CC940 { BfmeStrVKI key; unsigned char prepared; __forceinline ~LookupState008CC940() {} } state;
	BfmeStrVKI &key=state.key;
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
	state.prepared = 0;
	if (zero == 0)
	{
		state.prepared = parse008C6320(value, (void *)unused, &input, value, &key);
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

	if (state.prepared == 1 && candidate != 0)
	{
		value = ((BfmeNode1220 *)candidate)->bfmeTest1220(&key, unused);
		if (value != 0) return (Rva00899770 *)value;
	}

	Rva00899770 *found = 0;
	if (another != 0 && owner->m_count > 0)
	{
		Rva0089CEF0Owner *stackOwner =
			(Rva0089CEF0Owner *)((char *)owner->m_values[owner->m_count - 1] + 8);
		found = stackOwner->find(&key);
		if (found != 0)
			return found;
	}

	if (candidate != 0 && !((unsigned char)~(candidate->m_flags >> 15) & 1))
	{
		value = candidate->slot10(candidate, &key);
		if (value != 0) return (Rva00899770 *)value;
		found = ((BfmeNode1220 *)candidate)->bfmeTest1220(&key, unused);
		if (found != 0)
			return found;
		if (unused == 0)
		{
			NotifyString notify = g_Va013378C4Notify;
			if (notify != 0)
				notify(input.m_data->m_text);
			return (Rva00899770 *)g_bfmeFallbackDB;
		}
	}

	if (unused != 0)
	{
		found = owner->createString(original, 0, &input, one, 1, 0);
	}
	else
	{
		found = (Rva00899770 *)g_bfmeFallbackDB;
	}
	return found;
}
