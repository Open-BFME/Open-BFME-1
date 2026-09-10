// ?d_00794790@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.84 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BFME special push-button image callback, retail 0x00794790 (719 bytes).
//
// The current W3DPushButtonImageDraw dispatch names this helper as the first
// branch after bfmeGoEBNb(window), and the retail range is independently
// bounded by its complete prologue and the ret at +0x2ce.  This is the
// address-derived BFME helper selected by that named caller; it is not being
// given the standard ImageDrawOne/ImageDrawThree identity.  The ABI slice is
// TU-local so the common GameWindow headers remain unchanged.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef int Color;

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

// The BFME retail image width consumed by this body is the field at +0x28.
// The object is otherwise intentionally opaque.
inline Int imageHeight(const Image *image)
{
	return *(const Int *)((const unsigned char *)image + 0x28);
}

struct WinDrawData
{
	const Image *image;
	Int color;
	Int borderColor;
};

class WinInstanceData
{
public:
	UnsignedInt getState(void) const { return m_state; }

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;								// +0x08
	unsigned char m_unreconstructed_0c[0x170];

public:
	ICoord2D m_imageOffset;								// +0x17c
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

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];					// +0x48
	WinDrawData m_disabledDrawData[9];					// +0xb4
	WinDrawData m_hiliteDrawData[9];					// +0x120
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
		Color color = 0xffffffff);						// +0xf4
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
	virtual void setClipRegion(IRegion2D *region);		// +0x88
	virtual void unused35();
	virtual void enableClipping(Bool onoff);			// +0x90
};

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;

enum
{
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATE_SELECTED = 0x00000004,
	WIN_STATE_HILITED = 0x00000002
};

inline Int BitTest(UnsignedInt bits, UnsignedInt mask)
{
	return (bits & mask) != 0;
}

inline const Image *buttonEnabled(GameWindow *window, Int index)
{
	return window->winGetEnabledImage(index);
}

inline const Image *buttonDisabled(GameWindow *window, Int index)
{
	return window->winGetDisabledImage(index);
}

inline const Image *buttonHilite(GameWindow *window, Int index)
{
	return window->winGetHiliteImage(index);
}

// ?d_00794790@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void d_00794790(GameWindow *window, WinInstanceData *instData)
{
	const Image *topImage, *bottomImage, *centerImage;
	ICoord2D origin, size, start, end;
	Int xOffset, yOffset;
	Int i;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
	{
		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			topImage = buttonDisabled(window, 1);
			bottomImage = buttonDisabled(window, 4);
			centerImage = buttonDisabled(window, 3);
		}
		else
		{
			topImage = buttonDisabled(window, 0);
			bottomImage = buttonDisabled(window, 6);
			centerImage = buttonDisabled(window, 5);
		}
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			topImage = buttonHilite(window, 1);
			bottomImage = buttonHilite(window, 4);
			centerImage = buttonHilite(window, 3);
		}
		else
		{
			topImage = buttonHilite(window, 0);
			bottomImage = buttonHilite(window, 6);
			centerImage = buttonHilite(window, 5);
		}
	}
	else
	{
		if (BitTest(instData->getState(), WIN_STATE_SELECTED))
		{
			topImage = buttonEnabled(window, 1);
			bottomImage = buttonEnabled(window, 4);
			centerImage = buttonEnabled(window, 3);
		}
		else
		{
			topImage = buttonEnabled(window, 0);
			bottomImage = buttonEnabled(window, 6);
			centerImage = buttonEnabled(window, 5);
		}
	}

	if (topImage == 0 || bottomImage == 0 || centerImage == 0)
		return;

	ICoord2D topSize, bottomSize;
	topSize.y = imageHeight(topImage);
	bottomSize.y = imageHeight(bottomImage);

	ICoord2D topEnd, bottomStart;
	topEnd.x = origin.x + size.x + xOffset;
	topEnd.y = origin.y + topSize.y + yOffset;
	bottomStart.x = origin.x + xOffset;
	bottomStart.y = origin.y + size.y - bottomSize.y + yOffset;

	Int centerHeight, pieces;
	centerHeight = bottomStart.y - topEnd.y;

	if (centerHeight <= 0)
	{
		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end.x = origin.x + size.x;
		end.y = origin.y + yOffset + size.y / 2;
		TheWindowManager->winDrawImage(topImage, start.x, start.y,
			end.x, end.y);

		start.y = end.y;
		end.y = origin.y + size.y;
		TheWindowManager->winDrawImage(bottomImage, start.x, start.y,
			end.x, end.y);
	}
	else
	{
		pieces = centerHeight / imageHeight(centerImage);
		start.x = origin.x + xOffset;
		start.y = topEnd.y;
		end.x = start.x + size.x + xOffset;
		end.y = start.y + imageHeight(centerImage);
		for (i = 0; i < pieces; i++)
		{
			TheWindowManager->winDrawImage(centerImage, start.x, start.y,
				end.x, end.y);
			start.y += imageHeight(centerImage);
		}

		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = end.x;
		reg.hi.y = bottomStart.y;
		centerHeight = bottomStart.y - start.y;
		if (centerHeight > 0)
		{
			TheDisplay->setClipRegion(&reg);
			TheWindowManager->winDrawImage(centerImage, start.x, start.y,
				end.x, end.y);
			TheDisplay->enableClipping(0);
		}

		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end = topEnd;
		TheWindowManager->winDrawImage(topImage, start.x, start.y,
			end.x, end.y);

		start = bottomStart;
		end.x = start.x + size.x;
		end.y = start.y + bottomSize.y;
		TheWindowManager->winDrawImage(bottomImage, start.x, start.y,
			end.x, end.y);
	}
}
