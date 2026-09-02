// ?run@HideInGameChatShim@@SAXXZ
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// The HideInGameChat body behind the matched 5-byte ILT thunk
// (HideInGameChat.cpp -> HideInGameChatShim::run, pin 0x00512670).
//
// Park the pending entry text in the global UnicodeString that sits next to
// the chat-object pointer, fire the CloseChat movie event and mark the window
// closing; an idle window only records the close as pending.  Lives in its
// own TU so the ResetInGameChat tail call keeps a relocation and can resolve
// to the retail ILT 0x00033A6E.
#include "Common/UnicodeString.h"

class GameWindow;

UnicodeString GadgetTextEntryGetText(GameWindow *window);
void ResetInGameChat(void);

struct InGameChat
{
	unsigned char m_head[0x250];
	int m_movie;                   // +0x250
	unsigned char m_pad254[4];
	int m_slideState;              // +0x258: 3 closing, 4 close pending
	unsigned char m_pad25C[4];
	GameWindow *m_textEntry;       // +0x260

	void _bfme_reset();
};

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2, int unused1, int unused2, int unused3 );
};
extern WindowManager *g_theWindowManager;

class HideInGameChatShim
{
public:
	static void run();
};

// ?run@HideInGameChatShim@@SAXXZ
void HideInGameChatShim::run()
{
	InGameChat *chat = *(InGameChat **)0x012F4988;
	if (!chat)
		return;

	int state = chat->m_slideState;
	if (state == 3 || state == 4)
		return;

	if (state == 0)
	{
		chat->m_slideState = 4;
		return;
	}

	GameWindow *entry = chat->m_textEntry;
	if (entry)
		(*(UnicodeString *)0x012F498C).set( GadgetTextEntryGetText( chat->m_textEntry ) );
	else
		(*(UnicodeString *)0x012F498C).set( *(const UnicodeString *)0x01336E54 );

	g_theWindowManager->unidentified_00015235(
		(*(InGameChat **)0x012F4988)->m_movie, "CloseChat", 0,
		reinterpret_cast<const void *>( 0 ), reinterpret_cast<const void *>( 0 ),
		0, 0, 0 );
	InGameChat *closing = *(InGameChat **)0x012F4988;
	closing->m_slideState = 3;
	closing->_bfme_reset();
}

// NEAR MISS 234/242 (relocation slots excluded).  Two register-mirror regions
// remain against retail 0x00512670:
//   - m_textEntry load: retail keeps chat in ecx and loads the window into
//     eax (8b 81 / 85 c0 / push eax / lea ecx / push ecx); this toolchain
//     coalesces the dead chat pointer (8b 89 / 85 c9) and mirrors the pair.
//   - movie load: retail edx=chat / eax=movie / push eax; ours ecx/edx/push edx.
// The tail was cracked: retail reaches ResetInGameChat 0x00033A6E as a
// THISCALL member on the reloaded chat pointer (mov ecx,[0x12F4988] then
// c7 81 store then call) -- hence InGameChat::_bfme_reset below, which fixed
// the function length and the three early branch displacements.  Tried and
// failed for the mirrors: named/inline/double reads of m_textEntry and
// m_movie, hoisting the entry load, macro re-derefs (regresses to reloads),
// movie/tail locals.  Needs a shape that stops the ecx coalesce at the
// m_textEntry load; everything else including EH states is byte-exact.
