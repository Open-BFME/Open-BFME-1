// ?W3DGameWinDefaultDraw@@YGXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME W3D default window callback, retail 0x0078D410 (557 bytes).
// The reference twin is W3DGameWindow.cpp::W3DGameWinDefaultDraw.  BFME's
// GameWindow and WinInstanceData layouts are expanded, so the views below
// keep the retail offsets local to this callback.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class Image;
class VideoBuffer;

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
	UnsignedInt getState(void) const { return m_state; }

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;                                  // +0x08
	unsigned char m_unreconstructed_0c[0x170];

public:
	ICoord2D m_imageOffset;                               // +0x17c
	unsigned char m_unreconstructed_184[0x20];
	VideoBuffer *m_videoBuffer;                           // +0x1a4
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);

	const Image *winGetEnabledImage(Int index) const
	{
		return m_enabledDrawData[index].image;
	}

	const Image *winGetDisabledImage(Int index) const
	{
		return m_disabledDrawData[index].image;
	}

	const Image *winGetHiliteImage(Int index) const
	{
		return m_hiliteDrawData[index].image;
	}

	Color winGetEnabledColor(Int index) const
	{
		return m_enabledDrawData[index].color;
	}

	Color winGetEnabledBorderColor(Int index) const
	{
		return m_enabledDrawData[index].borderColor;
	}

	Color winGetDisabledColor(Int index) const
	{
		return m_disabledDrawData[index].color;
	}

	Color winGetDisabledBorderColor(Int index) const
	{
		return m_disabledDrawData[index].borderColor;
	}

	Color winGetHiliteColor(Int index) const
	{
		return m_hiliteDrawData[index].color;
	}

	Color winGetHiliteBorderColor(Int index) const
	{
		return m_hiliteDrawData[index].borderColor;
	}

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];                    // +0x48
	WinDrawData m_disabledDrawData[9];                   // +0x0b4
	WinDrawData m_hiliteDrawData[9];                     // +0x120
};

class W3DGameWindow : public GameWindow
{
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
	virtual void unused60();

	virtual void winDrawImage(const Image *image,
		Int startX, Int startY, Int endX, Int endY,
		Color color = 0xffffffff);                         // +0xf4
	virtual void winFillRect(Color color, Real width,
		Int startX, Int startY, Int endX, Int endY);       // +0xf8
	virtual void winOpenRect(Color color, Real width,
		Int startX, Int startY, Int endX, Int endY);       // +0xfc
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
	virtual void drawVideoBuffer(VideoBuffer *buffer, Real startX,
		Real startY, Real endX, Real endY, Color color = -1); // +0xe0
};

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;

enum
{
	FALSE = 0,
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATUS_IMAGE = 0x00000080,
	WIN_STATE_HILITED = 0x00000002,
	WIN_COLOR_UNDEFINED = 0x00ffffff
};

extern Real g_bfmeDefaultBU;

inline Int BitTest(UnsignedInt bits, UnsignedInt mask)
{
	return (bits & mask) != 0;
}

// ?W3DGameWinDefaultDraw@@YGXPAVGameWindow@@PAVWinInstanceData@@@Z
void __stdcall W3DGameWinDefaultDraw(GameWindow *window, WinInstanceData *instData)
{
	Real borderWidth = 1.0f;
	ICoord2D origin;
	ICoord2D size;
	W3DGameWindow *w3dWindow = (W3DGameWindow *)window;

	w3dWindow->winGetScreenPosition(&origin.x, &origin.y);
	w3dWindow->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_IMAGE))
	{
		const Image *image;

		if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == FALSE)
			image = window->winGetDisabledImage(0);
		else if (BitTest(instData->getState(), WIN_STATE_HILITED))
			image = window->winGetHiliteImage(0);
		else
			image = window->winGetEnabledImage(0);

		if (image)
		{
			ICoord2D start;
			ICoord2D end;

			start.x = origin.x + instData->m_imageOffset.x;
			start.y = origin.y + instData->m_imageOffset.y;
			end.x = start.x + size.x;
			end.y = start.y + size.y;
			TheWindowManager->winDrawImage(image, start.x, start.y,
				end.x, end.y);
		}
	}
	else
	{
		Color color;
		Color borderColor;

		if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == FALSE)
		{
			color = window->winGetDisabledColor(0);
			borderColor = window->winGetDisabledBorderColor(0);
		}
		else if (BitTest(instData->getState(), WIN_STATE_HILITED))
		{
			color = window->winGetHiliteColor(0);
			borderColor = window->winGetHiliteBorderColor(0);
		}
		else
		{
			color = window->winGetEnabledColor(0);
			borderColor = window->winGetEnabledBorderColor(0);
		}

		if (borderColor != WIN_COLOR_UNDEFINED)
			TheWindowManager->winOpenRect(borderColor, borderWidth,
				origin.x, origin.y, origin.x + size.x, origin.y + size.y);

		if (color != WIN_COLOR_UNDEFINED)
			TheWindowManager->winFillRect(color, borderWidth,
				origin.x + borderWidth, origin.y + borderWidth,
				origin.x + size.x - borderWidth,
				origin.y + size.y - borderWidth);
	}

	if (instData->m_videoBuffer)
	{
		ICoord2D pos, size;

		window->winGetScreenPosition(&pos.x, &pos.y);
		window->winGetSize(&size.x, &size.y);
		TheDisplay->drawVideoBuffer(instData->m_videoBuffer,
			pos.x, pos.y, pos.x + size.x, pos.y + size.y);
	}
}
