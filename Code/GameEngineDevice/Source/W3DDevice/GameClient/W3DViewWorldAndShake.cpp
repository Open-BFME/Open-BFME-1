// cl: /DNDEBUG /MD /EHsc
// readable body of ?screenToWorldAtZ@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
// readable body of ?Add_Camera_Shake@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
//
// The two W3DView overrides that only convert between the game's Coord3D world
// and W3D's Vector3 one, and touch no W3DView field at all. That is why they
// can share a TU while the rest of the cluster cannot: every other W3DView body
// carries its own partial picture of a 0x24B8-byte object, and those pictures
// disagree. These two need no picture.
//
// screenToWorldAtZ stays out of W3DView.cpp so getPickRay is a REL32 call
// rather than a same-TU inline; getPickRay is declared and not defined here for
// the same reason.
//
// Add_Camera_Shake: Zero Hour reaches the shaker through a global
// CameraShakeSystemClass object and so compiles the call as
// `mov ecx, OFFSET CameraShakerSystem`. Retail loads a pointer --
// `mov ecx, dword ptr [0x012F7FEC]` -- so in BFME the global is a
// CameraShakeSystemClass*, and that one word is the whole difference between
// the reference body and the retail one. Identity: the forwarded call resolves
// through ILT 0x000174A4 to the matched shaker entry point at 0x006D19A0,
// decorated as CameraShakeSystemClass::Add_Camera_Shake(const Vector3 &, float,
// float, float), and the body is the reference field for field -- a stack
// Vector3 loaded from the Coord3D and handed on with the three reals.

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Vector3
{
public:
	Vector3( void ) {}

	float X;
	float Y;
	float Z;

	static float Find_X_At_Z(float z, const Vector3 &p1, const Vector3 &p2)
	{
		return p1.X + ((z - p1.Z) * ((p2.X - p1.X) / (p2.Z - p1.Z)));
	}

	static float Find_Y_At_Z(float z, const Vector3 &p1, const Vector3 &p2)
	{
		return p1.Y + ((z - p1.Z) * ((p2.Y - p1.Y) / (p2.Z - p1.Z)));
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/camerashakesystem.h
class CameraShakeSystemClass
{
public:
	void Add_Camera_Shake( const Vector3 &position, float radius, float duration, float power );
};

// BFME's is a pointer where Zero Hour's is an object; 0x012F7FEC.
extern CameraShakeSystemClass *CameraShakerSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
public:
	virtual void screenToWorldAtZ(const ICoord2D *s, Coord3D *w, float z);
	virtual void Add_Camera_Shake( const Coord3D &position, float radius, float duration, float power );

private:
	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);
};

// ?screenToWorldAtZ@W3DView@@UAEXPBUICoord2D@@PAUCoord3D@@M@Z
void W3DView::screenToWorldAtZ(const ICoord2D *s, Coord3D *w, float z)
{
	Vector3 rayStart, rayEnd;

	getPickRay(s, &rayStart, &rayEnd);
	if (rayStart.Z - z < 120.0f)
		z = rayStart.Z - 120.0f;
	w->x = Vector3::Find_X_At_Z(z, rayStart, rayEnd);
	w->y = Vector3::Find_Y_At_Z(z, rayStart, rayEnd);
	w->z = z;
}

// ?Add_Camera_Shake@W3DView@@UAEXABUCoord3D@@MMM@Z
void W3DView::Add_Camera_Shake( const Coord3D &position, float radius, float duration, float power )
{
	Vector3 vpos;

	vpos.X = position.x;
	vpos.Y = position.y;
	vpos.Z = position.z;

	CameraShakerSystem->Add_Camera_Shake( vpos, radius, duration, power );
}
