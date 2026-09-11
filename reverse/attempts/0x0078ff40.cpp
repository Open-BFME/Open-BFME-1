// ?W3DGadgetCheckBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.996 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME-local reconstruction of W3DGadgetCheckBoxDraw, retail 0x0078FF40.
// The draw-data arrays belong to GameWindow and are witnessed at +0x48,
// +0xB4, and +0x120, with twelve-byte { image, color, borderColor } entries.
// The file-static text helper is kept in this TU because retail gives it the
// private register convention selected by MSVC once its caller is visible.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;

class Image;
class GameFont;

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATE_HILITED = 0x00000002 };
enum { WIN_STATE_SELECTED = 0x00000004 };
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

// BFME's DisplayString vtable has the colour setter at +0x28 and the
// four-integer draw at +0x38.  The unreferenced slots are intentional: they
// preserve those witnessed offsets without importing ZH's pool-glue base.
class DisplayString
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual Int getTextLength();
	virtual void unused04();
	virtual void unused05();
	virtual void setFont(GameFont *font);
	virtual GameFont *getFont();
	virtual void setWordWrap(Int wordWrap);
	virtual void setWordWrapCentered(unsigned char centered);
	virtual void setTextColor(Color color, Color dropColor);
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw(Int x, Int y, Color color, Color dropColor);
	virtual void getSize(Int *width, Int *height);
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void setUseHotkey(unsigned char use, Color color);
	virtual void setClipRegion(void *region);
};

// The BFME offsets are kept in the mirror rather than changing the vendored
// GameWindow header.  The non-virtual accessors inline exactly as the gadget
// header accessors do, but against the retail array bases.
class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus();
	Int winGetEnabledTextColor();
	Int winGetEnabledTextBorderColor();
	Int winGetDisabledTextColor();
	Int winGetDisabledTextBorderColor();
	Int winGetHiliteTextColor();
	Int winGetHiliteTextBorderColor();
	GameFont *winGetFont();

	Color winGetEnabledColor(Int index)
	{
		return m_enabledDrawData[index].color;
	}

	Color winGetEnabledBorderColor(Int index)
	{
		return m_enabledDrawData[index].borderColor;
	}

	Color winGetDisabledColor(Int index)
	{
		return m_disabledDrawData[index].color;
	}

	Color winGetDisabledBorderColor(Int index)
	{
		return m_disabledDrawData[index].borderColor;
	}

	Color winGetHiliteColor(Int index)
	{
		return m_hiliteDrawData[index].color;
	}

	Color winGetHiliteBorderColor(Int index)
	{
		return m_hiliteDrawData[index].borderColor;
	}

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];
	WinDrawData m_disabledDrawData[9];
	WinDrawData m_hiliteDrawData[9];
};

class WinInstanceData
{
public:
	UnsignedInt getState()
	{
		return m_state;
	}

	DisplayString *getTextDisplayString()
	{
		return m_text;
	}

	Int getTextLength()
	{
		if (m_text)
			return m_text->getTextLength();
		return 0;
	}

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;
	unsigned char m_unreconstructed_0c[0x190];
	DisplayString *m_text;
};

class GameWindowManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void winDrawImage(const Image *, Int, Int, Int, Int, Color = -1);
	virtual void winFillRect(Color, Real, Int, Int, Int, Int);
	virtual void winOpenRect(Color, Real, Int, Int, Int, Int);
	virtual void winDrawLine(Color, Real, Int, Int, Int, Int);
};

extern GameWindowManager *TheWindowManager;

inline Int BitTest(UnsignedInt bits, UnsignedInt mask)
{
	return (bits & mask) != 0;
}

inline Color GadgetCheckBoxGetEnabledColor(GameWindow *g)
{
	return g->winGetEnabledColor(0);
}

inline Color GadgetCheckBoxGetEnabledBorderColor(GameWindow *g)
{
	return g->winGetEnabledBorderColor(0);
}

inline Color GadgetCheckBoxGetEnabledUncheckedBoxColor(GameWindow *g)
{
	return g->winGetEnabledColor(1);
}

inline Color GadgetCheckBoxGetEnabledUncheckedBoxBorderColor(GameWindow *g)
{
	return g->winGetEnabledBorderColor(1);
}

inline Color GadgetCheckBoxGetEnabledCheckedBoxColor(GameWindow *g)
{
	return g->winGetEnabledColor(2);
}

inline Color GadgetCheckBoxGetEnabledCheckedBoxBorderColor(GameWindow *g)
{
	return g->winGetEnabledBorderColor(2);
}

inline Color GadgetCheckBoxGetDisabledColor(GameWindow *g)
{
	return g->winGetDisabledColor(0);
}

inline Color GadgetCheckBoxGetDisabledBorderColor(GameWindow *g)
{
	return g->winGetDisabledBorderColor(0);
}

inline Color GadgetCheckBoxGetDisabledUncheckedBoxColor(GameWindow *g)
{
	return g->winGetDisabledColor(1);
}

inline Color GadgetCheckBoxGetDisabledUncheckedBoxBorderColor(GameWindow *g)
{
	return g->winGetDisabledBorderColor(1);
}

inline Color GadgetCheckBoxGetDisabledCheckedBoxColor(GameWindow *g)
{
	return g->winGetDisabledColor(2);
}

inline Color GadgetCheckBoxGetDisabledCheckedBoxBorderColor(GameWindow *g)
{
	return g->winGetDisabledBorderColor(2);
}

inline Color GadgetCheckBoxGetHiliteColor(GameWindow *g)
{
	return g->winGetHiliteColor(0);
}

inline Color GadgetCheckBoxGetHiliteBorderColor(GameWindow *g)
{
	return g->winGetHiliteBorderColor(0);
}

inline Color GadgetCheckBoxGetHiliteUncheckedBoxColor(GameWindow *g)
{
	return g->winGetHiliteColor(1);
}

inline Color GadgetCheckBoxGetHiliteUncheckedBoxBorderColor(GameWindow *g)
{
	return g->winGetHiliteBorderColor(1);
}

inline Color GadgetCheckBoxGetHiliteCheckedBoxColor(GameWindow *g)
{
	return g->winGetHiliteColor(2);
}

inline Color GadgetCheckBoxGetHiliteCheckedBoxBorderColor(GameWindow *g)
{
	return g->winGetHiliteBorderColor(2);
}

#define WIN_DRAW_LINE_WIDTH 1.0f

// ?drawCheckBoxText@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
static void drawCheckBoxText(GameWindow *window, WinInstanceData *instData)
{
	ICoord2D origin, size, textPos;
	Int width, height;
	Color textColor, dropColor;
	DisplayString *text = instData->getTextDisplayString();

	if (text == 0 || text->getTextLength() == 0)
		return;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
	{
		textColor = window->winGetDisabledTextColor();
		dropColor = window->winGetDisabledTextBorderColor();
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		textColor = window->winGetHiliteTextColor();
		dropColor = window->winGetHiliteTextBorderColor();
	}
	else
	{
		textColor = window->winGetEnabledTextColor();
		dropColor = window->winGetEnabledTextBorderColor();
	}

	if (text->getFont() != window->winGetFont())
		text->setFont(window->winGetFont());

	text->getSize(&width, &height);
	textPos.x = origin.x + size.y;
	textPos.y = origin.y + (size.y / 2) - (height / 2);

	text->setTextColor(textColor, dropColor);
	text->draw(textPos.x, textPos.y, 1, 1);
}

// ?W3DGadgetCheckBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetCheckBoxDraw(GameWindow *window, WinInstanceData *instData)
{
	Int checkOffsetFromLeft;
	Color backColor, backBorder, boxColor, boxBorder;
	ICoord2D origin, size, start, end;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	checkOffsetFromLeft = size.x / 16;

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
	{
		backColor = GadgetCheckBoxGetDisabledColor(window);
		backBorder = GadgetCheckBoxGetDisabledBorderColor(window);

		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			boxColor = GadgetCheckBoxGetDisabledCheckedBoxColor(window);
			boxBorder = GadgetCheckBoxGetDisabledCheckedBoxBorderColor(window);
		}
		else
		{
			boxColor = GadgetCheckBoxGetDisabledUncheckedBoxColor(window);
			boxBorder = GadgetCheckBoxGetDisabledUncheckedBoxBorderColor(window);
		}
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		backColor = GadgetCheckBoxGetHiliteColor(window);
		backBorder = GadgetCheckBoxGetHiliteBorderColor(window);

		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			boxColor = GadgetCheckBoxGetHiliteCheckedBoxColor(window);
			boxBorder = GadgetCheckBoxGetHiliteCheckedBoxBorderColor(window);
		}
		else
		{
			boxColor = GadgetCheckBoxGetHiliteUncheckedBoxColor(window);
			boxBorder = GadgetCheckBoxGetHiliteUncheckedBoxBorderColor(window);
		}
	}
	else
	{
		backColor = GadgetCheckBoxGetEnabledColor(window);
		backBorder = GadgetCheckBoxGetEnabledBorderColor(window);

		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			boxColor = GadgetCheckBoxGetEnabledCheckedBoxColor(window);
			boxBorder = GadgetCheckBoxGetEnabledCheckedBoxBorderColor(window);
		}
		else
		{
			boxColor = GadgetCheckBoxGetEnabledUncheckedBoxColor(window);
			boxBorder = GadgetCheckBoxGetEnabledUncheckedBoxBorderColor(window);
		}
	}

	start.x = origin.x;
	start.y = origin.y;
	end.x = start.x + size.x;
	end.y = start.y + size.y;
	TheWindowManager->winOpenRect(backBorder, WIN_DRAW_LINE_WIDTH,
		start.x, start.y, end.x, end.y);

	start.x++;
	start.y++;
	end.x--;
	end.y--;
	TheWindowManager->winFillRect(backColor, WIN_DRAW_LINE_WIDTH,
		start.x, start.y, end.x, end.y);

	start.x = origin.x + checkOffsetFromLeft;
	start.y = origin.y + (size.y / 3);
	end.x = start.x + (size.y / 3);
	end.y = start.y + (size.y / 3);
	TheWindowManager->winOpenRect(boxBorder, WIN_DRAW_LINE_WIDTH,
		start.x, start.y, end.x, end.y);

	if (boxColor != WIN_COLOR_UNDEFINED)
	{
		TheWindowManager->winDrawLine(boxColor, WIN_DRAW_LINE_WIDTH,
			start.x, start.y, end.x, end.y);
		TheWindowManager->winDrawLine(boxColor, WIN_DRAW_LINE_WIDTH,
			start.x, end.y, end.x, start.y);
	}

	if (instData->getTextLength())
		drawCheckBoxText(window, instData);
}
