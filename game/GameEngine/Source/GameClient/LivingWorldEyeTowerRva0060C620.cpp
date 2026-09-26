// cl: /DNDEBUG /MD -I game/GameEngine/Include/Precompiled -I game/Libraries/Source/WWVegas/WWLib -I game/Libraries/Source/WWVegas/WWMath -I game/Libraries/Source/WWVegas/WWDebug -I game/Libraries/Include
//
// LivingWorldEyeTower::rva0060C620 (0x0060C620, 750 bytes).
//
// OWNER.  The matched LivingWorldEyeTower::processFrame at 0x0060C9D0 calls
// this body through ILT 0x0003E19E with the same eye-tower ECX it keeps for
// its two applyTo calls; the method name stays address-derived because no
// caller, vtable slot or string names it.
//
// WHAT THE BYTES SHOW.  The horizontal and vertical offsets from the Coord3D
// at +0x30 to the one at +0x24 give two angles.  The first matrix is an
// identity Matrix3 rotated about Y by atan2(-dz, dist), post-multiplied by a
// Z rotation of the planar heading minus pi/2; the second copies WWMath's
// Matrix3::Identity (initialised .data at VA 0x012D6A28, the first of
// matrix3.cpp's ten constants in declaration order), rotates it about Y by
// atan2(dz, dist) and pairs it with a Z rotation of that heading minus
// another pi.  Each product goes to the thiscall callee at 0x0061D4D0 on
// the pointers at +0x18 and +0x20 when set.
//
// SHAPE.  The frame layout needs both Coord3D temporaries (the first one's
// dead x/y stores let the second share its slot), the two block-scoped
// halves (so the second pair of matrices reuses the first pair's slots), a
// named pitch separate from the heading, and the in-place `yaw -= pi`.

#include <math.h>
#include "coord.h"
#include "matrix3.h"

class U4Target0060C2C0
{
public:
	void hand( void *payload );
};

class LivingWorldEyeTower
{
private:
	void rva0060C620();

	char m_head[0x18];
	U4Target0060C2C0 *m_ptr18;
	unsigned int m_dword1C;
	U4Target0060C2C0 *m_ptr20;
	Coord3D m_coord24;
	Coord3D m_coord30;
};

void LivingWorldEyeTower::rva0060C620()
{
	Coord3D delta;
	delta.set(&m_coord24);
	delta.sub(&m_coord30);
	Real dz = delta.z;
	Real dy = delta.y;
	Real dist = (Real)sqrt(delta.x * delta.x + dy * dy);
	Real pitch = (Real)atan2(-dz, dist);
	Real yaw;
	Matrix3 result;
	{
		Matrix3 rotY(true);
		rotY.Rotate_Y(pitch);
		Coord3D heading = m_coord24;
		heading.sub(&m_coord30);
		yaw = (Real)atan2(heading.x, -heading.y) - 1.5707964f;
		Matrix3 rotZ = Create_Z_Rotation_Matrix3(yaw);
		Matrix3::Multiply(rotZ, rotY, &result);
		if (m_ptr18)
			m_ptr18->hand(&result);
	}
	{
		Real pitch2 = (Real)atan2(dz, dist);
		Matrix3 rotY = Matrix3::Identity;
		rotY.Rotate_Y(pitch2);
		yaw -= 3.1415927f;
		Matrix3 rotZ = Create_Z_Rotation_Matrix3(yaw);
		Matrix3::Multiply(rotZ, rotY, &result);
		if (m_ptr20)
			m_ptr20->hand(&result);
	}
}
