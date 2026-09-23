// ?rva008CEE40@@YAXPAVRva008AE770Stack@@PAURva008CEE40Context@@@Z
// Retail RVA 0x008CEE40: 491 bytes, ret at 0x008CF02A then int3.
// Referenced by the data table at VA 0x012D5BB8; semantic identity unproven.
// The carved body at 0x008CEE40 has no matched caller, so its name stays
// address-derived. Its stack arguments match the Apt value stack at +0/+8 and
// a context with the fields read at +4/+8. The body calls the landed getName
// method and the existing createString alias, then installs the two witnessed
// Apt value tables at 0x01135D68 and 0x011360A8.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

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

	BfmeStringData3AF0 *m_data;
};

class Rva00899770;
class BfmeStrVKI;
class Rva8CD130Value;
class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, Int unused, BfmeStrVKI *name,
		Int one, Int another, Int zero);

	Int m_count;
	Int m_unused04;
	Rva8CD130Value **m_entries;
};

class Rva8CD130Value
{
public:
	virtual void AddRef();
	virtual void Release();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual Bool compareString(Rva8CD130Value *other);

	void getName(Rva8CD130String *output);

	Bool isRetained() const
	{
		return (m_flags >> 30) & 1;
	}

	Bool isUndefined() const
	{
		return ((m_flags >> 15) & 1) == 0;
	}

	UnsignedInt m_flags;
};

struct Rva008CEE40Context
{
	Int field00;
	void *field04;
	Int field08;
};

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
	Int m_capacity;
	Int m_count;
	Rva008D2A30Node **m_items;

	__forceinline void addPooled(Rva008D2A30Node *node)
	{
		Int &count = m_count;
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

struct Rva008CEE40Boolean
{
	void *m_vtable;
	UnsignedInt m_flags;
	union
	{
		Rva008CEE40Boolean *m_next;
		Bool m_value;
	};

	__forceinline static Rva008CEE40Boolean *Create(Bool value)
	{
		Rva008CEE40Boolean *object =
			(Rva008CEE40Boolean *)Rva008D2A30Head;

		if (object != 0)
		{
			Rva008D2A30Head = (Rva008D2A30Node *)object->m_next;
			g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
			object->m_value = value;
			return object;
		}

		object = (Rva008CEE40Boolean *)Rva008C5D70Alloc(12);
		if (object != 0)
		{
			object->m_vtable = (void *)0x01135D68;
			object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
			g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
			object->m_vtable = (void *)0x011360A8;
			object->m_value = value;
			return object;
		}

		return 0;
	}
};

void rva008CEE40(Rva008AE770Stack *stack, Rva008CEE40Context *context)
{
	Rva8CD130Value *topString;
	Rva8CD130Value *underString;

	{
		Rva8CD130String name;
		Rva8CD130String *out = &name;
		stack->m_entries[stack->m_count - 1]->getName(out);
		topString = (Rva8CD130Value *)stack->createString(
			context->field04, context->field08, (BfmeStrVKI *)&name, 1, 1, 0);
		Rva8CD130Value *under = stack->m_entries[stack->m_count - 2];
		under->getName(&name);
		underString = (Rva8CD130Value *)stack->createString(
			context->field04, context->field08, (BfmeStrVKI *)&name, 1, 1, 0);
	}

	Bool equal;
	if ((topString->m_flags & 0x3f) == 0x1b &&
		!topString->isUndefined() &&
		(underString->m_flags & 0x3f) == 0x1c &&
		!underString->isUndefined() &&
		topString->compareString(underString))
		equal = 1;
	else
		equal = 0;

	for (Int index = 1; index <= 2; ++index)
	{
		Rva8CD130Value *value = stack->m_entries[stack->m_count - index];
		if (!value->isRetained())
			value->Release();
	}

	stack->m_count -= 2;
	Rva008CEE40Boolean *result = Rva008CEE40Boolean::Create(equal);
	stack->m_entries[stack->m_count] = (Rva8CD130Value *)result;
	++stack->m_count;
	if (!((Rva8CD130Value *)result)->isRetained())
		((Rva8CD130Value *)result)->AddRef();
}
