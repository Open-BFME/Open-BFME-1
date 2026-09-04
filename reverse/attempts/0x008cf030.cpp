// ?rva8CF030BuildArray@@YAXPAVRva8CF030State@@PAX@Z
// partial score=0.82 date=2026-09-02
// ?rva8CF030BuildArray@@YAXPAVRva8CF030State@@PAX@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt array/list builder, retail 0x008CF030 (380 bytes).

struct Rva8CF030StringBlock
{
	unsigned short m_refs;
};

extern Rva8CF030StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
extern void *(__cdecl *g_rva8CF030Allocate)(unsigned);

class Rva8CF030String
{
public:
	Rva8CF030String()
	{
		m_block = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refs;
	}
	~Rva8CF030String()
	{
		Rva8CF030StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}

private:
	Rva8CF030StringBlock *m_block;
	unsigned m_unused;
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
};

void rva897300InitializeRefObject(void *object);

class Rva8CF030ListNode : public Rva8CF030List
{
public:
	Rva8CF030ListNode(Rva8CF030Value *value);
	static void *operator new(unsigned size)
	{
		void *raw = g_rva8CF030Allocate(size + 8);
		void *object = (char *)raw + 8;
		rva897300InitializeRefObject(object);
		return object;
	}
	static void operator delete(void *);
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
	Rva8CF030State *owner = state;
	Rva8CF030Value *top = owner->m_stack[owner->m_count - 1];
	Rva8CF030Value *countValue = owner->m_stack[owner->m_count - 2];
	int count = countValue->toInteger();
	Rva8CF030List **items = (Rva8CF030List **)g_rva8CF030Allocate(count * 4);
	int index = 0;

	for (; index < count; ++index)
	{
		Rva8CF030Value *value = owner->m_stack[owner->m_count - index - 3];
		Rva8CF030List *owner = value->getList();
		Rva8CF030List *list = (Rva8CF030List *)(owner->m_nextTagged & ~1u);
		if (list == 0)
		{
			Rva8CF030List *created = new Rva8CF030ListNode(value);
			owner = value->getList();
			Rva8CF030List *old = (Rva8CF030List *)(owner->m_nextTagged & ~1u);
			if (created != 0)
				created->addRef();
			if (old != 0)
				old->release();
			if (created == 0)
				owner->m_nextTagged = 0;
			else
				owner->m_nextTagged = (unsigned)created | (created->tagged() == true ? 1u : 0u);
			list = created;
		}
		items[index] = list;
	}

	top->consumeArray(items, count);
	owner->popValues(count + 2);
}
