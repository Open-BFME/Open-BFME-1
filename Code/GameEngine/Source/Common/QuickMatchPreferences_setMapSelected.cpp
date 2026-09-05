// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"

#include "Common/QuickmatchPreferences.h"
#include "Common/QuotedPrintable.h"

extern char g_bfmeJpegSingleMessage;
extern char g_bfmeJpegExtendedMessage;

class BfmeAsciiStringLengthSetter
{
public:
	void set( const char *value, Int length );
};

#pragma comment(linker, "/alternatename:?set@BfmeAsciiStringLengthSetter@@QAEXPBDH@Z=?set@AsciiString@@QAEXPBDH@Z")

void QuickMatchPreferences::setMapSelected(const AsciiString& mapName, Bool selected)
{
	const char *value = selected ? &g_bfmeJpegSingleMessage : &g_bfmeJpegExtendedMessage;
	BfmeAsciiStringLengthSetter *preference;
	(preference = reinterpret_cast<BfmeAsciiStringLengthSetter *>( &(*this)[AsciiStringToQuotedPrintable(mapName)] ),
		preference->set(value, value ? strlen(value) : 0));
}
