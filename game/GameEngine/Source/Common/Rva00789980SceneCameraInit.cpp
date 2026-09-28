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

// The existing GenBase00944940 alias calls the verified SimpleSceneClass
// constructor. The current scene.h view is 0x98 bytes; retail allocates 0x108.
// This opaque storage view retains that proven extent and ambient slot +0x18.
class GenBase00944940
{
public:
	GenBase00944940();
	virtual ~GenBase00944940() {}
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void Set_Ambient_Light(const Vector3 &color);
};

class Rva00789650 : public GenBase00944940
{
public:
	Rva00789650() {}

private:
	unsigned char m_body[0x104];
};


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
