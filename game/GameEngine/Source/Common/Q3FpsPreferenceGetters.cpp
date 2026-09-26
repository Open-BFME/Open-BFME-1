// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
/* Three adjacent bodies of the getLastLadderPort shape, retail 0x000AC870,
   0x000AC8F0 and 0x000AC960 -- the same find / end / atoi walk over the same
   preferences map at this+4.  Same two flag moves as the file next door and
   for the same reasons: EH off, and the AsciiString shim whose str() is
   inline.

   The first differs from the other two in two ways the bytes state plainly:
   its default when the key is absent is 5, where the other two return -1,
   and it CLAMPS -- anything outside [0,5) comes back as zero.  So the
   missing-key answer and the out-of-range answer are DIFFERENT values, which
   is the sort of thing only the bytes would tell you.  All three are Int.

   The KEYS are certain, read out of retail and re-checked by the build's
   string-reference gate: StartingSupplies, MaxFPS and FPSSlider.  The OWNER is not.  Neither
   body has a named caller, no Zero Hour counterpart exists for either key,
   and the setters that write the same two keys (0x000A9940 and 0x000A9970)
   sit on an owner that is itself only address-named.  So these keep the
   address-derived naming Q2TemporaryKeyStores.cpp established rather than
   borrowing a class name from the literals.

   The owner derives from UserPreferences and adds nothing, which is what puts
   the map at +4 where retail reads it; the derivation exists to carry a name,
   not a layout. */
#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/UserPreferences.h"

/* Retail INLINES AsciiString::str() here -- `mov eax,[x] / test / lea eax,[eax+8]`
   -- and every shared shim forwards to StringBase<char>::str(), which is out of
   line in string_base.h, so a call is emitted instead.  That is the last seven
   bytes of each body and nothing else.

   StringBase's m_data is private with only AsciiString as a friend, so a helper
   cannot name it; it reads the object's single dword directly instead.  Doing it
   here rather than in a new inputs/reference/shims/ header is deliberate: a shim or
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

class Gen000AC870Owner : public UserPreferences
{
public:
	Int Rva000AC870( void );			///< key "StartingSupplies"
	Int Rva000AC8F0( void );		///< key "MaxFPS"
	Int Rva000AC960( void );		///< key "FPSSlider"
};

Int Gen000AC870Owner::Rva000AC870( void )
{
	Gen000AC870Owner::const_iterator it = find("StartingSupplies");
	if (it == end())
	{
		return 5;
	}
	Int val = atoi(inlineStr(it->second));
	if (val < 0 || val >= 5)
	{
		return 0;
	}
	return val;
}

Int Gen000AC870Owner::Rva000AC8F0( void )
{
	Gen000AC870Owner::const_iterator it = find("MaxFPS");
	if (it == end())
	{
		return -1;
	}
	return atoi(inlineStr(it->second));
}

Int Gen000AC870Owner::Rva000AC960( void )
{
	Gen000AC870Owner::const_iterator it = find("FPSSlider");
	if (it == end())
	{
		return -1;
	}
	return atoi(inlineStr(it->second));
}
