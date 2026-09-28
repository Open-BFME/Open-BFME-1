// cl: /DNDEBUG /MD /EHsc

// ControlBar's build-tooltip layout: the guard that repopulates it, and the
// teardown that destroys it.
//
// They were two files, and each described the same ControlBar twice over. The
// teardown knew the pointer at +0x278 is a layout whose slot 4 destroys it, the
// byte at +0x27C is the shown flag, and the pointer at +0x2F4 is a window with a
// deleting destructor at slot 0. The guard, reading the SAME two pointers, called
// them m_unmodelled_278 and m_unmodelled_2F4 and typed them void *. Nothing was
// wrong in either file; the second one simply could not say what it was testing.

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

class Rva005929E0
{
public:
	void release(void);					// ILT 0x0003D294
};

class Glo012F4B98Type
{
public:
	char m_bfmeHead[0x488];
	Rva005929E0 m_bfmeSub;					// +0x488
};

class Glo012F368CType
{
public:
	virtual ~Glo012F368CType();				// slot 0
};

extern Glo012F4B98Type *Glo012F4B98;				// 0x012F4B98
extern Glo012F368CType *Glo012F368C;				// 0x012F368C

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void deleteBuildTooltipLayout(void);
	void repopulateBuildTooltipLayout(void);

	void doRepopulateBuildTooltipLayout(void);

private:
	char m_bfmeHeadA[0x278];
	BfmeTooltipLayout *m_bfmeLayout;			// +0x278
	bool m_bfmeShown;					// +0x27C
	char m_bfmeHeadB[0x2F4 - 0x280];
	BfmeTooltipWindow *m_bfmeWindow;			// +0x2F4
};

// Open-BFME5: ControlBar::deleteBuildTooltipLayout, retail 0x004C1450, 92
// bytes. The body carried only a machine byte-dump row; the symbols.csv pin
// names it.
//
// Four things happen, and which of them are deletes is readable from whether a
// null test guards them. The layout at +0x278 is called on slot 4 with a one
// and never tested, so that is an ordinary virtual call, not a delete. The
// window at +0x2F4 and the global at 0x012F368C are both tested first and then
// entered at slot 0 with a one, which is the deleting destructor -- both are
// deletes, and both pointers are cleared afterwards.
//
// Between them the global at 0x012F4B98, the one ?report@Glo012F4B98Type@@QAEXHM@Z
// is also called on, has the sub-object at +0x488 released when it is there.
//
// The byte at +0x27C is cleared before the first call, not after: it shares the
// zeroed register with the two pointer stores at the end, and the compiler
// keeps the store where the source puts it.

// ?deleteBuildTooltipLayout@ControlBar@@QAEXXZ
void ControlBar::deleteBuildTooltipLayout(void)
{
	m_bfmeShown = false;

	m_bfmeLayout->bfmeDestroy(1);

	delete m_bfmeWindow;
	m_bfmeWindow = 0;

	if (Glo012F4B98)
		Glo012F4B98->m_bfmeSub.release();

	delete Glo012F368C;
	Glo012F368C = 0;
}

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
