// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// CameraClass::Apply is kept in its own TU so its retail call targets and
// stack layout are not disturbed by the older unclaimed CameraClass methods
// that remain in camera.cpp.
#include "camera.h"
#include "ww3d.h"
#include "matrix4.h"
#include "dx8wrapper.h"

// Keep the BFME out-of-line projection helper's ABI local to this body.
// The shared DX8Wrapper header inlines the Zero Hour variant. Retail Apply
// calls this helper at 0x00933252, targeting the full body at 0x00907120.
// The resolution call uses the existing WW3D name and its verified thunk.
class CameraApplyProjectionCall
{
public:
	static void Set_Projection_Transform_With_Z_Bias(const Matrix4x4 &matrix, float znear, float zfar);
};

void CameraClass::Apply(void)
{
	Update_Frustum();

	int width,height,bits;
	bool windowed;
	WW3D::Get_Render_Target_Resolution(width,height,bits,windowed);
	
	D3DVIEWPORT8 vp;
	vp.X = (DWORD)(Viewport.Min.X * (float)width);
	vp.Y = (DWORD)(Viewport.Min.Y * (float)height);
	vp.Width = (DWORD)((Viewport.Max.X - Viewport.Min.X) * (float)width);
	vp.Height = (DWORD)((Viewport.Max.Y - Viewport.Min.Y) * (float)height);
	vp.MinZ = ZBufferMin;
	vp.MaxZ = ZBufferMax;
	DX8Wrapper::Set_Viewport(&vp);

	Matrix4x4 d3dprojection;
	Get_D3D_Projection_Matrix(&d3dprojection);
	CameraApplyProjectionCall::Set_Projection_Transform_With_Z_Bias(d3dprojection,ZNear,ZFar);
	DX8Wrapper::Set_Transform(D3DTS_VIEW,CameraInvTransform);
}
