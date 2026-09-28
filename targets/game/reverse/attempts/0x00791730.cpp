// ?W3DGadgetHorizontalSliderImageDrawB@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.9913 date=2026-09-28
// ?W3DGadgetHorizontalSliderImageDrawB@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// W3DGadgetHorizontalSliderImageDrawB, retail 0x00791730 (1380 bytes, ret).
// Identity: the seven UTF-16 debug literals it formats ("mult:%g/%g, img
// offset:%d,%d", "\norigin: %d,%d size:%d,%d", "\ns= %d <--> %d, numTicks=%g,
// pos = %d", "\nHighlighted: ...", "\n  bsX = ...", "\ntop: start=...") are
// Zero Hour's W3DGadgetHorizontalSliderImageDrawB (W3DHorizontalSlider.cpp)
// word for word, and the draw loops, the tooltip hand-off and the image
// accessors follow it line for line. BFME only adds the resolution scale gate:
// the 800x600 multipliers stay 1.0 when window status bit 0x08000000 is set.
// Retail's UnicodeString is the StringBase<unsigned short> wrapper
// (stringbaseunicode shim): by-value format strings, inline concat.
// BANKED 1380/1380 bytes, 12 differing: in the HILITED block (+0x2AE..+0x30D)
// retail loads size.x into eax and origin.x into ecx for `origin.x + size.x`
// (loop test and the "bsX" format args); ours swaps the two. Not reached by
// operand order, declaration order, block scope, raw state read (worse) or the
// 9 shape-family choices. Intended home: the Gadget directory next to
// W3DHorizontalSlider.cpp, whose older ZH-port copy of this function is
// unclaimed and should be removed when this lands.

#include <wchar.h>
#include "string_base.h"
template <typename T> inline const T *StringBase<T>::str() const { return m_data ? m_data->data : (const T *)L""; }
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;

#define INT_TO_REAL(x) ((Real)(x))

struct ICoord2D
{
	Int x, y;
};

class Image
{
public:
	Int getImageWidth( void ) const { return m_imageSize.x; }
	Int getImageHeight( void ) const { return m_imageSize.y; }

private:
	unsigned char m_unmodelled00[ 0x24 ];
	ICoord2D m_imageSize;
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

enum { MAX_DRAW_DATA = 9 };
enum { WIN_STATE_HILITED = 0x00000002 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	UnsignedInt getState( void ) { return m_state; }
	void setTooltipText( UnicodeString tip );

	unsigned char m_unmodelled00[ 0x08 ];
	UnsignedInt m_state;
	unsigned char m_unmodelled0c[ 0x4c - 0x0c ];
	WinDrawData m_disabledDrawData[ MAX_DRAW_DATA ];
	WinDrawData m_hiliteDrawData[ MAX_DRAW_DATA ];
	unsigned char m_unmodelled124[ 0x17c - 0x124 ];
	ICoord2D m_imageOffset;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	void *winGetUserData( void );
	UnsignedInt winGetStatus( void );
	const Image *winGetDisabledImage( Int index ) { return m_instData.m_disabledDrawData[ index ].image; }
	const Image *winGetHiliteImage( Int index ) { return m_instData.m_hiliteDrawData[ index ].image; }

private:
	unsigned char m_unmodelled00[ 0x68 ];
	WinInstanceData m_instData;
};

inline const Image *GadgetSliderGetDisabledImageLeft( GameWindow *g ) { return g->winGetDisabledImage( 0 ); }
inline const Image *GadgetSliderGetDisabledImageRight( GameWindow *g ) { return g->winGetDisabledImage( 1 ); }
inline const Image *GadgetSliderGetHiliteImageLeft( GameWindow *g ) { return g->winGetHiliteImage( 0 ); }

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetSlider.h
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

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60();
	virtual void winDrawImage( const Image *image, Int startX, Int startY,
		Int endX, Int endY, Color color = 0xFFFFFFFF );
};

extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;

// ?W3DGadgetHorizontalSliderImageDrawB@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetHorizontalSliderImageDrawB( GameWindow *window,
	WinInstanceData *instData )
{
	const Image *fillSquare, *blankSquare, *highlightSquare;
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
		xMulti = INT_TO_REAL( TheDisplay->getWidth() ) / 800;
		yMulti = INT_TO_REAL( TheDisplay->getHeight() ) / 600;
	}
	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	UnicodeString tooltip, tmp;
	tooltip.format( UnicodeString( L"mult:%g/%g, img offset:%d,%d" ), xMulti, yMulti, xOffset, yOffset );

	tmp.format( UnicodeString( L"\norigin: %d,%d size:%d,%d" ), origin.x, origin.y, size.x, size.y );
	tooltip.concat( tmp );

	tmp.format( UnicodeString( L"\ns= %d <--> %d, numTicks=%g, pos = %d" ), s->minVal, s->maxVal, s->numTicks, s->position );
	tooltip.concat( tmp );

	if( instData->getState() & WIN_STATE_HILITED )
	{
		highlightSquare = GadgetSliderGetHiliteImageLeft( window );
		ICoord2D backgroundStart, backgroundEnd;
		backgroundStart.x = origin.x - ( highlightSquare->getImageWidth() * xMulti ) / 2;
		backgroundStart.y = origin.y + ( highlightSquare->getImageHeight() * yMulti ) / 3;
		backgroundEnd.y = backgroundStart.y + highlightSquare->getImageHeight() * yMulti;
		backgroundEnd.x = backgroundStart.x + highlightSquare->getImageWidth() * xMulti;

		tmp.format( UnicodeString( L"\nHighlighted: (%d,%d) -> (%d,%d), step %d/%g, full %d/%d" ), backgroundStart.x, backgroundStart.y,
			backgroundEnd.x, backgroundEnd.y, highlightSquare->getImageWidth(), highlightSquare->getImageWidth() * xMulti,
			origin.x, size.x );
		tooltip.concat( tmp );

		while( backgroundStart.x < origin.x + size.x )
		{
			TheWindowManager->winDrawImage( highlightSquare,
				backgroundStart.x, backgroundStart.y,
				backgroundEnd.x, backgroundEnd.y );
			backgroundStart.x = backgroundEnd.x;
			backgroundEnd.x = backgroundStart.x + highlightSquare->getImageWidth() * xMulti;
		}
		tmp.format( UnicodeString( L"\n  bsX = %d, beX = %d (%d < %d+%d or %d?)" ), backgroundStart.x, backgroundEnd.x,
			backgroundStart.x, origin.x, size.x, origin.x + size.x );
		tooltip.concat( tmp );
	}

	fillSquare = GadgetSliderGetDisabledImageLeft( window );
	start.x = origin.x;
	start.y = origin.y;
	end.y = start.y + fillSquare->getImageHeight() * yMulti;
	end.x = start.x + fillSquare->getImageWidth() * xMulti;

	tmp.format( UnicodeString( L"\ntop: start=%d,%d, end=%d,%d" ), start.x, start.y, end.x, end.y );
	tooltip.concat( tmp );

	while( start.x <= origin.x + ( s->numTicks * ( s->position - s->minVal ) ) && end.x < origin.x + size.x && s->position != s->minVal )
	{
		TheWindowManager->winDrawImage( fillSquare,
			start.x, start.y,
			end.x, end.y );
		start.x = end.x + 2;
		end.x = start.x + fillSquare->getImageWidth() * xMulti;
	}

	blankSquare = GadgetSliderGetDisabledImageRight( window );
	end.x = start.x + blankSquare->getImageWidth() * xMulti;

	while( end.x < origin.x + size.x )
	{
		TheWindowManager->winDrawImage( blankSquare,
			start.x, start.y,
			end.x, end.y );
		start.x = end.x + 2;
		end.x = start.x + blankSquare->getImageWidth() * xMulti;
	}

	instData->setTooltipText( tooltip );
}
