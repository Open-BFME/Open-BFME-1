// cl: /DNDEBUG /MD
// Retail 0x00729EA0: build a triangle normal and cast the test ray against it.

struct Vector3
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/tri.h
class TriClass
{
public:
	const Vector3 *N;
	const Vector3 *V[3];
	void Compute_Normal(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/lineseg.h
class LineSegClass
{
	unsigned char m_pad[0x34];
};

struct CastResultStruct;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/coltest.h
class RayCollisionTestClass
{
public:
	CastResultStruct *Result;
	unsigned char m_pad04[0x08];
	LineSegClass Ray;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/colmath.h
class CollisionMath
{
	public:
	static bool Collide(const LineSegClass &line, const TriClass &tri, CastResultStruct *result);
};

class Rva00729EA0
{
public:
	static bool __stdcall castTriangle(RayCollisionTestClass &raytest,
		const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);
};

// ?castTriangle@Rva00729EA0@@SG_NAAVRayCollisionTestClass@@ABVVector3@@11@Z
bool __stdcall Rva00729EA0::castTriangle(RayCollisionTestClass &raytest,
	const Vector3 &p0, const Vector3 &p1, const Vector3 &p2)
{
	Vector3 normal;
	TriClass tri;
	tri.V[0] = &p0;
	tri.V[1] = &p1;
	tri.V[2] = &p2;
	tri.N = &normal;
	tri.Compute_Normal();
	return CollisionMath::Collide(raytest.Ray, tri, raytest.Result);
}
