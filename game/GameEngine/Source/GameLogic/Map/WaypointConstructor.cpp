// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Waypoint::Waypoint, retail 0x001AB600 (550 bytes); vtable 0x0109C3DC is shared with ~Waypoint 0x001ABA80.
// Unwind cleanups call ??1AsciiString 0x0005EE90, so the strings are AsciiString; +0x550 is the map xferTerrainState clears.
// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

#include <map>
#include <string.h>

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}

	float x, y, z;
};

enum { WAYPOINT_ID_AUTO = 0x7ffffffe };

class Waypoint;
extern Waypoint *g_waypointListHead;		// 0x012EF4D0
// 0x012ACC30 is the next auto-assigned waypoint id. Its address-derived
// owner is defined here beside the constructor that assigns and advances it.
class Rva001A1A30
{
public:
	static int s_value;
};

int Rva001A1A30::s_value = 0x40000000;

struct Gen_t_001a6d20_p4pod
{
	int m_value;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	unsigned char m_unreconstructed_00[0x550];
	std::map<int, Gen_t_001a6d20_p4pod> m_map550;	// +0x550
};

extern TerrainLogic *TheTerrainLogic;		// 0x012EF4CC

// Six-dword mask, zeroed at construction and again in the constructor body.
struct Rva001AB600Slot
{
	Rva001AB600Slot() { zeroData(); }
	void zeroData() { memset(m_data, 0, sizeof(m_data)); }

	int m_data[6];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	Waypoint();
	Waypoint(int id, AsciiString name, const Coord3D *pLoc,
		AsciiString label1, AsciiString label2,
		AsciiString label3, bool biDirectional, int extraField,
		AsciiString extraLabel);

	virtual ~Waypoint();

private:
	int m_id;					// +0x04
	AsciiString m_name;				// +0x08
	Coord3D m_location;				// +0x0c
	Waypoint *m_prev;				// +0x18
	Waypoint *m_next;				// +0x1c
	Waypoint *m_links[8];				// +0x20
	Waypoint *m_linkSource;				// +0x40
	Waypoint *m_field44;				// +0x44
	bool m_field48;					// +0x48, defaults true
	int m_numLinks;					// +0x4c
	AsciiString m_pathLabel1;			// +0x50
	AsciiString m_pathLabel2;			// +0x54
	AsciiString m_pathLabel3;			// +0x58
	bool m_biDirectional;				// +0x5c
	int m_extraField;				// +0x60
	AsciiString m_extraLabel;			// +0x64
	bool m_hasInclude;				// +0x68
	Rva001AB600Slot m_includeMask;			// +0x6c
	bool m_hasExclude;				// +0x84
	Rva001AB600Slot m_excludeMask;			// +0x88
	bool m_skipRelationship;			// +0xa0
	int m_unreconstructed_a4;			// +0xa4
	int m_linkedObjectId;				// +0xa8
	int m_frameThreshold;				// +0xac
};

Waypoint::Waypoint(int id, AsciiString name, const Coord3D *pLoc,
	AsciiString label1, AsciiString label2,
	AsciiString label3, bool biDirectional, int extraField,
	AsciiString extraLabel)
	: m_id(id), m_name(name), m_location(*pLoc),
	  m_field44(0), m_field48(true), m_numLinks(0),
	  m_pathLabel1(label1), m_pathLabel2(label2), m_pathLabel3(label3),
	  m_biDirectional(biDirectional), m_extraField(extraField),
	  m_extraLabel(extraLabel), m_hasInclude(false), m_hasExclude(false),
	  m_skipRelationship(false), m_unreconstructed_a4(0), m_linkedObjectId(0)
{
	m_includeMask.zeroData();
	m_excludeMask.zeroData();

	for (int i = 0; i < 8; i++)
		m_links[i] = 0;
	m_linkSource = 0;

	if (g_waypointListHead == 0)
		Rva001A1A30::s_value = 0x40000000;
	if (m_id == WAYPOINT_ID_AUTO)
	{
		m_id = Rva001A1A30::s_value;
		++Rva001A1A30::s_value;
	}

	m_next = g_waypointListHead;
	if (m_next)
		m_next->m_prev = this;
	m_prev = 0;
	g_waypointListHead = this;

	m_frameThreshold = 0;

	if (TheTerrainLogic)
		TheTerrainLogic->m_map550.clear();
}

// Default constructor, retail 0x001AB8B0 (371 bytes); the load path fills the fields afterwards.
Waypoint::Waypoint()
{
	m_id = 0;
	m_numLinks = 0;
	m_biDirectional = false;
	m_extraField = 0;
	m_field44 = 0;
	m_field48 = false;
	m_hasInclude = false;
	m_hasExclude = false;
	m_skipRelationship = false;
	m_location.x = 0;
	m_location.y = 0;
	m_location.z = 0;
	m_unreconstructed_a4 = 0;
	m_includeMask.zeroData();
	m_excludeMask.zeroData();

	for (int i = 0; i < 8; i++)
		m_links[i] = 0;
	m_linkSource = 0;

	if (g_waypointListHead == 0)
		Rva001A1A30::s_value = 0x40000000;
	if (m_id == WAYPOINT_ID_AUTO)
	{
		m_id = Rva001A1A30::s_value;
		++Rva001A1A30::s_value;
	}

	m_next = g_waypointListHead;
	if (m_next)
		m_next->m_prev = this;
	m_prev = 0;
	g_waypointListHead = this;

	m_frameThreshold = 0;

	if (TheTerrainLogic)
		TheTerrainLogic->m_map550.clear();
}

// Waypoint::~Waypoint, retail 0x001ABA80 (235 bytes). Native string and
// map declarations preserve the constructor layout and retail allocation.
// Address-only ILT to the RET at 0x00403860. Retail passes this as a
// cdecl stack argument; the thunk declaration itself carries no signature.
void __cdecl j_0002e8a2();
Waypoint::~Waypoint()
{
	Waypoint *self = this;

	if (self->m_next)
		self->m_next->m_prev = self->m_prev;
	if (self->m_prev)
		self->m_prev->m_next = self->m_next;
	else
		g_waypointListHead = self->m_next;

	if (TheTerrainLogic)
		TheTerrainLogic->m_map550.clear();

	((void (__cdecl *)(void *))j_0002e8a2)(self);
}
