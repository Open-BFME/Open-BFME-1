// ??AMapMetaDataMap@@QAEAAVMapMetaData@@ABVAsciiString@@@Z
// partial score=0.31 date=2026-09-21
// ?d_000c1d10@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: std::map<AsciiString,MapMetaData>::operator[](const AsciiString&),
// retail RVA 0x000C1D10.  Identity anchors: the same-shaped naked-asm lift at
// 0x0007DF70 (AsciiStringMapMetaDataMapOperatorThunk.cpp); the lower_bound
// call resolves to the shared STLport AsciiString-keyed descent
// (RvaTreeBoundsAsciiString.cpp, ICF-shared regardless of mapped type); the
// hinted insert_unique resolves to retail 0x000C19C0, already matched in
// RvaTreeInsertUniqueHint.cpp against a 252-byte mapped type -- exactly
// sizeof(MapMetaData) per the independently matched
// MapMetaData_ctor.cpp/MapMetaData_dtor.cpp; the default-construct and
// copy-construct calls resolve to MapMetaData's own matched ctor/copy-ctor
// (MapMetaData_ctor.cpp); the two destructor calls resolve to MapMetaData's
// matched dtor (MapMetaData_dtor.cpp).

#include <list>
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef unsigned short UnsignedShort;

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);

private:
	struct Data
	{
		Int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};

	Data *m_data;
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other) : StringBase<UnsignedShort>(other) {}
	~UnicodeString();
};

class MapDisplayNameTail : private StringBase<UnsignedShort>
{
public:
	MapDisplayNameTail() : StringBase<UnsignedShort>() {}
	MapDisplayNameTail(const MapDisplayNameTail &other) : StringBase<UnsignedShort>(other) {}
	~MapDisplayNameTail();
};

class MapDescriptionTail : private StringBase<UnsignedShort>
{
public:
	MapDescriptionTail() : StringBase<UnsignedShort>() {}
	MapDescriptionTail(const MapDescriptionTail &other) : StringBase<UnsignedShort>(other) {}
	~MapDescriptionTail();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
	bool operator<(const AsciiString &other) const;
	int compare(const AsciiString &other) const;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class WaypointMap : public std::map<AsciiString, Coord3D>
{
public:
	WaypointMap() : m_numStartSpots(0) {}
	Int m_numStartSpots;
};

typedef std::list<Coord3D> Coord3DList;

struct PlayerPosition
{
	Bool m_human;
	Bool m_computer;
	Bool m_loadAIScripts;
	Int m_forcePlayerTeam;
	void *m_factionHeader;
	UnsignedInt m_factionCount;
	UnsignedInt m_factionPad;

	PlayerPosition();
	PlayerPosition(const PlayerPosition &other);
	~PlayerPosition();
};

#pragma comment(linker, "/alternatename:??0PlayerPosition@@QAE@XZ=?j_0003a760@@YAXXZ")
#pragma comment(linker, "/alternatename:??0PlayerPosition@@QAE@ABU0@@Z=??0Gen_000C0DF0@@QAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:??1PlayerPosition@@QAE@XZ=??1Rva00078460Elem@@QAE@XZ")

struct MapPlayers
{
	PlayerPosition m_items[8];
};

// upstream layout: proven by MapMetaData_ctor.cpp / MapMetaData_dtor.cpp (both matched)
class MapMetaData
{
public:
	MapMetaData();
	MapMetaData(const MapMetaData &other);
	~MapMetaData();

private:
	UnicodeString m_displayName;
	UnicodeString m_description;
	float m_extentLoX;
	float m_extentLoY;
	float m_extentLoZ;
	float m_extentHiX;
	float m_extentHiY;
	float m_extentHiZ;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
	UnsignedInt m_timestampLo;
	UnsignedInt m_timestampHi;
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	AsciiString m_fileName;
	MapPlayers m_players;
	MapDisplayNameTail m_displayNameTail;
	MapDescriptionTail m_descriptionTail;
};

typedef _STL::pair<const AsciiString, MapMetaData> MapMetaDataPair;

typedef _STL::_Rb_tree<AsciiString, MapMetaDataPair, _STL::_Select1st<MapMetaDataPair>,
	_STL::less<AsciiString>, _STL::allocator<MapMetaDataPair> > MapMetaDataTree;

class MapMetaDataMap
{
public:
	MapMetaData &operator[](const AsciiString &key);

private:
	MapMetaDataTree m_tree;
};

// ?d_000c1d10@@YAXXZ
MapMetaData &MapMetaDataMap::operator[](const AsciiString &key)
{
	MapMetaDataTree::iterator it = m_tree.lower_bound(key);

	if (it != m_tree.end() && key.compare(it->first) >= 0)
		return it->second;

	MapMetaData defaultValue;
	MapMetaDataPair newEntry(key, defaultValue);
	it = m_tree.insert_unique(it, newEntry);
	return it->second;
}
