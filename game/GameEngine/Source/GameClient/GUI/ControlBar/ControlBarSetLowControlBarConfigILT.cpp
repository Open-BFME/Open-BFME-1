// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/controlbarvtables /Iinputs/reference/shims/controlbarlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// Retail 0x0002FA6D is a five-byte tail jump to the matched
// ControlBar::setLowControlBarConfig body at 0x0049E120 (protected, so the
// address-derived thunk class derives from ControlBar to reach it).
#include "PreRTS.h"
#include "GameClient/ControlBar.h"

class Rva0002FA6DControlBarThunk : public ControlBar
{
public:
	void forward();
};

void Rva0002FA6DControlBarThunk::forward()
{
	setLowControlBarConfig();
}
