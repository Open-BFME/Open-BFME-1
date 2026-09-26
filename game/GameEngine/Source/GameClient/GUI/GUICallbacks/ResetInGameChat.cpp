// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/languagefilter /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Clear the in-game chat entry by assigning it a global empty string.
//
// The UnicodeString comes from the shim rather than a hand-rolled stand-in. It
// is passed by value, and the AsciiString flavour of that only came out in
// retail's order once the real StringBase-backed class was used; this is the
// same template with G rather than D.
//
// Arguments evaluate right to left, so the string temporary is built before the
// window is fetched -- which is why retail reloads the global after the copy
// constructor rather than reusing the pointer it already tested.
#include "Common/UnicodeString.h"

class GameWindow;

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

struct InGameChat
{
	unsigned char m_head[0x260];
	GameWindow *m_textEntry;
};

// ?ResetInGameChat@@YAXXZ
void ResetInGameChat(void)
{
	InGameChat *chat = *(InGameChat **)0x012F4988;

	if (!chat)
		return;

	if (!chat->m_textEntry)
		return;

	GadgetTextEntrySetText((*(InGameChat **)0x012F4988)->m_textEntry,
		*(const UnicodeString *)0x01336E54);
}
