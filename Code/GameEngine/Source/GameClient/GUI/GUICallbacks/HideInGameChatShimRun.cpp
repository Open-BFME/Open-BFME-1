// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// ?run@HideInGameChatShim@@SAXXZ -- retail 0x00512670 (242 bytes), the
// HideInGameChat body: the matched ILT 0x00019583 (?HideInGameChat@@YAXXZ,
// HideInGameChat.cpp) jumps here through the HideInGameChatShim::run pin.
//
// An idle chat (state 0) only records a pending close (4); an open one parks
// the entry text in the global wide string, fires the CloseChat APT event and
// marks itself closing (3) before ResetInGameChat clears the entry.
//
// The chat pointer is a real extern, not an absolute-address cast: only a
// named global gives MSVC 7.1 retail's register choice at the +0x260 and
// +0x250 loads (eax/edx instead of the ecx mirror the cast produced).
#include "unicode_string.h"

class GameWindow;

UnicodeString GadgetTextEntryGetText(GameWindow *window);
void ResetInGameChat(void);

// Offsets only: the body proves no more than the three fields it touches.
class Rva005127A0InGameChat
{
public:
	unsigned char m_head[0x250];
	int dword_250;              // first argument of the APT event dispatcher
	unsigned char m_pad254[4];
	int dword_258;              // 0 idle, 3 closing, 4 close pending
	unsigned char m_pad25C[4];
	GameWindow *m_window260;    // text-entry gadget (GadgetTextEntryGetText)
};
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;   // 0x012F4988
extern UnicodeString g_unicode12F498C;                     // 0x012F498C

class WindowManager
{
public:
	void unidentified_00015235(int, const char *, int, const void *, const void *,
		const void *, const void *, const void *);
};
extern WindowManager *g_theWindowManager;                  // 0x012F19E8

class HideInGameChatShim
{
public:
	static void run();
};

void HideInGameChatShim::run()
{
	if (!g_Rva005127A0InGameChat)
		return;

	if (g_Rva005127A0InGameChat->dword_258 == 3 || g_Rva005127A0InGameChat->dword_258 == 4)
		return;

	if (g_Rva005127A0InGameChat->dword_258 == 0)
	{
		g_Rva005127A0InGameChat->dword_258 = 4;
		return;
	}

	if (g_Rva005127A0InGameChat->m_window260)
		g_unicode12F498C = GadgetTextEntryGetText(g_Rva005127A0InGameChat->m_window260);
	else
		g_unicode12F498C = *(const UnicodeString *)0x01336E54;   // UnicodeString::TheEmptyString

	g_theWindowManager->unidentified_00015235(g_Rva005127A0InGameChat->dword_250, "CloseChat", 0, 0, 0, 0, 0, 0);
	g_Rva005127A0InGameChat->dword_258 = 3;
	ResetInGameChat();
}
