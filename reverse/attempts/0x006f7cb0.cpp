// ?refresh@Rva006F7CB0Owner@@QAE_NPAVCameraClass@@@Z
// partial score=0.9 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2
// Open-BFME5: retail 0x006F7CB0 (191B).
// Recomputes a world-space bounding sphere (this+0x0 Vector3 center) from a
// local-space one (this+0x10 Vector3) through the matrix returned by
// this->m_transformSource->bfmeCalc919G() (pinned, still a dump) when that
// source is non-null -- inline Matrix3D::Transform_Vector, aliasing check
// included, matching reference/.../matrix3d.h byte for byte -- then culls
// the world sphere against camera->Update_Frustum()'s frustum (camera+0x104,
// the landed CameraClass shape) via CollisionMath::Overlap_Test, caches the
// bool result at this+0x7c, and returns whether it changed. Landed
// neighbours: SphereClass ctor (W3DRoadBuffer.cpp), Cull_Sphere@CameraClass
// (scene.cpp). Owner is address-derived: the sole caller
// (refreshActive@Rva006F88B0Owner) does not itself prove a game-class name.
//
// PARTIAL: 191/191 bytes -- exact size. Splitting each row's three
// products into separate named locals (x0/x1/x2 etc, evaluated Z,Y,X /
// Z,X,Y / Z,X,Y to match retail's own fld order) got row 0's first two
// terms and the whole control-flow skeleton (null-guard, the
// Transform_Vector aliasing check, Update_Frustum/Overlap_Test call
// shape, and the wasVisible/nowVisible compare-then-store-then-return
// tail) byte-exact; the residue is which operand of each row's THIRD
// (translation-adjacent) multiply MSVC 7.1 loads via fld vs leaves as the
// fmul memory operand, and the same swap on all three rows -- this is the
// documented "equivalent x87 expressions can compile differently...
// commuted multiplication operands" trap (docs/matching.md); neither
// operand order nor statement order changed it, and shape_family_levers
// found no applicable mechanical lever. Score: 172/191 matching bytes
// (0.90).

struct Vector3
{
	float X, Y, Z;
};

class Matrix3D
{
public:
	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		const Vector3 *v;
		if (out == (Vector3 *)&in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = &in;
		}
		float x0 = A.m_row[0][2] * v->Z;
		float x1 = A.m_row[0][1] * v->Y;
		float x2 = v->X * A.m_row[0][0];
		out->X = x0 + x1 + x2 + A.m_row[0][3];
		float y0 = A.m_row[1][2] * v->Z;
		float y1 = A.m_row[1][0] * v->X;
		float y2 = A.m_row[1][1] * v->Y;
		out->Y = y0 + y1 + y2 + A.m_row[1][3];
		float z0 = A.m_row[2][2] * v->Z;
		float z1 = A.m_row[2][0] * v->X;
		float z2 = A.m_row[2][1] * v->Y;
		out->Z = z0 + z1 + z2 + A.m_row[2][3];
	}

private:
	float m_row[3][4];
};

struct SphereClass
{
	Vector3 Center;
	float Radius;
};

class FrustumClass;

enum OverlapType
{
	OVERLAP_TYPE_POS = 0
};

class CollisionMath
{
public:
	static OverlapType Overlap_Test(const FrustumClass &frustum, const SphereClass &sphere);
};

class CameraClass
{
protected:
	void Update_Frustum() const;

	friend class Rva006F7CB0FrustumTrampoline;
};

class Rva006F7CB0FrustumTrampoline : public CameraClass
{
public:
	void refresh() const { Update_Frustum(); }
};

class BfmeCalc919G
{
public:
	int bfmeCalc919G();
};

class Rva006F7CB0Owner
{
public:
	bool refresh(CameraClass *camera);

private:
	Vector3 m_worldCenter;
	float m_worldRadius;
	Vector3 m_localCenter;
	float m_localRadius;
	char m_pad20[0x28 - 0x20];
	BfmeCalc919G *m_transformSource;
	char m_pad2c[0x7c - 0x2c];
	bool m_visible;
};

bool Rva006F7CB0Owner::refresh(CameraClass *camera)
{
	bool wasVisible = m_visible;

	if (m_transformSource != 0)
	{
		Matrix3D::Transform_Vector(
			*(const Matrix3D *)(void *)(long)m_transformSource->bfmeCalc919G(),
			m_localCenter, &m_worldCenter);
	}

	((Rva006F7CB0FrustumTrampoline *)camera)->refresh();
	const FrustumClass *frustum = (const FrustumClass *)((char *)camera + 0x104);
	OverlapType overlap = CollisionMath::Overlap_Test(*frustum, *(const SphereClass *)&m_worldCenter);

	bool nowVisible = (overlap != 1);
	m_visible = nowVisible;

	return nowVisible != wasVisible;
}
