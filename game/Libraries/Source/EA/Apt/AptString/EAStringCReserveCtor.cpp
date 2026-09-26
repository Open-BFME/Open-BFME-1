// cl: /O2 /DNDEBUG /MD

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

public:
	EAStringC(unsigned int nSize);
};

extern EAStringC::StringDataC g_emptyStringData;

EAStringC::EAStringC(unsigned int nSize)
{
	if (nSize)
	{
		unsigned int alloc = (nSize + 12) & ~3u;
		m_pData = (StringDataC *)g_bfmeAllocVKJ->allocate(alloc);
		m_pData->m_uRefCount = 1;
		m_pData->m_uMaxSize = (unsigned short)(alloc - 9);
		m_pData->m_uSize = 0;
		m_pData->m_uHash = 0;
		reinterpret_cast<char *>(m_pData)[sizeof(StringDataC)] = 0;
	}
	else
	{
		m_pData = &g_emptyStringData;
		++g_emptyStringData.m_uRefCount;
	}
}
