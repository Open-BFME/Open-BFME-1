// Address-derived string-vector lookup at retail 0x003C5360.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct Rva003C5360StringData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	char m_text[1];
};

struct Rva003C5360String
{
	Rva003C5360StringData *m_data;

	int compare(const Rva003C5360String &that) const
	{
		int thatLength = that.m_data ? that.m_data->m_length : 0;
		const char *thatText = that.m_data ? that.m_data->m_text :
			g_bfmeEmptyAscii;
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : g_bfmeEmptyAscii;
		int length = thisLength < thatLength ? thisLength : thatLength;
		int difference = memcmp(thisText, thatText, length);
		if (difference != 0)
			return difference;
		return thisLength - thatLength;
	}
};

struct Rva003C5360Vector
{
	Rva003C5360String **m_begin;
	Rva003C5360String **m_end;
	Rva003C5360String **m_capacity;
};

Rva003C5360String *__stdcall Rva003C5360Find(
	Rva003C5360Vector *vector, Rva003C5360String *key)
{
	int index = 0;
	Rva003C5360String **begin = vector->m_begin;
	unsigned int count = (unsigned int)(vector->m_end - begin);
	if (count > 0)
	{
		Rva003C5360String query = *key;
		Rva003C5360String **it = begin;
		while (index < count)
		{
			if (query.compare(*(*it)) == 0)
				return begin[index];
			++index;
			++it;
		}
	}
	return 0;
}
