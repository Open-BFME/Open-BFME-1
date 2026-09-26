// _Rva003B33C0CopyRange
// partial score=0.78 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Address-derived 32-byte record copy range at retail 0x003B33C0.

class UnicodeString
{
public:
	void set(const UnicodeString &other);

private:
	void *m_data;
};

struct Rva003B33C0Element
{
	int m_prefix;
	UnicodeString m_name;
	int m_value08;
	int m_value0c;
	unsigned char m_flag10;
	unsigned char m_padding11[3];
	UnicodeString m_name14;
	UnicodeString m_name18;
	int m_value1c;
};

extern "C" Rva003B33C0Element *__cdecl Rva003B33C0CopyRange(
	const Rva003B33C0Element *first,
	const Rva003B33C0Element *last,
	Rva003B33C0Element *result)
{
	int count = (int)(last - first);
	if (count > 0)
	{
		Rva003B33C0Element *end = result + count;
		while (count > 0)
		{
			result->m_name.set(first->m_name);
			result->m_value08 = first->m_value08;
			result->m_value0c = first->m_value0c;
			result->m_flag10 = first->m_flag10;
			result->m_name14.set(first->m_name14);
			result->m_name18.set(first->m_name18);
			result->m_value1c = first->m_value1c;
			++first;
			++result;
			--count;
		}
		return end;
	}
	return result;
}
