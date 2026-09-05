// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// twin of ?init@CampaignManager@@QAEXXZ (0x005BB8C0): a stack INI plus one
// load() call. Retail's string at 0x010F762C is "data\ini\fontsubstitution.ini"
// (reverse/string_xrefs.tsv:5003 -> 0x00473500); no matched caller or ZH source
// names the owner, so this lands address-derived per the twin-lane identity
// policy: the byte-exact body is progress even though the real function name
// is unknown.
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

void rva00473500LoadFontSubstitution(void)
{
	INI ini;
	ini.load(AsciiString("data\\ini\\fontsubstitution.ini"), INI_LOAD_OVERWRITE, 0);
}
