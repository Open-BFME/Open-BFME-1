// ?Rva008939C0@@YAPAXPAVBfmeElemCU@@HH@Z
// partial score=0.992 date=2026-09-28
// Rva008939C0 uses its retail address as its name because the caller only
// calls the body through the RVA token b_008939c0.
// Gen_00896320::rva00896100 passes a null input and a new count to allocate
// BfmeElemCU elements, then passes the old data pointer and zero counts to
// destroy and free that array. Retail calls the constructor at 0x00892B80
// and destructor thunk at 0x000463AD.
// This draft matches 99.2% of normalized instructions and emits 360 bytes.
// Its remaining structural difference is the one-byte loop NOP at +0xEF.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <new>

extern "C" void *(__cdecl *g_bfmeAllocDWF)(unsigned int);
extern "C" void (__cdecl *g_bfmeFreeDWF)(void *);

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};
class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *value);
};
void bfmeDropA(void *value);

class BfmeElemCU
{
public:
	static void *__cdecl operator new[](unsigned int bytes) throw()
	{
		return g_bfmeAllocDWF(bytes);
	}
	static void __cdecl operator delete[](void *value) throw()
	{
		g_bfmeFreeDWF(value);
	}
	BfmeElemCU();
	~BfmeElemCU();
	BfmeElemCU &operator=(const BfmeElemCU &other)
	{
		if (&other != this)
		{
			if (m_value && Rva00894D90Accessor::decrement((unsigned int *)m_value) == 0)
				bfmeDropA(m_value);
			m_value = other.m_value;
			if (m_value)
				Rva00894D80Accessor::increment((unsigned int *)m_value);
		}
		return *this;
	}
private:
	void *m_value;
};

void *Rva008939C0(BfmeElemCU *source, int oldCount, int newCount)
{
	if (!source)
		return new BfmeElemCU[newCount];

	{
	int count = *(volatile int *)&newCount;
	BfmeElemCU *destination = 0;
	if (count != 0)
	{
		destination = new BfmeElemCU[count];
		if (count >= oldCount)
			count = oldCount;
		if (count != 0)
		{
		int remaining = count;
		BfmeElemCU *out = destination;
		do
		{
			BfmeElemCU *current = out;
			++out;
			*current = *source;
			++source;
		} while (--remaining != 0);
		}
	}
	delete[] source;
	return destination;
	}
}
