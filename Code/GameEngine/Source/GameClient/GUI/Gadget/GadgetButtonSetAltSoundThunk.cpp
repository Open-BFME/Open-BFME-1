// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

// Two guards then one assignment. The EH frame exists for the by-value
// AsciiString parameter, which the callee destroys on the way out -- that is the
// releaseBuffer at the end, and the state store going to -1 just before it.
//
// The user-data pointer is fetched once and its member at +0x1c assigned, so
// the accessor call stays inside the guard rather than being hoisted.
#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);
};

class ButtonData
{
public:
	unsigned char m_head[0x1c];
	AsciiString m_altSound;					///< 0x1c
};

// ?GadgetButtonSetAltSound@@YAXPAVGameWindow@@VAsciiString@@@Z
void GadgetButtonSetAltSound( GameWindow *window, AsciiString sound )
{
	if (!window)
		return;

	ButtonData *data = (ButtonData *)window->winGetUserData();
	if (!data)
		return;

	data->m_altSound = sound;
}
