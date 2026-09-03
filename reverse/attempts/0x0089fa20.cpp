// ?d_0089fa20@@YAXXZ
// partial score=0.95 date=2026-09-03
// ?bfmeUtf8Length@EAStringC@@QBEHXZ
// cl: /O2 /DNDEBUG /MD

class EAStringC
{
	struct StringDataC
	{
		unsigned short m_refCount;
		unsigned short m_size;
		unsigned short m_maxSize;
		unsigned short m_hash;
	};

	StringDataC *m_data;

public:
	int bfmeUtf8Length() const;
};

int EAStringC::bfmeUtf8Length() const
{
	int count = 0;
	const unsigned char *p = reinterpret_cast<const unsigned char *>(m_data) + 8;
	for (;;)
	{
		unsigned char c = *p;
		unsigned int value;
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
			value = ((c & 0x0f) << 6) | (p[1] & 0x3f);
			value = ((value << 6) & 0xffffffc0) | (p[2] & 0x3f);
			p += 3;
		}
		else
		{
			value = ((c & 7) << 6) | (p[1] & 0x3f);
			value = ((value << 6) & 0xffffffc0) | (p[2] & 0x3f);
			value = ((value << 6) & 0xffffffc0) | (p[3] & 0x3f);
			p += 4;
		}
		if (value == 0)
			break;
		++count;
	}
	return count;
}
