// cl: /DNDEBUG /DWIN32 /MD /EHsc
// TerrainLogic::newMap, retail 0x001AE190, 58 bytes.
//
// TerrainLogic's vtable at 0x0109C428 installs the target's ILT in slot 5;
// the constructor at 0x001ADB80 and destructor at 0x001ADD90 install that
// table.  W3DTerrainLogic's derived table at 0x0111D090 installs its
// 0x006BE140 override in the same slot; that override calls this base body
// between its render-side updates.  Slot 6 is the matched
// TerrainLogic::getGroundHeight body.  BFME's waypoint list is global, unlike
// the member list in the Zero Hour header.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// Layout shared with the byte-matched TerrainLogic name lookups: the target
// reads the location at +0x0c and the next link at +0x1c.
class Waypoint
{
public:
	Coord3D *getLocation()
	{
		return &m_location;
	}

	Waypoint *getNext() const
	{
		return m_next;
	}

private:
	unsigned char m_unreconstructed_00[0x0c];
	Coord3D m_location;
	unsigned char m_unreconstructed_18[4];
	Waypoint *m_next;
};

extern Waypoint *g_waypointListHead;

class TerrainLogic
{
public:
	virtual void _tl_00(void) = 0;
	virtual void _tl_01(void) = 0;
	virtual void _tl_02(void) = 0;
	virtual void _tl_03(void) = 0;
	virtual void _tl_04(void) = 0;
	virtual void newMap(Bool saveGame);
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;

private:
	// Retail calls this no-argument member through ILT 0x00010DCA after
	// updating every waypoint.  Its 0x001ADF10 body consumes ECX as the same
	// TerrainLogic receiver; no public semantic spelling is yet proven.
	void rva001ADF10(void);
};

void TerrainLogic::newMap(Bool)
{
	for (Waypoint *way = g_waypointListHead; way; way = way->getNext())
	{
		Coord3D *location = way->getLocation();
		location->z += getGroundHeight(location->x, location->y, 0);
	}

	rva001ADF10();
}
