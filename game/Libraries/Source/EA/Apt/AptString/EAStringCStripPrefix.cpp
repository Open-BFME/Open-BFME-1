// cl: /O2 /DNDEBUG /MD /EHsc

/*
 * Honest RE identity: retail 0x0089F660 is a 198-byte EAStringC-family body
 * with no references in the image, so the name keeps its address. The proven
 * behavior: if the string starts with pStrText (strlen, size check against
 * m_pData->m_uSize at +2, inline memcmp over the buffer at +8), replace this
 * with the matched Mid (0x0089F1B0) past that prefix and return true, else
 * return false. The class model is the one from its sibling
 * EAStringCTrimRight.cpp (0x0089F530), two bodies earlier.
 * No original EA method name is claimed.
 */

extern "C" unsigned int __cdecl strlen(const char *);
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(strlen, memcmp)

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
	EAStringC Mid(int count) const;
	bool rva0089F660(const char *pStrText);
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

// ?rva0089F660@EAStringC@@QAE_NPBD@Z
bool EAStringC::rva0089F660(const char *pStrText)
{
	unsigned int uLength = strlen(pStrText);
	if (m_pData->m_uSize >= uLength && memcmp(GetInternalBuffer(), pStrText, uLength) == 0)
	{
		*this = Mid(static_cast<int>(uLength));
		return true;
	}
	return false;
}
