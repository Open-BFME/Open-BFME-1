// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// BFME extends the ZH SkirmishPreferences constructor after load("Skirmish.ini"):
// it finds the UserNames preference, decodes it to Unicode, and splits its
// comma-delimited tokens into the list at this+0x14.  The constructor callers,
// the vtable 0x010806B0, and the destructor's list clear establish this layout.

#include <list>

typedef bool Bool;
typedef unsigned short WideChar;

class AsciiString;
class UnicodeString;

template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	StringBase(void) : m_data(0) {}

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	public:
	Bool nextToken(StringBase<T> *token, const T *separators);

	private:
	void set(const StringBase<T> &other);
	void trim(void);
	void releaseBuffer(void);

	void *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}

	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}

	~AsciiString();

private:
	char *m_text;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}

	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}

	~UnicodeString()
	{
		releaseBuffer();
	}

	UnicodeString &operator=(const UnicodeString &other)
	{
		StringBase<WideChar>::set(other);
		return *this;
	}

	void trim(void)
	{
		StringBase<WideChar>::trim();
	}

	Bool nextToken(UnicodeString *token, const WideChar *separators)
	{
		return StringBase<WideChar>::nextToken(
			(StringBase<WideChar> *)token, separators);
	}
};

UnicodeString QuotedPrintableToUnicodeString(AsciiString original);

// The constructor at 0x0009F630 is the existing STLport sized-list body;
// m_userNames(0) deliberately consumes that out-of-line specialization.
extern template class _STL::list<UnicodeString>;

struct PreferenceNode
{
	unsigned char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();

	PreferenceNode *end(void) const
	{
		return m_end;
	}

private:
	PreferenceNode *m_end;
	unsigned char m_unreconstructed[8];
};

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences(void);
	virtual ~UserPreferences();
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	AsciiString m_filename;
};

class SkirmishPreferences : public UserPreferences
{
public:
	SkirmishPreferences(void);
	virtual ~SkirmishPreferences();
	virtual Bool write(void);

private:
	_STL::list<UnicodeString> m_userNames;
};

// ??0SkirmishPreferences@@
SkirmishPreferences::SkirmishPreferences(void)
	: m_userNames(0)
{
	load("Skirmish.ini");
	UnicodeString userNames;
	UnicodeString token;
	PreferenceNode *it;
	{
		AsciiString key("UserNames");
		it = find(key);
	}

	if (it == end())
		return;

	userNames = QuotedPrintableToUnicodeString(it->m_value);
	userNames.trim();
	while (userNames.nextToken(&token, L","))
		m_userNames.push_back(token);
}
