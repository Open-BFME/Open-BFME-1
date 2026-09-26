// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// partial score=0.08 date=2026-09-21
// Anonymous EA Apt string cluster body (no named caller). Address-derived
// name kept per naming policy. Concatenates prefix + self into out.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct StringDataC
{
	unsigned short m_uRefCount;
	unsigned short m_uSize;
	unsigned short m_uMaxSize;
	unsigned short m_uHash;
};

struct BfmeStringPool3AF0
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	void bfmeSetVKI(const char *s);
	StringDataC *m_pData;
};

class EAStringC
{
public:
	EAStringC(unsigned int nSize);

	~EAStringC()
	{
		StringDataC *data = m_pData;
		if (--data->m_uRefCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	StringDataC *m_pData;
};

extern "C" BfmeStrVKI *__cdecl rva0089EB30Prepend(BfmeStrVKI *out, const char *prefix, BfmeStrVKI *self)
{
	StringDataC *selfData = self->m_pData;
	unsigned int selfLen = selfData->m_uSize;

	if (selfLen == 0)
	{
		out->bfmeSetVKI(prefix);
		return out;
	}

	unsigned int prefixLen;
	{
		const char *p = prefix;
		while (*p != 0)
			++p;
		prefixLen = (unsigned int)(p - prefix);
	}

	if (prefixLen == 0)
	{
		out->m_pData = selfData;
		++selfData->m_uRefCount;
		return out;
	}

	EAStringC result(prefixLen + selfLen);
	char *dst = (char *)result.m_pData + sizeof(StringDataC);
	memcpy(dst, prefix, prefixLen);
	memcpy(dst + prefixLen, (char *)selfData + sizeof(StringDataC), selfLen);
	dst[prefixLen + selfLen] = 0;
	result.m_pData->m_uSize = (unsigned short)(prefixLen + selfLen);
	result.m_pData->m_uHash = 0;

	out->m_pData = result.m_pData;
	++result.m_pData->m_uRefCount;

	return out;
}
