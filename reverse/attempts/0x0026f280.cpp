// ?isValidLocomotorPosition@AIUpdateInterface@@QBE_NPBUCoord3D@@@Z
// partial score=0.78 date=2026-08-28
struct BFMEValidMovementFields
{
	char m_unreconstructed_000[0x08];
	Object *m_object;
	char m_unreconstructed_00C[0x1B8 - 0x00C];
	LocomotorSurfaceTypeMask m_validLocomotorSurfaces;
};

class BFMEValidMovementObject
{
public:
	PathfindLayerEnum getLayer(void) const;
};

class BFMEValidMovementPathfinder
{
public:
	Bool validMovementPosition(const Coord3D *pos, PathfindLayerEnum layer,
		LocomotorSurfaceTypeMask validSurfaces, Object *obj);
};

Bool AIUpdateInterface::isValidLocomotorPosition(const Coord3D *pos) const
{
	AI *ai = TheAI;
	const BFMEValidMovementFields *retail = reinterpret_cast<const BFMEValidMovementFields *>(this);
	return reinterpret_cast<BFMEValidMovementPathfinder *>(ai->pathfinder())->validMovementPosition(
		pos,
		reinterpret_cast<const BFMEValidMovementObject *>(retail->m_object)->getLayer(),
		retail->m_validLocomotorSurfaces,
		retail->m_object);
}
