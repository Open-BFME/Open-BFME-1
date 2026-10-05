// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /MD /EHsc
#include "dx8wrapper.h"


// Retail 0x00716500. stdcall vtable slot 0x15C(self, arg), then increment a counter.

struct Gen_00716500_Obj;

struct Gen_00716500_Vtbl
{
	void *m_gap[0x15C / 4];
	void (__stdcall *call)(Gen_00716500_Obj *self, void *p);
};

struct Gen_00716500_Obj
{
	Gen_00716500_Vtbl *vtbl;
};

extern unsigned int number_of_DX8_calls;

// ?run_00716500@@YAXPAX@Z
void run_00716500(void *p)
{
	reinterpret_cast<Gen_00716500_Obj *>(DX8Wrapper::_Get_D3D_Device8())->vtbl->call(reinterpret_cast<Gen_00716500_Obj *>(DX8Wrapper::_Get_D3D_Device8()), p);
	++number_of_DX8_calls;
}
