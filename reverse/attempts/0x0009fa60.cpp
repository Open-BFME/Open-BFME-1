// ?getUserName@SkirmishPreferences@@QAE?AVUnicodeString@@XZ
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// SkirmishPreferences::getUserName at retail RVA 0x0009FA60 (263B).
// Ported from Zero Hour's SkirmishGameOptionsMenu.cpp with the two BFME
// deltas confirmed by tools/dis_retail.py 0x0009FA60 and recorded in
// reverse/symbols.csv: the preference key is renamed "UserName" ->
// "CurrentUserName", and both fallback paths (key missing, decoded value
// trims to empty) return UnicodeString::TheEmptyString directly instead of
// falling back to IPEnumeration::getMachineName().

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
	bool isEmpty() const;
	void releaseBuffer();

	void *m_data;
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
	PreferenceNode *find(const AsciiString &) const;
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
	PreferenceNode *it;
	AsciiString key("CurrentUserName");
	it = find(key);

	if (it == end())
		return UnicodeString::TheEmptyString;

	ret = QuotedPrintableToUnicodeString(it->m_value);
	ret.trim();
	if (ret.isEmpty())
		ret = UnicodeString::TheEmptyString;
	return ret;
}
