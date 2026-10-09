// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// W3DGadgetHorizontalSliderDraw, retail 0x00790D80 (227 bytes).
//
// Zero Hour's W3DHorizontalSlider.cpp body verbatim; the only thing that ever
// blocked it was layout.  BFME's WinInstanceData is four bytes longer than the vendored
// one, so the three GameWindow draw-data arrays sit at +0x48 (enabled),
// +0xB4 (disabled) and +0x120 (hilite) with twelve-byte entries
// { image, color, borderColor } -- retail reads [win+0x4C]/[win+0x50],
// [win+0xB8]/[win+0xBC] and [win+0x124]/[win+0x128], which pins all three
// bases and the entry stride at once.  The GadgetSliderGet*Color helpers are
// header inlines over index 0, which is why retail reads them directly.
//
// Local ABI-slice replica so no shared header moves.
//
// The one shape note: in the filled-back block the origin+1 value must reach
// the addition as a TEMPORARY, not as a re-read of start.x.  MSVC 7.1 picks the
// lea's SIB base from that distinction -- `end.x = start.x + size.x - 2' over a
// stored-then-re-read start.x compiles to lea esi,[ecx+eax-2] (size as base),
// while retail is lea esi,[eax+ecx-2] (start as base), which is what the
// temporary produces.  Source operand order, parenthesisation, re-association
// and statement order are all canonicalised away and do not reach it; this is
// the only lever.  end.y matches either way, which is what made the asymmetry
// look like allocation noise rather than a source-level fact.  Same fix as
// IMECandidateMainDraw 0x004C4AB0.

#include <wchar.h>
#include "string_base.h"
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;

class Image
{
public:
    Int getImageWidth() const { return m_imageSize.x; }
    Int getImageHeight() const { return m_imageSize.y; }

private:
    unsigned char m_unmodelled00[0x24];
    struct { Int x, y; } m_imageSize;
};

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATE_HILITED = 0x00000002 };
enum { WIN_COLOR_UNDEFINED = 0x00FFFFFF };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
	ICoord2D() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	UnsignedInt getState(void) const { return m_state; }
	void setTooltipText(UnicodeString tip);

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;								///< retail this+0x08
	unsigned char m_unmodelled0c[0x17c - 0x0c];
public:
	ICoord2D m_imageOffset;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);			///< ILT thunk at 0x0002F94B
	Int winGetSize(Int *width, Int *height);			///< ILT thunk at 0x00036EBC
	UnsignedInt winGetStatus(void);						///< ILT thunk at 0x00023DDA
	void *winGetUserData(void);
	const Image *winGetDisabledImage(Int index) { return m_disabledDrawData[index].image; }
	const Image *winGetHiliteImage(Int index) { return m_hiliteDrawData[index].image; }

	Color winGetEnabledColor(Int index) { return m_enabledDrawData[index].color; }
	Color winGetEnabledBorderColor(Int index) { return m_enabledDrawData[index].borderColor; }
	Color winGetDisabledColor(Int index) { return m_disabledDrawData[index].color; }
	Color winGetDisabledBorderColor(Int index) { return m_disabledDrawData[index].borderColor; }
	Color winGetHiliteColor(Int index) { return m_hiliteDrawData[index].color; }
	Color winGetHiliteBorderColor(Int index) { return m_hiliteDrawData[index].borderColor; }

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];					///< retail this+0x48
	WinDrawData m_disabledDrawData[9];					///< retail this+0xB4
	WinDrawData m_hiliteDrawData[9];					///< retail this+0x120
};

// Only the two rect calls are reconstructed; the slots ahead of them place them.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
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
	virtual void winDrawImage(const Image *image, Int startX, Int startY, Int endX, Int endY, Color color = 0xFFFFFFFF);

	virtual void winFillRect(Color color, Real width,
													 Int startX, Int startY,
													 Int endX, Int endY);		///< vtable +0xF8
	virtual void winOpenRect(Color color, Real width,
													 Int startX, Int startY,
													 Int endX, Int endY);		///< vtable +0xFC
};

extern GameWindowManager *TheWindowManager;				///< retail [0x012F1B40]

inline Int BitTest(UnsignedInt bits, UnsignedInt mask) { return (bits & mask) != 0; }


#define WIN_DRAW_LINE_WIDTH 1.0f

// GadgetSlider.h header inlines, all over draw-data index 0.
inline Color GadgetSliderGetEnabledColor( GameWindow *g ) { return g->winGetEnabledColor( 0 ); }
inline Color GadgetSliderGetEnabledBorderColor( GameWindow *g ) { return g->winGetEnabledBorderColor( 0 ); }
inline Color GadgetSliderGetDisabledColor( GameWindow *g ) { return g->winGetDisabledColor( 0 ); }
inline Color GadgetSliderGetDisabledBorderColor( GameWindow *g ) { return g->winGetDisabledBorderColor( 0 ); }
inline Color GadgetSliderGetHiliteColor( GameWindow *g ) { return g->winGetHiliteColor( 0 ); }
inline Color GadgetSliderGetHiliteBorderColor( GameWindow *g ) { return g->winGetHiliteBorderColor( 0 ); }

// ?W3DGadgetHorizontalSliderDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetHorizontalSliderDraw( GameWindow *window, WinInstanceData *instData )
{
	Color backBorder, backColor;
	ICoord2D origin, size, start, end;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == 0 )
	{

		backBorder		= GadgetSliderGetDisabledBorderColor( window );
		backColor			= GadgetSliderGetDisabledColor( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		backBorder		= GadgetSliderGetHiliteBorderColor( window );
		backColor			= GadgetSliderGetHiliteColor( window );

	}  // end else if, hilited
	else
	{

		backBorder		= GadgetSliderGetEnabledBorderColor( window );
		backColor			= GadgetSliderGetEnabledColor( window );

	}  // end else, enabled

	// draw background border and rect over whole control
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if
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

}  // end W3DGadgetHorizontalSliderDraw

struct SliderData
{
	Int minVal;
	Int maxVal;
	Real numTicks;
	Int position;
};

class Display
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot0c( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual void slot18( void ) = 0;
	virtual void slot1c( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot24( void ) = 0;
	virtual void slot28( void ) = 0;
	virtual UnsignedInt getWidth( void ) = 0;
	virtual UnsignedInt getHeight( void ) = 0;
};


extern Display *TheDisplay;

#define INT_TO_REAL(x) ((Real)(x))
// W3DGadgetHorizontalSliderImageDraw =========================================
/** Draw horizontal slider with user supplied images */
//=============================================================================
// ?W3DGadgetHorizontalSliderImageDrawB@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// Open BFME 2 donor: Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DHorizontalSlider.cpp.
void W3DGadgetHorizontalSliderImageDrawB( GameWindow *window,
																				 WinInstanceData *instData )
{
	const Image *fillSquare, *blankSquare, *highlightSquare;//, *progressArrow;
	ICoord2D origin, size, start, end;
	Int xOffset, yOffset;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	SliderData *s = (SliderData *)window->winGetUserData();

	Real xMulti = 1.0f;
	Real yMulti = 1.0f;
	if( !( window->winGetStatus() & 0x08000000 ) )
	{
		xMulti = INT_TO_REAL(TheDisplay->getWidth()) / 800;
		yMulti = INT_TO_REAL(TheDisplay->getHeight()) / 600;
	}
	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	UnicodeString tooltip, tmp;
	tooltip.format(UnicodeString(L"mult:%g/%g, img offset:%d,%d"), xMulti, yMulti, xOffset, yOffset);

	tmp.format(UnicodeString(L"\norigin: %d,%d size:%d,%d"), origin.x, origin.y, size.x, size.y);
	tooltip.concat(tmp);

	tmp.format(UnicodeString(L"\ns= %d <--> %d, numTicks=%g, pos = %d"), s->minVal, s->maxVal, s->numTicks, s->position);
	tooltip.concat(tmp);

	if( instData->getState() & WIN_STATE_HILITED )
	{
		highlightSquare					= window->winGetHiliteImage( 0 );
		ICoord2D backgroundStart, backgroundEnd;
		backgroundStart.x = origin.x - (highlightSquare->getImageWidth() * xMulti)/2;
		backgroundStart.y = origin.y + (highlightSquare->getImageHeight() *yMulti)/3;
		backgroundEnd.y = backgroundStart.y + highlightSquare->getImageHeight()* yMulti;
		backgroundEnd.x = backgroundStart.x + highlightSquare->getImageWidth() * xMulti;

		tmp.format(UnicodeString(L"\nHighlighted: (%d,%d) -> (%d,%d), step %d/%g, full %d/%d"), backgroundStart.x, backgroundStart.y,
			backgroundEnd.x, backgroundEnd.y, highlightSquare->getImageWidth(), highlightSquare->getImageWidth() * xMulti,
			origin.x, size.x);
		tooltip.concat(tmp);

		while(backgroundStart.x < origin.x + size.x)
		{
			TheWindowManager->winDrawImage( highlightSquare,
																		backgroundStart.x, backgroundStart.y,
																		backgroundEnd.x, backgroundEnd.y );
			backgroundStart.x = backgroundEnd.x;
			backgroundEnd.x = backgroundStart.x + highlightSquare->getImageWidth() * xMulti;
		}
		tmp.format(UnicodeString(L"\n  bsX = %d, beX = %d (%d < %d+%d or %d?)"), backgroundStart.x, backgroundEnd.x,
			backgroundStart.x, origin.x, size.x, origin.x + size.x);
		tooltip.concat(tmp);
	}

	fillSquare = window->winGetDisabledImage( 0 );
	start.x = origin.x;
	start.y = origin.y;
	end.y = start.y + fillSquare->getImageHeight() * yMulti;
	end.x	= start.x + fillSquare->getImageWidth()* xMulti;

	tmp.format(UnicodeString(L"\ntop: start=%d,%d, end=%d,%d"), start.x, start.y, end.x, end.y);
	tooltip.concat(tmp);

	while(start.x <= origin.x + (s->numTicks * (s->position - s->minVal)) && end.x < origin.x + size.x && s->position != s->minVal)
	{
		TheWindowManager->winDrawImage( fillSquare,
																		start.x, start.y,
																		end.x, end.y );
		start.x = end.x + 2;
		end.x	= start.x + fillSquare->getImageWidth()* xMulti;

	}

	blankSquare	= window->winGetDisabledImage( 1 );
	end.x	= start.x + blankSquare->getImageWidth()* xMulti;

	while(end.x < origin.x + size.x )
	{
		TheWindowManager->winDrawImage( blankSquare,
																		start.x, start.y,
																		end.x, end.y );
		start.x = end.x + 2;
		end.x	= start.x + blankSquare->getImageWidth()* xMulti;
	}

	instData->setTooltipText(tooltip);

//	if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
//	{
//		progressArrow				= GadgetSliderGetHiliteImageRight( window );
//		if(!progressArrow)
//			return;
//		Int transPos = (s->numTicks * (s->position - s->minVal)) - progressArrow->getImageWidth() /2;
//		start.x = origin.x + transPos;
//		start.y = origin.y + fillSquare->getImageHeight()/3*2;
//		end.y = start.y + progressArrow->getImageHeight();
//		end.x	= start.x + progressArrow->getImageWidth();
//		TheWindowManager->winDrawImage( progressArrow,
//																			start.x, start.y,
//																			end.x, end.y );
//	}
}
