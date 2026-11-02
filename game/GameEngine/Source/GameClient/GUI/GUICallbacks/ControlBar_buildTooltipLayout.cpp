// cl: /DNDEBUG /MD /EHsc

// ControlBar's build-tooltip layout guard that repopulates it. The teardown
// (deleteBuildTooltipLayout) lives with the other popup bodies in
// ControlBarPopupDescription.cpp, which owns the animate-manager file static.

typedef int Int;

class BfmeTooltipLayout
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void bfmeDestroy(Int alsoFree) = 0;		// slot 4, vtable+0x10
};

class BfmeTooltipWindow
{
public:
	virtual ~BfmeTooltipWindow();				// slot 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void repopulateBuildTooltipLayout(void);

	void doRepopulateBuildTooltipLayout(void);

private:
	char m_bfmeHeadA[0x278];
	BfmeTooltipLayout *m_bfmeLayout;			// +0x278
	bool m_bfmeShown;					// +0x27C
	char m_bfmeHeadB[0x2F4 - 0x280];
	BfmeTooltipWindow *m_bfmeWindow;			// +0x2F4
};

// ControlBar::repopulateBuildTooltipLayout, retail 0x004C1920. Both pointers
// have to be there, and then the work is tail-jumped to, so this function is
// only the guard.

// ?repopulateBuildTooltipLayout@ControlBar@@QAEXXZ
void ControlBar::repopulateBuildTooltipLayout(void)
{
	if (m_bfmeWindow == 0)
		return;

	if (m_bfmeLayout == 0)
		return;

	doRepopulateBuildTooltipLayout();
}
