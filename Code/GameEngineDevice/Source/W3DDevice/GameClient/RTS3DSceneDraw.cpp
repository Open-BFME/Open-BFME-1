// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?draw@RTS3DScene@@UAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DScene.cpp

// FILE: RTS3DSceneDraw.cpp ///////////////////////////////////////////////////
//
// RTS3DScene::draw, retail 0x00711920.
//
// W3DScene.cpp compiles it at 61 of 65 bytes and the four are two immediates,
// both of them layout:
//
//   add ecx,0xfffffef8   -- the SubsystemInterface subobject sits 0x108 into
//                           RTS3DScene, not the 0x98 the reference headers give.
//                           draw() is declared only in that secondary base, so
//                           MSVC compiles the override against the secondary
//                           this and subtracts to reach the scene pointer
//                           WW3D::Render wants.  The immediate IS the subobject
//                           offset, which makes SimpleSceneClass 0x70 wider in
//                           BFME.
//   mov eax,[ecx+0x794]  -- m_camera, which is therefore at +0x89c in the
//                           complete object against the reference's +0x5b4.
//
// Both are in headers the whole of WW3D2 and GameEngineDevice share, so the
// shape is restated here: a 0x108-byte primary base over SceneClass, the
// pure-virtual secondary that owns draw(), and enough filler to put m_camera
// where retail reads it.  Nothing else about either class is claimed -- this
// body measures two offsets and no members.
//
// The five arguments are WW3D::Render(this, m_camera, false, false,
// Vector3(0,0,0)): retail allocates the twelve-byte colour temporary in the
// prologue with `sub esp,0xc' and only fills it inside the arm that calls, and
// the call is __cdecl, so the caller's `add esp,0x14' clears all five.
//
///////////////////////////////////////////////////////////////////////////////

class Vector3
{
public:
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X;
	float Y;
	float Z;
};

class CameraClass;

// The return type is part of the mangled name the ledger pins at 0x008FE3C0:
// decorated as ?Render@WW3D@@SA?AW4WW3DErrorType@@PAVSceneClass@@PAVCameraClass@@_N2ABVVector3@@@Z
enum WW3DErrorType { WW3D_ERROR_OK };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SceneClass
{
public:
	virtual ~SceneClass() {}
};

// 0x108 bytes: the vtable pointer SceneClass contributes plus 0x104 of members
// this body does not see.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass : public SceneClass
{
protected:
	char m_bfmeSceneBody[0x108 - 4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual void draw() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	// Declared, never defined: the call resolves by mangled name against the
	// ledger, where it is already pinned at 0x008FE3C0.
	static WW3DErrorType Render( SceneClass *scene, CameraClass *camera,
										 bool clear = false, bool clear_z = false,
										 const Vector3 &color = Vector3(0,0,0) );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DScene.h
class RTS3DScene : public SimpleSceneClass, public SubsystemInterface
{
public:

	virtual void draw();

private:

	// SubsystemInterface's vtable pointer lands at +0x108, so RTS3DScene's own
	// members start at +0x10c.
	char m_bfmeSceneMembers[0x89c - 0x10c];
	CameraClass *m_camera;											// @0x89c

};

void RTS3DScene::draw( )
{

	if (m_camera == 0) {
		return;
	}
	WW3D::Render( this, m_camera );


}  // end Customized_Render
