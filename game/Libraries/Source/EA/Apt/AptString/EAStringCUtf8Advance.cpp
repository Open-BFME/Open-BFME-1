// cl: /O2 /DNDEBUG /MD

const char *utf8Advance0089E750(const char *s, int n)
{
	int count = 0;
	volatile const unsigned char *p = reinterpret_cast<const unsigned char *>(s);
	if (n <= 0)
		return s;
	for (;;)
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
		if (++count >= n)
			return reinterpret_cast<const char *>(const_cast<const unsigned char *>(p));
	}
}
