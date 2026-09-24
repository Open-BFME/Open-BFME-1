// cl: /O2 /DNDEBUG /MD /EHsc
// UTF-8 codepoint substring of EAStringC: converts codepoint start/count to byte
// offsets and forwards to the byte-based Mid overloads in EAStringCMid.cpp.

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

struct EAStringData
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

extern EAStringData g_emptyStringData;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class EAStringC
{
public:
	EAStringC()
	{
		m_data = &g_emptyStringData;
		++g_emptyStringData.m_refCount;
	}

	~EAStringC()
	{
		EAStringData *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	EAStringC Mid(int start) const;
	EAStringC Mid(int start, int count) const;
	EAStringC utf8Mid0089FBC0(int start, int count) const;

private:
	EAStringData *m_data;
};

// Advances n codepoints; returns 0 when the terminator is decoded first.
static __forceinline const unsigned char *utf8Advance0089FBC0(const unsigned char *s, int n)
{
	volatile const unsigned char *p = s;
	for (int i = 0; i < n; ++i)
	{
		unsigned char c = *p;
		int value;
		if (c <= 0x7f)
		{
			value = c;
			++p;
		}
		else if ((c & 0xe0) == 0xc0)
		{
			value = c & 0x1f;
			value <<= 6;
			value |= p[1] & 0x3f;
			p += 2;
		}
		else if ((c & 0xf0) == 0xe0)
		{
			value = c & 0x0f;
			value <<= 6;
			value |= p[1] & 0x3f;
			value <<= 6;
			value |= p[2] & 0x3f;
			p += 3;
		}
		else
		{
			value = c & 7;
			value <<= 6;
			value |= p[1] & 0x3f;
			value <<= 6;
			value |= p[2] & 0x3f;
			value <<= 6;
			value |= p[3] & 0x3f;
			p += 4;
		}
		if (value == 0)
			return 0;
	}
	return const_cast<const unsigned char *>(p);
}

EAStringC EAStringC::utf8Mid0089FBC0(int start, int count) const
{
	int effectiveStart = start;
	int adjustedCount = count;
	if (start < 0)
	{
		adjustedCount -= start;
		effectiveStart = 0;
	}
	if (adjustedCount <= 0)
		return EAStringC();

	// The non-null hint keeps the buffer load and header skip as retail schedules them.
	const unsigned char *buffer = reinterpret_cast<const unsigned char *>(m_data);
	__assume(buffer != 0);
	buffer += 8;
	const unsigned char *first = utf8Advance0089FBC0(buffer, effectiveStart);
	if (first == 0)
		return EAStringC();
	const unsigned char *last = utf8Advance0089FBC0(first, adjustedCount);
	if (last == 0)
		return Mid((int)(first - buffer));
	return Mid((int)(first - buffer), (int)(last - first));
}
