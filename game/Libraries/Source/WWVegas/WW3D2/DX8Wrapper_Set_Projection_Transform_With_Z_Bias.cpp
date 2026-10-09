// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// BFME's retail helper is the older always-software Z-bias variant of the
// Zero Hour inline helper.  The sibling WW3D2 sources prove the device ABI:
// SetTransform is slot 44 (0xb0), and the call counter is at 0x01340594.
#define Matrix4x4 Matrix4
#include "matrix4.h"

#include "dx8wrapper.h"

extern unsigned int number_of_DX8_calls;

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
		// BFME stores float bits in the shared header's integer ZBias cell.
		float tmp_zbias = *reinterpret_cast<float *>(&ZBias);
		tmp[3][2] -= (znear * zfar / (zfar - znear)) *
			(tmp_zbias * (1.0f / 1600.0f));
		D3DDevice->SetTransform(
			D3DTS_PROJECTION, reinterpret_cast<D3DMATRIX *>(&tmp));
	}
	else {
		D3DDevice->SetTransform(
			D3DTS_PROJECTION, reinterpret_cast<D3DMATRIX *>(&ProjectionMatrix));
	}
	++number_of_DX8_calls;
}
