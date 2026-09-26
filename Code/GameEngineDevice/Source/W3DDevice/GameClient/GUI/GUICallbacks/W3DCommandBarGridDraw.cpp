// cl: /DNDEBUG /MD
// W3DCommandBarGridDraw, retail 0x00799FA0 (634 bytes).
//
// Identity: the Zero Hour twin (W3DControlBar.cpp) has the same shape --
// image-status early default draw, screen position/size, border colour from
// TheControlBar pushed into winSetEnabledBorderColor(0, color), default draw,
// then four drawLine calls at 0.33 and 0.66 of the window size.
// BFME inlines W3DGameWinDefaultDraw as the per-window draw callback at
// +0x1E8 with the embedded delegate at +0x218 as fallback (same shape as
// the landed W3DRightHUDDraw), and Display::drawLine is an inline wrapper
// that brackets the Real-coordinate line slot (+0xB8) with +0xB0/+0xDC
// (same shape as the landed ShellMenuScheme::draw).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;

class WinInstanceData;

struct ICoord2D
{
	Int x;
	Int y;
};

enum
{
	WIN_STATUS_IMAGE = 0x00000080
};

#define BitTest( x, i ) ( ( (x) & (i) ) != 0 )

class GameWindow
{
public:
	UnsignedInt winGetStatus( void );
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	Int winSetEnabledBorderColor( Int index, Color color );
};

typedef void (__cdecl *BfmeWindowDrawFunc)( GameWindow *, WinInstanceData * );

class BfmeWindowDrawDelegate
{
public:
	virtual void unused00();
	virtual void draw( GameWindow *window, WinInstanceData *instData );
};

inline void W3DGameWinDefaultDraw( GameWindow *window, WinInstanceData *instData )
{
	BfmeWindowDrawFunc draw = *(BfmeWindowDrawFunc *)((char *)window + 0x1e8);
	if ( draw )
		draw( window, instData );
	else
		((BfmeWindowDrawDelegate *)((char *)window + 0x218))->draw( window, instData );
}

// Only the +0x294 colour this callback reads is modelled; the ZH twin reads
// it through ControlBar::getBorderColor. The BFME offset is not witnessed by
// name_oracle, so the storage keeps an offset name.
class ControlBar
{
public:
	Color getBorderColor( void ) const { return m_unmodelled294; }

private:
	unsigned char m_unreconstructed_000[0x294];
	Color m_unmodelled294;                                 // +0x294
};

class Display
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
	virtual void slotB0( void );                           // +0xB0 opens the bracket
	virtual void slotB4();
	virtual void slotB8( Real startX, Real startY, Real endX, Real endY,
		Real lineWidth, UnsignedInt lineColor );             // +0xB8
	virtual void slotBC(); virtual void slotC0(); virtual void slotC4();
	virtual void slotC8(); virtual void slotCC(); virtual void slotD0();
	virtual void slotD4(); virtual void slotD8();
	virtual void slotDC( void );                           // +0xDC closes the bracket

	void drawLine( Real startX, Real startY, Real endX, Real endY, Real lineWidth,
		UnsignedInt lineColor )
	{
		slotB0();
		slotB8( startX, startY, endX, endY, lineWidth, lineColor );
		slotDC();
	}
};

extern ControlBar *TheControlBar;
extern Display *TheDisplay;

void W3DCommandBarGridDraw( GameWindow *window, WinInstanceData *instData )
{
	if( BitTest(window->winGetStatus(), WIN_STATUS_IMAGE ))
	{
		W3DGameWinDefaultDraw( window, instData );
		return;
	}

	ICoord2D pos, size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );

	Color color = TheControlBar->getBorderColor();
	window->winSetEnabledBorderColor(0, color);
	W3DGameWinDefaultDraw( window, instData );

	TheDisplay->drawLine(pos.x, pos.y + size.y * .33, pos.x + size.x, pos.y+ size.y*.33, 1,color);
	TheDisplay->drawLine(pos.x, pos.y + size.y * .66, pos.x + size.x, pos.y+ size.y*.66, 1,color);
	TheDisplay->drawLine(pos.x + size.x * .33, pos.y, pos.x + size.x *.33, pos.y +size.y, 1,color);
	TheDisplay->drawLine(pos.x + size.x  * .66, pos.y, pos.x + size.x *.66, pos.y + size.y, 1,color);
}
