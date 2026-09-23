// ?slice0089FBC0@Rva8CD130String@@QBE?AV1@HH@Z
// partial score=0.98 date=2026-09-23
// cl: /O2 /DNDEBUG /MD

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_text[1];
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva8CD130String;

class EAStringC
{
public:
	Rva8CD130String Mid(int start) const;
	Rva8CD130String Mid(int start, int count) const;
};

class Rva8CD130String
{
public:
	__forceinline Rva8CD130String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	Rva8CD130String slice0089FBC0(int start, int count) const;

	BfmeStringData3AF0 *m_data;
};

__forceinline Rva8CD130String rva0089FBC0Empty()
{
	Rva8CD130String result;
	return result;
}

Rva8CD130String Rva8CD130String::slice0089FBC0(int start, int count) const
{
	volatile int initial = 0;
	int effectiveStart = start;
	int adjustedCount = count;
	if (start < 0)
	{
		adjustedCount -= start;
		effectiveStart = 0;
	}
	if (adjustedCount <= 0)
		return Rva8CD130String();

	int index = 0;
	const unsigned char *buffer =
		reinterpret_cast<const unsigned char *>(m_data);
	_ReadWriteBarrier();
	buffer += 8;
	volatile const unsigned char *p =
		buffer;
	while (index < effectiveStart)
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
			return Rva8CD130String();
		++index;
	}

	if (p == 0)
		return Rva8CD130String();

	index = 0;
	volatile const unsigned char *q = p;
	while (index < adjustedCount)
	{
		unsigned char c = *q;
		int value;
		if (c <= 0x7f)
		{
			value = c;
			++q;
		}
		else if ((c & 0xe0) == 0xc0)
		{
			value = c & 0x1f;
			value <<= 6;
			value |= q[1] & 0x3f;
			q += 2;
		}
		else if ((c & 0xf0) == 0xe0)
		{
			value = c & 0x0f;
			value <<= 6;
			value |= q[1] & 0x3f;
			value <<= 6;
			value |= q[2] & 0x3f;
			q += 3;
		}
		else
		{
			value = c & 7;
			value <<= 6;
			value |= q[1] & 0x3f;
			value <<= 6;
			value |= q[2] & 0x3f;
			value <<= 6;
			value |= q[3] & 0x3f;
			q += 4;
		}
		if (value == 0)
			goto singleResult;
		++index;
	}

	if (!q)
		goto singleResult;
	{
		int startBytes = (int)(p - buffer);
		return reinterpret_cast<const EAStringC *>(this)->Mid(
			startBytes, (int)(q - p));
	}

singleResult:
	{
		int startBytes = (int)(p - buffer);
		return reinterpret_cast<const EAStringC *>(this)->Mid(startBytes);
	}
}
