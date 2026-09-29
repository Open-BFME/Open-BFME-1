// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "PreRTS.h"
#include "Common/AsciiString.h"

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[ 0x14 ];
	AsciiString m_value;
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;
	CustomMapNodeShim *find( const AsciiString &key ) throw();
};

class GameLODManager
{
public:
	int getStaticGameLODIndex( AsciiString name );
};

extern GameLODManager *TheGameLODManager;

class OptionPreferences
{
public:
	int rva00090900IdealStaticGameDetail( void );
};

// Retail 0x00090900 reads the key IdealStaticGameLOD (0x01076CD0). The name getIdealStaticGameDetail is
// still claimed by the 0x0007E0F0 row, so this body keeps an address-derived method name.
int OptionPreferences::rva00090900IdealStaticGameDetail( void )
{
	CustomPreferenceMapShim *map;
	CustomMapNodeShim *node;
	{
		AsciiString key( "IdealStaticGameLOD" );
		map = (CustomPreferenceMapShim *)( (unsigned char *)this + 4 );
		node = map->find( key );
	}

	if ( node == map->m_header )
		return -1;

	return TheGameLODManager->getStaticGameLODIndex( node->m_value );
}
