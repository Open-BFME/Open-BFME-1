// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// SkirmishPreferences::getUserName at retail RVA 0x0009FA60 (263B).
// Ported from Zero Hour's SkirmishGameOptionsMenu.cpp with the two BFME
// deltas confirmed by tools/dis_retail.py 0x0009FA60 and recorded in
// reverse/symbols.csv: the preference key is renamed "UserName" ->
// "CurrentUserName", and both fallback paths (key missing, decoded value
// trims to empty) return UnicodeString::TheEmptyString directly instead of
// falling back to IPEnumeration::getMachineName(). Levers (docs/shape_levers.md):
// find() is throw() so the key temporary needs no EH state; the key is a
// temporary destroyed right after the lookup; isEmpty is the inline two-part test
// (null data pointer or zero 16-bit length at +4) that retail compares against
// the zero it keeps in ebx.

template <typename T> struct StringInlineData
{
	unsigned short m_refCount;
	unsigned short m_reserved;
	unsigned short m_length;	// +4: the word retail tests in isEmpty
	unsigned short m_pad;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void set(const StringBase<T> &other);
	void trim();
	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
	void releaseBuffer();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() { releaseBuffer(); }

	UnicodeString &operator=(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
		return *this;
	}

	void trim() { StringBase<unsigned short>::trim(); }
	bool isEmpty() const { return StringBase<unsigned short>::isEmpty(); }
};

UnicodeString QuotedPrintableToUnicodeString(AsciiString original);

struct PreferenceNode
{
	char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();
	PreferenceNode *end() const { return m_end; }

private:
	PreferenceNode *m_end;
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class SkirmishPreferences : public UserPreferences
{
public:
	UnicodeString getUserName(void);
};

UnicodeString SkirmishPreferences::getUserName(void)
{
	UnicodeString ret;
	PreferenceNode *it = find("CurrentUserName");

	if (it == end())
		return UnicodeString::TheEmptyString;

	ret = QuotedPrintableToUnicodeString(it->m_value);
	ret.trim();
	if (ret.isEmpty())
		ret = UnicodeString::TheEmptyString;
	return ret;
}
