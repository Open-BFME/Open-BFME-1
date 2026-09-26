// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?getUnicodeBuildUser@Version@@QAE?AVUnicodeString@@XZ: game/GameEngine/Source/Common/version.cpp
//
// Retail 0x000AF3B0, 273 bytes. ZH body: translate a copy of m_buildUser
// into a local, format it through TheGameText->fetch("Version:BuildUser")
// and return by value (hidden sret, ret 4).

#include "string_base.h"

// Retail zeroes a default-constructed UnicodeString in line (no call); same
// specialization as the landed NetworkDirectConnectSystem.cpp.
template<> inline StringBase<unsigned short>::StringBase() : m_data(0) {}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	void translate(const AsciiString &src);
	void __cdecl format(UnicodeString fmt, ...);
	const unsigned short *str() const { return m_data ? m_data->data : L""; }
};

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameText.h
// declares fetch(const Char*) before fetch(AsciiString); MSVC lays the overload
// pair out reversed, so the const char* one lands in slot 10 (+0x28) as retail calls.
class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/version.h
// Every offset is read where the ZH twin reads that member by one of the four
// getUnicode* bodies: +0x0..+0xC getUnicodeVersion 0x000AEE00, +0x10
// getUnicodeBuildLocation 0x000AF220, +0x14 getUnicodeBuildUser 0x000AF3B0,
// +0x18/+0x1C getUnicodeBuildTime 0x000AF080.
class Version
{
public:
	UnicodeString getUnicodeBuildUser();

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

// ?getUnicodeBuildUser@Version@@QAE?AVUnicodeString@@XZ
UnicodeString Version::getUnicodeBuildUser()
{
	UnicodeString build;
	UnicodeString user;

	user.translate(AsciiString(m_buildUser));
	build.format(TheGameText->fetch("Version:BuildUser").str(), user.str());

	return build;
}
