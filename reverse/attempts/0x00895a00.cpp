// ?d_00895a00@@YAXXZ
// partial score=0.72 date=2026-09-10
// cl: /Oa

struct BfmeHdrVKI
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_data[1];
};

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPoolVKI *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}
	void __declspec(nothrow) bfmeSetVKI(const char *text);
	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeHdrVKI *m_data;
};

class BfmeDropObjectA;

struct BfmeResultEVB
{
	BfmeResultEVB();
	BfmeResultEVB(const BfmeResultEVB &other);
	~BfmeResultEVB();

	BfmeDropObjectA *m_bfmeAEVB;
};

struct BfmeStringDataEVB
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_data[1];
};

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
extern void (*TheBfmeFree)(void *value, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();

	void operator delete(void *value, unsigned int bytes)
	{
		TheBfmeFree(value, bytes);
	}

	int m_refCount;
	BfmeStringDataEVB *m_string;
	int m_kind;
	void *m_argument;
	void *m_object;
	void *m_buffer;
};


__forceinline BfmeResultEVB::~BfmeResultEVB()
{
	if (m_bfmeAEVB != 0 && --m_bfmeAEVB->m_refCount == 0)
		delete m_bfmeAEVB;
}

__forceinline BfmeResultEVB::BfmeResultEVB()
	: m_bfmeAEVB(0)
{
}

__forceinline BfmeResultEVB::BfmeResultEVB(const BfmeResultEVB &other)
	: m_bfmeAEVB(other.m_bfmeAEVB)
{
	if (m_bfmeAEVB != 0)
		++m_bfmeAEVB->m_refCount;
}

struct BfmeDropNodeEVB
{
	BfmeDropObjectA *m_object;
	BfmeDropNodeEVB *m_next;
};

class Rva00893030Manager
{
public:
	void lookupEVB(void **result, BfmeStrVKI *name);
	BfmeResultEVB bfmeBuildEVB(BfmeStrVKI *name);

	BfmeDropNodeEVB *m_head;
};

extern "C" int memcmp(const void *left, const void *right, unsigned int count);

#pragma intrinsic(memcmp)

__forceinline BfmeStringDataEVB **bfmeStringSlotEVB(void *object)
{
	return (BfmeStringDataEVB **)((char *)object + 4);
}

void Rva00893030Manager::lookupEVB(void **result, BfmeStrVKI *name)
{
	BfmeDropNodeEVB *node = m_head;
	volatile int guard = 0;
	void **output = result;
	if (node != 0)
	{
		BfmeHdrVKI *key = name->m_data;
		unsigned int length = key->m_length;
		do
		{
			volatile BfmeDropObjectA *object = node->m_object;
			BfmeStringDataEVB * volatile *slot =
				(BfmeStringDataEVB * volatile *)((char *)object + 4);
			BfmeStringDataEVB *candidate = *slot;
			if (length == candidate->m_length)
			{
				if (key == reinterpret_cast<BfmeHdrVKI *>(candidate) ||
						memcmp(key->m_data, candidate->m_data, length) == 0)
				{
					BfmeDropObjectA *object = node->m_object;
					*output = object;
					if (object != 0)
					{
						int *refCount = &object->m_refCount;
						++*refCount;
					}
					return;
				}
			}
			node = node->m_next;
		}
		while (node != 0);
	}
	*output = 0;
}

extern Rva00893030Manager *g_rva00893030Manager;

BfmeResultEVB bfmeMakeEVB(const char *name)
{
	BfmeStrVKI value(name);

	return g_rva00893030Manager->bfmeBuildEVB(&value);
}

BfmeResultEVB Rva00893030Manager::bfmeBuildEVB(BfmeStrVKI *name)
{
	BfmeResultEVB result;
	BfmeDropObjectA *value;
	lookupEVB((void **)&value, name);

	if (value != 0)
	{
		result.m_bfmeAEVB = value;
		return result;
	}

	value = static_cast<BfmeDropObjectA *>(Rva008C5D70Alloc(0x18));
	if (value != 0)
	{
		value->m_refCount = 0;
		value->m_string = reinterpret_cast<BfmeStringDataEVB *>(name->m_data);
		++value->m_string->m_refCount;
		value->m_kind = 1;
		value->m_argument = 0;
		value->m_object = 0;
		value->m_buffer = 0;
	}
	if (value != 0)
		++value->m_refCount;
	result.m_bfmeAEVB = value;

	BfmeDropNodeEVB *node = static_cast<BfmeDropNodeEVB *>(Rva008C5D70Alloc(8));
	if (node != 0)
	{
		node->m_object = value;
		node->m_next = 0;
	}
	else
		node = 0;

	node->m_next = m_head;
	m_head = node;
	return result;
}
