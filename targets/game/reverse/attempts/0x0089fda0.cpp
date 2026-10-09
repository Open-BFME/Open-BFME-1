// ?rva0089FDA0@EAStringC@@QAEAAV1@PBDH@Z
// partial score=0.382 date=2026-10-09
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

// ?rva0089FDA0@EAStringC@@QAEAAV1@PBDH@Z present-unmatched
// Evidence: targets/game/reverse/identity_evidence/0x0089fda0-utf8-append.md
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

	unsigned int count = 0;
	const char *text = source;
	unsigned int sourceSize = scan - text;
	if (sourceSize != 0)
	{
		do
		{
			if (*text++ == 0)
				break;
			++count;
		} while (count < sourceSize);
	}
	if (count != 0)
	{
		EAStringData *oldData[1] = { m_data };
		EAStringData *data = oldData[0];
		unsigned int oldSize = data->m_size;
		unsigned int newSize = oldSize + count;
		if (data->m_refCount == 1 && newSize <= data->m_maxSize)
		{
			m_data->m_size = (unsigned short)newSize;
			m_data->m_hash = 0;
			((char *)m_data)[newSize + 8] = 0;
		}
		else
		{
			const char *volatile oldText = (char *)data + 8;
			if (newSize != 0)
			{
				unsigned int allocationSize = (newSize + (newSize >> 3) + 0xc) & ~3u;
				m_data = (EAStringData *)g_bfmeStringPool1284->allocate(allocationSize);
				m_data->m_refCount = 1;
				m_data->m_maxSize = (unsigned short)(allocationSize - 9);
				m_data->m_size = (unsigned short)newSize;
				m_data->m_hash = 0;
				memcpy((char *)m_data + 8, oldText, oldSize);
				((char *)m_data)[newSize + 8] = 0;
			}
			else
			{
				m_data = &g_bfmeDefaultString1284;
				++g_bfmeDefaultString1284.m_refCount;
			}
			data = oldData[0];
			if (--data->m_refCount == 0)
				g_bfmeStringPool1284->free(data);
		}

		memcpy((char *)m_data + oldSize + 8, source, count);
	}
	return *this;
}
