// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GameSpyCloseOverlay, retail 0x00627AD0, 90 bytes.
//
// The reference's body with its per-overlay logging compiled out, which leaves
// one arm of the switch standing: the options overlay, and only when it is
// actually open, signals the shell script hook on the way down. The rest is
// the shared teardown -- run the layout's shutdown, destroy its windows,
// delete it, and clear the slot.
//
// overlayLayouts is the array at 0x012F70B4 and the options overlay is index
// 8, which is the 0x012F70D4 the first test reads directly. The layout's
// runShutdown is vtable+0x0C and takes the reference's defaulted argument;
// destroyWindows is +0x20, the same slot InGameUI_clearPopupMessageData.cpp
// pinned; and the delete is the scalar deleting destructor at slot 1.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum GSOverlayType
{
	GSOVERLAY_PLAYERINFO = 0,
	GSOVERLAY_MAPSELECT,
	GSOVERLAY_BUDDY,
	GSOVERLAY_PAGE,
	GSOVERLAY_GAMEOPTIONS,
	GSOVERLAY_GAMEPASSWORD,
	GSOVERLAY_LADDERSELECT,
	GSOVERLAY_BFME_SEVEN,
	GSOVERLAY_OPTIONS,
	GSOVERLAY_MAX
};

enum { SHELL_SCRIPT_HOOK_OPTIONS_CLOSED = 0x16 };

void SignalUIInteraction(Int hook);				// ILT 0x000348DD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void slot0() = 0;
	virtual ~WindowLayout();				// slot 1, vtable+0x04
	virtual void slot2() = 0;
	virtual void runShutdown(void *userData = 0) = 0;	// slot 3, vtable+0x0C
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void destroyWindows(void) = 0;			// slot 8, vtable+0x20
};

extern WindowLayout *overlayLayouts[GSOVERLAY_MAX];		// 0x012F70B4

void GameSpyCloseOverlay( GSOverlayType overlay )
{
	switch(overlay)
	{
		case GSOVERLAY_OPTIONS:
			if( overlayLayouts[overlay] )
			{
				SignalUIInteraction(SHELL_SCRIPT_HOOK_OPTIONS_CLOSED);
			}
			break;
	}
	if( overlayLayouts[overlay] )
	{
		overlayLayouts[overlay]->runShutdown();
		overlayLayouts[overlay]->destroyWindows();
		delete overlayLayouts[overlay];
		overlayLayouts[overlay] = 0;
	}
}
