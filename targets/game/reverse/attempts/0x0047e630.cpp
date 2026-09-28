// ?winProcessMouseEvent@GameWindowManager@@UAE?AW4WinInputReturnCode@@W4GameWindowMessage@@PAUICoord2D@@PAX@Z
// partial score=0.966 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// GameWindowManager::winProcessMouseEvent, retail 0x0047E630, 1569 bytes
// (the extent includes the switch's jump and index tables).
//
// Identity: GameWindowManager vtable slot 41 via ILT 0x00001136 (prior
// verdicts), and the body is Zero Hour's GameWindowManager.cpp
// winProcessMouseEvent with BFME's changes: one pass over the window list
// that keeps the first plain and first BELOW candidate and stops at the
// first ABOVE window, filtered on a GameWindow +0x1F4 value that must equal
// the manager's +0x38 (m_captureFlags by the matched constructor's layout); a GWM_MOUSE_POS case for the grab window; and the
// tooltip callback reached through two GameWindow virtuals (slot 9 tests
// the +0x1EC callback, slot 4 runs it; retail 0x004653C0 and 0x004655B0).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef float Real;
typedef bool Bool;

#define TRUE 1
#define FALSE 0
#define NULL 0

template <typename T>
class StringBase
{
    friend class UnicodeString;

private:
    StringBase(void) : m_data(0) {}
    StringBase(const StringBase<T> &other);
    ~StringBase(void);

    void *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString(void) : StringBase<WideChar>() {}
    UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
    ~UnicodeString(void) {}

    static UnicodeString TheEmptyString;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, Int tooltipDelay = -1,
		const RGBColor *color = 0, Real width = 1.0f);
};

extern Mouse *TheMouse;

class Display
{
public:
	virtual void vfn00(void) = 0;
	virtual void vfn01(void) = 0;
	virtual void vfn02(void) = 0;
	virtual void vfn03(void) = 0;
	virtual void vfn04(void) = 0;
	virtual void vfn05(void) = 0;
	virtual void vfn06(void) = 0;
	virtual void vfn07(void) = 0;
	virtual void vfn08(void) = 0;
	virtual void vfn09(void) = 0;
	virtual void vfn10(void) = 0;
	virtual UnsignedInt getWidth(void) = 0;
	virtual UnsignedInt getHeight(void) = 0;
};

extern Display *TheDisplay;

class DisplayString
{
public:
	virtual void vfn00(void) = 0;
	virtual void vfn01(void) = 0;
	virtual void vfn02(void) = 0;
	virtual Int getTextLength(void) = 0;
};

enum WinInputReturnCode
{
	WIN_INPUT_NOT_USED = 0,
	WIN_INPUT_USED = 1
};

enum WindowMsgHandledType
{
	MSG_IGNORED = 0,
	MSG_HANDLED = 1
};

enum GameWindowMessage
{
	GWM_NONE = 0,
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_LEFT_DRAG = 8,
	GWM_MIDDLE_UP = 10,
	GWM_RIGHT_UP = 14,
	GWM_MOUSE_ENTERING = 17,
	GWM_MOUSE_LEAVING = 18,
	GWM_MOUSE_POS = 24
};

enum
{
	WIN_STATUS_ACTIVE = 0x00000001,
	WIN_STATUS_DRAGABLE = 0x00000004,
	WIN_STATUS_HIDDEN = 0x00000010,
	WIN_STATUS_ABOVE = 0x00000020,
	WIN_STATUS_BELOW = 0x00000040,
	WIN_STATUS_NO_INPUT = 0x00000200,
	GWS_COMBO_BOX = 0x00008000
};

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitClear(x, i) ((x) &= ~(i))
#define SHORTTOLONG(a, b) ((UnsignedShort)(a) | ((UnsignedShort)(b) << 16))

class WinInstanceData
{
public:
	UnsignedInt getStyle(void) { return m_style; }
	Int getTooltipTextLength(void)
	{
		if (m_tooltip)
			return m_tooltip->getTextLength();
		return 0;
	}
	UnicodeString getTooltipText(void);

	UnsignedByte m_bfmeHead[0x0c];
	UnsignedInt m_style;
	UnsignedByte m_bfmeBody[0x198 - 0x10];
	Int m_tooltipDelay;
	UnsignedByte m_bfmeText[0x1a0 - 0x19c];
	DisplayString *m_tooltip;
};

class GameWindow
{
public:
	virtual void vfn00(void) = 0;
	virtual void vfn01(void) = 0;
	virtual void vfn02(void) = 0;
	virtual void vfn03(void) = 0;
	virtual Int vfn04(WinInstanceData *data, UnsignedInt mouse) = 0;
	virtual void vfn05(void) = 0;
	virtual void vfn06(void) = 0;
	virtual void vfn07(void) = 0;
	virtual void vfn08(void) = 0;
	virtual Bool vfn09(void) = 0;

	GameWindow *winPointInChild(Int x, Int y, Bool ignoreEnableCheck = FALSE,
		Bool playDisabledSound = FALSE);
	GameWindow *winPointInAnyChild(Int x, Int y, Bool ignoreHidden,
		Bool ignoreEnableCheck = FALSE);
	Bool winPointInWindow(Int x, Int y);
	GameWindow *winGetParent(void);
	Bool winIsChild(GameWindow *child);
	Int winGetPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	Int winSetPosition(Int x, Int y);
	WinInstanceData *winGetInstanceData(void);

	UnsignedByte m_bfme04[0x08 - 0x04];
	Int m_status;
	ICoord2D m_size;
	IRegion2D m_region;
	UnsignedByte m_bfme24[0x30 - 0x24];
	WinInstanceData m_instData;
	UnsignedByte m_bfme1D4[0x1f4 - 0x1d4];
	UnsignedInt m_callbackExtra2;
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
};

struct ModalWindow
{
	ModalWindow *next;
	GameWindow *window;
};

extern Bool sendMousePosMessages;

class GameWindowManager
{
public:
#define GWM_SLOT(n) virtual void vfn##n(void)
	GWM_SLOT(00); GWM_SLOT(01); GWM_SLOT(02); GWM_SLOT(03); GWM_SLOT(04);
	GWM_SLOT(05); GWM_SLOT(06); GWM_SLOT(07); GWM_SLOT(08); GWM_SLOT(09);
	GWM_SLOT(10); GWM_SLOT(11); GWM_SLOT(12); GWM_SLOT(13); GWM_SLOT(14);
	GWM_SLOT(15); GWM_SLOT(16); GWM_SLOT(17); GWM_SLOT(18); GWM_SLOT(19);
	GWM_SLOT(20); GWM_SLOT(21); GWM_SLOT(22); GWM_SLOT(23); GWM_SLOT(24);
	GWM_SLOT(25); GWM_SLOT(26); GWM_SLOT(27); GWM_SLOT(28); GWM_SLOT(29);
	GWM_SLOT(30); GWM_SLOT(31); GWM_SLOT(32); GWM_SLOT(33); GWM_SLOT(34);
	GWM_SLOT(35); GWM_SLOT(36); GWM_SLOT(37); GWM_SLOT(38); GWM_SLOT(39);
	GWM_SLOT(40);
	virtual WinInputReturnCode winProcessMouseEvent(GameWindowMessage msg,
		ICoord2D *mousePos, void *data);
	GWM_SLOT(42); GWM_SLOT(43); GWM_SLOT(44); GWM_SLOT(45); GWM_SLOT(46);
	virtual void winSetLoneWindow(GameWindow *window);
	GWM_SLOT(48); GWM_SLOT(49);
	virtual Bool isHidden(GameWindow *window);
	GWM_SLOT(51); GWM_SLOT(52); GWM_SLOT(53);
	virtual WindowMsgHandledType winSendInputMsg(GameWindow *window,
		UnsignedInt msg, UnsignedInt mData1, UnsignedInt mData2);
#undef GWM_SLOT

protected:
	UnsignedByte m_base[0x08 - 0x04];
	GameWindow *m_windowList;
	GameWindow *m_windowTail;
	GameWindow *m_destroyList;
	GameWindow *m_currMouseRgn;
	GameWindow *m_mouseCaptor;
	GameWindow *m_keyboardFocus;
	ModalWindow *m_modalHead;
	GameWindow *m_grabWindow;
	GameWindow *m_loneWindow;
	UnsignedByte m_tail[0x34 - 0x2c];
	const void *m_cursorBitmap;
	UnsignedInt m_captureFlags;	// +0x38, as the matched GameWindowManager ctor places it
};

// ?winProcessMouseEvent@GameWindowManager@@UAE?AW4WinInputReturnCode@@W4GameWindowMessage@@PAUICoord2D@@PAX@Z
WinInputReturnCode GameWindowManager::winProcessMouseEvent(GameWindowMessage msg,
	ICoord2D *mousePos, void *data)
{
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;
	UnsignedInt packedMouseCoords;
	GameWindow *window = NULL;
	GameWindow *toolTipWindow = NULL;
	Bool clearGrabWindow = FALSE;
	Bool objectTooltip = FALSE;

	packedMouseCoords = SHORTTOLONG(mousePos->x, mousePos->y);

	TheMouse->setCursorTooltip(UnicodeString::TheEmptyString);

	if (m_mouseCaptor)
	{
		m_grabWindow = NULL;
		window = m_mouseCaptor->winPointInChild(mousePos->x, mousePos->y);

		if (sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS)
		{
			GameWindow *win = window;

			if (win)
			{
				while (win != NULL)
				{
					if (winSendInputMsg(win, msg, packedMouseCoords, 0) == MSG_HANDLED)
					{
						returnCode = WIN_INPUT_USED;
						break;
					}

					if (win == m_mouseCaptor)
						break;

					win = win->winGetParent();
				}
			}
			else
			{
				if (winSendInputMsg(m_mouseCaptor, msg, packedMouseCoords, 0) == MSG_HANDLED)
					returnCode = WIN_INPUT_USED;
			}
		}
	}
	else
	{
		if (m_grabWindow)
		{
			GameWindow *parent;

			switch (msg)
			{
				case GWM_MOUSE_POS:
				{
					if (sendMousePosMessages &&
						m_grabWindow->winPointInWindow(mousePos->x, mousePos->y))
						winSendInputMsg(m_grabWindow, GWM_MOUSE_POS, packedMouseCoords, 0);
					break;
				}

				case GWM_LEFT_UP:
				{
					m_grabWindow->winPointInChild(mousePos->x, mousePos->y, FALSE, TRUE);

					BitClear(m_grabWindow->m_status, WIN_STATUS_ACTIVE);
					if (m_grabWindow->winPointInWindow(mousePos->x, mousePos->y))
						winSendInputMsg(m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0);
					else if (BitTest(m_grabWindow->m_status, WIN_STATUS_DRAGABLE))
						winSendInputMsg(m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0);

					clearGrabWindow = TRUE;
					break;
				}

				case GWM_NONE:
				case GWM_LEFT_DRAG:
				{
					if (BitTest(m_grabWindow->m_status, WIN_STATUS_DRAGABLE))
					{
						ICoord2D *mouseDelta = (ICoord2D *)data;
						Int dx = mouseDelta->x;
						Int dy = mouseDelta->y;

						if (m_grabWindow->winGetParent())
						{
							parent = m_grabWindow->winGetParent();

							if (m_grabWindow->m_region.lo.x + dx < 0)
								dx = 0 - m_grabWindow->m_region.lo.x;
							else if (m_grabWindow->m_region.hi.x + dx > parent->m_size.x)
								dx = parent->m_size.x - m_grabWindow->m_region.hi.x;

							if (m_grabWindow->m_region.lo.y + dy < 0)
								dy = 0 - m_grabWindow->m_region.lo.y;
							else if (m_grabWindow->m_region.hi.y + dy > parent->m_size.y)
								dy = parent->m_size.y - m_grabWindow->m_region.hi.y;
						}

						IRegion2D newRegion;
						ICoord2D grabSize;

						m_grabWindow->winGetPosition(&newRegion.lo.x, &newRegion.lo.y);
						m_grabWindow->winGetSize(&grabSize.x, &grabSize.y);

						newRegion.lo.x += dx;
						newRegion.lo.y += dy;

						if (newRegion.lo.x < 0)
							newRegion.lo.x = 0;
						if (newRegion.lo.y < 0)
							newRegion.lo.y = 0;

						newRegion.hi.x = newRegion.lo.x + grabSize.x;
						newRegion.hi.y = newRegion.lo.y + grabSize.y;

						if (newRegion.hi.x > (Int)TheDisplay->getWidth())
							newRegion.hi.x = (Int)TheDisplay->getWidth();
						if (newRegion.hi.y > (Int)TheDisplay->getHeight())
							newRegion.hi.y = (Int)TheDisplay->getHeight();

						newRegion.lo.x = newRegion.hi.x - grabSize.x;
						newRegion.lo.y = newRegion.hi.y - grabSize.y;

						m_grabWindow->winSetPosition(newRegion.lo.x, newRegion.lo.y);
					}

					winSendInputMsg(m_grabWindow, msg, packedMouseCoords, 0);
					break;
				}
			}

			returnCode = WIN_INPUT_USED;
		}
		else
		{
			if (m_modalHead && m_modalHead->window)
			{
				window = m_modalHead->window->winPointInChild(mousePos->x, mousePos->y);
			}
			else
			{
				GameWindow *normalWindow = NULL;
				GameWindow *belowWindow = NULL;

				for (window = m_windowList; window; window = window->m_next)
				{
					if (BitTest(window->m_status, WIN_STATUS_HIDDEN))
						continue;
					if (window->m_callbackExtra2 != m_captureFlags)
						continue;
					if (mousePos->x < window->m_region.lo.x ||
						mousePos->x > window->m_region.hi.x ||
						mousePos->y < window->m_region.lo.y ||
						mousePos->y > window->m_region.hi.y)
						continue;

					if (BitTest(window->m_status, WIN_STATUS_ABOVE))
						break;

					if (BitTest(window->m_status, WIN_STATUS_BELOW))
					{
						if (belowWindow == NULL)
							belowWindow = window;
					}
					else if (normalWindow == NULL)
					{
						normalWindow = window;
					}
				}

				if (window == NULL)
				{
					if (normalWindow)
						window = normalWindow;
					else
						window = belowWindow;
				}

				if (window)
				{
					GameWindow *childWindow =
						window->winPointInAnyChild(mousePos->x, mousePos->y, TRUE, TRUE);
					if (childWindow->vfn09() ||
						childWindow->m_instData.getTooltipTextLength())
						toolTipWindow = childWindow;

					window = window->winPointInChild(mousePos->x, mousePos->y);
				}
			}

			if (window)
				if (BitTest(window->m_status, WIN_STATUS_NO_INPUT))
				{
					if (window->winGetParent() &&
						BitTest(window->winGetParent()->winGetInstanceData()->getStyle(),
							GWS_COMBO_BOX))
						window = window->winGetParent();
					else
						window = NULL;
				}

			if (window)
			{
				if (sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS)
				{
					GameWindow *tempWin = window;
					GameWindow *oldLoneWindow = m_loneWindow;

					while (winSendInputMsg(tempWin, msg, packedMouseCoords, 0) == MSG_IGNORED)
					{
						tempWin = tempWin->m_parent;
						if (tempWin == NULL)
							break;
					}

					if (m_loneWindow && m_loneWindow == oldLoneWindow &&
						(msg == GWM_LEFT_UP || msg == GWM_MIDDLE_UP ||
						 msg == GWM_RIGHT_UP || tempWin))
					{
						if (!m_loneWindow->winIsChild(tempWin))
							winSetLoneWindow(NULL);
					}

					if (tempWin)
					{
						if (msg == GWM_LEFT_DOWN)
							m_grabWindow = tempWin;

						returnCode = WIN_INPUT_USED;
					}
				}
			}

			if (toolTipWindow == NULL)
			{
				if (isHidden(window) == FALSE)
					toolTipWindow = window;
			}

			Bool tooltipsOn = TRUE;
			if (tooltipsOn)
			{
				if (toolTipWindow)
				{
					if (toolTipWindow->vfn09())
						toolTipWindow->vfn04(&toolTipWindow->m_instData, packedMouseCoords);
					else if (toolTipWindow->m_instData.getTooltipTextLength())
						TheMouse->setCursorTooltip(toolTipWindow->m_instData.getTooltipText(),
							toolTipWindow->m_instData.m_tooltipDelay);
				}
				else
				{
					objectTooltip = TRUE;
				}
			}
		}
	}

	if ((m_grabWindow == NULL) && (window != m_currMouseRgn))
	{
		if (m_mouseCaptor)
		{
			if (m_mouseCaptor->winIsChild(m_currMouseRgn))
				winSendInputMsg(m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0);
		}
		else if (m_currMouseRgn)
			winSendInputMsg(m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0);

		if (window)
			winSendInputMsg(window, GWM_MOUSE_ENTERING, packedMouseCoords, 0);

		m_currMouseRgn = window;
	}

	if (clearGrabWindow == TRUE)
	{
		m_grabWindow = NULL;
		clearGrabWindow = FALSE;
	}

	return returnCode;
}
