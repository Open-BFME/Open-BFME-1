// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseunicode /Ireference/shims/campaignmanagerascii /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "Common/AsciiString.h"
#include <map>

struct Bfme5AsciiMapValue
{
	AsciiString name;
	AsciiString locale;
	int wins;
	int losses;
	int profileID;
	int flags;
	int rankPoints;
	int side;
	int preorder;
};

struct Bfme5AsciiMapCompare
{
	bool operator()(AsciiString left, AsciiString right) const;
};

typedef std::map<AsciiString, Bfme5AsciiMapValue, Bfme5AsciiMapCompare> Bfme5AsciiMap;
extern Bfme5AsciiMap *bfme5AsciiMap();

void bfme5AsciiMapFind(AsciiString key)
{
	Bfme5AsciiMap::iterator it = bfme5AsciiMap()->find(key);
	(void)it;
}
