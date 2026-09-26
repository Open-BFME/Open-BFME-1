// cl: /O2 /DNDEBUG /MD /EHsc

// Retail 0x0089EEF0 removes the character range [start, start + count) from an
// EAStringC and returns the new length. A non-positive count or end empties the
// string. The address-derived method name keeps the original identity open.

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
	unsigned short word_4;
	unsigned short word_6;
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

	BfmeStringData3AF0 *m_data;

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

public:
	int rva0089EEF0(int start, int count);
};

int EAStringC::rva0089EEF0(int start, int count)
{
	int end = count + start;
	if (count <= 0)
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
		m_data = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
		return 0;
	}
	if (end <= 0)
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
		m_data = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
		return 0;
	}

	if (start < 0)
		start = 0;

	BfmeStringData3AF0 *data = m_data;
	int size = data->m_size;
	if (end >= size)
		end = size;

	if (start == 0)
	{
		int newSize = size - end;
		ChangeBuffer(newSize, end, newSize, CB_PUSH_ZERO, newSize);
		return newSize;
	}

	if (end == size)
	{
		ChangeBuffer(start, 0, start, CB_PUSH_ZERO, start);
		return start;
	}

	count = start + (size - end);
	ChangeBuffer(count, 0, start, CB_NO_PUSH_ZERO, count);
	memcpy(reinterpret_cast<char *>(m_data) + sizeof(BfmeStringData3AF0) + start,
		reinterpret_cast<char *>(data) + sizeof(BfmeStringData3AF0) + end, size - end + 1);
	return count;
}
