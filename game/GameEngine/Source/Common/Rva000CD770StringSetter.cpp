// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

// The owner is unknown: only unused ILT 0x00003DB4 reaches this body.
// Assignment at +8 calls narrow set/release bodies 0x00887C90/0x00887940,
// excluding the previous LANPlayer::setHost(UnicodeString) claim.
class Rva000CD770
{
public:
	void setString(AsciiString value);

private:
	char m_leading[8];
	AsciiString m_string;
};

// ?setString@Rva000CD770@@QAEXVAsciiString@@@Z
void Rva000CD770::setString(AsciiString value)
{
	m_string = value;
}
