// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail keeps ecx as this across the call, so the field address is formed
// with lea edx rather than add ecx.  That is a thiscall member of the same
// object; the ILT at 0x0002CEEE jumps to bfmeBoundaryDistanceSquared3D.

struct Rva0018CF10Point
{
	unsigned char m_storage;
};

class Rva0018CF10Owner
{
public:
	float distanceSquaredTo(const Rva0018CF10Point *other) const;
	float compute(const Rva0018CF10Point *first,
		const Rva0018CF10Point *second) const;

private:
	unsigned char m_prefix[0x38];
	Rva0018CF10Point m_point;
};

float Rva0018CF10Owner::distanceSquaredTo(const Rva0018CF10Point *other) const
{
	return compute(&m_point, other);
}
