// cl: /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "dx8wrapper.h"

// BFME's older float-ABI Z-bias helper uses a static-only derived view.
// It accesses the existing DX8Wrapper static state without changing the
// shared header or adding a second public overload.
class BFMEZBiasSetter : public DX8Wrapper
{
public:
	static void set(float zbias);
};

// ?set@BFMEZBiasSetter@@SAXM@Z
void BFMEZBiasSetter::set(float zbias)
{
	float &current_zbias=*reinterpret_cast<float *>(&ZBias);
	if (zbias==current_zbias)
		return;
	current_zbias=zbias;
	if (ZNear!=ZFar) {
		Matrix4x4 tmp=ProjectionMatrix;
		tmp[3][2]-=(ZNear*ZFar/(ZFar-ZNear))*(zbias*(1.0f/16.0f));
		DX8CALL(SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&tmp));
	}
}
