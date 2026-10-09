// cl: /O2 /DNDEBUG /MD /EHsc

#pragma intrinsic(memcpy)
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

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
	__declspec(noinline) EAStringC(unsigned int nSize);
	EAStringC(const EAStringC &other) : m_pData(other.m_pData) { ++m_pData->m_uRefCount; }
	~EAStringC()
	{
		StringDataC *data = m_pData;
		if (--data->m_uRefCount == 0)
			g_rva01337A30AllocPair->free(data);
	}

	EAStringC rva0089E0C0(const EAStringC &other) const;
	char *GetInternalBuffer() const { return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC); }
};

// The shared empty string block at 0x012D5298, defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp.
extern EAStringC::StringDataC g_rva012D5298Empty;

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
		m_pData = &g_rva012D5298Empty;
		++g_rva012D5298Empty.m_uRefCount;
	}
}

EAStringC EAStringC::rva0089E0C0(const EAStringC &other) const
{
	unsigned int thisSize = m_pData->m_uSize;
	if (thisSize == 0)
		return other;

	unsigned int otherSize = other.m_pData->m_uSize;
	if (otherSize == 0)
		return *this;

	EAStringC result(thisSize + otherSize);
	EAStringC::StringDataC *resultData = result.m_pData;
	char *dst = (char *)(resultData + 1);
	memcpy(dst, GetInternalBuffer(), thisSize);
	memcpy(dst + thisSize, other.GetInternalBuffer(), otherSize);
	(dst + otherSize)[thisSize] = 0;
	resultData->m_uSize = thisSize + otherSize;
	m_pData->m_uHash = 0;
	return result;
}
