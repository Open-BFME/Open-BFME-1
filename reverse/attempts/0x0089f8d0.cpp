// ?charAt@BfmeUtf8Cursor0089F8D0@@QBEHH@Z
// partial score=0.85 date=2026-09-05
// cl: /O2 /DNDEBUG /MD

class BfmeUtf8Cursor0089F8D0
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
	int charAt(int index) const;
};

int BfmeUtf8Cursor0089F8D0::charAt(int index) const
{
	int value;
	if (index < 0)
		return -1;
	volatile const unsigned char *p = reinterpret_cast<const unsigned char *>(m_data) + 8;
	int count = 0;
	if (index > 0)
	{
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
				value = c & 0x1f;
				value <<= 6;
				value |= p[1] & 0x3f;
				p += 2;
			}
			else if ((c & 0xf0) == 0xe0)
			{
				value = ((c & 0x0f) << 6) | (p[1] & 0x3f);
				value = (p[2] & 0x3f) | (value << 6);
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
				goto ret_neg1;
			++count;
			if (count >= index)
				break;
		}
	}
	if (p != 0)
		goto decode_final;
ret_neg1:
	return -1;
decode_final:
	unsigned char c = *p;
	if (c <= 0x7f)
		return c;
	if ((c & 0xe0) == 0xc0)
	{
		value = c & 0x1f;
		value <<= 6;
		value |= p[1] & 0x3f;
		return value;
	}
	if ((c & 0xf0) == 0xe0)
	{
		value = ((c & 0x0f) << 6) | (p[1] & 0x3f);
		value = (p[2] & 0x3f) | (value << 6);
		return value;
	}
	return ((((c & 7) << 6 | (p[1] & 0x3f)) << 6 | (p[2] & 0x3f)) << 6) | (p[3] & 0x3f);
}
