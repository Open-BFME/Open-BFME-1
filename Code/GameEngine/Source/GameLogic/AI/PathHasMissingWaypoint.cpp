// BFME keeps an optional cursor into a Path's nodes and uses this query to
// detect any remaining waypoint ID that TerrainLogic can no longer resolve.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WaypointID;

static const WaypointID INVALID_WAYPOINT_ID = 0x7fffffff;

class Waypoint;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
struct PathNode
{
	PathNode *m_next;
	unsigned char m_middle[0x20 - 4];
	WaypointID m_waypointID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	Bool bfmeHasMissingWaypoint(void) const;

private:
	unsigned char m_head[4];
	PathNode *m_path;
	unsigned char m_middle[0x10 - 8];
	PathNode *m_waypointScanStart;
};

// ?bfmeHasMissingWaypoint@Path@@QBE_NXZ
Bool Path::bfmeHasMissingWaypoint(void) const
{
	PathNode *node = m_waypointScanStart;
	if (!node)
		node = m_path;

	while (node)
	{
		WaypointID waypointID = node->m_waypointID;
		if (waypointID != INVALID_WAYPOINT_ID &&
			TheTerrainLogic->getWaypointByID(waypointID) == 0)
			return true;
		node = node->m_next;
	}

	return false;
}
