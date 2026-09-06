// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// FUZZY-TWIN of Code/GameEngine/Source/GameClient/GUI/Rva00473500LoadFontSubstitution.cpp
// (?rva00473500LoadFontSubstitution@@YAXXZ, 0x00473500, 118B): same stack INI
// plus one load() call, but retail reads the AsciiString from an incoming
// by-reference PARAMETER (`mov eax, [esp+0x85c]`, one dword beyond this
// function's own local frame, then copy-constructed via the AsciiString
// copy ctor) instead of constructing a fresh AsciiString from a string
// literal address. No matched caller or ZH source names the owner, so this
// lands address-derived per the twin-lane identity policy.
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

void rva00093f70(const AsciiString &filename)
{
	INI ini;
	ini.load(filename, INI_LOAD_OVERWRITE, 0);
}
