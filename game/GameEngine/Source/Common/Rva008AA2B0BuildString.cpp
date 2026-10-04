// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail 0x008AA2B0 builds a string from the integer values on the Apt stack,
// then recycles or allocates an Rva008C3B60Node and transfers that string.
// No caller or identity table proves a semantic owner, so the function name
// remains address-derived.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

inline void *operator new(unsigned int, void *memory)
{
	return memory;
}

class EAStringC
{
public:
	EAStringC(unsigned int size);
	EAStringC()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~EAStringC()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

class Rva008A0320String
{
public:
	Rva008A0320String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~Rva008A0320String()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

// 0x008A0320 is a real body whose ledger name ?d_008a0320@@YAXXZ carries no
// proven signature, so it is reached through a member-pointer cast: the body
// takes (this, int) and returns a reference, and retail's caller passes this
// in ecx, so the call must keep thiscall codegen.
extern void __cdecl d_008a0320();
typedef Rva008A0320String &(Rva008A0320String::*Fn008A0320)(int);

class BfmeStrVKJ
{
public:
	BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &other);

	BfmeStringData3AF0 *m_data;
};

class BfmeStrEAW
{
public:
	BfmeStrEAW()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~BfmeStrEAW()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

class BfmeHostEAW
{
};

class Rva8CD130String;

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *out);
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned int length);
};

struct Rva008C3B60Node
{
	void *m_vptr;
	unsigned int m_flags;
	BfmeStringData3AF0 *m_data;
	Rva008C3B60Node *m_next;
};

class Rva008A9B00
{
public:
	Rva008A9B00();

	void *m_vptr;
	unsigned int m_flags;
	BfmeStringData3AF0 *m_data;
	Rva008A9B00 *m_next;
};

// 0x01337810: the Apt GC-root registry vector pointer, defined in
// game/Libraries/Source/Apt/Apt.cpp. The view type below is this TU's own.
struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(Rva008C3B60Node *node)
	{
		int index = m_count;
		int *pcount = &m_count;
		if (index >= m_capacity)
		{
			node->m_flags &= ~0x40000000u;
			return;
		}

		m_entries[index] = node;
		++*pcount;
	}
};

extern Rva00899560Pool *g_rva01337810GcRoots;
extern Rva008C3B60Node *Rva008C3B60Head;

struct Rva008AE770Stack
{
	int m_count;
};

extern Rva008AE770Stack Rva008AE770TheStack;

class AptValue : public BfmeHostEAW
{
public:
	int toInteger() const;
};

extern AptValue **g_bfmeArr1233;

Rva008C3B60Node *rva008AA130(BfmeHostEAW *first, int count)
{
	EAStringC result;
	((Rva8CD130Value *)first)->getName((Rva8CD130String *)&result);
	int index = 0;
	if (count > 0)
	{
		do
		{
			{
				BfmeStrEAW text;
				AptValue *value = g_bfmeArr1233[
					Rva008AE770TheStack.m_count - index - 1];
				((Rva8CD130Value *)value)->getName((Rva8CD130String *)&text);
				((BfmeStrVKJ *)&result)->bfmeAssignVKJ(
					*(const BfmeStrVKJ *)&text);
			}
			++index;
		} while (index < count);
	}

	Rva008C3B60Node *node = Rva008C3B60Head;
	if (node != 0)
	{
		Rva008C3B60Head = node->m_next;
		g_rva01337810GcRoots->addOrClear(node);
		if (node->m_data != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&node->m_data)->bfmeTruncVKK(0);
	}
	else
	{
		void *raw = Rva008C5D70Alloc(0x10);
		Rva008A9B00 *fresh;
		if (raw != 0)
			fresh = new (raw) Rva008A9B00();
		else
			fresh = 0;
		node = (Rva008C3B60Node *)fresh;
	}

	++result.m_data->m_refCount;
	BfmeStringData3AF0 *old = node->m_data;
	if (--old->m_refCount == 0)
		g_bfmeStringPool1284->free(old);
	node->m_data = result.m_data;
	return node;
}

Rva008C3B60Node *rva008AA2B0(int unused, int count)
{
	EAStringC result(count + count);
	int index = 0;
	if (count > 0)
	{
		do
		{
			int value = g_bfmeArr1233[
				Rva008AE770TheStack.m_count - index - 1]->toInteger();
			{
				Rva008A0320String text;
				{
					union { void (*fn)(); Fn008A0320 call; } u = { d_008a0320 };
					(text.*u.call)(value);
				}
				((BfmeStrVKJ *)&result)->bfmeAssignVKJ(
					*(const BfmeStrVKJ *)&text);
			}
			++index;
		} while (index < count);
	}

	Rva008C3B60Node *node = Rva008C3B60Head;
	if (node != 0)
	{
		Rva008C3B60Head = node->m_next;
		g_rva01337810GcRoots->addOrClear(node);
		if (node->m_data != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&node->m_data)->bfmeTruncVKK(0);
	}
	else
	{
		void *raw = Rva008C5D70Alloc(0x10);
		Rva008A9B00 *fresh;
		if (raw != 0)
			fresh = new (raw) Rva008A9B00();
		else
			fresh = 0;
		node = (Rva008C3B60Node *)fresh;
	}

	++result.m_data->m_refCount;
	BfmeStringData3AF0 *old = node->m_data;
	if (--old->m_refCount == 0)
		g_bfmeStringPool1284->free(old);
	node->m_data = result.m_data;
	return node;
}
