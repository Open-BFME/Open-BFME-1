// ?helper@Gen_00896320@@QAEXPAX00@Z
// partial score=0.8165 date=2026-10-31
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
class Rva00894D80Accessor { public: static void increment(unsigned int *value); };
__declspec(noinline) BfmeRefVGO &BfmeRefVGO::bfmeAssignVGO(const BfmeRefVGO &o)
{
	if (&o != this)
	{
		if (m_bfmeP && Rva00894D90Accessor::decrement(m_bfmeP) == 0)
			bfmeDropA(m_bfmeP);
		m_bfmeP = o.m_bfmeP;
		if (m_bfmeP)
			Rva00894D80Accessor::increment(m_bfmeP);
	}
	return *this;
}

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

// Matched row at retail 0x008939C0 (Rva008939C0RefArrayResize.cpp).
class BfmeElemCU;
void *Rva008939C0(BfmeElemCU *data, int count, int capacity);
BfmeDropObjectA **Rva008953C0Copy(BfmeDropObjectA **first,
	BfmeDropObjectA **last, BfmeDropObjectA **result);
BfmeDropObjectA **Rva00895430Copy(BfmeDropObjectA **first,
	BfmeDropObjectA **last, BfmeDropObjectA **result);
BfmeDropObjectA **bfmeCopyBackVPD(BfmeDropObjectA **first,
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

	Gen00896320Item *newData = (Gen00896320Item *)Rva008939C0(0, 0, capacity + 1);
	Gen00896320Item *oldEnd = m_begin + m_count;
	Rva008953C0Copy((BfmeDropObjectA **)m_begin,
		(BfmeDropObjectA **)oldEnd, (BfmeDropObjectA **)newData);
	m_capacity = capacity;
	if (m_begin != m_inline)
		Rva008939C0((BfmeElemCU *)m_begin, 0, 0);
	m_begin = newData;
	const Gen00896320Item empty;
	m_begin[m_count].bfmeAssignVGO(empty);
	__assume(empty.m_bfmeP == 0);
}

// Inserts [*first, *last) before *pos, keeping a cleared item after the last
// element; on overflow it grows to twice the capacity and retries.
void Gen_00896320::helper(void *first, void *last, void *pos)
{
	Gen00896320Item *const &from = *(Gen00896320Item **)first;
	Gen00896320Item *const &to = *(Gen00896320Item **)last;
	Gen00896320Item *const &where = *(Gen00896320Item **)pos;
	int n = to - from;
	if (n == 0)
		return;
	int capacity = m_capacity;
	int newCount = (int)m_count + n;
	if (newCount < capacity)
	{
		Gen00896320Item *end = &m_begin[m_count];
		if (where == end)
		{
			Rva00895430Copy((BfmeDropObjectA **)from,
				(BfmeDropObjectA **)to, (BfmeDropObjectA **)end);
			const Gen00896320Item empty;
			m_begin[newCount].bfmeAssignVGO(empty);
			__assume(empty.m_bfmeP == 0);
		}
		else
		{
			bfmeCopyBackVPD((BfmeDropObjectA **)where, (BfmeDropObjectA **)end,
				(BfmeDropObjectA **)&m_begin[(where - m_begin) + n]);
			Rva00895430Copy((BfmeDropObjectA **)from,
				(BfmeDropObjectA **)to, (BfmeDropObjectA **)where);
			const Gen00896320Item empty;
			m_begin[newCount].bfmeAssignVGO(empty);
			__assume(empty.m_bfmeP == 0);
		}
		m_count = newCount;
		return;
	}

	int newCapacity = (int)(capacity * 2.0f);
	if (newCapacity < newCount)
		newCapacity = newCount;
	int index = where - m_begin;
	rva00896100(newCapacity);
	Gen00896320Item *newWhere = &m_begin[index];
	helper(first, last, &newWhere);
}
