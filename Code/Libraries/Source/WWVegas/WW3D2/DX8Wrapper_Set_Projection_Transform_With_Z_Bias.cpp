// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// BFME's retail helper is the older always-software Z-bias variant of the
// Zero Hour inline helper.  The sibling WW3D2 sources prove the device ABI:
// SetTransform is slot 44 (0xb0), and the call counter is at 0x01340594.
#define Matrix4x4 Matrix4
#include "matrix4.h"

typedef unsigned int UnsignedInt;
typedef long HRESULT;

struct BfmeProjectionDevice;
struct BfmeProjectionDeviceVtable
{
	void *reserved[44];
	HRESULT (__stdcall *SetTransform)(BfmeProjectionDevice *, UnsignedInt, void *);
};
struct BfmeProjectionDevice
{
	BfmeProjectionDeviceVtable *vtable;
};

class DX8Wrapper
{
public:
	static void Set_Projection_Transform_With_Z_Bias(const Matrix4 &matrix, float znear, float zfar);
	static BfmeProjectionDevice *D3DDevice;
	static float ZBias;
	static float ZNear;
	static float ZFar;
	static Matrix4 ProjectionMatrix;
};

extern UnsignedInt number_of_DX8_calls;

// ?Set_Projection_Transform_With_Z_Bias@DX8Wrapper@@SAXABVMatrix4@@MM@Z
void DX8Wrapper::Set_Projection_Transform_With_Z_Bias(
	const Matrix4 &matrix, float znear, float zfar)
{
	Matrix4 tmp;
	ZFar = zfar;
	ZNear = znear;
	ProjectionMatrix = matrix.Transpose();

	if (znear != zfar) {
		tmp = ProjectionMatrix;
		float tmp_zbias = ZBias;
		tmp[3][2] -= (znear * zfar / (zfar - znear)) *
			(tmp_zbias * (1.0f / 16.0f));
		D3DDevice->vtable->SetTransform(
			D3DDevice, 3, reinterpret_cast<void *>(&tmp));
	}
	else {
		D3DDevice->vtable->SetTransform(
			D3DDevice, 3, reinterpret_cast<void *>(&ProjectionMatrix));
	}
	++number_of_DX8_calls;
}
