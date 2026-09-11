// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// MapMetaData::getFileName, retail 0x00451350, 211 bytes.
//
// The matched Q4Sort004566F0 comparator calls this method for both map
// operands.  The +0x50 member offset agrees with the matched MapMetaData
// lifecycle family.  BFME returns only the final backslash-delimited leaf,
// translated from the stored AsciiString into a UnicodeString.

typedef unsigned short WideChar;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

	unsigned int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const char *reverseFind(char needle) const
	{
		const char *start = str();
		const char *cursor = start + getLength();
		while (cursor != start)
		{
			--cursor;
			if (*cursor == needle)
				return cursor;
		}
		return 0;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}

	void translate(const AsciiString &text);
};

class MapMetaData
{
public:
	UnicodeString getFileName() const;

private:
	unsigned char m_beforeFileName[0x50];
	AsciiString m_fileName;
};

UnicodeString MapMetaData::getFileName() const
{
	UnicodeString result;
	const char *slash = m_fileName.reverseFind('\\');
	if (slash)
	{
		AsciiString leaf(slash + 1);
		result.translate(leaf);
	}
	else
	{
		result.translate(m_fileName);
	}
	return result;
}
