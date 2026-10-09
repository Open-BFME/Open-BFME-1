// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// The two inline handles rotate through an owning scratch array.

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
	char m_rest[0x14];
};

BfmeDropObjectA **__cdecl Rva008953C0Copy(
	BfmeDropObjectA **first, BfmeDropObjectA **last, BfmeDropObjectA **result);

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value)
	{
		return --*value;
	}
};

class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *value)
	{
		return ++*value;
	}
};

class Rva008947A0Elem;

class BfmeElemCU
{
public:
	// Array storage uses the recorded constructor and destructor callbacks.
	typedef Rva008947A0Elem ArrayElement;

	BfmeElemCU();
	BfmeElemCU(BfmeDropObjectA *value) : m_ptr(value)
	{
		if (m_ptr)
			Rva00894D80Accessor::increment((unsigned int *)m_ptr);
	}
	~BfmeElemCU()
	{
		if (m_ptr && Rva00894D90Accessor::decrement((unsigned int *)m_ptr) == 0)
			delete m_ptr;
	}
	BfmeElemCU &operator=(const BfmeElemCU &other)
	{
		if (this != &other)
		{
			if (m_ptr && Rva00894D90Accessor::decrement((unsigned int *)m_ptr) == 0)
				delete m_ptr;
			m_ptr = other.m_ptr;
			if (m_ptr)
				Rva00894D80Accessor::increment((unsigned int *)m_ptr);
		}
		return *this;
	}
	BfmeDropObjectA *m_ptr;
};

class Rva008947A0Elem
{
public:
	Rva008947A0Elem();
	~Rva008947A0Elem();

	BfmeElemCU &operator=(const BfmeElemCU &other)
	{
		return m_handle.operator=(other);
	}

	BfmeElemCU m_handle;
};

class BfmeDropObjectAVector
{
public:
	void swap(BfmeDropObjectAVector &other);

	int m_start;
	int m_finish;
	BfmeDropObjectA **m_capacity;
	BfmeElemCU m_inline[2];
};

// ?swap@BfmeDropObjectAVector@@QAEXAAV1@@Z
void BfmeDropObjectAVector::swap(BfmeDropObjectAVector &other)
{
	int t;

	t = other.m_start;
	other.m_start = m_start;
	m_start = t;

	t = other.m_finish;
	other.m_finish = m_finish;
	m_finish = t;

	BfmeDropObjectA **thisInlineAddr = (BfmeDropObjectA **)m_inline;

	BfmeDropObjectA **thisCap = m_capacity;
	bool thisWasInline = (thisCap == thisInlineAddr);

	BfmeDropObjectA **otherCap = other.m_capacity;
	BfmeDropObjectA **otherInlineAddr = (BfmeDropObjectA **)other.m_inline;
	bool otherWasInline = (otherCap == otherInlineAddr);

	if (otherWasInline)
		m_capacity = thisInlineAddr;
	else
		m_capacity = otherCap;

	if (thisWasInline)
		other.m_capacity = otherInlineAddr;
	else
		other.m_capacity = thisCap;

	if (otherWasInline || thisWasInline)
	{
		BfmeElemCU::ArrayElement scratch[2];
		scratch[1] = BfmeElemCU(0);

		Rva008953C0Copy(thisInlineAddr, (BfmeDropObjectA **)(m_inline + 2), (BfmeDropObjectA **)scratch);
		Rva008953C0Copy(otherInlineAddr, (BfmeDropObjectA **)(other.m_inline + 2), thisInlineAddr);
		Rva008953C0Copy((BfmeDropObjectA **)scratch, (BfmeDropObjectA **)scratch + 2, otherInlineAddr);
	}
}
