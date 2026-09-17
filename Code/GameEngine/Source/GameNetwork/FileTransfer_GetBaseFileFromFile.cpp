// cl: /GX

class AsciiString;
AsciiString GetBaseFileFromFile(AsciiString fname);

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend AsciiString GetBaseFileFromFile(AsciiString fname);
	friend AsciiString GetExtensionFromFile(AsciiString fname);

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *str);
	~StringBase();

public:
	T *getBufferForRead(int length);


private:
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
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	const char *str() const
	{
		return m_data ? &m_data->data[0] : (const char *)0x0107388B;
	}
	const char *reverseFind(char match) const
	{
		const char *first = str();
		const char *p = first + (m_data ? m_data->length : 0);
		while (p != first)
		{
			--p;
			if (*p == match)
				return p;
		}
		return 0;
	}

	static const AsciiString TheEmptyString;
	friend AsciiString GetBaseFileFromFile(AsciiString fname);
	friend AsciiString GetExtensionFromFile(AsciiString fname);
};

AsciiString GetBaseFileFromFile(AsciiString fname)
{
	const char *separator = fname.reverseFind('.');
	if (separator)
	{
		int prefixLength = separator - fname.str();
		AsciiString base;
		char *buffer = base.getBufferForRead(prefixLength);
		memcpy(buffer, fname.str(), prefixLength);
		buffer[prefixLength] = 0;
		return buffer;
	}
	return AsciiString::TheEmptyString;
}

// ?GetExtensionFromFile@@YA?AVAsciiString@@V1@@Z
AsciiString GetExtensionFromFile(AsciiString fname)
{
	StringBase<char>::Header *data = fname.m_data;
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
		if (ch == '.')
			return p + 1;
	}
	return fname;
}
