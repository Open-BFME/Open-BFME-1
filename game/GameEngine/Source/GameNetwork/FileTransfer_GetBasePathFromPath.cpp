// cl: /GX

class AsciiString;
AsciiString GetBasePathFromPath(AsciiString path);

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend AsciiString GetBasePathFromPath(AsciiString path);

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
	friend AsciiString GetBasePathFromPath(AsciiString path);
};

AsciiString GetBasePathFromPath(AsciiString path)
{
	const char *separator = path.reverseFind('\\');
	if (separator)
	{
		int prefixLength = separator - path.str();
		AsciiString base;
		char *buffer = base.getBufferForRead(prefixLength);
		memcpy(buffer, path.str(), prefixLength);
		buffer[prefixLength] = 0;
		return buffer;
	}
	return AsciiString::TheEmptyString;
}
