// cl: /DNDEBUG /MD /EHsc
// readable body of ?setVersion@Version@@QAEXHHHHVAsciiString@@000@Z: Code/GameEngine/Source/Common/version.cpp
//
// Retail 0x000AEB50, 188 bytes. Four int stores then four StringBase::set
// assigns (user, location, time, date) and dtors of the by-value strings.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/version.h
class Version
{
public:
	void setVersion(int major, int minor, int buildNum, int localBuildNum,
		AsciiString user, AsciiString location,
		AsciiString buildTime, AsciiString buildDate);

private:
	int m_major;
	int m_minor;
	int m_buildNum;
	int m_localBuildNum;
	AsciiString m_buildLocation;
	AsciiString m_buildUser;
	AsciiString m_buildTime;
	AsciiString m_buildDate;
};

// ?setVersion@Version@@QAEXHHHHVAsciiString@@000@Z
void Version::setVersion(int major, int minor, int buildNum, int localBuildNum,
	AsciiString user, AsciiString location,
	AsciiString buildTime, AsciiString buildDate)
{
	m_major = major;
	m_minor = minor;
	m_buildNum = buildNum;
	m_localBuildNum = localBuildNum;
	m_buildUser = user;
	m_buildLocation = location;
	m_buildTime = buildTime;
	m_buildDate = buildDate;
}
