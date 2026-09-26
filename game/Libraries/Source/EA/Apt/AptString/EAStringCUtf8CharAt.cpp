// cl: /O2 /DNDEBUG /MD

class BfmeUtf8Cursor0089F8D0
{
	// Opaque 8-byte string header; the UTF-8 bytes follow it.
	struct StringData;

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
			{
				p = 0;
				break;
			}
			++count;
			if (count >= index)
				break;
		}
	}
	if (p == 0)
		return -1;
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
	value = (((c & 7) << 12) | ((p[1] & 0x3f) << 6) | (p[2] & 0x3f)) << 6 | (p[3] & 0x3f);
	return value;
}
