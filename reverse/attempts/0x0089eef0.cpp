// ?Remove@EAStringC@@QAEHHH@Z
// partial score=0.95 date=2026-09-07
// cl: /O2 /DNDEBUG /MD /EHsc

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class EAStringC
{
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	BfmeStringData3AF0 *m_pData;

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(BfmeStringData3AF0);
	}

public:
	int Remove(int start, int count);
};

int EAStringC::Remove(int start, int count)
{
	int end = count + start;
	if (count <= 0)
	{
		BfmeStringData3AF0 *data = m_pData;
		if (--data->m_refCount == 0)
		{
			g_bfmeStringPool1284->free(data);
		}
		m_pData = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
		return 0;
	}
	if (end <= 0)
	{
		BfmeStringData3AF0 *data = m_pData;
		if (--data->m_refCount == 0)
		{
			g_bfmeStringPool1284->free(data);
		}
		m_pData = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
		return 0;
	}

	if (start < 0)
		start = 0;

	int size;
	BfmeStringData3AF0 *data = m_pData;
	size = data->m_size;
	if (end >= size)
		end = size;

	if (start == 0)
	{
		size -= end;
		ChangeBuffer(size, end, size, CB_PUSH_ZERO, size);
		return size;
	}

	if (end == size)
	{
		ChangeBuffer(start, 0, start, CB_PUSH_ZERO, start);
		return start;
	}

	int suffix = size - end;
	int newSize = start + suffix;
	ChangeBuffer(newSize, 0, start, CB_NO_PUSH_ZERO, newSize);
	memcpy(reinterpret_cast<char *>(m_pData) + sizeof(BfmeStringData3AF0) + start,
		reinterpret_cast<char *>(data) + sizeof(BfmeStringData3AF0) + end, suffix + 1);
	return count;
}
