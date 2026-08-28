// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// W3DGadgetStaticTextImageDraw, retail 0x00796ED0 (238 bytes), together with
// the file-static drawStaticTextText it calls, retail 0x00796BA0 (346 bytes).
//
// The static MUST live in the same TU as its caller: retail gives it MSVC 7.1's
// private internal-linkage register convention (window arrives in EAX, the two
// colours on the stack, caller cleans with `add esp,8'), which has no C++
// spelling on a declaration but which the compiler reproduces on its own once
// every call site is visible to it.
//
// Layout facts reused from W3DHorizontalSliderDraw_Thunk.cpp: BFME's
// WinInstanceData is four bytes longer than the vendored one, so the three
// GameWindow draw-data arrays sit at +0x48 (enabled), +0xB4 (disabled) and
// +0x120 (hilite) with twelve-byte entries { image, color, borderColor }.
// Retail reads [win+0x48] and [win+0xB4] here for the image, pinning entry+0.
// WinInstanceData::m_imageOffset is at +0x17C.
//
// Local ABI-slice replica so no shared header moves.
//
// The one shape note, and it is the same one in BOTH bodies: the `Int w =
// size.x, h = size.y;' pair.  MSVC 7.1 picks the lea's SIB base from the
// storage class of the addends, and routing the SIZE through a scalar
// temporary makes size the INDEX and start the BASE.  Without it both bodies
// emit lea [size + start] where retail is lea [start + size]:
//   0x00796DEB  end.x = start.x + size.x   retail 8d 14 08, ours 8d 14 01
//   0x00796F6A  end.x = start.x + size.x   retail 8d 1c 08, ours 8d 1c 01
// Nothing else reaches it -- operand swap, parenthesisation, re-association,
// compound assignment, statement reorder, and a temporary on the START side
// (which is the form that landed W3DGadgetHorizontalSliderDraw) were each
// measured here and none of them move the encoding.  The two addends are both
// ICoord2D members in the static-text bodies, which is the case an earlier
// pass recorded as having no handle to pull; the handle is the OTHER addend.
// end.y matches either way, which is what kept making this look like
// allocation noise rather than a source-level fact.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;
typedef unsigned char Bool;

class Image;
class GameWindow;

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATUS_WRAP_CENTERED = 0x00040000 };
enum { WIN_STATUS_HOTKEY_TEXT = 0x00100000 };
enum { WIN_COLOR_UNDEFINED = 0x00FFFFFF };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// DisplayString is reached only through its vtable; the slots ahead of the
// ones used place them.  Witnessed: getTextLength +0x0C, setWordWrap +0x20,
// setWordWrapCentered +0x24, the two-colour setter +0x28, the four-argument
// draw +0x38, getSize +0x3C, setUseHotkey +0x4C, setClipRegion +0x50.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void unused00();								///< +0x00
	virtual void unused01();								///< +0x04
	virtual void unused02();								///< +0x08
	virtual Int getTextLength(void);						///< +0x0C
	virtual void unused04();								///< +0x10
	virtual void unused05();								///< +0x14
	virtual void unused06();								///< +0x18
	virtual void unused07();								///< +0x1C
	virtual void setWordWrap(Int wordWrap);					///< +0x20
	virtual void setWordWrapCentered(Bool centered);		///< +0x24
	virtual void setTextColor(Color color, Color drop);		///< +0x28
	virtual void unused11();								///< +0x2C
	virtual void unused12();								///< +0x30
	virtual void unused13();								///< +0x34
	virtual void draw(Int x, Int y, Int color, Int drop);	///< +0x38
	virtual void getSize(Int *width, Int *height);			///< +0x3C
	virtual void unused16();								///< +0x40
	virtual void unused17();								///< +0x44
	virtual void unused18();								///< +0x48
	virtual void setUseHotkey(Bool use, Color color);		///< +0x4C
	virtual void setClipRegion(IRegion2D *region);			///< +0x50
};

struct TextData
{
	DisplayString *text;									///< +0x00
	Bool centered;											///< +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	unsigned char m_unreconstructed_000[0x17C];
	ICoord2D m_imageOffset;									///< retail this+0x17C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);								///< ILT thunk at 0x00046538
	Int winGetScreenPosition(Int *x, Int *y);				///< ILT thunk at 0x0002F94B
	Int winGetSize(Int *width, Int *height);				///< ILT thunk at 0x00036EBC
	UnsignedInt winGetStatus(void);							///< ILT thunk at 0x00023DDA
	Int winGetEnabledTextColor(void);						///< ILT thunk at 0x0002A5D1
	Int winGetEnabledTextBorderColor(void);					///< ILT thunk at 0x0002D7EA
	Int winGetDisabledTextColor(void);						///< ILT thunk at 0x0002D4E8
	Int winGetDisabledTextBorderColor(void);				///< ILT thunk at 0x0002C55C

	const WinDrawData *enabledDrawData(Int index) { return &m_enabledDrawData[index]; }
	const WinDrawData *disabledDrawData(Int index) { return &m_disabledDrawData[index]; }

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];						///< retail this+0x48
	WinDrawData m_disabledDrawData[9];						///< retail this+0xB4
	WinDrawData m_hiliteDrawData[9];						///< retail this+0x120
};

// Only winDrawImage is reconstructed; the slots ahead of it place it.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
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

	virtual void winDrawImage(const Image *image,
														Int startX, Int startY,
														Int endX, Int endY,
														Color color = 0xFFFFFFFF);	///< vtable +0xF4
	virtual void winFillRect(Color color, Real width,
													 Int startX, Int startY,
													 Int endX, Int endY);				///< vtable +0xF8
	virtual void winOpenRect(Color color, Real width,
													 Int startX, Int startY,
													 Int endX, Int endY);				///< vtable +0xFC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_000[0xC3C];
	Color m_hotKeyTextColor;								///< retail this+0xC3C
};

extern GameWindowManager *TheWindowManager;					///< retail [0x012F1B40]
extern GlobalData *TheGlobalData;							///< retail [0x012ED5C8]

inline Int BitTest(UnsignedInt bits, UnsignedInt mask) { return (bits & mask) != 0; }

#define TRUE 1
#define FALSE 0
#define NULL 0

// GadgetStaticText.h header inlines over draw-data index 0.
inline const Image *GadgetStaticTextGetEnabledImage( GameWindow *g ) { return g->enabledDrawData( 0 )->image; }
inline const Image *GadgetStaticTextGetDisabledImage( GameWindow *g ) { return g->disabledDrawData( 0 )->image; }

#define WIN_DRAW_LINE_WIDTH 1.0f

// drawStaticTextText =========================================================
// ?drawStaticTextText@@YAXPAVGameWindow@@HH@Z
//
// BFME's body differs from the vendored ZH one in four witnessed ways: three
// parameters, not four (no WinInstanceData); no centeredVertically branch, the
// vertical centering is unconditional; the horizontal else-branch adds the
// literal 7 rather than tData->leftMargin; and the single ZH
// draw(x,y,color,dropColor) becomes a two-colour setter at vtable +0x28
// followed by draw(x,y,1,1) at +0x38.
static void drawStaticTextText( GameWindow *window,
																Color textColor, Color textDropColor )
{
	TextData *tData = (TextData *)window->winGetUserData();
	Int textWidth, textHeight, wordWrap;
	DisplayString *text = tData->text;
	ICoord2D origin, size, textPos;
	IRegion2D clipRegion;

	// sanity
	if( text == NULL || text->getTextLength() == 0 )
		return;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// Set the text Wrap width
	wordWrap = size.x - 10;
	text->setWordWrap( wordWrap );
	if( BitTest( window->winGetStatus(), WIN_STATUS_WRAP_CENTERED ) )
		text->setWordWrapCentered( TRUE );
	else
		text->setWordWrapCentered( FALSE );
	if( BitTest( window->winGetStatus(), WIN_STATUS_HOTKEY_TEXT ) && TheGlobalData )
		text->setUseHotkey( TRUE, TheGlobalData->m_hotKeyTextColor );
	else
		text->setUseHotkey( FALSE, 0 );

	// how much space will this text take up
	text->getSize( &textWidth, &textHeight );

	// Init the clip region
	clipRegion.lo.x = origin.x;
	clipRegion.lo.y = origin.y;
	clipRegion.hi.x = origin.x + size.x;
	clipRegion.hi.y = origin.y + size.y;

	// horizontal centering?
	if( tData->centered )
	{
		textPos.x = origin.x + (size.x / 2) - (textWidth / 2);
	}
	else
	{
		textPos.x = origin.x + 7;
	}

	// vertical centering is unconditional in BFME
	textPos.y = origin.y + (size.y / 2) - (textHeight / 2);

	// draw the text
	text->setClipRegion( &clipRegion );
	text->setTextColor( textColor, textDropColor );
	text->draw( textPos.x, textPos.y, 1, 1 );

}  // end drawStaticTextText


// W3DGadgetStaticTextDraw ====================================================
// ?W3DGadgetStaticTextDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetStaticTextDraw( GameWindow *window, WinInstanceData *instData )
{
	TextData *tData = (TextData *)window->winGetUserData();
	Color backColor, backBorder, textColor, textOutlineColor;
	ICoord2D size, origin, start, end;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the colors we will use
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		backColor					= window->disabledDrawData( 0 )->color;
		backBorder				= window->disabledDrawData( 0 )->borderColor;
		textColor					= window->winGetDisabledTextColor();
		textOutlineColor	= window->winGetDisabledTextBorderColor();

	}  // end if, disabled
	else
	{

		backColor					= window->enabledDrawData( 0 )->color;
		backBorder				= window->enabledDrawData( 0 )->borderColor;
		textColor					= window->winGetEnabledTextColor();
		textOutlineColor	= window->winGetEnabledTextBorderColor();

	}  // end else, enabled

	// draw the back border
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		Int w = size.x, h = size.y;
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + w;
		end.y = start.y + h;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																			 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the back fill area
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		Int sx = origin.x + 1, sy = origin.y + 1;
		start.x = sx;
		start.y = sy;
		end.x = sx + size.x - 2;
		end.y = sy + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																			 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the text
	if( tData->text && (textColor != WIN_COLOR_UNDEFINED) )
		drawStaticTextText( window, textColor, textOutlineColor );

}  // end W3DGadgetStaticTextDraw

// W3DGadgetStaticTextImageDraw ===============================================
// ?W3DGadgetStaticTextImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetStaticTextImageDraw( GameWindow *window, WinInstanceData *instData )
{
	TextData *tData = (TextData *)window->winGetUserData();
	Color textColor, textOutlineColor;
	ICoord2D size, origin, start, end;
	const Image *image;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the colors we will use
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		image							= GadgetStaticTextGetDisabledImage( window );
		textColor					= window->winGetDisabledTextColor();
		textOutlineColor	= window->winGetDisabledTextBorderColor();

	}  // end if, disabled
	else
	{

		image							= GadgetStaticTextGetEnabledImage( window );
		textColor					= window->winGetEnabledTextColor();
		textOutlineColor	= window->winGetEnabledTextBorderColor();

	}  // end else, enabled

	// draw the back image
	if( image )
	{
		Int w = size.x, h = size.y;
		start.x = origin.x + instData->m_imageOffset.x;
		start.y = origin.y + instData->m_imageOffset.y;
		end.x = start.x + w;
		end.y = start.y + h;
		TheWindowManager->winDrawImage( image, start.x, start.y, end.x, end.y );

	}  // end if

	// draw the text
	if( tData->text && (textColor != WIN_COLOR_UNDEFINED) )
		drawStaticTextText( window, textColor, textOutlineColor );

}  // end W3DGadgetStaticTextImageDraw
