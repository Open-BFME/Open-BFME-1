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

// These reads are fields of the ledger-owned RenderStateStruct at
// VA 0x01340EC0: vertex_buffer_types[0] at +0x24C and vertex_buffers[0]
// at +0x260. Access the protected static through a TU-local derived scope.
class Rva00904BA0 : public DX8Wrapper
{
public:
	static __forceinline RenderStateStruct &state() { return render_state; }
};
extern unsigned int number_of_DX8_calls;

void __cdecl bfmeApplyBQ(void)
{
	if (Rva00904BA0::state().vertex_buffers[0] == 0)
		return;

	if (Rva00904BA0::state().vertex_buffer_types[0] != 0 &&
		Rva00904BA0::state().vertex_buffer_types[0] != 2)
		return;

	if (reinterpret_cast<BfmeStateBQ *>(Rva00904BA0::state().vertex_buffers[0])->m_bfmeBusyBQ)
		return;

	reinterpret_cast<BfmeDevBQ *>(DX8Wrapper::_Get_D3D_Device8())->m_bfmeVtblBQ->m_bfmeSetBQ(reinterpret_cast<BfmeDevBQ *>(DX8Wrapper::_Get_D3D_Device8()),
		*reinterpret_cast<BfmeStateBQ *>(Rva00904BA0::state().vertex_buffers[0])->m_bfmeSourceBQ);

	++number_of_DX8_calls;
}
