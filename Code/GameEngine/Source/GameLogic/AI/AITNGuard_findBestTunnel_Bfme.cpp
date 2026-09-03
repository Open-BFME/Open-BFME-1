// cl: /DNDEBUG /MD /EHsc
// stlport
// BFME's tunnel tracker keeps its tunnel-id list at +4 rather than the
// Zero Hour +8 location.  The list is the STLport circular list used by the
// retail AI state, and Object's position is inline in the BFME object body.

#include <list>

typedef int ObjectID;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class TunnelTracker
{
public:
	const std::list<ObjectID> *getContainerList() const
	{
		return &m_tunnelIDs;
	}

private:
	void *m_snapshotVtable;
	std::list<ObjectID> m_tunnelIDs;
};

class Player
{
public:
	TunnelTracker *getTunnelSystem()
	{
		return m_tunnelSystem;
	}

private:
	unsigned char m_bfmePrefix[0x22c];
	TunnelTracker *m_tunnelSystem;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// ?findBestTunnel@@YAPAVObject@@PAVPlayer@@PBUCoord3D@@@Z
static Object *findBestTunnel(Player *ownerPlayer, const Coord3D *pos)
{
	if (!ownerPlayer)
		return 0;

	TunnelTracker *tunnels = *(TunnelTracker **)((unsigned char *)ownerPlayer + 0x22c);
	Object *bestTunnel = 0;
	Real bestDistSqr = 0;
	const std::list<ObjectID> *allTunnels = tunnels->getContainerList();
	std::list<ObjectID>::const_iterator end = allTunnels->end();
	for (std::list<ObjectID>::const_iterator iter = allTunnels->begin(); iter != end; ++iter)
	{
		Object *currentTunnel = TheGameLogic->findObjectByID(*iter);
		if (currentTunnel)
		{
			Real dx = currentTunnel->getPosition()->x - pos->x;
			Real dy = currentTunnel->getPosition()->y - pos->y;
			Real distSqr = dx * dx + dy * dy;
			if (bestTunnel == 0 || distSqr < bestDistSqr)
			{
				bestDistSqr = distSqr;
				bestTunnel = currentTunnel;
			}
		}
	}
	return bestTunnel;
}

__declspec(noinline) Object *AITNGuardFindBestTunnelAnchor(Player *ownerPlayer, const Coord3D *pos)
{
	return findBestTunnel(ownerPlayer, pos);
}
