// ?d_00793260@@YAXXZ
// partial score=0.35 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DGadgetProgressBarDraw, retail 0x00793260 (553 bytes).
//
// This is the standard (non-image) ProgressBar body from the real
// W3DProgressBar.cpp.  BFME's WinDrawData arrays are four bytes later than the
// vendored Zero Hour slice used by the normal headers, so this TU keeps the
// BFME ABI view local: enabled/disabled/hilite bases are +0x48/+0xB4/+0x120,
// with { image, color, borderColor } entries and the bar data at index 4.
// Retail's reads at +0x4C/+0x50, +0xB8/+0xBC, +0x124/+0x128, and the bar
// entries at +0x7C/+0x80, +0xE8/+0xEC, +0x154/+0x158 establish that layout.
//
// The manager's three rectangle/line calls are also kept in the local ABI
// slice.  Their slots are +0xF8, +0xFC, and +0x100 in the BFME vtable.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef int Color;

class Image;

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATE_HILITED = 0x00000002 };
enum { WIN_COLOR_UNDEFINED = 0x00FFFFFF };

struct ICoord2D
{
	Int x;
	Int y;
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class WinInstanceData
{
public:
	virtual ~WinInstanceData(void);
	UnsignedInt getState(void) { return m_state; }

	Int m_id;
	UnsignedInt m_state;
	UnsignedInt m_style;
	UnsignedInt m_status;
	void *m_owner;
	WinDrawData m_enabledDrawData[9];
	WinDrawData m_disabledDrawData[9];
	WinDrawData m_hiliteDrawData[9];
};

class GameWindow
{
public:
	virtual void winDrawBorder(void) = 0;
	void *winGetUserData(void);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);

	Color winGetEnabledColor(Int index) { return m_instData.m_enabledDrawData[index].color; }
	Color winGetEnabledBorderColor(Int index) { return m_instData.m_enabledDrawData[index].borderColor; }
	Color winGetDisabledColor(Int index) { return m_instData.m_disabledDrawData[index].color; }
	Color winGetDisabledBorderColor(Int index) { return m_instData.m_disabledDrawData[index].borderColor; }
	Color winGetHiliteColor(Int index) { return m_instData.m_hiliteDrawData[index].color; }
	Color winGetHiliteBorderColor(Int index) { return m_instData.m_hiliteDrawData[index].borderColor; }

private:
	unsigned char m_unreconstructed_00[0x2c];
	WinInstanceData m_instData;
};

#define BFME_WINDOW_MANAGER_SLOT(n) virtual void unused##n(void);
class GameWindowManager
{
public:
	BFME_WINDOW_MANAGER_SLOT(00) BFME_WINDOW_MANAGER_SLOT(01) BFME_WINDOW_MANAGER_SLOT(02)
	BFME_WINDOW_MANAGER_SLOT(03) BFME_WINDOW_MANAGER_SLOT(04) BFME_WINDOW_MANAGER_SLOT(05)
	BFME_WINDOW_MANAGER_SLOT(06) BFME_WINDOW_MANAGER_SLOT(07) BFME_WINDOW_MANAGER_SLOT(08)
	BFME_WINDOW_MANAGER_SLOT(09) BFME_WINDOW_MANAGER_SLOT(10) BFME_WINDOW_MANAGER_SLOT(11)
	BFME_WINDOW_MANAGER_SLOT(12) BFME_WINDOW_MANAGER_SLOT(13) BFME_WINDOW_MANAGER_SLOT(14)
	BFME_WINDOW_MANAGER_SLOT(15) BFME_WINDOW_MANAGER_SLOT(16) BFME_WINDOW_MANAGER_SLOT(17)
	BFME_WINDOW_MANAGER_SLOT(18) BFME_WINDOW_MANAGER_SLOT(19) BFME_WINDOW_MANAGER_SLOT(20)
	BFME_WINDOW_MANAGER_SLOT(21) BFME_WINDOW_MANAGER_SLOT(22) BFME_WINDOW_MANAGER_SLOT(23)
	BFME_WINDOW_MANAGER_SLOT(24) BFME_WINDOW_MANAGER_SLOT(25) BFME_WINDOW_MANAGER_SLOT(26)
	BFME_WINDOW_MANAGER_SLOT(27) BFME_WINDOW_MANAGER_SLOT(28) BFME_WINDOW_MANAGER_SLOT(29)
	BFME_WINDOW_MANAGER_SLOT(30) BFME_WINDOW_MANAGER_SLOT(31) BFME_WINDOW_MANAGER_SLOT(32)
	BFME_WINDOW_MANAGER_SLOT(33) BFME_WINDOW_MANAGER_SLOT(34) BFME_WINDOW_MANAGER_SLOT(35)
	BFME_WINDOW_MANAGER_SLOT(36) BFME_WINDOW_MANAGER_SLOT(37) BFME_WINDOW_MANAGER_SLOT(38)
	BFME_WINDOW_MANAGER_SLOT(39) BFME_WINDOW_MANAGER_SLOT(40) BFME_WINDOW_MANAGER_SLOT(41)
	BFME_WINDOW_MANAGER_SLOT(42) BFME_WINDOW_MANAGER_SLOT(43) BFME_WINDOW_MANAGER_SLOT(44)
	BFME_WINDOW_MANAGER_SLOT(45) BFME_WINDOW_MANAGER_SLOT(46) BFME_WINDOW_MANAGER_SLOT(47)
	BFME_WINDOW_MANAGER_SLOT(48) BFME_WINDOW_MANAGER_SLOT(49) BFME_WINDOW_MANAGER_SLOT(50)
	BFME_WINDOW_MANAGER_SLOT(51) BFME_WINDOW_MANAGER_SLOT(52) BFME_WINDOW_MANAGER_SLOT(53)
	BFME_WINDOW_MANAGER_SLOT(54) BFME_WINDOW_MANAGER_SLOT(55) BFME_WINDOW_MANAGER_SLOT(56)
	BFME_WINDOW_MANAGER_SLOT(57) BFME_WINDOW_MANAGER_SLOT(58) BFME_WINDOW_MANAGER_SLOT(59)
	BFME_WINDOW_MANAGER_SLOT(60) BFME_WINDOW_MANAGER_SLOT(61)

	virtual void winFillRect(Color color, Real width,
									 Int startX, Int startY, Int endX, Int endY);
	virtual void winOpenRect(Color color, Real width,
									 Int startX, Int startY, Int endX, Int endY);
	virtual void winDrawLine(Color color, Real width,
									 Int startX, Int startY, Int endX, Int endY);
};
#undef BFME_WINDOW_MANAGER_SLOT

extern GameWindowManager *TheWindowManager;

#define FALSE 0
#define BitTest(bits, mask) (((bits) & (mask)) != 0)

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green,
												 UnsignedByte blue, UnsignedByte alpha)
{
	return ((Color)alpha << 24) | ((Color)red << 16) |
			((Color)green << 8) | (Color)blue;
}

#define WIN_DRAW_LINE_WIDTH 1.0f

inline Color GadgetProgressBarGetEnabledColor(GameWindow *g) { return g->winGetEnabledColor(0); }
inline Color GadgetProgressBarGetEnabledBorderColor(GameWindow *g) { return g->winGetEnabledBorderColor(0); }
inline Color GadgetProgressBarGetEnabledBarColor(GameWindow *g) { return g->winGetEnabledColor(4); }
inline Color GadgetProgressBarGetEnabledBarBorderColor(GameWindow *g) { return g->winGetEnabledBorderColor(4); }
inline Color GadgetProgressBarGetDisabledColor(GameWindow *g) { return g->winGetDisabledColor(0); }
inline Color GadgetProgressBarGetDisabledBorderColor(GameWindow *g) { return g->winGetDisabledBorderColor(0); }
inline Color GadgetProgressBarGetDisabledBarColor(GameWindow *g) { return g->winGetDisabledColor(4); }
inline Color GadgetProgressBarGetDisabledBarBorderColor(GameWindow *g) { return g->winGetDisabledBorderColor(4); }
inline Color GadgetProgressBarGetHiliteColor(GameWindow *g) { return g->winGetHiliteColor(0); }
inline Color GadgetProgressBarGetHiliteBorderColor(GameWindow *g) { return g->winGetHiliteBorderColor(0); }
inline Color GadgetProgressBarGetHiliteBarColor(GameWindow *g) { return g->winGetHiliteColor(4); }
inline Color GadgetProgressBarGetHiliteBarBorderColor(GameWindow *g) { return g->winGetHiliteBorderColor(4); }

// ?W3DGadgetProgressBarDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetProgressBarDraw(GameWindow *window, WinInstanceData *instData)
{
	ICoord2D origin, size, start, end;
	Color backColor, backBorder, barColor, barBorder;
	Int progress = (Int)window->winGetUserData();

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == FALSE)
	{
		backColor = GadgetProgressBarGetDisabledColor(window);
		backBorder = GadgetProgressBarGetDisabledBorderColor(window);
		barColor = GadgetProgressBarGetDisabledBarColor(window);
		barBorder = GadgetProgressBarGetDisabledBarBorderColor(window);
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		backColor = GadgetProgressBarGetHiliteColor(window);
		backBorder = GadgetProgressBarGetHiliteBorderColor(window);
		barColor = GadgetProgressBarGetHiliteBarColor(window);
		barBorder = GadgetProgressBarGetHiliteBarBorderColor(window);
	}
	else
	{
		backColor = GadgetProgressBarGetEnabledColor(window);
		backBorder = GadgetProgressBarGetEnabledBorderColor(window);
		barColor = GadgetProgressBarGetEnabledBarColor(window);
		barBorder = GadgetProgressBarGetEnabledBarBorderColor(window);
	}

	if (backBorder != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect(backBorder, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
	}

	if (backColor != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect(backColor, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
	}

	if (progress)
	{
		if (barBorder != WIN_COLOR_UNDEFINED)
		{
			start.x = origin.x;
			start.y = origin.y;
			end.x = start.x + (size.x * progress) / 100;
			end.y = start.y + size.y;
			if (end.x - start.x > 1)
			{
				TheWindowManager->winOpenRect(barBorder, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
			}
		}

		if (barColor != WIN_COLOR_UNDEFINED)
		{
			start.x = origin.x + 1;
			start.y = origin.y + 1;
			end.x = start.x + (size.x * progress) / 100 - 2;
			end.y = start.y + size.y - 2;
			if (end.x - start.x > 1)
			{
				TheWindowManager->winFillRect(barColor, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
				TheWindowManager->winDrawLine(GameMakeColor(255, 255, 255, 255),
					WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, start.y);
				TheWindowManager->winDrawLine(GameMakeColor(200, 200, 200, 255),
					WIN_DRAW_LINE_WIDTH, start.x, start.y, start.x, end.y);
			}
		}
	}
}
