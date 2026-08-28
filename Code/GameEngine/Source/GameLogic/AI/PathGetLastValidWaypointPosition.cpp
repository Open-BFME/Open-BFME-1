// Walk backward from BFME's waypoint cursor until a waypoint still resolves,
// then return that node's position. An empty scan falls back to the path head.

typedef unsigned int UnsignedInt;
typedef UnsignedInt WaypointID;
typedef float Real;

static const WaypointID INVALID_WAYPOINT_ID = 0x7fffffff;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	Real x;
	Real y;
	Real z;
};

class Waypoint;

class TerrainLogic
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot01();
	virtual void bfmeSlot02();
	virtual void bfmeSlot03();
	virtual void bfmeSlot04();
	virtual void bfmeSlot05();
	virtual void bfmeSlot06();
	virtual void bfmeSlot07();
	virtual void bfmeSlot08();
	virtual void bfmeSlot09();
	virtual void bfmeSlot10();
	virtual void bfmeSlot11();
	virtual void bfmeSlot12();
	virtual void bfmeSlot13();
	virtual void bfmeSlot14();
	virtual void bfmeSlot15();
	virtual void bfmeSlot16();
	virtual void bfmeSlot17();
	virtual void bfmeSlot18();
	virtual void bfmeSlot19();
	virtual void bfmeSlot20();
	virtual void bfmeSlot21();
	virtual void bfmeSlot22();
	virtual void bfmeSlot23();
	virtual void bfmeSlot24();
	virtual void bfmeSlot25();
	virtual void bfmeSlot26();
	virtual void bfmeSlot27();
	virtual void bfmeSlot28();
	virtual void bfmeSlot29();
	virtual void bfmeSlot30();
	virtual void bfmeSlot31();
	virtual Waypoint *getWaypointByID(WaypointID waypointID);
};

extern TerrainLogic *TheTerrainLogic;

struct PathNode
{
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	unsigned char m_middle[0x20 - 0x18];
	WaypointID m_waypointID;
};

class Path
{
public:
	Coord3D bfmeGetLastValidWaypointPosition(void) const;

private:
	unsigned char m_head[4];
	PathNode *m_path;
	unsigned char m_middle[0x10 - 0x08];
	PathNode *m_waypointScanStart;
};

// ?bfmeGetLastValidWaypointPosition@Path@@QBE?AUCoord3D@@XZ
Coord3D Path::bfmeGetLastValidWaypointPosition(void) const
{
	PathNode *node = m_waypointScanStart;
	volatile UnsignedInt unused = 0;
	Waypoint *waypoint = 0;
	while (node)
	{
		if (node->m_waypointID == INVALID_WAYPOINT_ID)
			break;

		waypoint = TheTerrainLogic->getWaypointByID(node->m_waypointID);
		if (waypoint)
			break;

		node = node->m_previous;
	}

	const Coord3D *position;
	if (node)
	{
		position = &node->m_position;
	}
	else if (m_path)
	{
		position = &m_path->m_position;
	}
	else
	{
		Coord3D zero;
		zero.x = 0.0f;
		zero.y = 0.0f;
		zero.z = 0.0f;
		position = &zero;
	}

	return *position;
}
