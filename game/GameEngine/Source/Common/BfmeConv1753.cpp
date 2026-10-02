// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

struct BfmeDevBQ;

struct BfmeVtblBQ
{
	void *m_bfmeSlotsBQ[89];
	void (__stdcall *m_bfmeSetBQ)(BfmeDevBQ *self, void *value);
};

struct BfmeDevBQ
{
	BfmeVtblBQ *m_bfmeVtblBQ;
};

struct BfmeStateBQ
{
	unsigned char m_bfmeHeadBQ[0x14];
	void **m_bfmeSourceBQ;
	char m_bfmeBusyBQ;
};

extern BfmeStateBQ *g_bfmeStateBQ;
extern int g_bfmeModeBQ;
extern int g_bfme936Count;

void __cdecl bfmeApplyBQ(void)
{
	if (g_bfmeStateBQ == 0)
		return;

	if (g_bfmeModeBQ != 0 && g_bfmeModeBQ != 2)
		return;

	if (g_bfmeStateBQ->m_bfmeBusyBQ)
		return;

	reinterpret_cast<BfmeDevBQ *>(DX8Wrapper::_Get_D3D_Device8())->m_bfmeVtblBQ->m_bfmeSetBQ(reinterpret_cast<BfmeDevBQ *>(DX8Wrapper::_Get_D3D_Device8()),
		*g_bfmeStateBQ->m_bfmeSourceBQ);

	++g_bfme936Count;
}
