// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?newTerrain@TerrainTypeCollection@@: Code/GameEngine/Source/Common/TerrainTypes.cpp
// Open-BFME: TerrainTypeCollection::newTerrain, retail 0x000A8680, 204 bytes.
//
// Identity: the Terrain block parser INI::parseTerrainDefinition (0x000C2AC0)
// calls findTerrain and then this body through ILT 0x0000FFAB on the same
// receiver, and the body is the Zero Hour twin line for line: allocate a
// TerrainType (0x30 bytes, constructor 0x000A82F0), copy the "DefaultTerrain"
// entry over it when one exists, assign the name, and push it on the head of
// the list at this+0x08 through the m_next link at +0x20.
//
// BFME de-pooled TerrainType, so the allocation is plain ::operator new.

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TerrainTypes.h
class TerrainType
{
public:
	TerrainType( void );						// 0x000A82F0 via ILT 0x0004A5E3
	virtual ~TerrainType();
	TerrainType &operator=( const TerrainType &that );	// 0x000A8490 via ILT 0x0001A00A

	void friend_setName( AsciiString name ) { m_name = name; }
	void friend_setNext( TerrainType *next ) { m_next = next; }

private:
	AsciiString m_name;							// this+0x04
	char m_slice_pad08[0x18];					// this+0x08 .. +0x1F, untouched
	TerrainType *m_next;						// this+0x20
	char m_slice_pad24[0x0C];					// this+0x24 .. +0x2F, untouched
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TerrainTypes.h
class TerrainTypeCollection
{
public:
	TerrainType *findTerrain( AsciiString name );
	TerrainType *newTerrain( AsciiString name );

private:
	char m_slice_pad[8];						// this+0x00 .. +0x07, untouched
	TerrainType *m_terrainList;					// this+0x08
};

TerrainType *TerrainTypeCollection::newTerrain( AsciiString name )
{
	TerrainType *terrain = 0;

	// allocate a new type
	terrain = new TerrainType;

	// copy default values from the default terrain entry
	TerrainType *defaultTerrain = findTerrain( AsciiString( "DefaultTerrain" ) );
	if( defaultTerrain )
		*terrain = *defaultTerrain;

	// assign a name
	terrain->friend_setName( name );

	// tie to list
	terrain->friend_setNext( m_terrainList );
	m_terrainList = terrain;

	// return the new terrain
	return terrain;

}  // end newTerrain
