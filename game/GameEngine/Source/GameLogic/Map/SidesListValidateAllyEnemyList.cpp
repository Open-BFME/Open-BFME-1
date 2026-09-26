// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

template <class T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase(const StringBase &source);
	StringBase &operator=(const StringBase &source);
	void clear(void);
	void concat(const StringBase &source);
	void concat(const T *text);
	void concat(const T *text, int length);
	bool isEmpty(void) const;
	bool nextToken(StringBase *out, const T *delimiters);
	void set(const StringBase &source);

private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase(void);
	~StringBase(void);
	void releaseBuffer(void);
	Header *m_data;
};

class AsciiString
{
public:
	AsciiString(void)
	{
		m_data = 0;
	}

	AsciiString(const AsciiString &source)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&source);
	}

	~AsciiString(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	AsciiString &operator=(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
		return *this;
	}

	void clear(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void concat(const AsciiString &source)
	{
		const StringBase<char> *string = (const StringBase<char> *)&source;
		((StringBase<char> *)this)->concat(
			string->m_data ? string->m_data->data : "",
			string->m_data ? string->m_data->length : 0);
	}

	bool isEmpty(void) const
	{
		return m_data == 0 || m_data->length == 0;
	}

	bool nextToken(AsciiString *out, const char *delimiters = 0)
	{
		return ((StringBase<char> *)this)->nextToken(
			(StringBase<char> *)out, delimiters);
	}

	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherData = other.m_data ? other.m_data->data : "";
		int thisLength = m_data ? m_data->length : 0;
		const char *thisData = m_data ? m_data->data : "";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	friend bool operator==(const AsciiString &left, const AsciiString &right)
	{
		return left.compare(right) == 0;
	}

private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

typedef bool Bool;

class SidesInfo;

class SidesList
{
public:
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);

protected:
	Bool validateAllyEnemyList(const AsciiString &tname, AsciiString &allies);
};

// Retail validateSides calls this body through thunk 0x00030797. The call
// sequence and the SidesList array offsets identify the method at 0x001969D0.
Bool SidesList::validateAllyEnemyList(const AsciiString &tname, AsciiString &allies)
{
	Bool modified = false;
	AsciiString str, newstr, token;

	str = allies;
	newstr.clear();
	while (str.nextToken(&token))
	{
		if (token == tname)
		{
			modified = true;
			continue;
		}

		SidesInfo *side = findSideInfo(token);
		if (!side)
		{
			modified = true;
			continue;
		}

		if (!newstr.isEmpty())
			newstr.concat(" ", 1);
		newstr.concat(token);
	}

	allies = newstr;
	return modified;
}
