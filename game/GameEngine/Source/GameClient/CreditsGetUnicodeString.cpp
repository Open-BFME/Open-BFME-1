// cl: /O2 /EHsc
// CreditsManager::getUnicodeString — ZH twin, BFME StringBase ABI.

template <typename T>
struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	const T *find(T c) const
	{
		const T *start = m_data ? m_data->text : (const T *)"";
		const T *end = start + (m_data ? m_data->length : 0);
		for (const T *p = start; p != end; ++p)
		{
			if (*p == c)
				return p;
		}
		return 0;
	}

public:
	void set(const StringBase &other);
	int compare(const T *s) const;

private:
	StringHeader<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	int compare(const char *s) const { return StringBase<char>::compare(s); }
	const char *find(char c) const { return StringBase<char>::find(c); }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
		return *this;
	}
	void translate(const AsciiString &src);
	static UnicodeString TheEmptyString;
};

class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class CreditsManager
{
	UnicodeString getUnicodeString(AsciiString str);
};

UnicodeString CreditsManager::getUnicodeString(AsciiString str)
{
	UnicodeString uStr;
	if (str.compare("<BLANK>") == 0)
		return UnicodeString::TheEmptyString;

	if (str.find(':'))
		uStr = TheGameText->fetch(str);
	else
		uStr.translate(str);

	return uStr;
}
