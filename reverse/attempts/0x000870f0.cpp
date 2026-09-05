// ?setUserName@LanLobbyUserNamePrefs@@QAEXVUnicodeString@@@Z
// partial score=0.9 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: byte-twin of ?setPreferredMap@CustomMatchPreferences@@QAEXVAsciiString@@@Z
// (Code/GameEngine/Source/Common/UserPreferences.cpp, retail 0x000ADFC0, 177B).
// Retail 0x000870F0, size 177. PARTIAL: 6 non-reloc bytes differ at +0x37/+0x3b,
// an eh-transposition (shape_levers.md row 2, `mov ecx,esp` / `mov [esp+N],esp`
// swapped) around the "UserName" key temporary's cleanup. Tried
// reference/shims/stringinline/StringInline.h instead of full engine headers:
// moved the divergence later (first diff +0x55, 51 bytes) because retail's
// operator= at that point (call ~0x00887???0) needs the map's mapped-value
// type identified -- StringInline's default AsciiString::operator= does a
// raw pointer copy instead of the real out-of-line assignment retail calls,
// and set@UnicodeString@@QAEXABV1@@Z (0x00887C90) fires AFTER the map lookup
// in body order, which this PreRTS.h version does not reproduce at all
// (suggests LanLobbyUserNamePrefs keeps the original UnicodeString in a
// member alongside the AsciiString-quoted PreferenceMap entry -- open
// question for the next attempt).
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/UserPreferences.h"
#include "Common/QuotedPrintable.h"

class LanLobbyUserNamePrefs : public UserPreferences
{
public:
	void setUserName(UnicodeString text);
};

// ?setUserName@LanLobbyUserNamePrefs@@QAEXVUnicodeString@@@Z
void LanLobbyUserNamePrefs::setUserName(UnicodeString text)
{
	(*this)["UserName"] = UnicodeStringToQuotedPrintable(text);
}
