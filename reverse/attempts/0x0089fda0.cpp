// ?rva0089FDA0@EAStringC@@QAEAAV1@PBDH@Z
// partial score=0.39 date=2026-09-23
// ?rva0089FDA0@EAStringC@@QAEAAV1@PBDH@Z
// cl: /O2 /DNDEBUG /MD

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct EAStringData
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

struct BfmeStringPool3AF0
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern EAStringData g_bfmeDefaultString1284;

class EAStringC
{
	EAStringData *m_data;

public:
	EAStringC &rva0089FDA0(const char *source, int limit);
};

EAStringC &EAStringC::rva0089FDA0(const char *source, int limit)
{
	const char *scan = source;
	int characterCount = 0;
	int value;

	if (limit > 0)
	{
		while (characterCount < limit)
		{
			unsigned char c = (unsigned char)*scan;
			if (c <= 0x7f)
			{
				value = c;
				++scan;
			}
			else if ((c & 0xe0) == 0xc0)
			{
				value = c & 0x1f;
				value <<= 6;
				value |= scan[1] & 0x3f;
				scan += 2;
			}
			else if ((c & 0xf0) == 0xe0)
			{
				value = c & 0x0f;
				value <<= 6;
				value |= scan[1] & 0x3f;
				value <<= 6;
				value |= scan[2] & 0x3f;
				scan += 3;
			}
			else
			{
				value = c & 7;
				value <<= 6;
				value |= scan[1] & 0x3f;
				value <<= 6;
				value |= scan[2] & 0x3f;
				value <<= 6;
				value |= scan[3] & 0x3f;
				scan += 4;
			}

			if (value == 0)
				break;
			++characterCount;
		}
	}

	int sourceSize = scan - source;
	int count = 0;
	const char *text = source;
	if (sourceSize != 0)
	{
		do
		{
			if (*text++ == 0)
				break;
			++count;
		} while (count < sourceSize);
	}
	if (count == 0)
		return *this;

	EAStringData *oldData = m_data;
	unsigned int oldSize = oldData->m_size;
	unsigned int newSize = oldSize + count;
	if (oldData->m_refCount == 1 && newSize <= oldData->m_maxSize)
	{
		oldData->m_size = (unsigned short)newSize;
		oldData->m_hash = 0;
		((char *)oldData)[newSize + 8] = 0;
	}
	else
	{
		unsigned int allocationSize = (newSize + (newSize >> 3) + 0xc) & ~3u;
		EAStringData *newData = (EAStringData *)g_bfmeStringPool1284->allocate(allocationSize);
		m_data = newData;
		newData->m_refCount = 1;
		newData->m_maxSize = (unsigned short)(allocationSize - 9);
		newData->m_size = (unsigned short)newSize;
		newData->m_hash = 0;
		((char *)newData)[newSize + 8] = 0;
		memcpy((char *)newData + 8, (char *)oldData + 8, oldSize);
		if (--oldData->m_refCount == 0)
			g_bfmeStringPool1284->free(oldData);
	}

	memcpy((char *)m_data + oldSize + 8, source, count);
	return *this;
}
