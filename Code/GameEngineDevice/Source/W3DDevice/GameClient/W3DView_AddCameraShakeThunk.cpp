// cl: /DNDEBUG /MD /EHsc
// readable body of ?Add_Camera_Shake@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
// Open-BFME5: W3DView::Add_Camera_Shake, spelled against the retail BFME shape.
//
// Zero Hour reaches the shaker through a global CameraShakeSystemClass object
// and so compiles the call as `mov ecx, OFFSET CameraShakerSystem`.  Retail
// loads a pointer -- `mov ecx, dword ptr [0x012F7FEC]` -- so in BFME the global
// is a CameraShakeSystemClass*, and that one word is the whole difference
// between the reference body and the retail one.  Spelling it in its own
// translation unit keeps the change off the 22 already matched bodies in
// W3DView.cpp (AGENTS.md, "Placement and integrity").
//
// Identity: the forwarded call resolves through ILT 0x000174A4 to the matched
// shaker entry point at 0x006D19A0, decorated as
// CameraShakeSystemClass::Add_Camera_Shake(const Vector3 &, float, float,
// float), and the body is the reference W3DView::Add_Camera_Shake field for
// field --
// a stack Vector3 loaded from the Coord3D and handed on with the three reals.

typedef float Real;

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
	virtual void Add_Camera_Shake( const Coord3D &position, float radius, float duration, float power );
};

void W3DView::Add_Camera_Shake( const Coord3D &position, float radius, float duration, float power )
{
	Vector3 vpos;

	vpos.X = position.x;
	vpos.Y = position.y;
	vpos.Z = position.z;

	CameraShakerSystem->Add_Camera_Shake( vpos, radius, duration, power );
}
