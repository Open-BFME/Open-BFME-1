// ?rva0089E930@EAStringC@@QBE?AV1@PBD@Z
// partial score=0.7828 date=2026-10-10
// cl: /O2 /DNDEBUG /MD /EHsc

#pragma intrinsic(memcpy)
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)
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

class BfmeStrVKI { public: void bfmeSetVKI(const char *); };
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

	EAStringC rva0089E930(const char *other) const;
    EAStringC(StringDataC *data) : m_pData(data) { ++data->m_uRefCount; }
    EAStringC(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
	char *GetInternalBuffer() const { return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC); }
};

// Ported from Open BFME 2 Code/Libraries/Source/EA/Apt/AptString/EAStringCConcat.cpp.
EAStringC EAStringC::rva0089E930(const char *other) const
{
	unsigned int thisSize = m_pData->m_uSize;
	if (thisSize == 0)
		return EAStringC(other);

	unsigned int otherSize = strlen(other);
	if (otherSize == 0)
		return *this;

	EAStringC result(thisSize + otherSize);
	const char *source = GetInternalBuffer();
	char *dst = (char *)result.m_pData;
	memcpy(dst + 8, source, thisSize);
	memcpy(dst + thisSize + 8, other, otherSize);
	(dst + otherSize + 8)[thisSize] = 0;
	((StringDataC *)dst)->m_uSize = thisSize + otherSize;
	m_pData->m_uHash = 0;
	return EAStringC((StringDataC *)dst);
}
