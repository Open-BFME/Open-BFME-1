// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The 0x008961E0 helper calls rva00896100 with its unchanged Gen_00896320
// receiver. The target reads count/capacity/data at +0/+4/+8 and uses one
// inline handle at +0x0C. Its allocator callbacks are the one-word ctor/dtor
// pair at 0x00892B80 and 0x00784A70; slot assignment calls BfmeRefVGO.

class BfmeDropObjectA;
class BfmeRefVGO
{
public:
	BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &o);
	unsigned *m_bfmeP;
};

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

__declspec(noinline) void bfmeDropA(void *value);

class Rva00896100Item : public BfmeRefVGO
{
public:
	Rva00896100Item() { m_bfmeP = 0; }
	~Rva00896100Item()
	{
		if (m_bfmeP && Rva00894D90Accessor::decrement(m_bfmeP) == 0)
			bfmeDropA(m_bfmeP);
	}
};

typedef Rva00896100Item Gen00896320Item;

extern void b_008939c0(void);
BfmeDropObjectA **Rva008953C0Copy(BfmeDropObjectA **first,
	BfmeDropObjectA **last, BfmeDropObjectA **result);

class Gen_00896320
{
public:
	void append(void **source);
	void helper(void *first, void *last, void *result);
	void rva00896100(int capacity);

private:
	unsigned m_count;
	int m_capacity;
	Gen00896320Item *m_begin;
	Gen00896320Item m_inline[1];
};

void Gen_00896320::append(void **source)
{
	Gen00896320Item *end = &m_begin[m_count];
	Gen00896320Item *next = (Gen00896320Item *)source + 1;
	Gen00896320Item *begin = (Gen00896320Item *)source;
	helper(&begin, &next, &end);
}

void Gen_00896320::rva00896100(int capacity)
{
	int current = m_capacity;
	if (capacity <= current)
		return;
	if (capacity <= 1)
	{
		m_capacity = capacity;
		return;
	}

	Gen00896320Item *newData = (Gen00896320Item *)((void *(__cdecl *)(void *, int, int))b_008939c0)(0, 0, capacity + 1);
	Gen00896320Item *oldEnd = m_begin + m_count;
	Rva008953C0Copy((BfmeDropObjectA **)m_begin,
		(BfmeDropObjectA **)oldEnd, (BfmeDropObjectA **)newData);
	m_capacity = capacity;
	if (m_begin != m_inline)
		((void (__cdecl *)(void *, int, int))b_008939c0)(m_begin, 0, 0);
	m_begin = newData;
	const Gen00896320Item empty;
	m_begin[m_count].bfmeAssignVGO(empty);
	__assume(empty.m_bfmeP == 0);
}
