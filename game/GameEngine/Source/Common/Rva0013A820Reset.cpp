// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

// The ten four-byte members are narrow strings: every `call` in this body goes
// to 0x00887940, the char StringBase release body matched in
// Libraries/Source/string/StringBase.cpp. AsciiString::clear() forwards to
// StringBase<char>::clear(), which is the out-of-line releaseBuffer, so the
// real header gives the call without any stand-in method. Same convention as
// Rva006F9900Find.cpp and Bfme7NarrowStringChainDestructors.cpp.
#include "ascii_string.h"

class Rva0013A820
{
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	int m_14;
	int m_18;
	AsciiString m_1C;
	AsciiString m_20;
	int m_24;
	AsciiString m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	int m_40;
	AsciiString m_44;

public:
	void reset();
};

void Rva0013A820::reset()
{
	m_00.clear();
	m_04.clear();
	m_08.clear();
	m_0C.clear();
	m_10.clear();
	m_1C.clear();
	m_20.clear();
	m_28.clear();
	m_3C.clear();
	m_44.clear();
	m_40 = 0;
	m_38 = 0;
	m_34 = 0;
	m_30 = 0;
	m_2C = 0;
	m_24 = 0;
	m_18 = 0;
	m_14 = 0;
}
