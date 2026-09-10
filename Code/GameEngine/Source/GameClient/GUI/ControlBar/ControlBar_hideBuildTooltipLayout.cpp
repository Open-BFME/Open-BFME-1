// cl: /DNDEBUG /MD /EHsc

// The source definition and the identical inlined branch in the verified
// popup update callback establish this ControlBar method. See
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameClient/GUI/GUICallbacks/ControlBarPopupDescription.cpp.
//
// BFME stores the callback's AnimateWindowManager pointer in the global slot
// presently ledgered as Glo012F368C.  Its reversed byte is at +0x11.  The
// animation switch is g_bfmeReadyPT, while GlobalData::m_animateWindows is at
// +0xBC4 in this executable.  These views are TU-local so no shared header is
// changed.

typedef bool Bool;

class Glo012F368CType
{
};

extern Glo012F368CType *Glo012F368C;                         // 0x012F368C
extern Bool g_bfmeReadyPT;                                   // 0x012F3690

class GlobalData
{
private:
	char m_bfmeHead[0xBC4];

public:
	Bool m_animateWindows;
};

extern GlobalData *TheWritableGlobalData;                    // 0x012ED5C8

class BfmeAnimateWindowManager
{
public:
	Bool isReversed(void) const
	{
		return *(const Bool *)((const char *)this + 0x11);
	}

	void reverseAnimateWindow(void);                            // ILT 0x00027B65
};

class ControlBar
{
public:
	void hideBuildTooltipLayout(void);
	void deleteBuildTooltipLayout(void);                        // ILT 0x00027336
};

// ?hideBuildTooltipLayout@ControlBar@@QAEXXZ
void ControlBar::hideBuildTooltipLayout(void)
{
	BfmeAnimateWindowManager *manager =
		reinterpret_cast<BfmeAnimateWindowManager *>(Glo012F368C);
	if (manager && manager->isReversed())
		return;
	if (g_bfmeReadyPT && manager && TheWritableGlobalData->m_animateWindows)
		manager->reverseAnimateWindow();
	else
		deleteBuildTooltipLayout();
}
