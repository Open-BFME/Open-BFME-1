// ?d_00518ff0@@YAXXZ
// partial score=0.3 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
//
// ?setup@Rva0051A5A0Host@@QAEXH@Z -- 282B. Caller 0x0051A5A0
// (Rva0051A5A0HostApply.cpp) and reverse/symbols.csv prove
// Rva0051A5A0Host::setup(int). Full boundary decode: a byte flag at +0x3d3
// gates re-entry (same value -> no-op), two GameWindow* fields at +0x3bc/
// +0x3c8 must be non-null, then the WOLLoginMenu.cpp idiom exactly:
// build a GameWindowList, push_front the first window, push_back the
// second, clearTabList(), registerTabList(list), winSetFocus(first) --
// vtable slots 0xa0/0x9c/0xb0 match GameWindowManager.h's declaration
// order (registerTabList, clearTabList, ..., winSetFocus) exactly. When
// the incoming flag is false, only clearTabList() runs.

#include "GameClient/GameWindowManager.h"

class Rva0051A5A0Host
{
public:
	void setup(int enable);

private:
	unsigned char pad1[0x3bc];
	GameWindow *m_windowA; // +0x3bc
	unsigned char pad2[0x3c8 - 0x3c0];
	GameWindow *m_windowB; // +0x3c8
	unsigned char pad3[0x3d3 - 0x3cc];
	unsigned char m_tabState; // +0x3d3
};

// ?setup@Rva0051A5A0Host@@QAEXH@Z
void Rva0051A5A0Host::setup(int enable)
{
	Rva0051A5A0Host *self = this;
	unsigned char en = (unsigned char)enable;
	if (en == self->m_tabState)
		return;

	if (self->m_windowB == NULL)
		return;
	if (self->m_windowA == NULL)
		return;

	self->m_tabState = en;
	if (!en)
	{
		TheWindowManager->clearTabList();
		return;
	}

	GameWindowList tabList;
	tabList.push_front(self->m_windowA);
	tabList.push_back(self->m_windowB);
	TheWindowManager->clearTabList();
	TheWindowManager->registerTabList(tabList);
	TheWindowManager->winSetFocus(self->m_windowA);
}
