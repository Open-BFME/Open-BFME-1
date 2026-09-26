// cl: /DNDEBUG /MD /EHsc /O2

// STLport 4.5.3 _Locale_impl destructor and compiler-emitted scalar-deleting
// wrapper. Retail RTTI identifies vtable 0x0112EB34 as _STL::_Locale_impl;
// slot zero is the 30-byte wrapper at 0x0083B310. The wrapper calls the exact
// 83-byte implementation destructor at 0x00836520.

extern "C" char *g_bfmeFreeList1150[];
extern "C" int g_bfmeGuardXH;
extern "C" void __cdecl bfmeLockXH(void *guard);

void __cdecl operator delete(void *block);

namespace _STL
{

class _Locale_impl
{
public:
	virtual ~_Locale_impl();
	virtual void incrementReference() = 0;
	virtual void decrementReference() = 0;

private:
	void *m_facets;
	unsigned int m_facetCount;
	char *volatile m_start;
	char *m_finish;
	char *volatile m_endOfStorage;
};

_Locale_impl::~_Locale_impl()
{
	char *end = m_endOfStorage;
	char *start = m_start;
	unsigned int used = end - start;

	if (start != 0)
	{
		if (used > 0x80)
		{
			operator delete(start);
		}
		else
		{
			char **list = g_bfmeFreeList1150 + ((used - 1) >> 3);
			bfmeLockXH(&g_bfmeGuardXH);
			*(char **)start = *list;
			*list = start;
			g_bfmeGuardXH = 0;
		}
	}
}

void forceLocaleImplDeletingDestructor(_Locale_impl *value)
{
	delete value;
}

} // namespace _STL
