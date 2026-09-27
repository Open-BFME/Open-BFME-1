// ?_FunctionRva008C7500@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
// partial score=0.989 date=2026-09-28
// ?_FunctionRva008C7500@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
// Opaque Apt string-equality handler; SWF7 undefined count feeds a switch, the name compare reuses it.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

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

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~Rva8CD130String()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
	}

	__forceinline bool operator==(const Rva8CD130String &other) const
	{
		unsigned left = m_data->m_length;
		unsigned right = other.m_data->m_length;
		return left == right
			&& (m_data == other.m_data
				|| memcmp(m_data + 1, other.m_data + 1, left) == 0);
	}

	BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value
{
public:
	virtual void AddRef();
	virtual void Release();
	void getName(Rva8CD130String *output);

	bool isUndefined() const
	{
		return ((m_flags >> 15) & 1) == 0;
	}

	bool maxRefCountHit() const
	{
		return ((m_flags >> 30) & 1) != 0;
	}

	unsigned m_flags;
};

struct Rva008D2A30Node
{
	void *m_vtable;
	unsigned m_flags;
	union
	{
		Rva008D2A30Node *m_next;
		bool m_value;
	};
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva008D2A30Node **m_items;

	__forceinline void addPooled(Rva008D2A30Node *node)
	{
		int &count = m_count;
		if (count >= m_capacity)
			node->m_flags &= 0xbfffffff;
		else
		{
			m_items[count] = node;
			count++;
		}
	}
};

extern Rva008D2A30Node *Rva008D2A30Head;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);

struct Rva008C7500Boolean
{
	void *m_vtable;
	unsigned m_flags;
	union
	{
		Rva008C7500Boolean *m_next;
		bool m_value;
	};

	__forceinline static Rva008C7500Boolean *Create(bool value)
	{
		Rva008C7500Boolean *object =
			(Rva008C7500Boolean *)Rva008D2A30Head;

		if (object != 0)
		{
			Rva008D2A30Head = (Rva008D2A30Node *)object->m_next;
			g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
			object->m_value = value;
		}
		else
		{
			void *memory = Rva008C5D70Alloc(12);
			if (memory != 0)
			{
				object = (Rva008C7500Boolean *)memory;
				object->m_vtable = (void *)0x01135D68;
				object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
				g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
				object->m_vtable = (void *)0x011360A8;
				object->m_value = value;
			}
			else
				object = 0;
		}

		return object;
	}
};

class AptActionInterpreter
{
public:
	struct LocalContextT;

	static void _FunctionRva008C7500(
		AptActionInterpreter *interpreter, LocalContextT *);

	int m_stackTop;
	int m_stackCapacity;
	Rva8CD130Value **m_stack;
};

extern int Rva00892370Get();
extern Rva8CD130Value *g_bfmeFallbackDB;

void AptActionInterpreter::_FunctionRva008C7500(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	Rva8CD130Value *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	Rva8CD130Value *under = interpreter->m_stack[interpreter->m_stackTop - 2];
	Rva8CD130Value *result = 0;
	int undefinedCount = 0;

	if (Rva00892370Get() == 7)
	{
		if (top->isUndefined())
			undefinedCount = 1;
		if (under->isUndefined())
			++undefinedCount;

		switch (undefinedCount)
		{
		case 1:
			result = g_bfmeFallbackDB;
			break;
		case 2:
			result = (Rva8CD130Value *)Rva008C7500Boolean::Create(true);
			break;
		}
	}

	if (result == 0)
	{
		Rva8CD130String topName;
		Rva8CD130String underName;
		top->getName(&topName);
		under->getName(&underName);
		if (topName == underName)
			undefinedCount = 1;
		result = (Rva8CD130Value *)Rva008C7500Boolean::Create(
			undefinedCount != 0);
	}

	for (int index = 1; index <= 2; ++index)
	{
		Rva8CD130Value *value =
			interpreter->m_stack[interpreter->m_stackTop - index];
		if (!value->maxRefCountHit())
			value->Release();
	}

	interpreter->m_stackTop -= 2;
	interpreter->m_stack[interpreter->m_stackTop] = result;
	++interpreter->m_stackTop;
	if (!result->maxRefCountHit())
		result->AddRef();
}
