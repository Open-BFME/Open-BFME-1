// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail keeps ecx as this across the call, so the field address is formed
// with lea edx rather than add ecx.  That is a thiscall member of the same
// object; the ILT at 0x0002CEEE jumps to bfmeBoundaryDistanceSquared3D.

struct Rva0018CF10Point
{
	unsigned char m_storage;
};

// The callee at 0x0018CE80 (Object_bfmeBoundaryDistanceSquared3D.cpp).
struct BfmeBoundaryPoint3D;
class BfmeBoundaryObject3D
{
public:
	float bfmeBoundaryDistanceSquared3D(const BfmeBoundaryPoint3D *first, const BfmeBoundaryPoint3D *second) const;
};

class Rva0018CF10Owner
{
public:
	float distanceSquaredTo(const Rva0018CF10Point *other) const;

private:
	unsigned char m_prefix[0x38];
	Rva0018CF10Point m_point;
};

float Rva0018CF10Owner::distanceSquaredTo(const Rva0018CF10Point *other) const
{
	return ((const BfmeBoundaryObject3D *)this)->bfmeBoundaryDistanceSquared3D((const BfmeBoundaryPoint3D *)&m_point, (const BfmeBoundaryPoint3D *)other);
}
