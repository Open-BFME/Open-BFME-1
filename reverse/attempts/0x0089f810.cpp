// ?d_0089f810@@YAXXZ
// partial score=0.9 date=2026-09-03
// cl: /O2 /DNDEBUG /MD

class BfmeUtf8Cursor0089F810
{
	struct StringData
	{
		unsigned short m_refCount;
		unsigned short m_size;
		unsigned short m_maxSize;
		unsigned short m_hash;
	};

	StringData *m_data;

public:
	const unsigned char *after(int index) const;
};

const unsigned char *BfmeUtf8Cursor0089F810::after(int index) const
{
	int value;
	const unsigned char *p = reinterpret_cast<const unsigned char *>(m_data) + 8;
	int count = 0;
	if (index <= 0)
		return 0;
	for (;;)
	{
		unsigned char c = *p;
		if (c <= 0x7f)
		{
			value = c;
			++p;
		}
		else if ((c & 0xe0) == 0xc0)
		{
			value = (c & 0x1f) << 6;
			value |= p[1] & 0x3f;
			p += 2;
		}
		else if ((c & 0xf0) == 0xe0)
		{
			value = c & 0x0f;
			value = (p[1] & 0x3f) | (value << 6);
			value = (p[2] & 0x3f) | (value << 6);
			p += 3;
		}
		else
		{
			value = c & 7;
			value = (p[1] & 0x3f) | (value << 6);
			value = (p[2] & 0x3f) | (value << 6);
			value = (p[3] & 0x3f) | (value << 6);
			p += 4;
		}
		if (value == 0)
			return 0;
		++count;
		if (count >= index)
			return p;
	}
}
