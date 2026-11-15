// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
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

#include "string_base.h"

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

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

// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/version.cpp
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
