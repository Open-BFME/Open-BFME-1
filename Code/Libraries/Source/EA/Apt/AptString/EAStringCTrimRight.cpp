// cl: /O2 /DNDEBUG /MD /EHsc

/*
 * Honest RE identity: retail 0x0089F530 is a 270-byte EAStringC-family body,
 * not an independently named original EA Apt method.  The proven behavior is
 * the backward strchr scan over the internal buffer, using m_pData->m_uSize at
 * +2 and the character buffer at +8, followed by the address-qualified
 * 206-byte substring helper at 0x0089F010 and return of this after assignment.
 * The helper is declaration-only: its return-by-value declaration preserves
 * the hidden return-storage plus thiscall receiver ABI visible at the call.
 * No original PC EAStringC source or EA Apt 2.00.00 attribution is claimed.
 */

extern "C" char *__cdecl strchr(const char *, int);

struct BfmeAllocVKJ
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

class EAStringC
{
	public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	private:
	StringDataC *m_pData;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

	public:
	__forceinline EAStringC();

	EAStringC(const EAStringC &other)
		: m_pData(other.m_pData)
	{
		++m_pData->m_uRefCount;
	}

	__forceinline ~EAStringC()
	{
		StringDataC *data = m_pData;
		if (--data->m_uRefCount == 0)
			g_bfmeAllocVKJ->free(data);
	}

	__forceinline EAStringC &operator=(const EAStringC &other)
	{
		++other.m_pData->m_uRefCount;
		StringDataC *oldData = m_pData;
		if (--oldData->m_uRefCount == 0)
			g_bfmeAllocVKJ->free(oldData);
		m_pData = other.m_pData;
		return *this;
	}
	EAStringC rva0089F010(int count) const;
	EAStringC &rva0089F530(const char *pStrText);
};

extern EAStringC::StringDataC g_emptyStringData;

__forceinline EAStringC::EAStringC()
{
	++g_emptyStringData.m_uRefCount;
	m_pData = &g_emptyStringData;
}

typedef char EAStringC_StringDataC_size_must_be_8[
	(sizeof(EAStringC::StringDataC) == 8) ? 1 : -1];
typedef char EAStringC_size_must_be_4[(sizeof(EAStringC) == 4) ? 1 : -1];

EAStringC &EAStringC::rva0089F530(const char *pStrText)
{
	const unsigned int uSize = m_pData->m_uSize;
	const char *p = GetInternalBuffer() + uSize - 1;
	unsigned int uTrim = 0;
	while (uTrim < uSize)
	{
		char c = *p;
		--p;
		if (!strchr(pStrText, c))
			break;
		++uTrim;
	}
	EAStringC result;
	result = rva0089F010(static_cast<int>(uSize - uTrim));
	*this = result;
	return *this;
}
