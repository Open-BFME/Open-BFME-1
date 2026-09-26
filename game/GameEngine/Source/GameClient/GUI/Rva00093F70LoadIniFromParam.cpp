// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// FUZZY-TWIN of game/GameEngine/Source/GameClient/GUI/Rva00473500LoadFontSubstitution.cpp
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
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
