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

struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

struct BfmeIterator1285;

class BfmeIteratorList1285
{
public:
	BfmeIterator1285 *bfmeFirst1285();
	BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *iterator);

	int m_count;
	BfmeIterator1285 *m_array;
};

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
	Rva8CCD60StringBlock *m_string;
	char m_gap[0x14];
	Rva8CCD60Value *m_indirect;
};

struct Rva8CCD60Iterator
{
	Rva8CCD60StringBlock *m_name;
	void *m_extra;
};

class Rva8CCD60IteratorList : public BfmeIteratorList1285
{
public:
	Rva8CCD60Iterator *first()
	{
		return (Rva8CCD60Iterator *)bfmeFirst1285();
	}
	Rva8CCD60Iterator *next(Rva8CCD60Iterator *iterator)
	{
		return (Rva8CCD60Iterator *)bfmeNext1285((BfmeIterator1285 *)iterator);
	}

	unsigned m_nextTagged;
};

class Rva8CCD60StringValue : public Rva8CCD60Value
{
};

class Rva008B2EA0Node;
Rva008B2EA0Node *rva008B2EA0Create();

inline Rva8CCD60StringValue *rva892940CreateStringValue()
{
	return (Rva8CCD60StringValue *)rva008B2EA0Create();
}

class Rva00899770;
class BfmeStrVKI;

// Body at 0x008cc940: ?d_008cc940@@YAXXZ. The retail callee is linked as a
// cdecl void() body, so the thiscall state method is recovered through a
// member-pointer call (the pattern aptExportString.cpp uses).
struct Rva008AE770Stack
{
};

extern void d_008cc940();

class Rva8CCD60State
{
public:
	void expandPrototypeValues(void *first, void *second);
	Rva8CCD60Value *makeValue(void *first, void *second, void *data,
		int one1, int one2, int zero)
	{
		typedef Rva00899770 *(Rva008AE770Stack::*Fn)(void *, int, BfmeStrVKI *, int, int, int);
		union { void (*fn)(); Fn call; } u = { d_008cc940 };
		return (Rva8CCD60Value *)(((Rva008AE770Stack *)this)->*u.call)(
			first, (int)second, (BfmeStrVKI *)data, one1, one2, zero);
	}

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

class AptValue;
extern AptValue *g_bfmeFallbackDB;

void Rva8CCD60State::expandPrototypeValues(void *first, void *second)
{
	Rva8CCD60Value *value = m_stack[m_count - 1];
	unsigned flags = value->m_flags;
	int type = flags & 0x3f;
	if (type == 1 || type == 42)
	{
		if (!((unsigned char)~(unsigned char)(flags >> 15) & 1))
		{
			Rva8CCD60Value *stringValue = type == 1 ? value : value->m_indirect;
			value = makeValue(first, second, &stringValue->m_string, 1, 1, 0);
		}
	}

	value->addRef();
	Rva8CCD60Value *old = m_stack[m_count - 1];
	if (!old->maxRefCountHit())
		old->release();
	--m_count;
	pushValue((Rva8CCD60Value *)g_bfmeFallbackDB);

	Rva8CCD60IteratorList *list = value->getIteratorList();
	while (list != 0)
	{
		for (Rva8CCD60Iterator *iterator = list->first(); iterator != 0;
			iterator = list->next(iterator))
		{
			if (_strcmpi(iterator->m_name->m_text, "__proto__") != 0 &&
				_strcmpi(iterator->m_name->m_text, "prototype") != 0)
			{
				Rva8CCD60StringValue *created = rva892940CreateStringValue();
				++iterator->m_name->m_refs;
				Rva8CCD60StringBlock *oldString = created->m_string;
				--oldString->m_refs;
				if (oldString->m_refs == 0)
					reinterpret_cast<void (__cdecl **)(void *)>(
						g_rva01337A30AllocPair)[1](oldString);
				created->m_string = iterator->m_name;
				pushValue(created);
			}
		}
		Rva8CCD60Value *next = (Rva8CCD60Value *)(list->m_nextTagged & ~1u);
		if (next == 0)
			break;
		list = next->getIteratorList();
	}
	value->release();
}
