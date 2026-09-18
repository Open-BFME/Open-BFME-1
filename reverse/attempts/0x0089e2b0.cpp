// ?d_0089e2b0@@YAXXZ
// partial score=0.78 date=2026-09-17
// ?Replace@EAStringC@@QAEHPBD0@Z
// Recovered from the EAStringC family and the retail Replace body at 0x0089E2B0.
// cl: /O2 /DNDEBUG /MD /EHsc

extern "C" char *__cdecl strstr(const char *, const char *);
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
extern "C" unsigned int __cdecl strlen(const char *);

struct BfmeAllocVKJ
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct EAStringData
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

template <typename T> class StringBase
{
	protected:
	EAStringData *m_data;
	StringBase() {}

	private:
	StringBase(const StringBase &other) : m_data(other.m_data)
	{
		++m_data->m_refCount;
	}

	StringBase(EAStringData *data) : m_data(data)
	{
		++m_data->m_refCount;
	}

	protected:
	void releaseBuffer()
	{
		EAStringData *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	~StringBase() { releaseBuffer(); }

	friend class EAStringC;
};

class EAStringC : private StringBase<char>
{
	typedef EAStringData StringDataC;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_data) + sizeof(StringDataC);
	}

public:
	EAStringC(unsigned int size);
	int Replace(const char *find, const char *replacement);
};

int EAStringC::Replace(const char *find, const char *replacement)
{
	int findLength = strlen(find);
	if (findLength == 0)
		return 0;

	int replacementLength = strlen(replacement);

	const char *source = GetInternalBuffer();
	int count = 0;
	const char *match = strstr(source, find);
	while (match != 0)
	{
		++count;
		match = strstr(match + findLength, find);
	}
	if (count == 0)
		return 0;

	register int newLength = m_data->m_size
		+ (replacementLength - findLength) * count;
	EAStringC result(newLength);
	StringDataC *oldData = m_data;
	char *destination = result.GetInternalBuffer();
	char *destinationStart = destination;
	source = GetInternalBuffer();

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

	int tailLength = newLength
		- static_cast<int>(destination - destinationStart);
	if (tailLength != 0)
	{
		memcpy(destination, source, tailLength);
		destination += tailLength;
	}
	*destination = 0;
	result.m_data->m_size = static_cast<unsigned short>(newLength);
	result.m_data->m_hash = 0;

	++result.m_data->m_refCount;
	if (--oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);
	m_data = result.m_data;
	return count;
}
