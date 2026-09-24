// ?rva8CF030BuildArray@@YAXPAVRva8CF030State@@PAX@Z
// partial score=0.9 date=2026-09-24
// ?rva8CF030BuildArray@@YAXPAVRva8CF030State@@PAX@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt array builder, retail 0x008CF030 (380 bytes); residue is register allocation only.

struct BfmeStringData3AF0
{
	unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0
{
	void *m_unknown00;
	void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);

class Rva8CF030String
{
public:
	Rva8CF030String() : m_data(&g_bfmeDefaultString1284) { ++m_data->m_refCount; }
	~Rva8CF030String()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
	}

private:
	BfmeStringData3AF0 *m_data;
};

class Rva8CF030List;
class Rva8CF030Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual bool tagged();
	virtual Rva8CF030List *getList();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void consumeArray(Rva8CF030List **items, int count);

	int toInteger() const;
};

class Rva8CF030List
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual bool tagged();

	char m_gap04[8];
	unsigned m_nextTagged;

	Rva8CF030List *next() const { return (Rva8CF030List *)(m_nextTagged & ~1u); }
	void setNext(Rva8CF030List *list)
	{
		Rva8CF030List *old = next();
		if (list != 0)
			list->addRef();
		if (old != 0)
			old->release();
		if (list == 0)
			m_nextTagged = 0;
		else if (list->tagged() == 1)
			m_nextTagged = (unsigned)list | 1;
		else
			m_nextTagged = (unsigned)list;
	}
};

void rva897300InitializeRefObject(void *object);

class Rva8CF030ListNode : public Rva8CF030List
{
public:
	Rva8CF030ListNode(Rva8CF030Value *value);
	static void *operator new(unsigned size)
	{
		void *raw = Rva008C5D70Alloc(size + 8);
		void *object = (char *)raw + 8;
		rva897300InitializeRefObject(object);
		return object;
	}
	static void operator delete(void *object, unsigned size);
	char m_gap10[0x0c];
};

class Rva8CF030State
{
public:
	void popValues(int count);

	int m_count;
	int m_unused;
	Rva8CF030Value **m_stack;
};

void rva8CF030BuildArray(Rva8CF030State *state, void *)
{
	Rva8CF030String unusedString;
	Rva8CF030Value *top = state->m_stack[state->m_count - 1];
	int index = 0;
	int count = state->m_stack[state->m_count - 2]->toInteger();
	Rva8CF030List **items = (Rva8CF030List **)Rva008C5D70Alloc(count * 4);
	for (; index < count; ++index)
	{
		Rva8CF030Value *value = state->m_stack[state->m_count - index - 3];
		Rva8CF030List *list = value->getList()->next();
		if (list == 0)
		{
			list = new Rva8CF030ListNode(value);
			value->getList()->setNext(list);
		}
		items[index] = list;
	}
	top->consumeArray(items, count);
	state->popValues(count + 2);
}
