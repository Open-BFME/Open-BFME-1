// Address-derived lookup body for the guarded lookup owner at 0x003C8A50.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

struct Rva003C8A50StringData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	char m_text[1];
};

class Rva003C8A50String
{
public:
	Rva003C8A50StringData *m_data;

	int compare(const Rva003C8A50String &that) const
	{
		int thatLength = that.m_data ? that.m_data->m_length : 0;
		const char *thatText = that.m_data ? that.m_data->m_text : g_bfmeEmptyAscii;
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : g_bfmeEmptyAscii;
		int length = thisLength < thatLength ? thisLength : thatLength;
		int difference = memcmp(thisText, thatText, length);
		if (difference != 0)
			return difference;
		return thisLength - thatLength;
	}
};

class Gen003C8A50Result
{
public:
	char m_pad00[4];
	Rva003C8A50String m_key;
};

struct Rva003C8A50Vector
{
	char m_pad00[0x30];
	Gen003C8A50Result **m_begin;
	Gen003C8A50Result **m_end;
};

class Gen003C8A50
{
public:
	Gen003C8A50Result *find(const char *key);

private:
	char m_pad00[4];
	Rva003C8A50Vector *m_storage;
};

Gen003C8A50Result *Gen003C8A50::find(const char *key)
{
	Rva003C8A50Vector *storage = m_storage;
	if (storage == 0)
		return (Gen003C8A50Result *)storage;

	unsigned int index = 0;
	Gen003C8A50Result **begin = storage->m_begin;
	unsigned int count = (unsigned int)(storage->m_end - begin);

	if (count > 0)
	{
		Rva003C8A50String query = *(const Rva003C8A50String *)key;
		Gen003C8A50Result **it = begin;
		while (index < count)
		{
			Gen003C8A50Result *candidate = *it;
			if (query.compare(candidate->m_key) == 0)
				return begin[index];

			++index;
			++it;
		}
	}

	return 0;
}
