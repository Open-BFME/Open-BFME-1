// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?init@ControlBarResizer@@QAEXXZ: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarResizer.cpp

// INI ini; ini.load(AsciiString("Data\\INI\\ControlBarResizer.ini"), INI_LOAD_OVERWRITE, NULL);
//
// That is the whole function, and it is what the real source says in
// ControlBarResizer.cpp. It stays in its own translation unit for one reason: the
// INI object is a 0x848-byte stack local, and every INI header in the tree
// carries an 8K read buffer that makes the class roughly 0x2438 -- large enough
// that the frame takes a __chkstk probe retail does not have. BFME's INI is the
// two 1028-byte line buffers plus about 64 bytes and nothing more.
//
// Declaring INI here rather than shadowing Common/INI.h keeps that size local to
// this function. ControlBarResizer.cpp needs the real header for its field-parse
// tables, which reference INI::parseAsciiString and INI::parseBool.
//
// The AsciiString is the shim's rather than a hand-rolled stand-in. The
// temporary is passed by value, and only the StringBase-backed shim emits
// `mov [esp+N],esp` before `mov ecx,esp` the way retail does.
#include "Common/AsciiString.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	INI();
	~INI();

	void load(AsciiString filename, INILoadType loadType, Xfer *xfer);

private:
	char m_storage[0x848];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarResizer.h
class ControlBarResizer
{
public:
	void init(void);
};

// ?init@ControlBarResizer@@QAEXXZ
void ControlBarResizer::init(void)
{
	INI ini;
	ini.load(AsciiString("Data\\INI\\ControlBarResizer.ini"), INI_LOAD_OVERWRITE, 0);
}
