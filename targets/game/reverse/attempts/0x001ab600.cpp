// ??0Waypoint@@QAE@HVBFMERetailAsciiString@@PBUCoord3D@@000_NH0@Z
// partial score=0.27 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Waypoint::Waypoint(...), retail 0x001AB600, size 550.
//
// Identity: shared vtable 0x0109C3DC with the banked Waypoint destructor
// 0x001ABA80 (reverse/attempts/0x001aba80.cpp, score=0.97) and the landed
// Waypoint layout in TerrainLogicNameLookups.cpp (m_location +0x0c, m_next
// +0x1c). This body proves the rest of the head-insert doubly linked list
// (m_prev at +0x18, always reset to 0 on insert), five by-value AsciiString
// parameters copy-constructed in declaration order (name, three path
// labels, and a BFME-only extra label at +0x64 with no ZH counterpart), a
// BFME auto-assigned id counter at VA 0x012ACC30 used when id==0x7ffffffe,
// and the same TheTerrainLogic path-cache invalidation the destructor
// performs (reusing the destructor's pinned resetActive callee).
//
//   callees: 0x00887B60 x5 -> AsciiString copy ctor (ledger: GameSpyGroupRoom)
//            0x00887940 x5 -> releaseBuffer, BFMERetailAsciiString
//            0x0041FF82 x1 -> pinned ?resetActive@Rva001ABA80TerrainCache@@QAEXH@Z
//   globals: 0x0109C3DC vtable; 0x012EF4D0 g_waypointListHead (Waypoint*);
//            0x012EF4CC TheTerrainLogic; 0x012ACC30 BFME auto-id counter

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &other);	// retail 0x00887B60
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();						// retail 0x00887940
	unsigned char m_pad[4];
};

struct Coord3D
{
	float x, y, z;
};

enum { WAYPOINT_ID_AUTO = 0x7ffffffe };

class Waypoint;
extern Waypoint *g_waypointListHead;			// VA 0x012EF4D0

// The auto-id counter BFME assigns when the caller passes 0x7ffffffe: lazily
// seeded to 0x40000000 the first time a Waypoint is ever constructed.
extern int g_rva012ACC30WaypointAutoId;		// VA 0x012ACC30

// TheTerrainLogic's path/boundary cache at +0x550, same layout the
// destructor recovered.
class Rva001ABA80CacheEntry
{
public:
	unsigned char m_unreconstructed_00[4];
	int m_field4;
	Rva001ABA80CacheEntry *m_next;
	Rva001ABA80CacheEntry *m_prev;
};

class Rva001ABA80TerrainCache
{
public:
	void resetActive(int arg);				// retail ILT 0x0041FF82, pinned

	Rva001ABA80CacheEntry *m_entry;
	int m_active;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	unsigned char m_unreconstructed_00[0x550];
	Rva001ABA80TerrainCache m_cache;			// +0x550
};

extern TerrainLogic *TheTerrainLogic;			// VA 0x012EF4CC

// A pair of opaque BFME extension slots at +0x6c/+0x88: six zero-filled
// dwords plus a trailing flag byte. Retail zero-fills the six dwords twice
// (a redundant defensive clear the constructor body repeats) and the flag
// byte once; neither identity is proven, so the fields stay address-derived
// and the struct stays a trivial POD so no array constructor helper is used.
struct Rva001AB600Slot
{
	void zeroData()
	{
		m_data[0] = 0;
		m_data[1] = 0;
		m_data[2] = 0;
		m_data[3] = 0;
		m_data[4] = 0;
		m_data[5] = 0;
	}

	int m_data[6];
	unsigned char m_flag;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	Waypoint(int id, BFMERetailAsciiString name, const Coord3D *pLoc,
		BFMERetailAsciiString label1, BFMERetailAsciiString label2,
		BFMERetailAsciiString label3, bool biDirectional, int extraField,
		BFMERetailAsciiString extraLabel);

	virtual ~Waypoint();

private:
	int m_id;						// +0x04
	BFMERetailAsciiString m_name;				// +0x08
	Coord3D m_location;					// +0x0c
	Waypoint *m_prev;					// +0x18
	Waypoint *m_next;					// +0x1c
	Waypoint *m_links[8];					// +0x20
	int m_numLinks;						// +0x40
	int m_unreconstructed_44;
	unsigned char m_unreconstructed_48;			// defaults true
	unsigned char m_unreconstructed_49[3];
	int m_unreconstructed_4c;
	BFMERetailAsciiString m_pathLabel1;			// +0x50
	BFMERetailAsciiString m_pathLabel2;			// +0x54
	BFMERetailAsciiString m_pathLabel3;			// +0x58
	bool m_biDirectional;					// +0x5c
	unsigned char m_unreconstructed_5d[3];
	int m_extraField;					// +0x60
	BFMERetailAsciiString m_extraLabel;			// +0x64
	unsigned char m_unreconstructed_68;			// +0x68
	unsigned char m_unreconstructed_69[3];
	Rva001AB600Slot m_slots[2];				// +0x6c
	int m_unreconstructed_a4;
	int m_unreconstructed_a8;
	int m_unreconstructed_ac;
};

Waypoint::Waypoint(int id, BFMERetailAsciiString name, const Coord3D *pLoc,
	BFMERetailAsciiString label1, BFMERetailAsciiString label2,
	BFMERetailAsciiString label3, bool biDirectional, int extraField,
	BFMERetailAsciiString extraLabel)
	: m_name(name), m_pathLabel1(label1), m_pathLabel2(label2),
	  m_pathLabel3(label3), m_extraLabel(extraLabel)
{
	m_id = id;
	m_location = *pLoc;

	m_unreconstructed_44 = 0;
	m_unreconstructed_48 = 1;
	m_unreconstructed_4c = 0;

	m_extraField = extraField;
	m_biDirectional = biDirectional;

	m_unreconstructed_68 = 0;

	Rva001AB600Slot *slot0 = &m_slots[0];
	slot0->zeroData();
	slot0->m_flag = 0;

	Rva001AB600Slot *slot1 = &m_slots[1];
	slot1->zeroData();
	slot1->m_flag = 0;

	m_unreconstructed_a4 = 0;
	m_unreconstructed_a8 = 0;

	slot0->zeroData();
	slot1->zeroData();

	m_links[0] = 0;
	m_links[1] = 0;
	m_links[2] = 0;
	m_links[3] = 0;
	m_links[4] = 0;
	m_links[5] = 0;
	m_links[6] = 0;
	m_links[7] = 0;
	m_numLinks = 0;

	if (g_waypointListHead == 0)
		g_rva012ACC30WaypointAutoId = 0x40000000;
	if (m_id == WAYPOINT_ID_AUTO)
	{
		m_id = g_rva012ACC30WaypointAutoId;
		++g_rva012ACC30WaypointAutoId;
	}

	m_next = g_waypointListHead;
	if (g_waypointListHead)
		g_waypointListHead->m_prev = this;
	m_prev = 0;
	g_waypointListHead = this;

	m_unreconstructed_ac = 0;

	if (TheTerrainLogic)
	{
		Rva001ABA80TerrainCache *cache = &TheTerrainLogic->m_cache;
		if (cache->m_active)
		{
			cache->resetActive(cache->m_entry->m_field4);
			cache->m_entry->m_next = cache->m_entry;
			cache->m_entry->m_field4 = 0;
			cache->m_entry->m_prev = cache->m_entry;
			cache->m_active = 0;
		}
	}
}
