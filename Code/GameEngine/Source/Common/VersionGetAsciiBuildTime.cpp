// cl: /DNDEBUG /MD /EHsc
// readable body of ?getAsciiBuildTime@Version@@QAE?AVAsciiString@@XZ: Code/GameEngine/Source/Common/version.cpp
//
// Retail 0x000AEFA0, 171 bytes. ZH body: format("%s %s", m_buildDate.str(),
// m_buildTime.str()) into a local and return by value.

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
	void __cdecl format(AsciiString fmt, ...);
	const char *str() const { return m_data ? m_data->m_text : ""; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/version.h
class Version
{
public:
	AsciiString getAsciiBuildTime();

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

// ?getAsciiBuildTime@Version@@QAE?AVAsciiString@@XZ
AsciiString Version::getAsciiBuildTime()
{
	AsciiString timeStr;
	timeStr.format("%s %s", m_buildDate.str(), m_buildTime.str());
	return timeStr;
}
