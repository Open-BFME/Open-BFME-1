// ?rva0089EB30@@YA?AVEAStringC@@PBDABV1@@Z
// partial score=0.6982 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /EHsc

#pragma intrinsic(memcpy)
#pragma intrinsic(strlen)
extern "C" unsigned int __cdecl strlen(const char *);
class BfmeStrVKI { public: void __declspec(nothrow) bfmeSetVKI(const char *); };
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

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
	EAStringC(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
	friend EAStringC rva0089EB30(const char *prefix, const EAStringC &text);
	EAStringC(const EAStringC &other) : m_pData(other.m_pData) { ++m_pData->m_uRefCount; }
	~EAStringC()
	{
		StringDataC *data = m_pData;
		if (--data->m_uRefCount == 0)
			g_bfmeStringPool1284->free(data);
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

EAStringC rva0089EB30(const char *prefix, const EAStringC &text)
{
    unsigned int textSize = text.m_pData->m_uSize;
    if (textSize == 0)
        return EAStringC(prefix);
    unsigned int prefixSize = strlen(prefix);
    if (prefixSize == 0)
        return text;
    EAStringC result(prefixSize + textSize);
    EAStringC::StringDataC *resultData = result.m_pData;
    memcpy((char *)(resultData + 1), prefix, prefixSize);
    char *tail = (char *)(resultData + 1) + prefixSize;
    memcpy(tail, text.GetInternalBuffer(), textSize);
    tail[textSize] = 0;
    resultData->m_uSize = textSize + prefixSize;
    resultData->m_uHash = 0;
    return result;
}
