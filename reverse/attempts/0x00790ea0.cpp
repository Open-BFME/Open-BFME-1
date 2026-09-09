// ?W3DGadgetHorizontalSliderImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.68 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// W3DGadgetHorizontalSliderImageDraw, retail 0x00790EA0 (639 bytes).
//
// The BFME retail slider keeps the reference callback's image-array and
// SliderData contract, but scales the control for the active display.  The
// status guard, 1/800 and 1/600 scale factors, 0.6 box-width factor, 1-pixel
// padding, and 0.8 highlight offset are all present in the retail body.
// This TU keeps those BFME layouts local; no shared header is moved.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern double sqrt(double);

class Image
{
public:
	Int getImageWidth(void) const { return m_imageWidth; }

private:
	unsigned char m_unreconstructed_00[0x24];
	Int m_imageWidth;
};

struct ICoord2D
{
	Int x, y;

	Int length(void) const { return (Int)sqrt((double)(x * x + y * y)); }
};

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
	UnsignedInt m_state;
};

class GameWindow
{
public:
	void *winGetUserData(void);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);

	const Image *winGetHiliteImage(Int index) { return m_hiliteDrawData[index].image; }
	const Image *winGetDisabledImage(Int index) { return m_disabledDrawData[index].image; }

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];
	WinDrawData m_disabledDrawData[9];
	WinDrawData m_hiliteDrawData[9];
};

inline const Image *GadgetSliderGetHiliteImageLeft(GameWindow *window)
{
	return window->winGetHiliteImage(0);
}

inline const Image *GadgetSliderGetDisabledImageRight(GameWindow *window)
{
	return window->winGetDisabledImage(1);
}

inline const Image *GadgetSliderGetDisabledImageLeft(GameWindow *window)
{
	return window->winGetDisabledImage(0);
}

struct SliderData
{
	Int minVal;
	Int maxVal;
	Real numTicks;
	Int position;
};

#define BFME_DISPLAY_SLOT(n) virtual void bfmeDisplaySlot##n(void);
class Display
{
public:
	BFME_DISPLAY_SLOT(00)
	BFME_DISPLAY_SLOT(01)
	BFME_DISPLAY_SLOT(02)
	BFME_DISPLAY_SLOT(03)
	BFME_DISPLAY_SLOT(04)
	BFME_DISPLAY_SLOT(05)
	BFME_DISPLAY_SLOT(06)
	BFME_DISPLAY_SLOT(07)
	BFME_DISPLAY_SLOT(08)
	BFME_DISPLAY_SLOT(09)
	BFME_DISPLAY_SLOT(10)
	virtual UnsignedInt getWidth(void);
	virtual UnsignedInt getHeight(void);
};
#undef BFME_DISPLAY_SLOT

extern Display *TheDisplay;

#define BFME_WINDOW_MANAGER_SLOT(n) virtual void bfmeWindowManagerSlot##n(void);
class GameWindowManager
{
public:
	BFME_WINDOW_MANAGER_SLOT(00)
	BFME_WINDOW_MANAGER_SLOT(01)
	BFME_WINDOW_MANAGER_SLOT(02)
	BFME_WINDOW_MANAGER_SLOT(03)
	BFME_WINDOW_MANAGER_SLOT(04)
	BFME_WINDOW_MANAGER_SLOT(05)
	BFME_WINDOW_MANAGER_SLOT(06)
	BFME_WINDOW_MANAGER_SLOT(07)
	BFME_WINDOW_MANAGER_SLOT(08)
	BFME_WINDOW_MANAGER_SLOT(09)
	BFME_WINDOW_MANAGER_SLOT(10)
	BFME_WINDOW_MANAGER_SLOT(11)
	BFME_WINDOW_MANAGER_SLOT(12)
	BFME_WINDOW_MANAGER_SLOT(13)
	BFME_WINDOW_MANAGER_SLOT(14)
	BFME_WINDOW_MANAGER_SLOT(15)
	BFME_WINDOW_MANAGER_SLOT(16)
	BFME_WINDOW_MANAGER_SLOT(17)
	BFME_WINDOW_MANAGER_SLOT(18)
	BFME_WINDOW_MANAGER_SLOT(19)
	BFME_WINDOW_MANAGER_SLOT(20)
	BFME_WINDOW_MANAGER_SLOT(21)
	BFME_WINDOW_MANAGER_SLOT(22)
	BFME_WINDOW_MANAGER_SLOT(23)
	BFME_WINDOW_MANAGER_SLOT(24)
	BFME_WINDOW_MANAGER_SLOT(25)
	BFME_WINDOW_MANAGER_SLOT(26)
	BFME_WINDOW_MANAGER_SLOT(27)
	BFME_WINDOW_MANAGER_SLOT(28)
	BFME_WINDOW_MANAGER_SLOT(29)
	BFME_WINDOW_MANAGER_SLOT(30)
	BFME_WINDOW_MANAGER_SLOT(31)
	BFME_WINDOW_MANAGER_SLOT(32)
	BFME_WINDOW_MANAGER_SLOT(33)
	BFME_WINDOW_MANAGER_SLOT(34)
	BFME_WINDOW_MANAGER_SLOT(35)
	BFME_WINDOW_MANAGER_SLOT(36)
	BFME_WINDOW_MANAGER_SLOT(37)
	BFME_WINDOW_MANAGER_SLOT(38)
	BFME_WINDOW_MANAGER_SLOT(39)
	BFME_WINDOW_MANAGER_SLOT(40)
	BFME_WINDOW_MANAGER_SLOT(41)
	BFME_WINDOW_MANAGER_SLOT(42)
	BFME_WINDOW_MANAGER_SLOT(43)
	BFME_WINDOW_MANAGER_SLOT(44)
	BFME_WINDOW_MANAGER_SLOT(45)
	BFME_WINDOW_MANAGER_SLOT(46)
	BFME_WINDOW_MANAGER_SLOT(47)
	BFME_WINDOW_MANAGER_SLOT(48)
	BFME_WINDOW_MANAGER_SLOT(49)
	BFME_WINDOW_MANAGER_SLOT(50)
	BFME_WINDOW_MANAGER_SLOT(51)
	BFME_WINDOW_MANAGER_SLOT(52)
	BFME_WINDOW_MANAGER_SLOT(53)
	BFME_WINDOW_MANAGER_SLOT(54)
	BFME_WINDOW_MANAGER_SLOT(55)
	BFME_WINDOW_MANAGER_SLOT(56)
	BFME_WINDOW_MANAGER_SLOT(57)
	BFME_WINDOW_MANAGER_SLOT(58)
	BFME_WINDOW_MANAGER_SLOT(59)
	BFME_WINDOW_MANAGER_SLOT(60)
	virtual void winDrawImage(const Image *image,
														Int startX, Int startY, Int endX, Int endY,
														Int color = 0xFFFFFFFF);
};
#undef BFME_WINDOW_MANAGER_SLOT

extern GameWindowManager *TheWindowManager;

inline Int BitTest(UnsignedInt value, UnsignedInt mask)
{
	return (value & mask) != 0;
}

enum { WIN_STATE_HILITED = 0x00000002 };
enum { WIN_STATUS_NO_SCALE = 0x08000000 };

void W3DGadgetHorizontalSliderImageDraw(GameWindow *window,
														WinInstanceData *instData)
{
	const Image *fillSquare, *blankSquare, *highlightSquare;
	ICoord2D origin, size, start, end, highlightOffset;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	highlightSquare = GadgetSliderGetHiliteImageLeft(window);
	blankSquare = GadgetSliderGetDisabledImageRight(window);
	fillSquare = GadgetSliderGetDisabledImageLeft(window);

	SliderData *s = (SliderData *)window->winGetUserData();

	Real xMulti = 1.0f;
	Real yMulti = 1.0f;
	if (BitTest(window->winGetStatus(), WIN_STATUS_NO_SCALE) == 0)
	{
		xMulti = (Real)TheDisplay->getWidth();
		yMulti = (Real)TheDisplay->getHeight();
		xMulti /= 800;
		yMulti /= 600;
	}

	Int numBoxes = 0;
	Int numSelectedBoxes = 0;
	Int numHighlightBoxes;
	Int boxWidth = (Int)(fillSquare->getImageWidth() * xMulti * 0.6);
	Int boxPadding = 1;
	Int scaledWidth = (Int)(size.y * yMulti);
	start.x = origin.x;
	end.x = start.x + boxWidth;
	Real selectedPercent = (s->position - s->minVal) /
																								(Real)(s->maxVal - s->minVal);
	Int maxSelectedX = origin.x + (Int)(selectedPercent * size.x);
	while (end.x < origin.x + size.x)
	{
		if (start.x <= maxSelectedX && end.x < origin.x + size.x &&
			s->position != s->minVal)
			++numSelectedBoxes;
		start.x = end.x + boxPadding;
		end.x = start.x + boxWidth;
		++numBoxes;
	}

	numHighlightBoxes = numBoxes + 1;
	Int distanceCovered = end.x - origin.x - boxWidth;
	highlightOffset.x = -(boxWidth + boxPadding) / 2;
	highlightOffset.y = (Int)(scaledWidth * 0.8);
	Int blankness = size.x - distanceCovered;
	origin.x += blankness / 2;

	Int i;
	if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		ICoord2D backgroundStart, backgroundEnd;
		backgroundStart.y = origin.y + highlightOffset.y;
		backgroundEnd.y = backgroundStart.y + boxWidth + boxPadding;
		for (i = 0; i < numHighlightBoxes; ++i)
		{
			backgroundStart.x = origin.x + highlightOffset.x +
				i * (boxWidth + boxPadding);
			backgroundEnd.x = backgroundStart.x + boxWidth + boxPadding;
			TheWindowManager->winDrawImage(highlightSquare,
																								backgroundStart.x, backgroundStart.y,
																								backgroundEnd.x, backgroundEnd.y);
		}
	}

	start.y = origin.y;
	end.y = start.y + boxWidth;
	for (i = 0; i < numSelectedBoxes; ++i)
	{
		start.x = origin.x + i * (boxWidth + boxPadding);
		end.x = start.x + boxWidth;
		TheWindowManager->winDrawImage(fillSquare,
																								start.x, start.y,
																								end.x, end.y);
	}
	for (i = numSelectedBoxes; i < numBoxes; ++i)
	{
		start.x = origin.x + i * (boxWidth + boxPadding);
		end.x = start.x + boxWidth;
		TheWindowManager->winDrawImage(blankSquare,
																								start.x, start.y,
																								end.x, end.y);
	}
}
