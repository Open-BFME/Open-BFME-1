// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The Terrain block. Find the terrain by name, create it if absent, parse into
// it -- the standard find-then-create shape.
//
// The two calls are what name findTerrain. The second one is already matched as
// TerrainTypeCollection::newTerrain, on the same receiver -- TheTerrainTypes at
// 0x012ED640, whose name comes from GameEngine::init's string literal and whose
// type is proven by that newTerrain row. Zero Hour declares findTerrain
// immediately above newTerrain with the identical signature, and the first call
// is the one whose null result gates the second.
#include "PreRTS.h"
#include "Common/INI.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TerrainTypes.h
class TerrainType
{
public:
	static const FieldParse m_terrainTypeFieldParseTable[];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TerrainTypes.h
class TerrainTypeCollection
{
public:
	TerrainType *findTerrain( AsciiString name );
	TerrainType *newTerrain( AsciiString name );
};

extern TerrainTypeCollection *TheTerrainTypes;

void INI::parseTerrainDefinition( INI* ini )
{
	AsciiString name;
	name = ini->getNextToken();

	TerrainType *terrain = TheTerrainTypes->findTerrain( name );
	if( terrain == NULL )
		terrain = TheTerrainTypes->newTerrain( name );

	ini->initFromINI( terrain, TerrainType::m_terrainTypeFieldParseTable );
}
