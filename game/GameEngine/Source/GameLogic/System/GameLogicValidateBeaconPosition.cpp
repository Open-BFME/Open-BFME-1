// cl: /DNDEBUG /MD
//
// BFME 1.03 RVA 0x001A40C0.  The sole matched caller is the
// MSG_PLACE_BEACON arm of GameLogic::logicMessageDispatcher.  It passes the
// address of the message's writable Coord3D and continues beacon creation only
// when this helper returns true.  The TerrainLogic constructor installs vtable
// 0x0111D090; its slots +0x20, +0x34, and +0x4C resolve respectively to the
// extent, closest-edge (Coord3D sret), and underwater operations used here.

typedef bool Bool;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	Bool isInRegionNoZ(const Coord3D *query) const
	{
		return lo.x < query->x && query->x < hi.x
			&& lo.y < query->y && query->y < hi.y;
	}
};

// upstream vtable order: game/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void getExtent(Region3D *extent) const = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual Coord3D findClosestEdgePoint(const Coord3D *closestTo) const = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
};

extern TerrainLogic *TheTerrainLogic;

// The original private/static spelling is not recoverable from retail.  Keep
// the identity honest and RVA-qualified while preserving the proven role.
Bool isValidBeaconPosition_001A40C0(Coord3D *position)
{
	if (TheTerrainLogic != 0)
	{
		Region3D extent;
		TheTerrainLogic->getExtent(&extent);
		if (!extent.isInRegionNoZ(position))
			*position = TheTerrainLogic->findClosestEdgePoint(position);

		Bool valid = !TheTerrainLogic->isUnderwater(position->x, position->y, 0, 0);
		return valid;
	}

	return false;
}
