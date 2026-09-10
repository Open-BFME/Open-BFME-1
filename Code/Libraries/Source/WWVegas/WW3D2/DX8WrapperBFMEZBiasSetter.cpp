// cl: /Ireference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
		tmp[3][2]-=(ZNear*ZFar/(ZNear-ZFar))*(zbias*(1.0f/16.0f));
		DX8CALL(SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&tmp));
	}
}
