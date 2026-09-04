// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/water /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// readable body of ?renderMirror@WaterRenderObjClass@@IAEXPAVCameraClass@@@Z

#define Matrix4x4 Matrix4  // BFME renamed it

#include "camera.h"
#include "ww3d.h"
#include "shader.h"

typedef int Int;
typedef float Real;

struct IDirect3DSurface8;

class TextureClass
{
public:
	void Release_Ref(void);
};

class ZTextureClass;

class DX8Wrapper
{
public:
	static void Set_Render_Target_With_Z(TextureClass *texture,
		ZTextureClass *ztexture = 0);
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget,
		bool useDefaultDepthBuffer = true);
};

// The retail WaterRenderObjClass has the scene, water level, reflection
// resource and time-of-day fields at these offsets.  The reflection slot is a
// ref-counted pointer in the object; retail passes the slot address to the
// BFME render-target helper and owns the temporary Z target through its local
// ref holder below.
class WaterTextureRef
{
public:
	TextureClass *Pointer;

	WaterTextureRef(void) : Pointer(0) {}
	~WaterTextureRef(void)
	{
		if (Pointer != 0)
			Pointer->Release_Ref();
	}
};

class WaterRenderObjClass
{
	char m_beforeD0[0xd0];
	SceneClass *m_parentScene;
	char m_beforeLevel[0x2c];
	Real m_level;
	char m_beforeReflection[0x148];
	TextureClass *m_pReflectionTexture;
	char m_beforeTod[0x1b0];
	Int m_tod;

	protected:
	void renderSky(void);
	void renderSkyBody(Matrix3D *mat);

	void renderMirror(CameraClass *cam);
};

void WaterRenderObjClass::renderMirror(CameraClass *cam)
{
	Matrix3D OldCameraMatrix = cam->Get_Transform();
	Matrix4 FullMatrix4(cam->Get_Transform());
	Vector3 WaterNormal(0, 0, 1);
	Vector4 WaterPlane(WaterNormal.X, WaterNormal.Y, WaterNormal.Z, m_level);
	Vector3 rRight, rUp, rN, rPos;

	Matrix4 FullMatrix(FullMatrix4.Transpose());

	Real axis_distance = Vector3::Dot_Product((Vector3 &)FullMatrix[0], WaterNormal);
	rRight = (Vector3 &)FullMatrix[0] - (2.0f * axis_distance * WaterNormal);

	axis_distance = Vector3::Dot_Product((Vector3 &)FullMatrix[1], WaterNormal);
	rUp = (Vector3 &)FullMatrix[1] - (2.0f * axis_distance * WaterNormal);

	axis_distance = Vector3::Dot_Product((Vector3 &)FullMatrix[2], WaterNormal);
	rN = (Vector3 &)FullMatrix[2] - (2.0f * axis_distance * WaterNormal);

	axis_distance = Vector3::Dot_Product((Vector3 &)FullMatrix[3], WaterNormal);
	axis_distance -= WaterPlane.W;
	rPos = (Vector3 &)FullMatrix[3] - (2.0f * axis_distance * WaterNormal);

	Matrix3D reflectedTransform(rRight, rUp, rN, rPos);

	{
		WaterTextureRef ztexture;
		DX8Wrapper::Set_Render_Target_With_Z(
			(TextureClass *)&m_pReflectionTexture,
			(ZTextureClass *)&ztexture);
	}

	WW3D::Begin_Render(false, true, Vector3(0.0f, 0.0f, 0.0f));

	cam->Set_Transform(reflectedTransform);

	Vector2 vMin, vMax, vOldMax, vOldMin;
	cam->Get_Viewport(vOldMin, vOldMax);
	vMax.X = vMax.Y = 1.0f;
	vMin.X = vMin.Y = 0.0f;
	cam->Set_Viewport(vMin, vMax);

	cam->Apply();

	ShaderClass::Invert_Backface_Culling(true);

	renderSky();
	if (m_tod == 4)
		renderSkyBody(&reflectedTransform);

	WW3D::Render(m_parentScene, cam);

	cam->Set_Transform(OldCameraMatrix);
	cam->Set_Viewport(vOldMin, vOldMax);

	cam->Apply();

	ShaderClass::Invert_Backface_Culling(false);

	WW3D::End_Render(false);

	DX8Wrapper::Set_Render_Target((IDirect3DSurface8 *)NULL, false);
}
