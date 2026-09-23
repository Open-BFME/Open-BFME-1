// ?W3DGadgetProgressBarImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.9228 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// W3DGadgetProgressBarImageDraw, retail 0x00793620 (868 bytes).
//
// The drift row included two alignment bytes at 0x0079361E.  Retail's first
// instruction is the prologue at 0x00793620; the body ends at 0x00793983.
// Keep the BFME ABI slice local: the vendored headers describe the shorter
// Zero Hour WinInstanceData/GameWindow layout.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;

class Image
{
public:
	Int getImageWidth(void) const { return m_imageWidth; }
	Int getImageHeight(void) const { return m_imageHeight; }

private:
	unsigned char m_unreconstructed_00[0x24];
	Int m_imageWidth;
	Int m_imageHeight;
};

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	ICoord2D lo, hi;
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

	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;
	unsigned char m_unreconstructed_08[0x170];
	ICoord2D m_imageOffset;
};

class GameWindow
{
public:
	void *winGetUserData(void);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);

	const Image *winGetEnabledImage(Int index) { return m_enabledDrawData[index].image; }
	const Image *winGetDisabledImage(Int index) { return m_disabledDrawData[index].image; }
	const Image *winGetHiliteImage(Int index) { return m_hiliteDrawData[index].image; }

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];
	WinDrawData m_disabledDrawData[9];
	WinDrawData m_hiliteDrawData[9];
};

inline const Image *GadgetProgressBarGetEnabledImageLeft(GameWindow *g) { return g->winGetEnabledImage(0); }
inline const Image *GadgetProgressBarGetEnabledImageRight(GameWindow *g) { return g->winGetEnabledImage(1); }
inline const Image *GadgetProgressBarGetEnabledImageCenter(GameWindow *g) { return g->winGetEnabledImage(2); }
inline const Image *GadgetProgressBarGetEnabledBarImageRight(GameWindow *g) { return g->winGetEnabledImage(5); }
inline const Image *GadgetProgressBarGetEnabledBarImageCenter(GameWindow *g) { return g->winGetEnabledImage(6); }

inline const Image *GadgetProgressBarGetDisabledImageLeft(GameWindow *g) { return g->winGetDisabledImage(0); }
inline const Image *GadgetProgressBarGetDisabledImageRight(GameWindow *g) { return g->winGetDisabledImage(1); }
inline const Image *GadgetProgressBarGetDisabledImageCenter(GameWindow *g) { return g->winGetDisabledImage(2); }
inline const Image *GadgetProgressBarGetDisabledBarImageRight(GameWindow *g) { return g->winGetDisabledImage(5); }
inline const Image *GadgetProgressBarGetDisabledBarImageCenter(GameWindow *g) { return g->winGetDisabledImage(6); }

inline const Image *GadgetProgressBarGetHiliteImageLeft(GameWindow *g) { return g->winGetHiliteImage(0); }
inline const Image *GadgetProgressBarGetHiliteImageRight(GameWindow *g) { return g->winGetHiliteImage(1); }
inline const Image *GadgetProgressBarGetHiliteImageCenter(GameWindow *g) { return g->winGetHiliteImage(2); }
inline const Image *GadgetProgressBarGetHiliteBarImageRight(GameWindow *g) { return g->winGetHiliteImage(5); }
inline const Image *GadgetProgressBarGetHiliteBarImageCenter(GameWindow *g) { return g->winGetHiliteImage(6); }

#define BFME_DISPLAY_SLOT(n) virtual void bfmeDisplaySlot##n(void);
class Display
{
public:
	BFME_DISPLAY_SLOT(00) BFME_DISPLAY_SLOT(01) BFME_DISPLAY_SLOT(02)
	BFME_DISPLAY_SLOT(03) BFME_DISPLAY_SLOT(04) BFME_DISPLAY_SLOT(05)
	BFME_DISPLAY_SLOT(06) BFME_DISPLAY_SLOT(07) BFME_DISPLAY_SLOT(08)
	BFME_DISPLAY_SLOT(09) BFME_DISPLAY_SLOT(10) BFME_DISPLAY_SLOT(11)
	BFME_DISPLAY_SLOT(12) BFME_DISPLAY_SLOT(13) BFME_DISPLAY_SLOT(14)
	BFME_DISPLAY_SLOT(15) BFME_DISPLAY_SLOT(16) BFME_DISPLAY_SLOT(17)
	BFME_DISPLAY_SLOT(18) BFME_DISPLAY_SLOT(19) BFME_DISPLAY_SLOT(20)
	BFME_DISPLAY_SLOT(21) BFME_DISPLAY_SLOT(22) BFME_DISPLAY_SLOT(23)
	BFME_DISPLAY_SLOT(24) BFME_DISPLAY_SLOT(25) BFME_DISPLAY_SLOT(26)
	BFME_DISPLAY_SLOT(27) BFME_DISPLAY_SLOT(28) BFME_DISPLAY_SLOT(29)
	BFME_DISPLAY_SLOT(30) BFME_DISPLAY_SLOT(31) BFME_DISPLAY_SLOT(32)
	BFME_DISPLAY_SLOT(33)
	virtual void setClipRegion(IRegion2D *region);
	virtual void bfmeDisplaySlot35(void);
	virtual void enableClipping(Bool onoff);
};
#undef BFME_DISPLAY_SLOT

extern Display *TheDisplay;

#define BFME_WINDOW_MANAGER_SLOT(n) virtual void bfmeWindowManagerSlot##n(void);
class GameWindowManager
{
public:
	BFME_WINDOW_MANAGER_SLOT(00) BFME_WINDOW_MANAGER_SLOT(01) BFME_WINDOW_MANAGER_SLOT(02)
	BFME_WINDOW_MANAGER_SLOT(03) BFME_WINDOW_MANAGER_SLOT(04) BFME_WINDOW_MANAGER_SLOT(05)
	BFME_WINDOW_MANAGER_SLOT(06) BFME_WINDOW_MANAGER_SLOT(07) BFME_WINDOW_MANAGER_SLOT(08)
	BFME_WINDOW_MANAGER_SLOT(09) BFME_WINDOW_MANAGER_SLOT(10) BFME_WINDOW_MANAGER_SLOT(11)
	BFME_WINDOW_MANAGER_SLOT(12) BFME_WINDOW_MANAGER_SLOT(13) BFME_WINDOW_MANAGER_SLOT(14)
	BFME_WINDOW_MANAGER_SLOT(15) BFME_WINDOW_MANAGER_SLOT(16) BFME_WINDOW_MANAGER_SLOT(17)
	BFME_WINDOW_MANAGER_SLOT(18) BFME_WINDOW_MANAGER_SLOT(19) BFME_WINDOW_MANAGER_SLOT(20)
	BFME_WINDOW_MANAGER_SLOT(21) BFME_WINDOW_MANAGER_SLOT(22) BFME_WINDOW_MANAGER_SLOT(23)
	BFME_WINDOW_MANAGER_SLOT(24) BFME_WINDOW_MANAGER_SLOT(25) BFME_WINDOW_MANAGER_SLOT(26)
	BFME_WINDOW_MANAGER_SLOT(27) BFME_WINDOW_MANAGER_SLOT(28) BFME_WINDOW_MANAGER_SLOT(29)
	BFME_WINDOW_MANAGER_SLOT(30) BFME_WINDOW_MANAGER_SLOT(31) BFME_WINDOW_MANAGER_SLOT(32)
	BFME_WINDOW_MANAGER_SLOT(33) BFME_WINDOW_MANAGER_SLOT(34) BFME_WINDOW_MANAGER_SLOT(35)
	BFME_WINDOW_MANAGER_SLOT(36) BFME_WINDOW_MANAGER_SLOT(37) BFME_WINDOW_MANAGER_SLOT(38)
	BFME_WINDOW_MANAGER_SLOT(39) BFME_WINDOW_MANAGER_SLOT(40) BFME_WINDOW_MANAGER_SLOT(41)
	BFME_WINDOW_MANAGER_SLOT(42) BFME_WINDOW_MANAGER_SLOT(43) BFME_WINDOW_MANAGER_SLOT(44)
	BFME_WINDOW_MANAGER_SLOT(45) BFME_WINDOW_MANAGER_SLOT(46) BFME_WINDOW_MANAGER_SLOT(47)
	BFME_WINDOW_MANAGER_SLOT(48) BFME_WINDOW_MANAGER_SLOT(49) BFME_WINDOW_MANAGER_SLOT(50)
	BFME_WINDOW_MANAGER_SLOT(51) BFME_WINDOW_MANAGER_SLOT(52) BFME_WINDOW_MANAGER_SLOT(53)
	BFME_WINDOW_MANAGER_SLOT(54) BFME_WINDOW_MANAGER_SLOT(55) BFME_WINDOW_MANAGER_SLOT(56)
	BFME_WINDOW_MANAGER_SLOT(57) BFME_WINDOW_MANAGER_SLOT(58) BFME_WINDOW_MANAGER_SLOT(59)
	BFME_WINDOW_MANAGER_SLOT(60)
	virtual void winDrawImage(const Image *image, Int startX, Int startY,
																	Int endX, Int endY, Int color = 0xFFFFFFFF);
};
#undef BFME_WINDOW_MANAGER_SLOT

extern GameWindowManager *TheWindowManager;

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATE_HILITED = 0x00000002 };

inline Int BitTest(UnsignedInt bits, UnsignedInt mask) { return (bits & mask) != 0; }

void W3DGadgetProgressBarImageDraw( GameWindow *window, WinInstanceData *instData )
{
	ICoord2D origin, size, start, end;
	const Image *backLeft, *backRight, *backCenter, 
				 *barRight, *barCenter;//*backSmallCenter,*barLeft,, *barSmallCenter;
	Int progress = (Int)window->winGetUserData();
	Int xOffset, yOffset;
	Int i;

	// get window size and position
  window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	// get the right images to use
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == 0 )
	{

		backLeft				= GadgetProgressBarGetDisabledImageLeft( window );
		//barLeft					= GadgetProgressBarGetDisabledBarImageLeft( window );
		backRight				= GadgetProgressBarGetDisabledImageRight( window );
		barRight				= GadgetProgressBarGetDisabledBarImageRight( window );
		backCenter			= GadgetProgressBarGetDisabledImageCenter( window );
		barCenter				= GadgetProgressBarGetDisabledBarImageCenter( window );
		//backSmallCenter	= GadgetProgressBarGetDisabledImageSmallCenter( window );
		//barSmallCenter	= GadgetProgressBarGetDisabledBarImageSmallCenter( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		backLeft				= GadgetProgressBarGetHiliteImageLeft( window );
		//barLeft					= GadgetProgressBarGetHiliteBarImageLeft( window );
		backRight				= GadgetProgressBarGetHiliteImageRight( window );
		barRight				= GadgetProgressBarGetHiliteBarImageRight( window );
		backCenter			= GadgetProgressBarGetHiliteImageCenter( window );
		barCenter				= GadgetProgressBarGetHiliteBarImageCenter( window );
		//backSmallCenter	= GadgetProgressBarGetHiliteImageSmallCenter( window );
		//barSmallCenter	= GadgetProgressBarGetHiliteBarImageSmallCenter( window );

	}  // end else if, hilited
	else
	{

		backLeft				= GadgetProgressBarGetEnabledImageLeft( window );
		//barLeft					= GadgetProgressBarGetEnabledBarImageLeft( window );
		backRight				= GadgetProgressBarGetEnabledImageRight( window );
		barRight				= GadgetProgressBarGetEnabledBarImageRight( window );
		backCenter			= GadgetProgressBarGetEnabledImageCenter( window );
		barCenter				= GadgetProgressBarGetEnabledBarImageCenter( window );
		//backSmallCenter	= GadgetProgressBarGetEnabledImageSmallCenter( window );
		//barSmallCenter	= GadgetProgressBarGetEnabledBarImageSmallCenter( window );

	}  // end else, enabled

	// sanity
	if( backLeft == 0 || backRight == 0 ||
			backCenter == 0 ||
			barRight == 0)
			// backSmallCenter == 0 ||barLeft == 0 ||barCenter == 0 || barSmallCenter == 0 )
		return;

	// get image sizes for the ends
	ICoord2D leftSize, rightSize;
	leftSize.x = backLeft->getImageWidth();
	leftSize.y = backLeft->getImageHeight();
	rightSize.x = backRight->getImageWidth();
	rightSize.y = backRight->getImageHeight();

	// get two key points used in the end drawing
	ICoord2D leftEnd, rightStart;
	rightStart.y = origin.y + yOffset;
	leftEnd.x = origin.x + leftSize.x + xOffset;
	leftEnd.y = origin.y + size.y + yOffset;
	rightStart.x = origin.x + size.x - rightSize.x + xOffset;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;

	// how many whole repeating pieces will fit in that width
	pieces = centerWidth / backCenter->getImageWidth();

	// draw the pieces
	start.x = leftEnd.x;
	start.y = origin.y + yOffset;
	end.y = start.y + size.y;
	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + backCenter->getImageWidth();
		TheWindowManager->winDrawImage( backCenter, 
																		start.x, start.y,
																		end.x, end.y );
		start.x += backCenter->getImageWidth();

	}  // end for i

	//
	// how many small repeating pieces will fit in the gap from where the
	// center repeating bar stopped and the right image, draw them
	// and overlapping underneath where the right end will go
	//
//	centerWidth = rightStart.x - start.x;
//	pieces = centerWidth / backCenter->getImageWidth() + 1;
//	end.y = start.y + size.y;
//	IRegion2D clipRegion;
//	
//	TheDisplay->setClipRegion()
//	for( i = 0; i < pieces; i++ )
//	{
//
//		end.x = start.x + backCenter->getImageWidth();
//		TheWindowManager->winDrawImage( backCenter,
//																		start.x, start.y,
//																		end.x, end.y );
//		start.x += backCenter->getImageWidth();
//
//	}  // end for i
//
	IRegion2D reg;
	reg.lo.x = start.x;
	reg.lo.y = start.y;
	reg.hi.x = rightStart.x;
	reg.hi.y = end.y;
	centerWidth = rightStart.x - start.x;
	if( centerWidth > 0)
	{
		TheDisplay->setClipRegion(&reg);
		end.x = start.x + backCenter->getImageWidth();
		TheWindowManager->winDrawImage( backCenter,
																		start.x, start.y,
																		end.x, end.y );
		TheDisplay->enableClipping(0);
	}


	// draw left end
	start.x = origin.x + xOffset;
	start.y = origin.y + yOffset;
	end = leftEnd;
	TheWindowManager->winDrawImage(backLeft, start.x, start.y, end.x, end.y);

	// draw right end
	start = rightStart;
	end.x = start.x + rightSize.x;
	end.y = start.y + size.y;
	TheWindowManager->winDrawImage(backRight, start.x, start.y, end.x, end.y);

	
	ICoord2D barWindowSize;  // end point of bar from window origin

	barWindowSize.x = ((size.x - 20) * progress) / 100;
	barWindowSize.y = size.y;
		
	pieces = barWindowSize.x / barCenter->getImageWidth();
 	// draw the pieces
	start.x = origin.x +10;
	start.y = origin.y + yOffset +5;
	end.y = start.y + size.y - 10;
	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + barCenter->getImageWidth();
		TheWindowManager->winDrawImage( barCenter, 
																		start.x, start.y,
																		end.x, end.y );
		start.x += barCenter->getImageWidth();

	}  // end for i
	start.x = origin.x + 10 + barCenter->getImageWidth() * pieces;
	//pieces = (size.x - barWindowSize.x -20) / barRight->getImageWidth();
	//Changed By Saad for flashing grey piece
	pieces = ((size.x - 20) / barCenter->getImageWidth()) - pieces;
	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + barRight->getImageWidth();
		TheWindowManager->winDrawImage( barRight, 
																		start.x, start.y,
																		end.x, end.y );
		start.x += barRight->getImageWidth();

	}  // end for i

}  // end W3DGadgetProgressBarImageDraw
