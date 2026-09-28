// ?W3DGadgetPushButtonImageDrawOne@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.95 date=2026-09-28
// ?W3DGadgetPushButtonImageDrawOne@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// Retail 0x00795140 (2761 bytes): EH prologue through the final ret at +0xAC8
// (int3 padding follows at 0x00795C09); the ledger extent is already correct.
//
// Identity: the matched W3DGadgetPushButtonImageDraw dispatcher (0x00795EE0)
// calls this symbol for the single-image button.  The body is the Zero Hour
// W3DPushButton.cpp DrawOne with BFME's additions: seven function statics
// looked up at entry (Cameo_push, Cameo_hilited, RadialPush, RadialOver,
// RadialBorder, RadialClockOverlay1, RadialClockOverlay2), a status-bit
// 0x04000000 radial mode with stencil helpers, the radial clock overlays and
// a static file-local overlay helper at 0x00794040.  Status bit names come
// from their position in the ZH DrawOne control flow.  drawButtonText is the
// matched file-local helper at 0x00793EE0.
//
// NEAR MISS: same size, instruction stream equal; 139 bytes differ, all
// stack-slot displacements.  Retail frame: image -64, string temps and colours
// -60, block floats -56..-40, start -36, size -28, end -20.  Ours puts the
// seventh AsciiString temporary alone on -56 and rotates end/start/size.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class GameFont;
class VideoBuffer;
class Image;
class PlayerList;
class GlobalData;

// BFME ICoord2D has a user-declared empty constructor (retail ??0ICoord2D@@QAE@XZ).
struct ICoord2D
{
	Int x;
	Int y;
	ICoord2D() {}
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// Image width at +0x24; the rest of Image stays opaque.
inline Int imageWidth(const Image *image)
{
	return *(const Int *)((const unsigned char *)image + 0x24);
}

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
	UnsignedInt getStatus(void) const { return m_status; }

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;								// +0x08
	UnsignedInt m_style;								// +0x0C
	UnsignedInt m_status;								// +0x10
	unsigned char m_unreconstructed_14[0x168];

public:
	ICoord2D m_imageOffset;								// +0x17C
	unsigned char m_unreconstructed_184[0x18];
	DisplayString *m_text;								// +0x19C
	DisplayString *m_tooltip;							// +0x1A0
	VideoBuffer *m_videoBuffer;							// +0x1A4
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);
	void *winGetUserData(void);
	void winSetUserData(void *data);
	GameFont *winGetFont(void);

	const Image *winGetEnabledImage(Int index) const { return m_enabledDrawData[index].image; }
	const Image *winGetDisabledImage(Int index) const { return m_disabledDrawData[index].image; }
	const Image *winGetHiliteImage(Int index) const { return m_hiliteDrawData[index].image; }

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];					// +0x48
	WinDrawData m_disabledDrawData[9];					// +0xB4
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
		Color color = 0xffffffff);						// +0xF4
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
	virtual void unused37(); virtual void unused38();
	virtual void unused39(); virtual void unused40();
	virtual void unused41(); virtual void unused42();
	virtual void unused43();
	virtual void beginImageDraw(void);					// +0xB0
	virtual void unused45(); virtual void unused46();
	virtual void unused47(); virtual void unused48();
	virtual void slotC4(Real x, Real y, Real width, Real height,
		Color color);									// +0xC4
	virtual void unused50(); virtual void unused51(); virtual void unused52();
	virtual void drawImageCore(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode);	// +0xD4
	virtual void unused54();
	virtual void endImageDraw(void);					// +0xDC
	virtual void drawVideoBuffer(VideoBuffer *buffer, Real startX,
		Real startY, Real endX, Real endY, Color color = -1);	// +0xE0

	// Direct helper bodies at the retail call sites, not vtable slots.
	void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode);
	void bfmeRunD(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Real percent, Color color);
	void drawRectClock(Real startX, Real startY, Real width, Real height,
		Real percent, Color color);
	void drawRemainingRectClock(Real startX, Real startY, Real width,
		Real height, Real percent, Color color);
	void drawOpenRect(Real startX, Real startY, Real width, Real height,
		Real lineWidth, Color color);
};

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;
extern PlayerList *ThePlayerList;
extern GlobalData *TheWritableGlobalData;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

void d_00933af0(void);
void Rva00933B80StencilBlendA(void);
void Rva00933BF0StencilBlendB(void);
void Rva00933810StencilStateA(void);

// Existing retail thunk at RVA 0x000327A4 (the banked number-draw body).
void j_000327a4(GameWindow *window, WinInstanceData *instData,
	struct PushButtonData *pData);

inline void drawImageInline(Display *display, const Image *image,
	Real startX, Real startY, Real endX, Real endY, Color color, Int mode)
{
	display->beginImageDraw();
	display->drawImageCore(image, startX, startY, endX, endY, color, mode);
	display->endImageDraw();
}

inline void fillRectInline(Display *display, Real x, Real y, Real width,
	Real height, Color color)
{
	display->beginImageDraw();
	display->slotC4(x, y, width, height, color);
	display->endImageDraw();
}

// PlayerList+0x0C is m_local (layout witness); deeper fields stay opaque.
inline const unsigned char *localPlayerOf(const PlayerList *list)
{
	return *(const unsigned char * const *)((const unsigned char *)list + 0x0C);
}

inline Color globalColorAt(const GlobalData *data, Int offset)
{
	return *(const Color *)((const unsigned char *)data + offset);
}

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green,
	UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

struct PushButtonData
{
	UnsignedByte drawClock;								// +0x00
	Int percentClock;									// +0x04
	Color colorClock;									// +0x08
	UnsignedByte drawBorder;							// +0x0C
	Color colorBorder;									// +0x10
	void *userData;										// +0x14
	const Image *overlayImage;							// +0x18
	unsigned char unmodelled_1C[0x0C];
	UnsignedByte field28;								// +0x28
};

enum
{
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATE_SELECTED = 0x00000004,
	WIN_STATE_HILITED = 0x00000002,
	WIN_STATUS_WRAP_CENTERED = 0x00040000,
	GAME_COLOR_UNDEFINED = 0x00FFFFFF,
	NORMAL_CLOCK = 1,
	INVERSE_CLOCK = 2
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

void getButtonTextColors(GameWindow *window, WinInstanceData *instData,
	Color *textColor, Color *dropColor);

// File-local text helper (retail 0x00793EE0); the caller passes window in
// ECX and instData in EAX, the private register convention of a static.
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

enum
{
	WIN_STATUS_USE_OVERLAY_STATES = 0x00200000,
	WIN_STATUS_NOT_READY = 0x00400000,
	WIN_STATUS_FLASHING = 0x00800000,
	WIN_STATUS_ALWAYS_COLOR = 0x01000000,
	WIN_STATUS_RVA00795140_04000000 = 0x04000000,
	WIN_STATUS_RVA00795140_40000000 = 0x40000000,
	WIN_STATUS_RVA00795140_80000000 = 0x80000000
};

// Retail 0x00794040: centred, image-scaled overlay draw (private register call).
static void drawCenteredScaledImage00794040(const Image *image, const ICoord2D *start,
	const ICoord2D *size, Color color)
{
	Real halfX = size->x * 0.5f;
	Real halfY = size->y * 0.5f;
	Real centerX = start->x + halfX;
	Real centerY = start->y + halfY;
	Real extentX = imageWidth(image) * halfX * (1.0f / 48.0f);
	Real extentY = *(const Int *)((const unsigned char *)image + 0x28) * halfY * (1.0f / 48.0f);
	drawImageInline(TheDisplay, image, centerX - extentX, centerY - extentY,
		centerX + extentX, centerY + extentY, color, 2);
}

// ?W3DGadgetPushButtonImageDrawOne@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetPushButtonImageDrawOne(GameWindow *window, WinInstanceData *instData)
{
	static const Image *cameoPush = TheMappedImageCollection->findImageByName("Cameo_push");
	static const Image *cameoHilited = TheMappedImageCollection->findImageByName("Cameo_hilited");
	static const Image *radialPush = TheMappedImageCollection->findImageByName("RadialPush");
	static const Image *radialOver = TheMappedImageCollection->findImageByName("RadialOver");
	static const Image *radialBorder = TheMappedImageCollection->findImageByName("RadialBorder");
	static const Image *radialClock1 = TheMappedImageCollection->findImageByName("RadialClockOverlay1");
	static const Image *radialClock2 = TheMappedImageCollection->findImageByName("RadialClockOverlay2");

	const Image *image = 0;
	ICoord2D size, start, end;

	image = buttonEnabled(window, 0);

	if (!BitTest(window->winGetStatus(), WIN_STATUS_USE_OVERLAY_STATES) &&
		!BitTest(window->winGetStatus(), WIN_STATUS_RVA00795140_40000000))
	{
		if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
		{
			if (BitTest(instData->getState(), WIN_STATE_SELECTED))
				image = buttonDisabled(window, 1);
			else
				image = buttonDisabled(window, 0);
		}
		else if (BitTest(instData->getState(), WIN_STATE_HILITED))
		{
			if (BitTest(instData->getState(), WIN_STATE_SELECTED))
				image = buttonHilite(window, 1);
			else
				image = buttonHilite(window, 0);
		}
		else
		{
			if (BitTest(instData->getState(), WIN_STATE_SELECTED))
				image = buttonHilite(window, 1);
		}
	}

	Bool radial = (Bool)BitTest(window->winGetStatus(), WIN_STATUS_RVA00795140_04000000);

	if (image)
	{
		window->winGetScreenPosition(&start.x, &start.y);
		window->winGetSize(&size.x, &size.y);

		start.x += instData->m_imageOffset.x;
		start.y += instData->m_imageOffset.y;

		end.x = start.x + size.x;
		end.y = start.y + size.y;

		Int drawMode = 2;
		Color colorMultiplier = 0xffffffff;

		if (BitTest(window->winGetStatus(), WIN_STATUS_USE_OVERLAY_STATES) &&
			!BitTest(window->winGetStatus(), WIN_STATUS_RVA00795140_40000000))
		{
			if (!BitTest(window->winGetStatus(), WIN_STATUS_ENABLED))
			{
				if (!BitTest(window->winGetStatus(), WIN_STATUS_NOT_READY))
				{
					if (!BitTest(window->winGetStatus(), WIN_STATUS_ALWAYS_COLOR))
						drawMode = 1;
					else
						colorMultiplier = 0xff909090;
				}
			}
		}

		if (radial)
		{
			drawMode = (drawMode == 1) ? 4 : 0;
			d_00933af0();
			Rva00933B80StencilBlendA();
			fillRectInline(TheDisplay, start.x, start.y, end.x - start.x,
				end.y - start.y, 0xffffffff);
			Rva00933BF0StencilBlendB();
		}

		drawImageInline(TheDisplay, image, start.x, start.y, end.x, end.y,
			colorMultiplier, drawMode);

		if (radial)
			Rva00933810StencilStateA();
	}

	if (instData->m_text && instData->m_text->getTextLength())
		drawButtonText(window, instData);

	window->winGetScreenPosition(&start.x, &start.y);
	window->winGetSize(&size.x, &size.y);

	if (instData->m_videoBuffer)
	{
		TheDisplay->drawVideoBuffer(instData->m_videoBuffer,
			start.x, start.y, start.x + size.x, start.y + size.y);
	}

	PushButtonData *pData = (PushButtonData *)window->winGetUserData();
	if (pData)
	{
		if (pData->overlayImage)
			drawImageInline(TheDisplay, pData->overlayImage, start.x, start.y,
				start.x + size.x, start.y + size.y, 0xffffffff, 2);

		if (pData->drawClock)
		{
			if (pData->drawClock == NORMAL_CLOCK && pData->percentClock > 0)
			{
				TheDisplay->drawRectClock(start.x, start.y, size.x, size.y,
					pData->percentClock, pData->colorClock);
			}
			else if (pData->drawClock == INVERSE_CLOCK && pData->percentClock < 100)
			{
				Color clockColor = 0;
				if (ThePlayerList && localPlayerOf(ThePlayerList))
				{
					const unsigned char *owner = *(const unsigned char * const *)(localPlayerOf(ThePlayerList) + 0x04);
					if (owner && owner[0x118])
						clockColor = globalColorAt(TheWritableGlobalData, 0x1218);
					else
						clockColor = globalColorAt(TheWritableGlobalData, 0x1214);
				}

				Real halfX = size.x * 0.5f;
				Real halfY = size.y * 0.5f;
				Real centerX = start.x + halfX;
				Real centerY = start.y + halfY;
				Real extentX = halfX * (46.0f / 48.0f);
				Real extentY = halfY * (46.0f / 48.0f);
				Real bottom = centerY + extentY;
				Real right = centerX + extentX;
				Real top = centerY - extentY;
				Real left = centerX - extentX;
				TheDisplay->bfmeRunD(radialClock1, left, top, right, bottom,
					pData->percentClock, pData->colorClock);
				TheDisplay->bfmeRunD(radialClock2, left, top, right, bottom,
					pData->percentClock, clockColor);
			}
			pData->drawClock = 0;
			window->winSetUserData(pData);
		}

		if (!radial && pData->drawBorder && pData->colorBorder != GAME_COLOR_UNDEFINED)
			TheDisplay->drawOpenRect(start.x - 1, start.y - 1, size.x + 2,
				size.y + 2, 1, pData->colorBorder);

		if (pData->field28 == 1)
			j_000327a4(window, instData, pData);
	}

	if (BitTest(window->winGetStatus(), WIN_STATUS_FLASHING) && !radial)
		drawImageInline(TheDisplay, cameoHilited, start.x, start.y,
			start.x + size.x, start.y + size.y, 0xffffffff, 2);

	static const Color normalColor = GameMakeColor(255, 255, 255, 255);
	static const Color grayColor = GameMakeColor(144, 144, 144, 255);
	Color overlayColor = BitTest(window->winGetStatus(), WIN_STATUS_RVA00795140_80000000) ?
		grayColor : normalColor;

	if (BitTest(window->winGetStatus(), WIN_STATUS_USE_OVERLAY_STATES) &&
		BitTest(window->winGetStatus(), WIN_STATUS_ENABLED))
	{
		if (BitTest(instData->getState(), WIN_STATE_HILITED))
		{
			if (BitTest(instData->getState(), WIN_STATE_SELECTED))
			{
				if (radial)
					drawCenteredScaledImage00794040(radialPush, &start, &size, overlayColor);
				else
					TheDisplay->drawImage(cameoPush, start.x, start.y,
						start.x + size.x, start.y + size.y, overlayColor, 2);
			}
			else
			{
				if (radial)
					drawCenteredScaledImage00794040(radialOver, &start, &size, overlayColor);
				else
					TheDisplay->drawImage(cameoHilited, start.x, start.y,
						start.x + size.x, start.y + size.y, overlayColor, 2);
			}
		}
		else if (radial)
			drawCenteredScaledImage00794040(radialBorder, &start, &size, overlayColor);
		else if (BitTest(instData->getState(), WIN_STATE_SELECTED))
			TheDisplay->drawImage(cameoPush, start.x, start.y,
				start.x + size.x, start.y + size.y, overlayColor, 2);
	}
	else if (radial)
		drawCenteredScaledImage00794040(radialBorder, &start, &size, overlayColor);
}
