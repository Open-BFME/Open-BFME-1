// Retail RVA 0x00789980, 498 bytes.
//
// The owner is address-derived from the landed 0x00789900 constructor and
// 0x007897D0 destructor: vtable 0x01126CCC slot 1 routes through thunk
// 0x0001A893 to this body.  The body creates a SimpleSceneClass-derived
// 0x108-byte scene and a CameraClass, then installs the camera transform.

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include

extern "C" double sin(double value);
extern "C" double cos(double value);
#pragma intrinsic(sin, cos)

#include "matrix3d.h"

// The real scene.h SimpleSceneClass supplies the constructor retail calls at
// 0x00944940, so the base is spelled by its defining name and resolves instead
// of the GenBase00944940 stand-in.  scene.h's view is 0x98 bytes while retail
// allocates 0x108, so m_tail below restores that proven extent.
#include "scene.h"

namespace
{
class Rva00789650 : public SimpleSceneClass
{
public:
	Rva00789650() {}

private:
	// retail allocates 0x108 for this object; scene.h's SimpleSceneClass is
	// 0x98. The remaining 0x70 is the BFME tail the upstream header lacks.
	unsigned char m_tail[0x70];
};
}


#include "camera.h"

class Rva00789900Init
{
public:
	virtual ~Rva00789900Init();
	virtual void rva00789980();

private:
	unsigned int m_04;
	unsigned int m_08;
	Rva00789650 *m_scene;
	CameraClass *m_camera;
};

void Rva00789900Init::rva00789980()
{
	m_scene = new Rva00789650();
	m_scene->Set_Ambient_Light(Vector3(0.5f, 0.5f, 0.5f));

	m_camera = new CameraClass();
	m_camera->Set_Clip_Planes(1.0f, 5000.0f);
	m_camera->Set_View_Plane(0.87266463f, -1.0f);

	Matrix3D transform(true);
	transform.Rotate_Y(-3.1415927410125732f);
	transform.Rotate_Z(3.1415927410125732f);

	m_camera->Set_Transform(transform);
}
