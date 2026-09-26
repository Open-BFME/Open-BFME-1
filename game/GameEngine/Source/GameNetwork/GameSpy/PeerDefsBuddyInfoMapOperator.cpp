// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// HandleBuddyResponses obtains a BuddyInfoMap through the named GameSpyInfo
// getter at vtable slot +0x54 and calls this STLport operator[] at 0x004EE3D0.
// The mapped type is the real PeerDefs BuddyInfo: two integer fields, three
// AsciiStrings, and two UnicodeStrings.  Its copy body is the seven-field
// 0x004E9FD0 helper, and its destructor is 0x004EA090.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _BFME_RETAIL_PLAYER_INFO_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "StringInline.h"

// Keep the instantiation isolated from the engine's full AsciiString header.
// These are the exact data-bearing declarations from the PeerDefs header and
// GP shim; StringInline supplies the already-proven one-pointer string ABI.
typedef int GPProfile;
typedef int GPEnum;

class BuddyInfo
{
public:
	GPProfile m_id;
	AsciiString m_name;
	AsciiString m_email;
	AsciiString m_countryCode;
	GPEnum m_status;
	UnicodeString m_statusString;
	UnicodeString m_locationString;
};

template BuddyInfo &std::map<GPProfile, BuddyInfo>::operator[](
	const GPProfile &key);
