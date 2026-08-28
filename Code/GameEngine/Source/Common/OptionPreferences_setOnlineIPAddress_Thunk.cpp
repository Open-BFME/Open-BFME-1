// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?setOnlineIPAddress@OptionPreferences@@: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionsMenu.cpp

// One map subscript and one assignment, the online counterpart of
// setLANIPAddress -- same shape, different key.
//
// This address was claimed as getAlternateMouseModeEnabled, whose mangling says
// QAE_NXZ: thiscall, no stack arguments, returning Bool. The body ends ret 4 and
// stores a by-value AsciiString, so it takes an argument and returns nothing.
// The key settles which setter it is: GameSpyIPAddress, which the reference
// header ties to setOnlineIPAddress.
#include "PreRTS.h"
#include "Common/UserPreferences.h"

// ?setOnlineIPAddress@OptionPreferences@@QAEXVAsciiString@@@Z
void OptionPreferences::setOnlineIPAddress( AsciiString IP )
{
	(*this)["GameSpyIPAddress"] = IP;
}
