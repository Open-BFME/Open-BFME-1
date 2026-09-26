// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// W3DGadgetPushButtonDraw, retail 0x00794D30 (822 bytes).
//
// The callback name is independently established by W3DFunctionLexicon and
// W3DGameWindowManager::getPushButtonDrawFunc; the raw body starts with its
// own prologue and ends at +0x335 ret, with int3 padding at +0x336.  The
// function-table row is the only ledger row over the complete range.  BFME's
// body uses the expanded GameWindow draw-data arrays and the begin/draw/end
// display sequence, then dispatches the observed +0x28 button-data flag to
// the existing retail thunk at RVA 0x000327A4.  The ABI declarations below
// are TU-local so the common headers remain untouched.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class GameFont;
class VideoBuffer;
class Image;

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

// BFME DisplayString slots used by drawButtonText; getTextLength is +0x0C.
class DisplayString
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual Int getTextLength(void);
	virtual void unused04();
	virtual void unused05();
	virtual void setFont(GameFont *font);
	virtual GameFont *getFont(void);
	virtual void setWordWrap(Int width);
	virtual void setWordWrapCentered(Bool centered);
	virtual void setTextColor(Color color, Color dropColor);
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw(Int x, Int y, Color color, Color dropColor);
	virtual void getSize(Int *width, Int *height);
};

// Only members witnessed by this callback are modeled.  The text pointer and
// video buffer offsets are BFME retail offsets, not inferred adjacency.
class WinInstanceData
{
public:
	UnsignedInt getState(void) const { return m_state; }
	UnsignedInt getStatus(void) const { return m_status; }

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;                                  // +0x08
	UnsignedInt m_style;                                  // +0x0C
	UnsignedInt m_status;                                 // +0x10
	unsigned char m_unreconstructed_14[0x188];

	public:
	DisplayString *m_text;                                 // +0x19C
	DisplayString *m_tooltip;                              // +0x1A0
	VideoBuffer *m_videoBuffer;                            // +0x1A4
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// The three 9-entry arrays are the BFME GameWindow storage observed at
// +0x48, +0xB4 and +0x120.  Each entry is image/color/borderColor (12 bytes).
class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);
	void *winGetUserData(void);
	void winSetUserData(void *data);

	Color enabledColor(Int index) const { return m_enabledDrawData[index].color; }
	Color enabledBorderColor(Int index) const { return m_enabledDrawData[index].borderColor; }
	Color disabledColor(Int index) const { return m_disabledDrawData[index].color; }
	Color disabledBorderColor(Int index) const { return m_disabledDrawData[index].borderColor; }
	Color hiliteColor(Int index) const { return m_hiliteDrawData[index].color; }
	Color hiliteBorderColor(Int index) const { return m_hiliteDrawData[index].borderColor; }

	GameFont *winGetFont(void);

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];                     // +0x48
	WinDrawData m_disabledDrawData[9];                    // +0xB4
	WinDrawData m_hiliteDrawData[9];                      // +0x120
};

class GameWindowManager
{
public:
	virtual void unused00(); virtual void unused01();
	virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09();
	virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13();
	virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21();
	virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25();
	virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33();
	virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37();
	virtual void unused38(); virtual void unused39();
	virtual void unused40(); virtual void unused41();
	virtual void unused42(); virtual void unused43();
	virtual void unused44(); virtual void unused45();
	virtual void unused46(); virtual void unused47();
	virtual void unused48(); virtual void unused49();
	virtual void unused50(); virtual void unused51();
	virtual void unused52(); virtual void unused53();
	virtual void unused54(); virtual void unused55();
	virtual void unused56(); virtual void unused57();
	virtual void unused58(); virtual void unused59();
	virtual void unused60(); virtual void unused61();

	virtual void winFillRect(Color color, Real width,
		Int startX, Int startY, Int endX, Int endY);          // +0xF8
	virtual void winOpenRect(Color color, Real width,
		Int startX, Int startY, Int endX, Int endY);          // +0xFC
};

class Display
{
public:
	virtual void unused00(); virtual void unused01();
	virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09();
	virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13();
	virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21();
	virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25();
	virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33();
	virtual void setClipRegion(IRegion2D *region);          // +0x88
	virtual void unused35();
	virtual void enableClipping(Bool onoff);               // +0x90
	virtual void unused37(); virtual void unused38();
	virtual void unused39(); virtual void unused40();
	virtual void unused41(); virtual void unused42();
	virtual void unused43(); virtual void beginImageDraw();// +0xB0
	virtual void unused45(); virtual void unused46();
	virtual void unused47(); virtual void unused48();
	virtual void unused49(); virtual void unused50();
	virtual void unused51(); virtual void unused52();
	virtual void drawImageCore(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode);          // +0xD4
	virtual void unused54();
	virtual void endImageDraw(void);                        // +0xDC
	virtual void drawVideoBuffer(VideoBuffer *buffer, Real startX,
		Real startY, Real endX, Real endY, Color color = -1);// +0xE0

	// These are direct helper bodies in the retail call sites, not vtable
	// slots.  Their float coordinate signatures preserve the x87 conversions.
	void drawRectClock(Real startX, Real startY, Real width, Real height,
		Real percent, Color color);
	void drawRemainingRectClock(Real startX, Real startY, Real width,
		Real height, Real percent, Color color);
	void drawOpenRect(Real startX, Real startY, Real width, Real height,
		Real lineWidth, Color color);
};

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;

// This helper is the already matched BFME text-colour selector at RVA
// 0x00793E50.  The retail drawButtonText body reaches it through the
// 0x000089DB thunk; keeping the declaration here preserves that route.
void getButtonTextColors(GameWindow *window, WinInstanceData *instData,
	Color *textColor, Color *dropColor);

inline void drawImage(Display *display, const Image *image,
	Real startX, Real startY, Real endX, Real endY, Color color, Int mode)
{
	display->beginImageDraw();
	display->drawImageCore(image, startX, startY, endX, endY, color, mode);
	display->endImageDraw();
}

// The retail data is the standard button prefix followed by BFME-only
// fields.  Only the +0x28 flag is consumed here; the explicit padding records
// its proven offset without inventing names for the intervening storage.
struct PushButtonData
{
	UnsignedByte drawClock;                                // +0x00
	UnsignedByte padding01[3];
	Int percentClock;                                      // +0x04
	Color colorClock;                                      // +0x08
	UnsignedByte drawBorder;                              // +0x0C
	UnsignedByte padding0D[3];
	Color colorBorder;                                     // +0x10
	void *userData;                                        // +0x14
	const Image *overlayImage;                             // +0x18
	unsigned char unmodelled_1C[0x0C];
	UnsignedByte field28;                                  // +0x28
};

enum
{
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATE_SELECTED = 0x00000004,
	WIN_STATE_HILITED = 0x00000002,
	WIN_STATUS_WRAP_CENTERED = 0x00040000,
	WIN_COLOR_UNDEFINED = 0x00FFFFFF,
	NORMAL_CLOCK = 1,
	INVERSE_CLOCK = 2
};

inline Int BitTest(UnsignedInt bits, UnsignedInt mask)
{
	return (bits & mask) != 0;
}

inline Color buttonEnabledColor(GameWindow *window)
{
	return window->enabledColor(0);
}

inline Color buttonEnabledBorderColor(GameWindow *window)
{
	return window->enabledBorderColor(0);
}

inline Color buttonDisabledColor(GameWindow *window)
{
	return window->disabledColor(0);
}

inline Color buttonDisabledBorderColor(GameWindow *window)
{
	return window->disabledBorderColor(0);
}

inline Color buttonHiliteColor(GameWindow *window)
{
	return window->hiliteColor(0);
}

inline Color buttonHiliteBorderColor(GameWindow *window)
{
	return window->hiliteBorderColor(0);
}

// This is the existing retail thunk at RVA 0x000327A4 (targeting the
// already banked number-draw body).  Its parameterized declaration is local
// to this TU; no new identity or ledger row is claimed for the callee.
void j_000327a4(GameWindow *window, WinInstanceData *instData,
	PushButtonData *pData);

// Keep the named text callback in this TU.  MSVC's file-local convention
// passes the first two pointer arguments in registers at the call site.
static void drawButtonText(GameWindow *window, WinInstanceData *instData)
{
	ICoord2D origin, size, textPos;
	Int width, height;
	Color textColor, dropColor;
	DisplayString *text = instData->m_text;

	if (text == 0 || text->getTextLength() == 0)
		return;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);
	text->setWordWrapCentered(BitTest(instData->getStatus(),
		WIN_STATUS_WRAP_CENTERED));
	text->setWordWrap(size.x);

	getButtonTextColors(window, instData, &textColor, &dropColor);

	if (text->getFont() != window->winGetFont())
		text->setFont(window->winGetFont());
	text->getSize(&width, &height);

	textPos.x = origin.x + (size.x / 2) - (width / 2);
	textPos.y = origin.y + (size.y / 2) - (height / 2);
	text->setTextColor(textColor, dropColor);
	text->draw(textPos.x, textPos.y, 1, 1);
}

// ?W3DGadgetPushButtonDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetPushButtonDraw(GameWindow *window, WinInstanceData *instData)
{
	Color color, border;
	ICoord2D origin, size, start, end;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (!BitTest(window->winGetStatus(), WIN_STATUS_ENABLED))
	{
		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			color = window->disabledColor(1);
			border = window->disabledBorderColor(1);
		}
		else
		{
			color = buttonDisabledColor(window);
			border = buttonDisabledBorderColor(window);
		}
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			color = window->hiliteColor(1);
			border = window->hiliteBorderColor(1);
		}
		else
		{
			color = window->hiliteColor(0);
			border = window->hiliteBorderColor(0);
		}
	}
	else
	{
		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			color = window->enabledColor(1);
			border = window->enabledBorderColor(1);
		}
		else
		{
			color = buttonEnabledColor(window);
			border = buttonEnabledBorderColor(window);
		}
	}

	start.x = origin.x;
	start.y = origin.y;
	end.x = start.x + size.x;
	end.y = start.y + size.y;

	if (border != WIN_COLOR_UNDEFINED)
		TheWindowManager->winOpenRect(border, 1.0f,
			start.x, start.y, end.x, end.y);

	if (color != WIN_COLOR_UNDEFINED)
	{
		start.x++;
		start.y++;
		end.x--;
		end.y--;
		TheWindowManager->winFillRect(color, 1.0f,
			start.x, start.y, end.x, end.y);
	}

	if (instData->m_text && instData->m_text->getTextLength())
		drawButtonText(window, instData);

	if (instData->m_videoBuffer)
	{
		TheDisplay->drawVideoBuffer(instData->m_videoBuffer,
			(Real)origin.x, (Real)origin.y,
			(Real)(origin.x + size.x), (Real)(origin.y + size.y));
	}

	PushButtonData *pData = (PushButtonData *)window->winGetUserData();
	if (pData)
	{
		if (pData->overlayImage)
			drawImage(TheDisplay, pData->overlayImage,
				(Real)origin.x, (Real)origin.y,
				(Real)(origin.x + size.x), (Real)(origin.y + size.y),
				-1, 2);

		if (pData->drawClock)
		{
			if (pData->drawClock == NORMAL_CLOCK)
				TheDisplay->drawRectClock((Real)origin.x, (Real)origin.y,
					(Real)size.x, (Real)size.y, (Real)pData->percentClock,
					pData->colorClock);
			else if (pData->drawClock == INVERSE_CLOCK)
				TheDisplay->drawRemainingRectClock((Real)origin.x,
					(Real)origin.y, (Real)size.x, (Real)size.y,
					(Real)pData->percentClock, pData->colorClock);
			pData->drawClock = 0;
			window->winSetUserData(pData);
		}

		if (pData->field28 == 1)
			j_000327a4(window, instData, pData);

		if (pData->drawBorder && pData->colorBorder != WIN_COLOR_UNDEFINED)
			TheDisplay->drawOpenRect((Real)(origin.x - 1),
				(Real)(origin.y - 1), (Real)(size.x + 2),
				(Real)(size.y + 2), 1.0f, pData->colorBorder);
	}
}
