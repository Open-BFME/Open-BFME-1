// ?isVisible@Rva0073DF50@@QAE_NPBUCoord3D@@M@Z
// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// The receiver is deliberately address-derived: no named caller or vtable
// slot proves the method's original class or spelling. The witnessed +0x104
// member is a CameraClass pointer; the remaining prefix is not modeled.
#include "Lib/BaseType.h"
#include "camera.h"
#include "colmath.h"
#include "sphere.h"

class Rva0073DF50
{
public:
	Bool isVisible(const Coord3D *center, Real radius);

private:
	char m_unmodeled0000[0x104];
	CameraClass *m_3DCamera;
};

Bool Rva0073DF50::isVisible(const Coord3D *center, Real radius)
{
	CameraClass *camera = m_3DCamera;
	Vector3 vector(center->x, center->y, center->z);
	SphereClass sphere;
	sphere.Center = vector;
	sphere.Radius = radius;
	return CollisionMath::Overlap_Test(camera->Get_Frustum(), sphere) != CollisionMath::OUTSIDE;
}
