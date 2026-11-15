// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?getAsciiVersion@Version@@QAE?AVAsciiString@@XZ: game/GameEngine/Source/Common/version.cpp
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

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/version.h
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
