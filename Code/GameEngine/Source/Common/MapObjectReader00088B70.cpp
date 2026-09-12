// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// WorldHeightMap.cpp
// Class to encapsulate height map.
// Author: John Ahlquist, April 2001

#define INSTANTIATE_WELL_KNOWN_KEYS

#include "windows.h"
#include "stdlib.h"
#include <string.h>
#include "Common/STLTypedefs.h"

#include "Common/DataChunk.h"
//#include "Common/GameFileSystem.h"
#include "Common/FileSystem.h" // for LOAD_TEST_ASSETS
#include "Common/GlobalData.h"
#include "Common/MapReaderWriterInfo.h"
#include "Common/TerrainTypes.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/WellKnownKeys.h"

#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/SidesList.h"

#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/TileData.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/W3DShadow.h"

#include "Common/file.h"


#define K_OBJECTS_VERSION_2 2
// Retail RVA 0x00088B70, full 545-byte object-record reader.
// The exact caller at RVA 0x00088F10 passes two arguments and links the returned
// MapObject pointer through next (+4). This is not the three-argument Boolean
// WorldHeightMap::ParseObjectDataChunk callback from the Zero Hour reference.
// The layout and legacy-version/key behavior follow the corresponding ZH reader;
// BFME additionally checks acceptsThingTemplateName before resolving a template.
// The MapObject constructor is reached through RVA 0x0001230A -> 0x00088160.
// Vector3 is an ABI reconstruction of the nontrivial three-float value argument;
// it does not assert a recovered original spelling for the retail declaration.

class Rva0088B70ThingRegistry
{
public:
	bool acceptsThingTemplateName(const AsciiString &name);
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern Rva0088B70ThingRegistry *bfmeThingRegistry_0088B70;

class Rva0041230aName
{
public:
	~Rva0041230aName();
	void *m_data;
};
class Rva0041230aFileView
{
public:
	Rva0041230aName bfmeReadAsciiString();
};

// Vector3 has a component-copy constructor. Passing it by value retains the
// retail saved-ESP record; the POD Coord3D spelling loses four bytes.
typedef Vector3 MapObjectPosition;
class Rva0041230aMapObject
{
public:
	char m_pad0[0x24];
	Dict m_properties;
	char m_pad1[0x44 - 0x24 - sizeof(Dict)];
	Int m_runtimeFlags;
	char m_pad2[0x60 - 0x44 - sizeof(Int)];
public:
	Rva0041230aMapObject(MapObjectPosition loc, const AsciiString &name, Real angle, Int flags,
		const Dict *props, const ThingTemplate *tmplate);
	Dict *getProperties() { return &m_properties; }
	void setIsWaypoint() { m_runtimeFlags |= 0x04; }
	void setIsLight() { m_runtimeFlags |= 0x02; }
	void setIsScorch() { m_runtimeFlags |= 0x08; }
};

Rva0041230aMapObject *Rva00088B70ReadMapObject(DataChunkInput &file, DataChunkInfo *info)
{
	Coord3D loc;
	loc.x = file.readReal();
	loc.y = file.readReal();
	loc.z = file.readReal();

	Real minZ = -100*MAP_XY_FACTOR;
	Real maxZ = 12799.8046875f; // retail 0x4647ff38 at VA 0x0107c7fc

	if (info->version <= K_OBJECTS_VERSION_2) {
		loc.z = 0;
	}

	Real angle = file.readReal();
	Int flags = file.readInt();
	Rva0041230aName name = reinterpret_cast<Rva0041230aFileView &>(file).bfmeReadAsciiString();
	Dict d(0);
	if (info->version >= K_OBJECTS_VERSION_2)
	{
		d = file.readDict();
	}

	if (loc.z<minZ || loc.z>maxZ) {
		return 0;
	}

	const AsciiString &nameRef = *reinterpret_cast<const AsciiString *>(&name);
	const ThingTemplate *tmplate = NULL;
	if (bfmeThingRegistry_0088B70->acceptsThingTemplateName(nameRef))
		tmplate = bfmeThingRegistry_0088B70->findTemplate(nameRef);

	Rva0041230aMapObject *pThisOne;

	pThisOne = new Rva0041230aMapObject(Vector3(loc.x, loc.y, loc.z), nameRef, angle, flags, &d, tmplate);

	if (pThisOne->getProperties()->getType(TheKey_waypointID) == Dict::DICT_INT)
		pThisOne->setIsWaypoint();

	if (pThisOne->getProperties()->getType(TheKey_lightHeightAboveTerrain) == Dict::DICT_REAL)
		pThisOne->setIsLight();

	if (pThisOne->getProperties()->getType(TheKey_scorchType) == Dict::DICT_INT)
		pThisOne->setIsScorch();

	return pThisOne;
}
