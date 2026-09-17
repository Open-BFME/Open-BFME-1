// ?d_0089e2b0@@YAXXZ
// partial score=0.72 date=2026-09-17
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
	EAStringC(unsigned int size);

	__forceinline ~EAStringC()
	{
		StringDataC *data = m_pData;
		if (--data->m_uRefCount == 0)
			g_bfmeAllocVKJ->free(data);
	}

	int Replace(const char *find, const char *replacement);
};

int EAStringC::Replace(const char *find, const char *replacement)
{
	int findLength = strlen(find);
	if (findLength == 0)
		return 0;
	EAStringC *self = this;

	int replacementLength = strlen(replacement);

	const char *source = self->GetInternalBuffer();
	const char *match = strstr(source, find);
	int count = 0;
	while (match != 0)
	{
		++count;
		match = strstr(match + findLength, find);
	}
	if (count == 0)
		return 0;

	int newLength = self->m_pData->m_uSize
		+ (replacementLength - findLength) * count;
	EAStringC result(newLength);
	char *destination = result.GetInternalBuffer();
	source = self->GetInternalBuffer();

	for (int remaining = count; remaining != 0; --remaining)
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
		- static_cast<int>(destination - result.GetInternalBuffer());
	if (tailLength != 0)
	{
		memcpy(destination, source, tailLength);
		destination += tailLength;
	}
	*destination = 0;
	result.m_pData->m_uSize = static_cast<unsigned short>(newLength);
	result.m_pData->m_uHash = 0;

	++result.m_pData->m_uRefCount;
	StringDataC *old = self->m_pData;
	if (--old->m_uRefCount == 0)
		g_bfmeAllocVKJ->free(old);
	self->m_pData = result.m_pData;
	return count;
}
