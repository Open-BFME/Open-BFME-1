// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?resetIdleWorker@InGameUI@@EAEXXZ: Code/GameEngine/Source/GameClient/InGameUI.cpp

// Blank the idle-worker caption if the window exists, reset the index, then
// clear thirty-two lists.
//
// Each list is one pointer wide -- retail walks the array four bytes at a time --
// and its nodes are twelve bytes with no destructor call, so the element is a
// four-byte POD sitting behind the eight-byte node header.
//
// The UnicodeString is the shim's; it is passed by value and only the real
// StringBase-backed class puts the temporary together in retail's order.
#include "Common/UnicodeString.h"

#include <list>

typedef int Int;

class GameWindow;

void GadgetRadioSetText(GameWindow *window, UnicodeString text);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual ~InGameUI();

private:
	virtual void resetIdleWorker(void);

	unsigned char m_head[0x131C - 4];
	std::list<void *> m_idleWorkerLists[32];
	GameWindow *m_idleWorkerWin;
	Int m_currentIdleWorker;
};

// ?resetIdleWorker@InGameUI@@EAEXXZ
void InGameUI::resetIdleWorker(void)
{
	if (m_idleWorkerWin)
		GadgetRadioSetText(m_idleWorkerWin, *(const UnicodeString *)0x01336E54);

	m_currentIdleWorker = -1;

	for (Int i = 0; i < 32; i++)
		m_idleWorkerLists[i].clear();
}
