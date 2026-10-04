// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: clean C++ reconstruction of MapMetaData::~MapMetaData().
//
// The owner is established by the matched MapMetaData constructor and copy
// constructor.  The destructor's unwind order independently confirms the
// BFME layout: two wide strings, the eight PlayerPosition records, the file
// string, two Coord3D lists, the waypoint map, and two trailing wide-string
// bases.  The opaque member wrappers below retain those proven sizes while
// routing each destructor to its already matched retail body.

// The two list members use the real STLport instantiation; its matched
// _List_base<Coord3D> destructor supplies the same four-byte list body.
#include <list>
#include <map>

typedef unsigned short UnsignedShort;

struct Coord3D
{
	float x;
	float y;
	float z;
};

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer( void );
	T *m_data;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void releaseBuffer( void );

private:
	char *m_data;
};

class AsciiString
{
public:
	~AsciiString();
	bool operator<( const AsciiString &other ) const;

private:
	char *m_data;
};

class WaypointMap : public std::map< AsciiString, Coord3D >
{
public:
	int m_numStartSpots;
};

typedef std::list< Coord3D > Coord3DList;

// Retail's per-record destructor is the one real body at 0x0001F951, named
// after the array whose element it destroys (see
// game/GameEngine/Source/Common/Rva00078460Dtor.cpp).  Naming this record
// type for that body keeps the call site on the defining symbol directly.
class Rva00078460Elem
{
public:
	~Rva00078460Elem();

private:
	char m_body[ 0x14 ];
};

struct MapPlayers
{
	Rva00078460Elem m_items[ 8 ];
};

class MapMetaData
{
public:
	~MapMetaData();

private:
	StringBase< UnsignedShort > m_displayName;
	StringBase< UnsignedShort > m_description;
	unsigned char m_extentAndFlags[ 0x30 ];
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	BFMERetailAsciiString m_fileName;
	MapPlayers m_players;
	StringBase< UnsignedShort > m_displayNameTail;
	StringBase< UnsignedShort > m_descriptionTail;
};

// ??1MapMetaData@@QAE@XZ
MapMetaData::~MapMetaData()
{
}
