// ?refresh@Rva006F7CB0Owner@@QAE_NPAVCameraClass@@@Z
// Retail 0x006F7CB0: address-derived owner; the named caller does not prove
// its class identity. The volatile matrix X read preserves retail's x87
// operand order in the inlined transform.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// The body transforms a stored sphere when a matrix source exists, culls it
// against the camera frustum, stores the visibility result and returns whether
// that value changed. The getter at 0x0041CEC0 supplies the transform matrix.
// Its sole caller is address-derived and does not establish this class name.

#include "camera.h"
#include "colmath.h"
#include "matrix3d.h"
#include "sphere.h"

static __forceinline void transformVector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	Vector3 tmp;
	Vector3 *v;
	if (out == &in)
	{
		tmp = in;
		v = &tmp;
	}
	else
	{
		v = (Vector3 *)&in;
	}
	float x = A[0][2] * v->Z;
	x = x + A[0][1] * v->Y;
	x = (*(volatile const float *)&A[0][0]) * v->X + x;
	x = x + A[0][3];
	out->X = x;
	float y = A[1][2] * v->Z;
	y = y + A[1][0] * v->X;
	y = y + A[1][1] * v->Y;
	y = y + A[1][3];
	out->Y = y;
	float z = A[2][2] * v->Z;
	z = z + A[2][0] * v->X;
	z = z + A[2][1] * v->Y;
	z = z + A[2][3];
	out->Z = z;
}

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
		transformVector(
			*(const Matrix3D *)(void *)(long)m_transformSource->bfmeCalc919G(),
			m_localCenter, &m_worldCenter);
	}

	((Rva006F7CB0FrustumTrampoline *)camera)->refresh();
	const FrustumClass *frustum = (const FrustumClass *)((char *)camera + 0x104);
	CollisionMath::OverlapType overlap = CollisionMath::Overlap_Test(*frustum, *(const SphereClass *)&m_worldCenter);

	bool nowVisible = (overlap != 1);
	m_visible = nowVisible;

	return wasVisible != nowVisible;
}
