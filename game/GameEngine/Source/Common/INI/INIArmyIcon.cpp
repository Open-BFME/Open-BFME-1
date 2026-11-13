// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// The LivingWorldArmyIcon block, retail 0x0060B820. BFME-only.
//
// The function names itself: the INIException it throws when handed a null INI
// pushes "ParseArmyIconBlock::Invalid data passed in.", so the C++ name here is
// the binary's own and not a convention.
//
// TheLivingWorldManager at 0x012F706C is the same global INILivingWorld.cpp
// already reaches. The icon record it hands back is unnamed and nothing in this
// body reads a member, so it stays an opaque class, and the lookup that returns
// it is named for the call site: one AsciiString by const reference.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"
#include <vector>

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class BfmeArmyIcon
;

class BfmeArmyIconBase
{
public:
	BfmeArmyIconBase( AsciiString name );

private:
	AsciiString m_name;
	volatile int m_fields[ 5 ];
};

// ??0BfmeArmyIconBase@@QAE@VAsciiString@@@Z
__declspec(noinline) BfmeArmyIconBase::BfmeArmyIconBase( AsciiString name )
	: m_name( name )
{
	m_fields[ 0 ] = 0;
	m_fields[ 1 ] = 0;
	m_fields[ 2 ] = 0;
	m_fields[ 3 ] = 0;
	m_fields[ 4 ] = 0;
}

class BfmeArmyIcon : public BfmeArmyIconBase
{
public:
	__declspec(noinline) BfmeArmyIcon( const AsciiString &name );
	static const FieldParse m_fieldParseTable[];
};

// ??0BfmeArmyIcon@@QAE@ABVAsciiString@@@Z
__declspec(noinline) BfmeArmyIcon::BfmeArmyIcon( const AsciiString &name )
	: BfmeArmyIconBase( name )
{
}

class BfmeLivingWorldManagerIcons
{
public:
	BfmeArmyIcon *findArmyIcon( const AsciiString &name );

private:
	char m_unmodelled[ 0x264 ];
	std::vector<BfmeArmyIcon *> m_armyIcons;
};

// The global at 0x012F706C is EA's `LivingWorldManager *TheLivingWorldManager`
// (data_rows.csv row ?TheLivingWorldManager@@3PAVLivingWorldManager@@A), defined
// once in LivingWorldManager.cpp. This TU keeps its own view class, whose
// findArmyIcon body is a matched retail function, and reaches it through a cast,
// so only the global's spelling is shared.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;		// 0x012F706C

static inline BfmeLivingWorldManagerIcons *livingWorldManager()
{
	return (BfmeLivingWorldManagerIcons *)TheLivingWorldManager;
}

// Retail .rdata VA 0x01115DC8 (64 B), the table ParseArmyIconBlock hands
// INI::initFromINI. Its parser slots hold the incremental-link thunks, not the
// bodies: ILT 0x0001E32B jumps to ParseIconObjectBlock (0x0060B710) and ILT
// 0x00018E7B to INI::rva000BABF0 (0x000BABF0), so the thunk rows' names are
// the relocation targets.
extern "C" void __identifier("?j_0001e32b@@YAXXZ")( INI *, void *, void *, const void * );
extern "C" void __identifier("?j_00018e7b@@YAXXZ")( INI *, void *, void *, const void * );

const FieldParse BfmeArmyIcon::m_fieldParseTable[] =
{
	{ "Object", __identifier("?j_0001e32b@@YAXXZ"), 0, 0x0 },
	{ "OnSelectedSound", __identifier("?j_00018e7b@@YAXXZ"), 0, 0x4 },
	{ "OnMoveSound", __identifier("?j_00018e7b@@YAXXZ"), 0, 0x8 },
	{ 0, 0, 0, 0 }
};

// ?findArmyIcon@BfmeLivingWorldManagerIcons@@QAEPAVBfmeArmyIcon@@ABVAsciiString@@@Z
BfmeArmyIcon *BfmeLivingWorldManagerIcons::findArmyIcon( const AsciiString &name )
{
	BfmeArmyIcon *icon = new BfmeArmyIcon( name );
	m_armyIcons.push_back( icon );
	return icon;
}

// ?ParseArmyIconBlock@@YAXPAVINI@@@Z
void ParseArmyIconBlock( INI *ini )
{
	if( !ini )
		throw INIException( 3, "ParseArmyIconBlock::Invalid data passed in." );

	const char *token = ini->getNextToken();
	if( !token )
		return;

	BfmeArmyIcon *icon = livingWorldManager()->findArmyIcon( AsciiString( token ) );

	if( icon )
		ini->initFromINI( icon, BfmeArmyIcon::m_fieldParseTable );
}
