// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

// Open-BFME5 conversions.

struct BfmeO1145;

struct BfmeT1145
{
	char m_bfmePad[0x104];
	void (__stdcall *m_bfme104)(BfmeO1145 *o, int a, int b);
	char m_bfmePad2[0xa4];
	void (__stdcall *m_bfme1ac)(BfmeO1145 *o, int a);
};

struct BfmeO1145
{
	BfmeT1145 *m_bfmeTbl;
};

extern "C" void __cdecl bfmeTail1145(void);

void bfmeGo1145(void)
{
	BfmeO1145 *o;

	o = reinterpret_cast<BfmeO1145 *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeTbl->m_bfme104(o, 0, 0);
	o = reinterpret_cast<BfmeO1145 *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeTbl->m_bfme104(o, 1, 0);
	o = reinterpret_cast<BfmeO1145 *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeTbl->m_bfme104(o, 2, 0);
	o = reinterpret_cast<BfmeO1145 *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeTbl->m_bfme104(o, 3, 0);
	o = reinterpret_cast<BfmeO1145 *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeTbl->m_bfme104(o, 4, 0);
	o = reinterpret_cast<BfmeO1145 *>(DX8Wrapper::_Get_D3D_Device8());
	o->m_bfmeTbl->m_bfme1ac(o, 0);
	bfmeTail1145();
}
