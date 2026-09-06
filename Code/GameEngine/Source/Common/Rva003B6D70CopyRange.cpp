// cl: /DNDEBUG /MD /EHsc
// Address-derived 32-byte record copy range at retail 0x003B6D70.

class UnicodeString
{
public:
	void set(const UnicodeString &other);

private:
	void *m_data;
};

struct Rva003AC170Element
{
	char m_bytes[12];
};

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	vector &operator=(const vector &other);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

struct Rva003B6D70Element
{
	int m_prefix;
	UnicodeString m_name;
	int m_value08;
	_STL::vector<Rva003AC170Element> m_items;
	int m_value18;
	unsigned char m_flag1c;
	unsigned char m_padding1d[3];
};

extern "C" Rva003B6D70Element *__cdecl Rva003B6D70CopyRange(
	const Rva003B6D70Element *first,
	const Rva003B6D70Element *last,
	Rva003B6D70Element *result)
{
	int count = (int)(last - first);
	if (count > 0)
	{
		Rva003B6D70Element *source = const_cast<Rva003B6D70Element *>(first);
		while (count > 0)
		{
			result->m_name.set(source->m_name);
			result->m_value08 = source->m_value08;
			result->m_items = source->m_items;
			result->m_value18 = source->m_value18;
			result->m_flag1c = source->m_flag1c;
			++source;
			++result;
			--count;
		}
	}
	return result;
}
