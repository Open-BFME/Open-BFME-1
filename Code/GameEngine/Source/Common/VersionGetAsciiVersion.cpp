// cl: /DNDEBUG /MD /EHsc
// readable body of ?getAsciiVersion@Version@@QAE?AVAsciiString@@XZ:
// Code/GameEngine/Source/Common/version.cpp
//
// Retail 0x000AEC40, 144 bytes. NDEBUG ZH body: format("%d.%d", m_major, m_minor)
// into a local AsciiString and return it by value (hidden sret, ret 4).

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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/version.h
class Version
{
public:
	AsciiString getAsciiVersion();

private:
	int m_major;
	int m_minor;
};

// ?getAsciiVersion@Version@@QAE?AVAsciiString@@XZ
AsciiString Version::getAsciiVersion()
{
	AsciiString version;
	version.format("%d.%d", m_major, m_minor);
	return version;
}
