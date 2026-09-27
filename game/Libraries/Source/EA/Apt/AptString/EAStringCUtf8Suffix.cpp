// cl: /O2 /DNDEBUG /MD /EHsc
// UTF-8 codepoint suffix of EAStringC: advances `start` codepoints from the
// byte buffer and forwards the byte offset to the byte-based Mid overload in
// EAStringCMid.cpp. Sibling of the landed utf8Mid0089FBC0 (0x0089FBC0) and
// bfmeUtf8Length (0x0089FA20): same buffer load, same decode loop, same
// Mid(0x0089F1B0) return shape. Name keeps the address token; no caller,
// vtable slot, string literal or Zero Hour twin names the method.

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
	EAStringC utf8Suffix0089FAC0(int start) const;

private:
	EAStringData *m_data;
};

// Advances n codepoints; returns 0 when the terminator is decoded first.
static __forceinline const unsigned char *utf8Advance0089FAC0(const unsigned char *s, int n)
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

EAStringC EAStringC::utf8Suffix0089FAC0(int start) const
{
	int effectiveStart = start;
	if (effectiveStart < 0)
		effectiveStart = 0;

	// The non-null hint keeps the buffer load and header skip as retail schedules them.
	const unsigned char *buffer = reinterpret_cast<const unsigned char *>(m_data);
	__assume(buffer != 0);
	buffer += 8;
	const unsigned char *first = utf8Advance0089FAC0(buffer, effectiveStart);
	if (first == 0)
		return EAStringC();
	return Mid((int)(first - buffer));
}
