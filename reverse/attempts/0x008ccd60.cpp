// ?expandPrototypeValues@Rva8CCD60State@@QAEXPAX0@Z
// partial score=0.74 date=2026-09-02
// ?expandPrototypeValues@Rva8CCD60State@@QAEXPAX0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt prototype-chain expansion, retail 0x008CCD60 (363 bytes).

extern "C" int __cdecl _strcmpi(const char *, const char *);

struct Rva8CCD60StringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
	unsigned m_capacity;
	char m_text[1];
};

extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class Rva8CCD60IteratorList;

class Rva8CCD60Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual Rva8CCD60IteratorList *getIteratorList();

	bool maxRefCountHit() const
	{
		return ((m_flags >> 30) & 1) != 0;
	}

	unsigned m_flags;
	char m_gap[0x18];
	Rva8CCD60Value *m_indirect;
};

struct Rva8CCD60Iterator
{
	Rva8CCD60StringBlock *m_name;
};

class Rva8CCD60IteratorList
{
public:
	Rva8CCD60Iterator *first();
	Rva8CCD60Iterator *next(Rva8CCD60Iterator *iterator);

	void *m_unused;
	unsigned m_nextTagged;
};

class Rva8CCD60StringValue : public Rva8CCD60Value
{
public:
	Rva8CCD60StringBlock *m_string;
};

Rva8CCD60StringValue *rva892940CreateStringValue();

class Rva8CCD60State
{
public:
	void expandPrototypeValues(void *first, void *second);
	Rva8CCD60Value *makeValue(void *first, void *second, void *data,
		int one1, int one2, int zero);

	void pushValue(Rva8CCD60Value *value)
	{
		m_stack[m_count++] = value;
		if (!value->maxRefCountHit())
			value->addRef();
	}

	int m_count;
	int m_unused;
	Rva8CCD60Value **m_stack;
};

extern Rva8CCD60Value *g_bfmeFallbackDB;

void Rva8CCD60State::expandPrototypeValues(void *first, void *second)
{
	Rva8CCD60IteratorList *list;
	Rva8CCD60Value *value = m_stack[m_count - 1];
	unsigned flags = value->m_flags;
	int type = flags & 0x3f;
	if (type == 1 || type == 42)
	{
		flags >>= 15;
		*(unsigned char *)&flags = (unsigned char)~*(unsigned char *)&flags;
		if (!(*(unsigned char *)&flags & 1))
		{
			Rva8CCD60Value *stringValue = type == 1 ? value : value->m_indirect;
			value = makeValue(first, second, (char *)stringValue + 8, 1, 1, 0);
		}
	}

	value->addRef();
	Rva8CCD60Value *old = m_stack[m_count - 1];
	if (!old->maxRefCountHit())
		old->release();
	--m_count;
	pushValue(g_bfmeFallbackDB);

	for (list = value->getIteratorList(); list != 0; )
	{
		for (Rva8CCD60Iterator *iterator = list->first(); iterator != 0;
			iterator = list->next(iterator))
		{
			const char *name = iterator->m_name->m_text;
			if (_strcmpi(name, "__proto__") != 0 &&
				_strcmpi(name, "prototype") != 0)
			{
				Rva8CCD60StringValue *created = rva892940CreateStringValue();
				Rva8CCD60StringBlock *replacement = iterator->m_name;
				++replacement->m_refs;
				Rva8CCD60StringBlock *oldString = created->m_string;
				--oldString->m_refs;
				if (oldString->m_refs == 0)
					Rva01337A30ReleaseTable[1](oldString);
				created->m_string = replacement;
				pushValue(created);
			}
		}
		unsigned next = list->m_nextTagged & ~1u;
		list = next == 0 ? 0 : ((Rva8CCD60Value *)next)->getIteratorList();
	}
	value->release();
}
