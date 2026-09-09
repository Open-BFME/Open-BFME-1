// ?W3DGadgetPushButtonImageDrawThree@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.86 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// W3DGadgetPushButtonImageDrawThree, retail 0x00794120 (1314 bytes).
//
// Identity: the named W3DGadgetPushButtonImageDraw dispatcher and the
// W3DPushButtonImageDispatch_Thunk both call this symbol.  The retail range
// starts with a complete sub-esp/prologue and ends at the pop/ret sequence at
// +0x520; functions.csv has only the one generated row over that range.
//
// This is a TU-local ABI slice.  The retail body reads BFME's expanded
// WinInstanceData and GameWindow draw-data layout directly, and its display
// tail uses the BFME float-coordinate calls witnessed in the retail stream.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class DisplayString
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual Int getTextLength(void);								///< +0x0c
};
class VideoBuffer;

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

// Image::m_imageSize is at +0x20 in the BFME image object; width is +0x24.
class Image
{
private:
	unsigned char m_unreconstructed_00[0x24];

public:
	Int getImageWidth(void) const { return *(const Int *)((const char *)this + 0x24); }
};

class GameWindow;

// The body only needs the state, image offset, text and video-buffer members.
// The leading eight bytes include the object vptr and id in the retail class.
class WinInstanceData
{
public:
	UnsignedInt getState(void) const { return m_state; }

	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;								///< retail this+0x08
	unsigned char m_unreconstructed_0c[0x170];
	ICoord2D m_imageOffset;								///< retail this+0x17c
	unsigned char m_unreconstructed_184[0x18];
	DisplayString *m_text;								///< retail this+0x19c
	DisplayString *m_tooltip;								///< retail this+0x1a0
	VideoBuffer *m_videoBuffer;								///< retail this+0x1a4
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);			///< ILT 0x0002f94b
	Int winGetSize(Int *width, Int *height);			///< ILT 0x00036ebc
	UnsignedInt winGetStatus(void);						///< ILT 0x00023dda
	void *winGetUserData(void);								///< ILT 0x00046538
	void winSetUserData(void *userData);							///< ILT 0x00002e69

	const Image *winGetEnabledImage(Int index) const { return m_enabledDrawData[index].image; }
	const Image *winGetDisabledImage(Int index) const { return m_disabledDrawData[index].image; }
	const Image *winGetHiliteImage(Int index) const { return m_hiliteDrawData[index].image; }

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];					///< retail this+0x48
	WinDrawData m_disabledDrawData[9];					///< retail this+0xb4
	WinDrawData m_hiliteDrawData[9];					///< retail this+0x120
};

class GameWindowManager
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02();
	virtual void unused03(); virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07(); virtual void unused08();
	virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14();
	virtual void unused15(); virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19(); virtual void unused20();
	virtual void unused21(); virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25(); virtual void unused26();
	virtual void unused27(); virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31(); virtual void unused32();
	virtual void unused33(); virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37(); virtual void unused38();
	virtual void unused39(); virtual void unused40(); virtual void unused41();
	virtual void unused42(); virtual void unused43(); virtual void unused44();
	virtual void unused45(); virtual void unused46(); virtual void unused47();
	virtual void unused48(); virtual void unused49(); virtual void unused50();
	virtual void unused51(); virtual void unused52(); virtual void unused53();
	virtual void unused54(); virtual void unused55(); virtual void unused56();
	virtual void unused57(); virtual void unused58(); virtual void unused59();
	virtual void unused60();

	virtual void winDrawImage(const Image *image, Int startX, Int startY,
										 Int endX, Int endY, Color color = 0xffffffff);	///< +0xf4
};

class Display
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02();
	virtual void unused03(); virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07(); virtual void unused08();
	virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14();
	virtual void unused15(); virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19(); virtual void unused20();
	virtual void unused21(); virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25(); virtual void unused26();
	virtual void unused27(); virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31(); virtual void unused32();
	virtual void unused33();
	virtual void setClipRegion(IRegion2D *region);						///< +0x88
	virtual void unused35();
	virtual void enableClipping(Bool onoff);							///< +0x90
	virtual void unused37(); virtual void unused38(); virtual void unused39();
	virtual void unused40(); virtual void unused41(); virtual void unused42();
	virtual void unused43(); virtual void unused44(); virtual void unused45();
	virtual void unused46(); virtual void unused47(); virtual void unused48();
	virtual void unused49(); virtual void unused50(); virtual void unused51();
	virtual void unused52(); virtual void unused53(); virtual void unused54();
	virtual void unused55();

	virtual void drawVideoBuffer(VideoBuffer *buffer, Real startX, Real startY,
										 Real endX, Real endY, Color color = 0xffffffff);	///< +0xe0

	// BFME's direct display helpers use float screen coordinates in this body.
	void drawImage(const Image *image, Real startX, Real startY,
				 Real endX, Real endY, Color color, Int mode);
	void drawRectClock(Real startX, Real startY, Real width, Real height,
				  Real percent, Color color);
	void drawRemainingRectClock(Real startX, Real startY, Real width, Real height,
									Real percent, Color color);
	void drawOpenRect(Real startX, Real startY, Real width, Real height,
				 Real lineWidth, Color color);
};

extern GameWindowManager *TheWindowManager;							///< retail [0x012f1b40]
extern Display *TheDisplay;									///< retail [0x012f1270]

struct PushButtonData
{
	UnsignedByte drawClock;								///< +0x00
	Int percentClock;									///< +0x04
	Color colorClock;									///< +0x08
	Bool drawBorder;									///< +0x0c
	Color colorBorder;									///< +0x10
	void *userData;										///< +0x14
	const Image *overlayImage;								///< +0x18
};

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATE_SELECTED = 0x00000004 };
enum { WIN_STATE_HILITED = 0x00000002 };
enum { NORMAL_CLOCK = 1, INVERSE_CLOCK = 2 };
enum { GAME_COLOR_UNDEFINED = 0x00ffffff };

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

// Address-derived local spelling for the already-witnessed text callee.  It
// is intentionally not a claimed ledger identity; the claimed body below
// only owns W3DGadgetPushButtonImageDrawThree.
static void buttonTextHelper(GameWindow *window, WinInstanceData *instData)
{
	if (window == 0 || instData == 0)
		return;
}

// ?W3DGadgetPushButtonImageDrawThree@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetPushButtonImageDrawThree(GameWindow *window, WinInstanceData *instData)
{
	const Image *leftImage, *rightImage, *centerImage;
	ICoord2D origin, size, start, end;
	Int xOffset, yOffset;
	Int i;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	// Keep the two long-lived object pointers in declaration order after the
	// geometry calls.  This is the source-level shape used to steer the retail
	// EBX/EBP object allocation while leaving the initial call order intact.
	register GameWindow *drawWindow = window;
	register WinInstanceData *drawData = instData;
	xOffset = drawData->m_imageOffset.x;
	yOffset = drawData->m_imageOffset.y;

	if (!BitTest(drawWindow->winGetStatus(), WIN_STATUS_ENABLED))
	{
		if (BitTest(drawData->getState(), WIN_STATE_SELECTED))
		{
			leftImage = buttonDisabled(drawWindow, 1);
			rightImage = buttonDisabled(drawWindow, 4);
			centerImage = buttonDisabled(drawWindow, 3);
		}
		else
		{
			leftImage = buttonDisabled(drawWindow, 0);
			rightImage = buttonDisabled(drawWindow, 6);
			centerImage = buttonDisabled(drawWindow, 5);
		}
	}
	else if (BitTest(drawData->getState(), WIN_STATE_HILITED))
	{
		if (BitTest(drawData->getState(), WIN_STATE_SELECTED))
		{
			leftImage = buttonHilite(drawWindow, 1);
			rightImage = buttonHilite(drawWindow, 4);
			centerImage = buttonHilite(drawWindow, 3);
		}
		else
		{
			leftImage = buttonHilite(drawWindow, 0);
			rightImage = buttonHilite(drawWindow, 6);
			centerImage = buttonHilite(drawWindow, 5);
		}
	}
	else
	{
		if (BitTest(drawData->getState(), WIN_STATE_SELECTED))
		{
			leftImage = buttonEnabled(drawWindow, 1);
			rightImage = buttonEnabled(drawWindow, 4);
			centerImage = buttonEnabled(drawWindow, 3);
		}
		else
		{
			leftImage = buttonEnabled(drawWindow, 0);
			rightImage = buttonEnabled(drawWindow, 6);
			centerImage = buttonEnabled(drawWindow, 5);
		}
	}

	if (leftImage == 0 || rightImage == 0 || centerImage == 0)
		return;

	ICoord2D leftSize, rightSize;
	rightSize.x = rightImage->getImageWidth();
	leftSize.x = leftImage->getImageWidth();

	ICoord2D leftEnd, rightStart;
	leftEnd.x = origin.x + leftSize.x + xOffset;
	leftEnd.y = origin.y + size.y + yOffset;
	rightStart.x = origin.x + size.x - rightSize.x + xOffset;
	rightStart.y = origin.y + yOffset;

	Int centerWidth, pieces;
	centerWidth = rightStart.x - leftEnd.x;

	if (centerWidth <= 0)
	{
		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end.y = leftEnd.y;
		end.x = origin.x + xOffset + size.x / 2;
		TheWindowManager->winDrawImage(leftImage, start.x, start.y, end.x, end.y);

		start.y = rightStart.y;
		start.x = end.x;
		end.x = origin.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage(rightImage, start.x, start.y, end.x, end.y);
	}
	else
	{
		pieces = centerWidth / centerImage->getImageWidth();
		start.x = leftEnd.x;
		start.y = origin.y + yOffset;
		end.y = start.y + size.y + yOffset;
		for (i = 0; i < pieces; i++)
		{
			end.x = start.x + centerImage->getImageWidth();
			TheWindowManager->winDrawImage(centerImage, start.x, start.y, end.x, end.y);
			start.x += centerImage->getImageWidth();
		}

		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = rightStart.x;
		reg.hi.y = end.y;
		centerWidth = rightStart.x - start.x;
		if (centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.x = start.x + centerImage->getImageWidth();
			TheWindowManager->winDrawImage(centerImage, start.x, start.y, end.x, end.y);
			TheDisplay->enableClipping(0);
		}

		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end = leftEnd;
		TheWindowManager->winDrawImage(leftImage, start.x, start.y, end.x, end.y);

		start = rightStart;
		end.x = start.x + rightSize.x;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage(rightImage, start.x, start.y, end.x, end.y);
	}

	if (drawData->m_text && drawData->m_text->getTextLength())
		buttonTextHelper(drawWindow, drawData);

	drawWindow->winGetScreenPosition(&start.x, &start.y);
	drawWindow->winGetSize(&size.x, &size.y);
	if (drawData->m_videoBuffer)
	{
		TheDisplay->drawVideoBuffer(drawData->m_videoBuffer,
			(Real)start.x, (Real)start.y,
			(Real)(start.x + size.x), (Real)(start.y + size.y));
	}

	PushButtonData *pData = (PushButtonData *)drawWindow->winGetUserData();
	if (pData)
	{
		if (pData->overlayImage)
		{
			TheDisplay->drawImage(pData->overlayImage,
				(Real)origin.x, (Real)origin.y,
				(Real)(origin.x + size.x), (Real)(origin.y + size.y),
				0xffffffff, 2);
		}

		if (pData->drawClock)
		{
			if (pData->drawClock == NORMAL_CLOCK)
				TheDisplay->drawRectClock((Real)start.x, (Real)start.y,
					(Real)size.x, (Real)size.y, (Real)pData->percentClock, pData->colorClock);
			else if (pData->drawClock == INVERSE_CLOCK)
				TheDisplay->drawRemainingRectClock((Real)start.x, (Real)start.y,
					(Real)size.x, (Real)size.y, (Real)pData->percentClock, pData->colorClock);
			pData->drawClock = 0;
			drawWindow->winSetUserData(pData);
		}

		if (pData->drawBorder && pData->colorBorder != GAME_COLOR_UNDEFINED)
			TheDisplay->drawOpenRect((Real)(start.x - 1), (Real)(start.y - 1),
				(Real)(size.x + 2), (Real)(size.y + 2), 1.0f, pData->colorBorder);
	}
}
