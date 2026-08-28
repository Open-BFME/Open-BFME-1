// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?getLastLadderPort@CustomMatchPreferences@@QAEGXZ: Code/GameEngine/Source/Common/UserPreferences.cpp
// readable body of ?getLastLadderPort@QuickMatchPreferences@@QAEGXZ: Code/GameEngine/Source/Common/UserPreferences.cpp
/* The two getLastLadderPort bodies, retail 0x000ABEA0 and 0x000AC230.

   Same reference source and same include line as UserPreferences.cpp next
   door, compiled with EH OFF.  That is the whole reason this is a second
   translation unit: retail's body carries no EH frame at all, and the temp
   AsciiString the find() argument builds forces one under /EHsc -- the body
   comes out the right length with an unwind prologue where retail has none.

   The return width is not a guess either.  Retail zeroes AX, not EAX, on the
   not-found path, which is what fixes UnsignedShort over Int.

   The second flag fact is str(), and it is handled by the helper below
   rather than by the include line. */
#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/UserPreferences.h"
#include "Common/QuickmatchPreferences.h"
#include "Common/CustomMatchPreferences.h"

/* Retail INLINES AsciiString::str() here -- `mov eax,[x] / test / lea eax,[eax+8]`
   -- and every shared shim forwards to StringBase<char>::str(), which is out of
   line in string_base.h, so a call is emitted instead.  That is the last seven
   bytes of each body and nothing else.

   StringBase's m_data is private with only AsciiString as a friend, so a helper
   cannot name it; it reads the object's single dword directly instead.  Doing it
   here rather than in a new reference/shims/ header is deliberate: a shim or
   header change trips the FULL gate, and that gate is currently red upstream on
   22 DIR32 symbols this change has nothing to do with.

   The +8 is the BFME string header width -- a 4-byte ref count and two shorts --
   which is the same offset retail's own inlined copies emit. */
static const char *inlineStr( const AsciiString &s )
{
	static const char TheNullChr = 0;
	const char *header = *(const char *const *)&s;

	return header ? header + 8 : &TheNullChr;
}

UnsignedShort QuickMatchPreferences::getLastLadderPort( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderPort");
	if (it == end())
	{
		return 0;
	}
	return atoi(inlineStr(it->second));
}

UnsignedShort CustomMatchPreferences::getLastLadderPort( void )
{
	CustomMatchPreferences::const_iterator it = find("LastLadderPort");
	if (it == end())
	{
		return 0;
	}
	return atoi(inlineStr(it->second));
}
