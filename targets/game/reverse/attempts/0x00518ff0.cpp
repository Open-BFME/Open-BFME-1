// ?setup@Rva0051A5A0Host@@QAEXH@Z
// partial score=0.26 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
	unsigned char en = (unsigned char)enable;
	if (en == m_tabState)
		return;

	GameWindow *second = m_windowB;
	if (second == NULL)
		return;
	if (m_windowA == NULL)
		return;

	m_tabState = en;
	if (!en)
	{
		TheWindowManager->clearTabList();
		return;
	}

	GameWindowList tabList;
	tabList.push_front(m_windowA);
	tabList.push_back(second);
	TheWindowManager->clearTabList();
	TheWindowManager->registerTabList(tabList);
	TheWindowManager->winSetFocus(m_windowA);
}
