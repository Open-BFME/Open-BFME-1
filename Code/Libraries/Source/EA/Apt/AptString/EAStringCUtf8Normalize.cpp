// cl: /O2 /DNDEBUG /MD

extern "C" int __cdecl tolower(int character);

class BfmeUtf8String008A00C0;

class EAStringC
{
	public:
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	private:
	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

	friend class BfmeUtf8String008A00C0;
};

class BfmeUtf8String008A00C0
{
	class StringData
	{
	public:
		unsigned short m_refCount;
		unsigned short m_size;
		unsigned short m_maxSize;
		unsigned short m_hash;
		char m_text[1];
	};

	StringData *m_data;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_data) + 8;
	}

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, int pushZero, unsigned int internalSize);

public:
	BfmeUtf8String008A00C0 &map();
};

BfmeUtf8String008A00C0 &BfmeUtf8String008A00C0::map()
{
	BfmeUtf8String008A00C0 *self = this;
	unsigned int size = self->m_data->m_size;
	(reinterpret_cast<EAStringC *>(self))->ChangeBuffer(
		size, 0, size, EAStringC::CB_PUSH_ZERO, size);

	unsigned char *p = reinterpret_cast<unsigned char *>(self->GetInternalBuffer());
	for (;;)
	{
		unsigned char c = *p;
		unsigned char *start = p;
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
			break;
		value = tolower(value);
		if (value < 0x80)
		{
			start[0] = (unsigned char)value;
			continue;
		}
		if (value < 0x800)
		{
			start[0] = (unsigned char)((value >> 6) | 0xc0);
				start[1] = (unsigned char)((value & 0x3f) | 0x80);
			continue;
		}
		if (value < 0x10000)
		{
			start[0] = (unsigned char)((value >> 12) | 0xe0);
			start[1] = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
			start[2] = (unsigned char)((value & 0x3f) | 0x80);
			continue;
		}
		start[0] = (unsigned char)((value >> 18) | 0xf0);
		start[1] = (unsigned char)(((value >> 12) & 0x3f) | 0x80);
		start[2] = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
		start[3] = (unsigned char)((value & 0x3f) | 0x80);
	}
	return *this;
}
