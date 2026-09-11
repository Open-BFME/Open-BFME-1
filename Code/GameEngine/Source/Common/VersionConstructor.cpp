// cl: /DNDEBUG /MD /EHsc
// Authentic body from version.cpp.  The narrow StringBase ABI is stated
// locally because the shared BFME sweep shim intentionally uses a different
// public AsciiString representation.

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	void set(const StringBase<T> &other);

private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &that)
	{
		set(*(const StringBase<char> *)&that);
		return *this;
	}
};

class Version
{
public:
	Version();

private:
	int m_major;
	int m_minor;
	int m_buildNum;
	int m_localBuildNum;
	AsciiString m_buildLocation;
	AsciiString m_buildUser;
	AsciiString m_buildTime;
	AsciiString m_buildDate;
	bool m_showFullVersion;
};

// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/version.cpp
Version::Version()
{
	m_major = 1;
	m_minor = 0;
	m_buildNum = 0;
	m_localBuildNum = 0;
	m_buildUser = AsciiString("somebody");
	m_buildLocation = AsciiString("somewhere");
	m_showFullVersion = false;
}
