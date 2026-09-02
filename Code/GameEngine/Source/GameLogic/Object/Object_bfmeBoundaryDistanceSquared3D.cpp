// Computes squared separation from this object's 3D bounding sphere to two
// supplied positions, accounting for the geometry's vertical center offset.

extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

extern const float BfmeBoundaryZero3D;

struct BfmeBoundaryPoint3D
{
	float x;
	float y;
	float z;
};

class BfmeBoundaryGeometry3D
{
public:
	float bfmeZDeltaToCenter(void) const;

private:
	char m_prefix[0x14];
	float m_radius;

	friend class BfmeBoundaryObject3D;
};

class BfmeBoundaryObject3D
{
public:
	float bfmeBoundaryDistanceSquared3D(
		const BfmeBoundaryPoint3D *first,
		const BfmeBoundaryPoint3D *second) const;

private:
	char m_prefix[0xac];
	BfmeBoundaryGeometry3D m_geometry;
};

// ?bfmeBoundaryDistanceSquared3D@BfmeBoundaryObject3D@@QBEMPBUBfmeBoundaryPoint3D@@0@Z
float BfmeBoundaryObject3D::bfmeBoundaryDistanceSquared3D(
	const BfmeBoundaryPoint3D *first,
	const BfmeBoundaryPoint3D *second) const
{
	float radius = m_geometry.m_radius;
	float zOffset = m_geometry.bfmeZDeltaToCenter();
	float dx = first->x - second->x;
	float dy = first->y - second->y;
	float dz = first->z + zOffset - second->z;
	float distance = static_cast<float>(sqrt(dx * dx + dy * dy + dz * dz));
	distance -= radius;
	if (distance < BfmeBoundaryZero3D)
		return BfmeBoundaryZero3D;
	return distance * distance;
}
