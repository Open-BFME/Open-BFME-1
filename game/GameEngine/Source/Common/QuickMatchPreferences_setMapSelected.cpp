// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
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
