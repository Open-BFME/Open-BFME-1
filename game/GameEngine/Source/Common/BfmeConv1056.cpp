// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME5 conversions.
#include "dx8wrapper.h"

struct BfmeVt1056
{
	char m_bfmePad[0x104];
	void (__stdcall *m_bfmeFn)(void *o, int a, int b);
};

struct BfmeE1056
{
	BfmeVt1056 *m_bfmeVt;
};

void bfmeGo1056E(void)
{
	// 0x012D6DFC is ShaderClass::ShaderDirty (dir32_addresses.csv).
	ShaderClass::Invalidate();

	BfmeE1056 *p = reinterpret_cast<BfmeE1056 *>(DX8Wrapper::_Get_D3D_Device8());

	p->m_bfmeVt->m_bfmeFn(p, 0, 0);
	reinterpret_cast<BfmeE1056 *>(DX8Wrapper::_Get_D3D_Device8())->m_bfmeVt->m_bfmeFn(reinterpret_cast<BfmeE1056 *>(DX8Wrapper::_Get_D3D_Device8()), 1, 0);
}
