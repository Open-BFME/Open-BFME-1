// ?d_0089e2b0@@YAXXZ
// partial score=0.40 date=2026-09-21
// ?Replace@EAStringC@@QAEHPBD0@Z
// Supersedes an earlier "score=0.78" self-report on this RVA that
// re-verification with probe.py and shape_search showed was inflated
// (real score ~0.27): see reverse/re_attempts.log for the 0x0089E2B0
// history.
// Recovered from the EAStringC family (proven class shape from
// EAStringCTrimRight.cpp / EAStringCReserveCtor.cpp) and the retail
// Replace body at 0x0089E2B0.  Minimizes named locals (no separate
// destinationStart/oldData) to reduce register pressure toward retail's
// edi=this/ebp=findLength register schedule.  Retail still keeps 'find'
// in ebx (this compiles it into esi) and its frame is one dword (4B)
// larger -- retail caches one more persistent value across the whole
// function than this shape does; shape_family_levers/eh_levers found no
// further mechanical lever from here as of this attempt.
// cl: /O2 /DNDEBUG /MD /EHsc

extern "C" char *__cdecl strstr(const char *, const char *);
extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int bytes);
extern "C" unsigned int __cdecl strlen(const char *);

#pragma intrinsic(memcpy)

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

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
	EAStringC(unsigned int nSize);

	EAStringC(const EAStringC &other)
		: m_pData(other.m_pData)
	{
		++m_pData->m_uRefCount;
	}

	__forceinline ~EAStringC()
	{
		StringDataC *data = m_pData;
		if (--data->m_uRefCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	int Replace(const char *find, const char *replacement);
};

int EAStringC::Replace(const char *find, const char *replacement)
{
	int findLength = strlen(find);
	if (findLength == 0)
		return 0;

	int replacementLength = strlen(replacement);

	int count = 0;
	const char *match = strstr(GetInternalBuffer(), find);
	if (match != 0)
	{
		do
		{
			++count;
			match = strstr(match + findLength, find);
		} while (match != 0);
	}
	if (count == 0)
		return 0;

	int newLength = m_pData->m_uSize + (replacementLength - findLength) * count;
	EAStringC result(newLength);
	char *destination = result.GetInternalBuffer();
	char *destinationStart = destination;
	const char *source = GetInternalBuffer();

	for (int remaining = count; remaining > 0; --remaining)
	{
		match = strstr(source, find);
		int prefixLength = static_cast<int>(match - source);
		if (prefixLength != 0)
		{
			memcpy(destination, source, prefixLength);
			destination += prefixLength;
		}
		source = match + findLength;
		memcpy(destination, replacement, replacementLength);
		destination += replacementLength;
	}

	int tailLength = newLength - static_cast<int>(destination - destinationStart);
	if (tailLength != 0)
	{
		memcpy(destination, source, tailLength);
		destination += tailLength;
	}
	*destination = 0;
	result.m_pData->m_uSize = static_cast<unsigned short>(newLength);
	result.m_pData->m_uHash = 0;

	++result.m_pData->m_uRefCount;
	if (--m_pData->m_uRefCount == 0)
		g_bfmeStringPool1284->free(m_pData);
	m_pData = result.m_pData;
	return count;
}
