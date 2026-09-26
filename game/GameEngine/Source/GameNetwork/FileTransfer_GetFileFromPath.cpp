// cl: /GX
//
// Returns the part of a path after the final directory separator. This is the
// backslash sibling of GetExtensionFromFile's identical reverse-search body.

class AsciiString;
AsciiString GetFileFromPath(AsciiString path);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend AsciiString GetFileFromPath(AsciiString path);

	StringBase(const StringBase<T> &other);
	StringBase(const T *str);
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	friend AsciiString GetFileFromPath(AsciiString path);
};

AsciiString GetFileFromPath(AsciiString path)
{
	StringBase<char>::Header *data = path.m_data;
	const char *start;
	unsigned int len;
	if (data)
	{
		start = &data->data[0];
		len = data->length;
	}
	else
	{
		start = (const char *)0x0107388B;
		len = 0;
	}

	const char *p = start + len;
	while (p != start)
	{
		char ch = p[-1];
		--p;
		if (ch == '\\')
			return p + 1;
	}
	return path;
}
