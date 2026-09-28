// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
// RVA 0x006FD990 (622 B, ret 4): projects the four view-plane corners of the
// camera at +0x70 onto the Z=0 ground plane into a caller-supplied Vector3[4].
// Owner identity unproved (vtable 0x011207C0); the only caller,
// Rva006FE730CameraBounds::update, reaches it through ILT 0x00042843 on the
// same object. Camera at +0x70 is witnessed by Rva006FDCB0CameraProjection.
// The ground intersection is WWMath's Vector3::Find_X_At_Z / Find_Y_At_Z, the
// same idiom Zero Hour's HeightMap/W3DView ray casts use; hand-written
// negated-Z helpers schedule the output-pointer load one x87 op early.
#include "camera.h"

class Rva006FD990CameraCorners {
public:
	void build(Vector3 *output);
	char pad000[0x70];
	CameraClass *camera70;
};

void Rva006FD990CameraCorners::build(Vector3 *output)
{
	CameraClass *camera = camera70;
	Vector2 minimum, maximum;
	camera70->Get_View_Plane(minimum, maximum);
	Matrix3D transform(camera70->Get_Transform());
	Vector2 dimensions = maximum - minimum;
	double width = dimensions.X;
	double height = dimensions.Y;
	for (int i = 0; i < 4; ++i) {
		int x, y;
		switch (i) {
			case 0: y = 1; x = 0; break;
			case 1: x = 1; y = 1; break;
			case 3: x = 1; y = 0; break;
			case 2: y = 0; x = 0; break;
			default: y = 0; x = 0; break;
		}
		Vector3 local;
		local.X = (x - 0.5 - camera->Get_Viewport().Min.X) * width;
		local.Y = (y - 0.5 - camera->Get_Viewport().Min.Y) * height;
		local.Z = -1.0f;
		Vector3 direction;
		Matrix3D::Rotate_Vector(transform, local, &direction);
		direction.Normalize();
		Vector3 end = direction + camera70->Get_Position();
		float groundX = Vector3::Find_X_At_Z(0.0f, camera70->Get_Position(), end);
		float groundY = Vector3::Find_Y_At_Z(0.0f, camera70->Get_Position(), end);
		output[i].X = groundX;
		output[i].Y = groundY;
		output[i].Z = 0.0f;
	}
}
