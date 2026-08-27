// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
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

class BfmeArmyIcon
;

class BfmeArmyIconBase
{
public:
	BfmeArmyIconBase( AsciiString name );

private:
	char m_storage[ 0x18 ];
};

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

extern BfmeLivingWorldManagerIcons *TheLivingWorldManager;		// 0x012F706C

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

	BfmeArmyIcon *icon = TheLivingWorldManager->findArmyIcon( AsciiString( token ) );

	if( icon )
		ini->initFromINI( icon, BfmeArmyIcon::m_fieldParseTable );
}
