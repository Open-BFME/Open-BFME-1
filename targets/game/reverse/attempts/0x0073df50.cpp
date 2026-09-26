// ?d_0073df50@@YAXXZ
// partial score=0.66 date=2026-09-25
// cl: /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include /ICode/Libraries/Source /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad
#include "../../Code/Libraries/Source/WWVegas/WWMath/sphere.h"
#include "../../Code/Libraries/Source/WWVegas/WWMath/frustum.h"
#include "../../Code/Libraries/Source/WWVegas/WWMath/colmath.h"

class CameraClass
{
protected:
	void Update_Frustum(void) const;
	unsigned char m_bfmeCameraHead[0x104];
	FrustumClass m_frustum;
};

class Rva0073DF50Camera : public CameraClass
{
public:
	using CameraClass::Update_Frustum;
	using CameraClass::m_frustum;
};

class Rva0073DF50
{
public:
	int isVisible(const Vector3 *position, float radius);

	unsigned char m_bfmeHead[0x104];
	Rva0073DF50Camera *m_camera;
};

int Rva0073DF50::isVisible(const Vector3 *position, float radius)
{
	Vector3 center(position->X, position->Y, position->Z);
	SphereClass sphere(center, radius);
	Rva0073DF50Camera *camera = m_camera;

	camera->Update_Frustum();
	return CollisionMath::Overlap_Test(camera->m_frustum, sphere) != 1;
}
