// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: TerrainTypes.cpp /////////////////////////////////////////////////////////////////////////
// Author: Colin Day, December 2001
// Desc:   Terrain type descriptions and collection
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#define DEFINE_TERRAIN_TYPE_NAMES

#include "Common/INI.h"
#include "Common/TerrainTypes.h"

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
TerrainTypeCollection *TheTerrainTypes = NULL;

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
const FieldParse TerrainType::m_terrainTypeFieldParseTable[] = 
{

	{ "Texture",		INI::parseAsciiString,			NULL,		offsetof( TerrainType, m_texture ) },
	{ "BlendEdges", INI::parseBool,							NULL,		offsetof( TerrainType, m_blendEdgeTexture ) },
	{ "Class",			INI::parseIndexList,				terrainTypeNames, offsetof( TerrainType, m_class ) },
	{ "RestrictConstruction", INI::parseBool,		NULL,		offsetof( TerrainType, m_restrictConstruction ) },

	{ NULL,					NULL,												NULL,		0 },

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0TerrainType@@ present-unmatched
TerrainType::TerrainType( void )
{

	m_name.clear();
	m_texture.clear();
	m_blendEdgeTexture = FALSE;
	m_class = TERRAIN_NONE;
	m_restrictConstruction = FALSE;
	m_next = NULL;

}  // end TerrainType

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1TerrainType@@ present-unmatched
TerrainType::~TerrainType( void )
{

}  // end ~TerrainType

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
TerrainTypeCollection::TerrainTypeCollection( void )
{

	m_terrainList = NULL;

}  // end TerrainTypeCollection

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1TerrainTypeCollection@@ present-unmatched
TerrainTypeCollection::~TerrainTypeCollection( void )
{
	TerrainType *temp;

	// delete all the type instances
	while( m_terrainList )
	{

		// get the next element
		temp = m_terrainList->friend_getNext();

		// delete the head of the type list
		m_terrainList->deleteInstance();

		// set the new head of the type list
		m_terrainList = temp;

	}  // end while

}  // end ~TerrainTypeCollection

//-------------------------------------------------------------------------------------------------
/** Find a terrain type given the name */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/TerrainTypes_findTerrain.cpp
// ?findTerrain@TerrainTypeCollection@@ present-unmatched
TerrainType *TerrainTypeCollection::findTerrain( AsciiString name )
{
	TerrainType *terrain;

	for( terrain = m_terrainList; terrain; terrain = terrain->friend_getNext() )
	{

		if( terrain->getName() == name )
			return terrain;

	}  // end for terrain

	// not found
	return NULL;

}  // end findTerrain

//-------------------------------------------------------------------------------------------------
/** Allocate a new type, assign the name, and tie to type list */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/TerrainTypeCollectionNewTerrainThunk.cpp
// ?newTerrain@TerrainTypeCollection@@ present-unmatched
TerrainType *TerrainTypeCollection::newTerrain( AsciiString name )
{
	TerrainType *terrain = NULL;

	// allocate a new type
	terrain = newInstance(TerrainType);

	// copy default values from the default terrain entry
	TerrainType *defaultTerrain = findTerrain( AsciiString( "DefaultTerrain" ) );
	if( defaultTerrain )
		*terrain = *defaultTerrain;
/*
	{

		terrain->friend_setTexture( defaultTerrain->getTexture() );
		terrain->friend_setClass( defaultTerrain->getClass() );
		terrain->friend_setBlendEdge( defaultTerrain->isBlendEdge() );
			
	}  // end if
*/

	// assign a name
	terrain->friend_setName( name );

	// tie to list
	terrain->friend_setNext( m_terrainList );
	m_terrainList = terrain;
			
	// return the new terrain
	return terrain;

}  // end newTerrain
