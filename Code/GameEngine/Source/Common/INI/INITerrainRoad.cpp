// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The Road and Bridge blocks. Each searches its own list and then checks the
// kind flag on whatever it found, which is what produces these:
//
//   Redefining bridge '%s' as a road!
//   Redefining road '%s' as a bridge!\n
//
// The kind is a byte at TerrainRoadType+0x08. Note what that implies and what
// this file does not pretend to explain: the road list can hold an entry whose
// flag says bridge, or the message would be unreachable. That is retail's
// behaviour, not an inference from the naming.
//
// The two searches are separate functions with identical 246-byte bodies that
// differ in one operand -- 0x006023A0 walks the list at collection+0x08 and
// 0x006024E0 walks the one at +0x0c -- so they are findRoad and findBridge
// rather than the combined findRoadOrBridge Zero Hour also declares.
//
// TheTerrainRoads at 0x012F7008 is named by GameEngine::init's string literal
// and typed TerrainRoadCollection by a matched initSubsystem row. newRoad is
// already matched at the create branch of the Road block, and Zero Hour declares
// findRoadOrBridge, findRoad, newRoad, findBridge and newBridge together, so the
// two remaining names come from the same header as the one already proven.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainRoads.h
class TerrainRoadType
{
public:
	AsciiString getName( void ) const;
	// Inline: retail reads the byte where the call would be -- mov cl,[eax+8]
	// then test cl,cl -- so the kind flag is not behind a call.
	Bool isBridge( void ) const { return m_isBridge; }

	static const FieldParse m_terrainRoadFieldParseTable[];
	static const FieldParse m_terrainBridgeFieldParseTable[];

private:
	char m_unknown00[ 0x08 ];
	Bool m_isBridge;			// 0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainRoads.h
class TerrainRoadCollection
{
public:
	TerrainRoadType *findRoad( AsciiString name );
	TerrainRoadType *findBridge( AsciiString name );
	TerrainRoadType *newRoad( AsciiString name );
	TerrainRoadType *newBridge( AsciiString name );
};

extern TerrainRoadCollection *TheTerrainRoads;

void INI::parseTerrainRoadDefinition( INI* ini )
{
	AsciiString name;
	name = ini->getNextToken();

	TerrainRoadType *road = TheTerrainRoads->findRoad( name );
	if( road )
	{
		if( road->isBridge() )
			throw INIException( 3, "Redefining bridge '%s' as a road!", road->getName().str() );
	}
	else
	{
		road = TheTerrainRoads->newRoad( name );
	}

	ini->initFromINI( road, TerrainRoadType::m_terrainRoadFieldParseTable );
}

void INI::parseTerrainBridgeDefinition( INI* ini )
{
	AsciiString name;
	name = ini->getNextToken();

	TerrainRoadType *bridge = TheTerrainRoads->findBridge( name );
	if( bridge )
	{
		if( !bridge->isBridge() )
			throw INIException( 3, "Redefining road '%s' as a bridge!\n", bridge->getName().str() );
	}
	else
	{
		bridge = TheTerrainRoads->newBridge( name );
	}

	ini->initFromINI( bridge, TerrainRoadType::m_terrainBridgeFieldParseTable );
}
