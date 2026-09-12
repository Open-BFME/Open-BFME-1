// ??1Waypoint@@UAE@XZ
// partial score=0.97 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Waypoint::~Waypoint(), retail 0x001ABA80, size 235.
//
// Identity: this body and the constructor at 0x001AB600 both install vtable
// 0x0109C3DC. re_attempts for the neighbour body 0x001ABBB0 (Codex-GPT-5.6)
// independently ties that vtable/ctor/dtor triple to Waypoint via the
// getPathLabel1/2/3 getters reading +0x50/+0x54/+0x58, which match the
// already-landed Waypoint layout in TerrainLogicNameLookups.cpp (m_location
// at +0x0c, m_next at +0x1c, g_waypointListHead). This body recovers the
// m_prev link at +0x18 that sibling left opaque, and shows two BFME-only
// additions past ZH's Waypoint: an extra AsciiString member at +0x64 and a
// cache-reset call through TheTerrainLogic+0x550 with no ZH counterpart.
//
//   callees: 0x00887940 x5 -> ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ, matched
//            0x0041FF82 x1 -> ILT to unmatched b_001a6d20; pinned here as
//              Rva001ABA80TerrainCache::resetActive since the real callee
//              has no recovered name or signature
//            0x0042E8A2 x1 -> ILT to the matched 1-byte ret skeleton
//              ?m@Gen_00403860@@QAEXXZ; pinned separately under a cdecl
//              free-function name because that row's own thiscall mangling
//              cannot reproduce this call site's push-and-cdecl-cleanup shape
//   globals: 0x012EF4CC -> TheTerrainLogic; 0x012EF4D0 -> g_waypointListHead

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	unsigned char m_pad[4];
};

class Waypoint;

// TheTerrainLogic's path/boundary cache at +0x550. Entry fields are recovered
// only from the reset sequence: m_field4 at +0x00, m_next at +0x08, m_prev at
// +0x0c; nothing else about this cache is modeled.
class Rva001ABA80CacheEntry
{
public:
	int m_field4;
	Rva001ABA80CacheEntry *m_next;
	Rva001ABA80CacheEntry *m_prev;
};

class Rva001ABA80TerrainCache
{
public:
	void resetActive(int arg);

	Rva001ABA80CacheEntry *m_entry;
	int m_active;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	unsigned char m_unreconstructed_00[0x550];
	Rva001ABA80TerrainCache m_cache;		// +0x550
};

extern TerrainLogic *TheTerrainLogic;
extern Waypoint *g_waypointListHead;

extern "C" void __cdecl Rva001ABA80ResetHook(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	virtual ~Waypoint();

private:
	unsigned char m_unreconstructed_00[4];		// m_id (vtable is implicit at +0x00)
	BFMERetailAsciiString m_name;			// +0x08
	unsigned char m_unreconstructed_0c[0x0c];	// m_location (Coord3D)
	Waypoint *m_prev;				// +0x18
	Waypoint *m_next;				// +0x1c
	unsigned char m_unreconstructed_20[0x50 - 0x20]; // m_links[8] + m_numLinks + BFME extras
	BFMERetailAsciiString m_pathLabel1;		// +0x50
	BFMERetailAsciiString m_pathLabel2;		// +0x54
	BFMERetailAsciiString m_pathLabel3;		// +0x58
	unsigned char m_unreconstructed_5c[0x64 - 0x5c]; // m_biDirectional + a BFME int
	BFMERetailAsciiString m_unreconstructed_64;	// +0x64, BFME addition past ZH
};

Waypoint::~Waypoint()
{
	Rva001ABA80TerrainCache *cache;

	if (m_next)
		m_next->m_prev = m_prev;
	if (m_prev)
		m_prev->m_next = m_next;
	else
		g_waypointListHead = m_next;

	if (TheTerrainLogic) {
		cache = &TheTerrainLogic->m_cache;
		if (cache->m_active) {
			cache->resetActive(cache->m_entry->m_field4);
			cache->m_entry->m_next = cache->m_entry;
			cache->m_entry->m_field4 = 0;
			cache->m_entry->m_prev = cache->m_entry;
			cache->m_active = 0;
		}
	}

	Rva001ABA80ResetHook(this);
}
