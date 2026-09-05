// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseunicode /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: TWIN lane. 0x000871D0 and 0x0009FBB0 are byte-twins (relocations
// masked) of the ZH "prefs[key] = UnicodeStringToQuotedPrintable(val);" idiom
// (e.g. GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/
// NetworkDirectConnect.cpp:202 -- prefs["UserName"] = ...). The disassembly
// confirms it: the call at +0x43 targets 0x0003F4DB, a `jmp` thunk
// (Code/GameEngine/Source/Common/thunks_030.cpp) landing on 0x00105F40, which
// the ledger already matches as UnicodeStringToQuotedPrintable
// (Code/Libraries/Source/WWVegas/WWLib/quoted_printable.cpp) -- not the
// AsciiString overload at 0x00106150, a different, already-matched function.
//
// Using the plain PreRTS.h/UserPreferences.h include order reproduces the
// ASCII part exactly but gets the wide (UnicodeString) by-value construction
// backwards (`mov [esp+N],esp` / `mov ecx,esp` swapped): the ZH reference
// UnicodeString is a POD 4-byte-header class with an out-of-line copy ctor,
// not this project's StringBase<wchar_t>-backed one. Putting
// reference/shims/stringbaseunicode and reference/shims/campaignmanagerascii
// ahead of the reference tree on the include path (the same order
// Bfme5EvaSideSoundsCleanup.cpp already uses) makes PreRTS.h's own
// "Common/AsciiString.h" / "Common/UnicodeString.h" includes resolve to the
// StringBase-backed shims retail actually linked, which is what the by-value
// shape needs -- without touching UserPreferences.h.
//
// The only differing relocation between the two targets is the key literal
// pushed at entry (read directly out of retail .rdata): "StartingSupplies"
// for 0x000871D0, "CurrentUserName" for 0x0009FBB0. No caller or class name
// is recoverable for either address, so both live on an address-derived
// owner that adds nothing to UserPreferences, following the convention
// already established by Gen000AC870Owner
// (Code/GameEngine/Source/Common/Q3FpsPreferenceGetters.cpp) and
// Gen000A9490Owner (Code/GameEngine/Source/Common/Q2TemporaryKeyStores.cpp).

#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/GameSpyMiscPreferences.h"
#include "Common/UserPreferences.h"
#include "Common/LadderPreferences.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/Registry.h"
#include "Common/QuickmatchPreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/IgnorePreferences.h"
#include "Common/QuotedPrintable.h"

class Gen000871D0Owner : public UserPreferences
{
public:
	void Rva000871D0( UnicodeString val );		///< key "StartingSupplies"
};

class Gen0009FBB0Owner : public UserPreferences
{
public:
	void Rva0009FBB0( UnicodeString val );		///< key "CurrentUserName"
};

// retail 0x000871D0
void Gen000871D0Owner::Rva000871D0( UnicodeString val )
{
	(*this)["StartingSupplies"] = UnicodeStringToQuotedPrintable(val);
}

// retail 0x0009FBB0
void Gen0009FBB0Owner::Rva0009FBB0( UnicodeString val )
{
	(*this)["CurrentUserName"] = UnicodeStringToQuotedPrintable(val);
}
