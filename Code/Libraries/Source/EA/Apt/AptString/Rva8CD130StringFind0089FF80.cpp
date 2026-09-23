// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef unsigned short UnsignedShort;
typedef int Int;

struct Rva8CD130StringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	UnsignedShort m_flags;
	char m_text[1];
};

extern char *__cdecl ji_009f709c(const char *haystack, const char *needle);

class Rva8CD130String
{
public:
	Int find0089FF80(const char *text, Int start);

	Rva8CD130StringData *m_data;
};

Int Rva8CD130String::find0089FF80(const char *text, Int start)
{
	Rva8CD130StringData *data = m_data;
	unsigned char *buffer = (unsigned char *)data + 8;
	volatile const unsigned char *scan = buffer;
	Int characterIndex = 0;

	while (characterIndex < start)
	{
		unsigned char c = *scan;
		Int value;
		if (c <= 0x7f)
		{
			value = c;
			++scan;
		}
		else if ((c & 0xe0) == 0xc0)
		{
			value = c & 0x1f;
			value <<= 6;
			value |= scan[1] & 0x3f;
			scan += 2;
		}
		else if ((c & 0xf0) == 0xe0)
		{
			value = c & 0x0f;
			value <<= 6;
			value |= scan[1] & 0x3f;
			value <<= 6;
			value |= scan[2] & 0x3f;
			scan += 3;
		}
		else
		{
			value = c & 7;
			value <<= 6;
			value |= scan[1] & 0x3f;
			value <<= 6;
			value |= scan[2] & 0x3f;
			value <<= 6;
			value |= scan[3] & 0x3f;
			scan += 4;
		}

		if (value == 0)
			return -1;
		++characterIndex;
	}

	if (scan == 0)
		return -1;

	Int startByte = scan - buffer;
	if (startByte >= data->m_length)
		return -1;

	Int searchOffset = startByte;
	if (searchOffset < 0)
		searchOffset = 0;
	char *found = ji_009f709c((char *)m_data + searchOffset + 8, text);
	if (found == 0)
		return -1;

	Int foundByte = (Int)found - (Int)m_data - 8;
	if (foundByte < 0)
		return -1;
	Int result = start;
	Int offset = startByte;
	volatile const unsigned char *cursor = buffer;
	if (offset < foundByte)
	{
		do
		{
			unsigned char c = *cursor;
			Int width;
			if (c <= 0x7f)
				width = 1;
			else if ((c & 0xe0) == 0xc0)
				width = 2;
			else if ((c & 0xf0) == 0xe0)
				width = 3;
			else
				width = 4;
			cursor += width;
			offset += width;
			++result;
		} while (offset < foundByte);
	}
	return result;
}
