// ?rva00899800@@YAPAVAptValue@@PAXH@Z
// Retail 0x00899800 (748 B): Apt native (name, value) that erases or stores the name in the lazily built table at 0x01337A28.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

struct Rva008D2A30Node
{
	void *m_vtable;
	UnsignedInt m_flags;
	union
	{
		Rva008D2A30Node *m_next;
		Bool m_value;
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
extern void *(__cdecl *Rva008C5D70Alloc)(UnsignedInt bytes);

class AptValue
{
public:
	Bool isUndefined() const
	{
		return ((m_flags >> 15) & 1) == 0;
	}
	Bool isString() const
	{
		UnsignedInt type = m_flags & 0x3f;
		return (type == 1 || type == 42) && !isUndefined();
	}

	void *m_vtable;
	union
	{
		UnsignedInt m_flags;
		struct
		{
			UnsignedInt m_type : 6;
			UnsignedInt m_bits : 9;
			UnsignedInt m_pooled : 1;
		};
	};
	void *m_payload08;
	char m_padding0c[0x14];
	AptValue *m_indirect;

};

extern AptValue **g_bfmeArr1233;
extern int g_stack01338748;
extern void *g_Rva01337A28Index;
class BfmeS1238;
extern int Rva00898D20Get();
extern BfmeS1238 *Rva00898D40At(void *unused, int index);
extern void __cdecl bfmeAppend(int, int, int);
extern "C" void (*TheBfmeFree)(void *, UnsignedInt);
extern const char vtable01135D68[], vtable011360A8[];

struct BfmeStateNode
{
	virtual void retain();
	virtual void release();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual Bool slot05();
};

// Retail unwind state 0 pushes 16 and the allocation, then calls the 0x008976D0 thunk.
struct Gen_uws16_008976d0
{
	static void operator delete(void *object, unsigned int bytes);
};

class Rva0089C860State : public Gen_uws16_008976d0
{
public:
	Rva0089C860State(int value) { initialize(value); }
	Rva0089C860State *initialize(int value);
	~Rva0089C860State();
	static void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}
	int m_value;
	int m_flags;
	BfmeStateNode *m_node;
	int m_tail;
};

struct BfmeKey1279;
class BfmeLookup1279
{
public:
	void bfmeErase1279(BfmeKey1279 &key);
};

class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
};

struct Rva00899800Boolean
{
	void *m_vtable;
	UnsignedInt m_flags;
	union
	{
		Rva00899800Boolean *m_next;
		Bool m_value;
	};

	__forceinline static Rva00899800Boolean *createFalse()
	{
		Rva00899800Boolean *object =
			(Rva00899800Boolean *)Rva008D2A30Head;
		if (object != 0)
		{
			Rva008D2A30Head = (Rva008D2A30Node *)object->m_next;
			g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
			object->m_value = 0;
			return object;
		}

		object = (Rva00899800Boolean *)Rva008C5D70Alloc(12);
		if (object != 0)
		{
			object->m_vtable = (void *)vtable01135D68;
			object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
			g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
			object->m_vtable = (void *)vtable011360A8;
			object->m_value = 0;
			return object;
		}

		return 0;
	}

	__forceinline static Rva00899800Boolean *createTrue()
	{
		Rva00899800Boolean *object =
			(Rva00899800Boolean *)Rva008D2A30Head;
		if (object != 0)
		{
			Rva008D2A30Head = (Rva008D2A30Node *)object->m_next;
			g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
			object->m_value = 1;
			return object;
		}

		object = (Rva00899800Boolean *)Rva008C5D70Alloc(12);
		if (object != 0)
		{
			UnsignedInt flags =
				(object->m_flags & 0xf0008005) | 0x40008005;
			object->m_vtable = (void *)vtable01135D68;
			object->m_flags = flags;
			g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
			object->m_vtable = (void *)vtable011360A8;
			object->m_value = 1;
			return object;
		}

		return 0;
	}
};

AptValue *rva00899800(void *, int argc)
{
	if (argc != 2)
		return (AptValue *)Rva00899800Boolean::createFalse();

	AptValue *top = g_bfmeArr1233[g_stack01338748 - 1];
	if (!(top->m_flags & 0x8000) || !top->isString())
		return (AptValue *)Rva00899800Boolean::createFalse();

	Rva0089C860State *table = (Rva0089C860State *)g_Rva01337A28Index;
	AptValue *under = g_bfmeArr1233[g_stack01338748 - 2];
	if (table == 0)
	{
		g_Rva01337A28Index = new Rva0089C860State(8);
		bfmeAppend((int)g_Rva01337A28Index, (int)&Rva00898D20Get,
			(int)&Rva00898D40At);
		table = (Rva0089C860State *)g_Rva01337A28Index;
	}

	if (under->m_type == 3)
	{
		AptValue *key = top;
		if (key->m_type != 1)
			key = key->m_indirect;
		((BfmeLookup1279 *)table)->bfmeErase1279(
			*(BfmeKey1279 *)&key->m_payload08);
	}
	else
	{
		AptValue *key = top;
		if (key->m_type != 1)
			key = key->m_indirect;
		((Rva8D0D80Table *)table)->add(
			(Rva8D0D80String *)&key->m_payload08,
			(Rva8D0D80Value *)under);
	}

	return (AptValue *)Rva00899800Boolean::createTrue();
}
