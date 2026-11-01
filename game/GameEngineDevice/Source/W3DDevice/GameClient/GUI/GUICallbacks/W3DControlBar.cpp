// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DControlBar.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day
// Desc: Control bar callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "Common/GlobalData.h"
#include "Common/Radar.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameClient/GameWindow.h"
#include "W3DDevice/GameClient/W3DGameWindow.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Display.h"
#include "GameClient/ControlBar.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/ControlBarScheme.h"
#include "GameClient/MapUtil.h"
#include "GameLogic/GameLogic.h"

// Retail inlines ~AsciiString at every scope exit and calls
// StringBase<char>::releaseBuffer (0x00887940) directly, never the
// 0x0005EE90 jmp body the out-of-line declaration would bind to.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
// W3DCameoMovieDraw: retail body (0x00799D00) in W3DCameoMovieDraw_Thunk.cpp.


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?W3DRightHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// BFME's GameWindow carries a per-window draw-callback pointer and an
// embedded polymorphic draw delegate past the fields the ZH header above
// declares; both are reached here by their retail byte offset. The
// delegate's own vtable pointer lives at its own address (a normal embedded
// C++ subobject), and its second slot performs the fallback draw.
typedef void (__cdecl *BfmeWindowDrawFunc)( GameWindow *, WinInstanceData * );

class BfmeWindowDrawDelegate
{
public:
	virtual void unused00();
	virtual void draw( GameWindow *window, WinInstanceData *instData );
};

void W3DRightHUDDraw( GameWindow *window, WinInstanceData *instData )
{
	if ( BitTest( window->winGetStatus(), WIN_STATUS_IMAGE ) )
	{
		BfmeWindowDrawFunc draw = *(BfmeWindowDrawFunc *)((char *)window + 0x1e8);
		if ( draw )
			draw( window, instData );
		else
			((BfmeWindowDrawDelegate *)((char *)window + 0x218))->draw( window, instData );
	}
}  // end W3DRightHUDDraw

Real logN(Real value, Real logBase)
{
	return (Real)log10(value)/ log10(logBase);
}

//-------------------------------------------------------------------------------------------------
/** Temporary power meter drawing ... there are some problems with this meter, that is
	* what to do when the player doesn't have power, builds a building before a power plant
	* etc, but I don't want to spend time on this since it's not a task right now and I'm
	* sure it will be in the future.  This is just down and dirty to see SOMETHING  (CD) */
//-------------------------------------------------------------------------------------------------
// Partial BFME views, backed by this body and GlobalData's FieldParse table.
struct EnergyView0079AEC0 {
 void *field00; int m_energyProduction, m_energyConsumption;
 int getConsumption() const { return m_energyConsumption; }
 int getProduction() const { return m_energyProduction; }
};
struct PowerGlobals0079AEC0 {
 char pad0000[0xC5C]; int m_powerBarBase; float m_powerBarIntervals; int m_powerBarYellowRange;
};

class Rva00589320Player;
class Rva002EE330PlayerList { public: Rva00589320Player *getLocalPlayer(); };
class DisplayView0079AEC0 { public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot0A();
virtual void slot0B();
virtual void slot0C();
virtual void slot0D();
virtual void slot0E();
virtual void slot0F();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot1A();
virtual void slot1B();
virtual void slot1C();
virtual void slot1D();
virtual void slot1E();
virtual void slot1F();
virtual void slot20();
virtual void slot21();
virtual void setClipRegion(IRegion2D *);
virtual void slot8C();
virtual void enableClipping(Bool);
};
struct Rva0079AEC0Coord : ICoord2D { Rva0079AEC0Coord() {} };
// BFME W3DPowerDraw: retail 0x0079A980, registered by name in the
// FunctionLexicon table (string "W3DPowerDraw" -> ILT 0x00046BB4).  Against
// Zero Hour it reads the local player directly (no observer bar), through
// the same views as W3DPowerDrawA below.
void W3DPowerDraw( GameWindow *window, WinInstanceData *instData )
{
	static const Image *centerBarYellow = TheMappedImageCollection->findImageByName("PowerPointY");
	static const Image *centerBarRed = TheMappedImageCollection->findImageByName("PowerPointR");
	static const Image *centerBarGreen = TheMappedImageCollection->findImageByName("PowerPointG");
	const Image *centerBar = NULL;
	static const Image *slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	Player *player = (Player *)((Rva002EE330PlayerList *)ThePlayerList)->getLocalPlayer();

	if(!player || !TheGlobalData)
		return;
	EnergyView0079AEC0 *energy = (EnergyView0079AEC0 *)((char *)player + 0xA4);
	if( energy == NULL )
		return;

	Int consumption = energy->getConsumption();
	Int production = energy->getProduction();	

	Rva0079AEC0Coord pos; ICoord2D size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );

	static Real pixelsPerInterval = size.x / ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarIntervals;
	Int delta = ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarYellowRange;
	
	if((consumption > energy->getProduction() - delta) && (consumption <= energy->getProduction()))
	{
		centerBar = centerBarYellow;
	}
	else if( consumption > production)
	{
		centerBar = centerBarRed;
	}
	else
	{
		centerBar = centerBarGreen;
	}
	if( !slider || !centerBar)
		return;

	Int range;
	range = logN(production, ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarBase) * (size.x / ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarIntervals);
	if(range >= size.x)
		range = size.x;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = range;
	
	if( centerWidth > 0)
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageWidth();
		ICoord2D start, end;
		// draw the pieces
		start.x = pos.x;
		start.y = pos.y;
		end.y = start.y + size.y;
		for( Int i = 0; i < pieces; i++ )
		{

			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar, 
																			start.x, start.y,
																			end.x, end.y );
			start.x += centerBar->getImageWidth();

		}  // end for i

		// we will draw the image but clip the parts we don't want to show
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = pos.x + size.x;
		reg.hi.y = pos.y + size.y;
		centerWidth = pos.x +size.x  - start.x;
		if( centerWidth > 0)
		{
			((DisplayView0079AEC0 *)TheDisplay)->setClipRegion(&reg);
			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			((DisplayView0079AEC0 *)TheDisplay)->enableClipping(FALSE);
		}
	}
	Int posXstart;
	Int posXend;
	Real consumptionForNeedle = (consumption == 1) ? 1.5f : INT_TO_REAL(consumption);//Log(1) == 0, but we need to show something for 1 power used.
	range = logN(consumptionForNeedle, ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarBase) * (size.x / ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarIntervals);
	if(centerWidth <= 0 && range <= 0)
		return;
	if(range >= size.x)
	{
		posXstart = pos.x + size.x - slider->getImageWidth();
		posXend = pos.x + size.x;
	}
	else
	{
		posXstart = pos.x + range - slider->getImageWidth()/2;
		posXend = pos.x + range + slider->getImageWidth()/2;
	}
	if(posXstart <=pos.x)
	{
		posXstart	 = pos.x;
		posXend	= pos.x + slider->getImageWidth();
	}
	TheWindowManager->winDrawImage(slider, posXstart, pos.y + size.y - slider->getImageHeight(), posXend, pos.y + size.y);
}

void W3DPowerDrawA( GameWindow *window, WinInstanceData *instData )
{
	static const Image *endBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellowEndR");
	static const Image *beginBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellowEndL");
	static const Image *centerBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellow");
	static const Image *endBarRed = TheMappedImageCollection->findImageByName("PowerBarRedEndR");
	static const Image *beginBarRed = TheMappedImageCollection->findImageByName("PowerBarRedEndL");
	static const Image *centerBarRed = TheMappedImageCollection->findImageByName("PowerBarRed");
	static const Image *endBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreenEndR");
	static const Image *beginBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreenEndL");
	static const Image *centerBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreen");
	const Image *endBar = NULL;
	const Image *beginBar = NULL;
	const Image *centerBar = NULL;
	static const Image *slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	Player *player = (Player *)((Rva002EE330PlayerList *)ThePlayerList)->getLocalPlayer();

	if(!player || !TheGlobalData)
		return;
	EnergyView0079AEC0 *energy = (EnergyView0079AEC0 *)((char *)player + 0xA4);
	if( energy == NULL )
		return;

	Int consumption = energy->getConsumption();
	Int production = energy->getProduction();	

	Int range;
	Rva0079AEC0Coord pos; ICoord2D size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );

	static Real pixelsPerInterval = size.x / ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarIntervals;
	Int delta = ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarYellowRange;
	
	if((consumption > energy->getProduction() - delta) && (consumption <= energy->getProduction()))
	{
		// 6 and 1 is Green, 6 and 2 is yellow, 6 and 6 is yellow
		endBar = endBarYellow;
		beginBar = beginBarYellow;
		centerBar = centerBarYellow;
	}
	else if( consumption > production)
	{
		endBar = endBarRed;
		beginBar = beginBarRed;
		centerBar = centerBarRed;
	}
	else
	{
		endBar = endBarGreen;
		beginBar = beginBarGreen;
		centerBar = centerBarGreen;
	}
	//slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	if( !slider || !endBar || !beginBar || !centerBar)
		return;

	range = logN(production, ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarBase) * (size.x / ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarIntervals);
	if(range >= size.x)
		range = size.x;
	if(range < endBar->getImageWidth() + beginBar->getImageWidth())
		range = endBar->getImageWidth() + beginBar->getImageWidth();



	// get image sizes for the ends
	ICoord2D leftSize, rightSize, start, end;
	leftSize.x = beginBar->getImageWidth();
	leftSize.y = beginBar->getImageHeight();
	rightSize.x = endBar->getImageWidth();
	rightSize.y = endBar->getImageHeight();

	// get two key points used in the end drawing
	ICoord2D leftEnd, rightStart;
	leftEnd.x = pos.x + leftSize.x;
	leftEnd.y = pos.y + size.y;
	rightStart.x = pos.x + (range - rightSize.x);
	rightStart.y = pos.y;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;
	
	if( centerWidth <= 0)
	{
		// draw left end
		start.x = pos.x;
		start.y = pos.y;
		end.y = leftEnd.y;
		end.x = pos.x + range/2;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.y = rightStart.y;
		start.x = end.x;
		end.x = pos.x + range;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	else
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageWidth();

		// draw the pieces
		start.x = leftEnd.x;
		start.y = pos.y;
		end.y = start.y + size.y; //centerImage->getImageHeight() + yOffset;
		for( Int i = 0; i < pieces; i++ )
		{

			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar, 
																			start.x, start.y,
																			end.x, end.y );
			start.x += centerBar->getImageWidth();

		}  // end for i

		// we will draw the image but clip the parts we don't want to show
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = rightStart.x;
		reg.hi.y = end.y;
		centerWidth = rightStart.x - start.x;
		if( centerWidth > 0)
		{
			((DisplayView0079AEC0 *)TheDisplay)->setClipRegion(&reg);
			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			((DisplayView0079AEC0 *)TheDisplay)->enableClipping(FALSE);
		}

		// draw left end
		start.x = pos.x;
		start.y = pos.y;
		end = leftEnd;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start = rightStart;
		end.x = start.x + rightSize.x;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	Int posXstart;
	Int posXend;
	Real consumptionForNeedle = (consumption == 1) ? 1.5f : INT_TO_REAL(consumption);//Log(1) == 0, but we need to show something for 1 power used.
	range = logN(consumptionForNeedle, ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarBase) * (size.x / ((const PowerGlobals0079AEC0 *)TheGlobalData)->m_powerBarIntervals);
	if(range >= size.x)
	{
		posXstart = pos.x + (size.x - slider->getImageWidth());
		posXend = pos.x + size.x;
	}
	else
	{
		posXstart = pos.x + (range - slider->getImageWidth()/2);
		posXend = pos.x + (range + slider->getImageWidth()/2);
	}
	if(posXstart <=pos.x)
	{
		posXstart	 = pos.x;
		posXend	= pos.x + slider->getImageWidth();
	}
	TheWindowManager->winDrawImage(slider, posXstart, pos.y + size.y - slider->getImageHeight(), posXend, pos.y + size.y);
}


void W3DCommandBarBackgroundDraw( GameWindow *window, WinInstanceData *instData )
{

	ControlBarSchemeManager *man = TheControlBar->getControlBarSchemeManager();
	if(!man)
		return;
	static NameKeyType winNamekey	= TheNameKeyGenerator->nameToKey( AsciiString( "ControlBar.wnd:BackgroundMarker" ) );
	GameWindow *win =  TheWindowManager->winGetWindowFromId(NULL,winNamekey);
	static ICoord2D basePos;
	if(!win)
	{
		return;
		//win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey( AsciiString( "ControlBar.wnd:BackgroundMarker" ) ));
	}
	TheControlBar->getBackgroundMarkerPos(&basePos.x, &basePos.y);
	ICoord2D pos, offset;
	win->winGetScreenPosition(&pos.x,&pos.y);
	offset.x = pos.x - basePos.x;
	offset.y = pos.y - basePos.y;

	man->drawBackground(offset);
}


void W3DCommandBarForegroundDraw( GameWindow *window, WinInstanceData *instData )
{

	ControlBarSchemeManager *man = TheControlBar->getControlBarSchemeManager();
	if(!man)
		return;

	static NameKeyType winNamekey	= TheNameKeyGenerator->nameToKey( AsciiString( "ControlBar.wnd:BackgroundMarker" ) );
	GameWindow *win = TheWindowManager->winGetWindowFromId(NULL,winNamekey);
	static ICoord2D basePos;
	if(!win)
	{
		return;
		//win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey( AsciiString( "ControlBar.wnd:BackgroundMarker" ) ));
	}
	TheControlBar->getForegroundMarkerPos(&basePos.x, &basePos.y);
	ICoord2D pos, offset;
	win->winGetScreenPosition(&pos.x,&pos.y);
	offset.x = pos.x - basePos.x;
	offset.y = pos.y - basePos.y;

	man->drawForeground(offset);

}

void W3DNoDraw( GameWindow *window, WinInstanceData *instData )
{

	// draw the default stuff
//	W3DGameWinDefaultDraw( window, instData );
	
}  // end W3DRightHUDDraw

void drawSkinnyBorder( Int x, Int y, Int width, Int height);
// BFME's Display 2D calls take Real coordinates and each one is bracketed by
// beginImageDraw/endImageDraw (slots 0xB0 and 0xDC), the shape of the
// matched FullFadeTransition::draw.  The Zero Hour Display.h above declares
// the Zero Hour vtable, so the map preview reaches them through a slot view.
class BfmeMapPreviewDisplay
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void beginImageDraw();
	virtual void slot45();
	virtual void drawLine( Real startX, Real startY, Real endX, Real endY,
		Real lineWidth, UnsignedInt lineColor );
	virtual void drawOpenRect( Real startX, Real startY, Real width, Real height,
		Real lineWidth, UnsignedInt lineColor );
	virtual void drawFillRect( Real startX, Real startY, Real width, Real height,
		UnsignedInt color );
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void endImageDraw();
};

inline void mapPreviewFillRect( BfmeMapPreviewDisplay *display, Real x, Real y,
	Real width, Real height, UnsignedInt color )
{
	display->beginImageDraw();
	display->drawFillRect( x, y, width, height, color );
	display->endImageDraw();
}

inline void mapPreviewLine( BfmeMapPreviewDisplay *display, Real startX, Real startY,
	Real endX, Real endY, Real lineWidth, UnsignedInt lineColor )
{
	display->beginImageDraw();
	display->drawLine( startX, startY, endX, endY, lineWidth, lineColor );
	display->endImageDraw();
}

// The out-of-line Real-coordinate drawImage wrapper at retail 0x0040D900
// (begin, slot 0xD4, end), called by its ledger name as in the matched
// Rva00470C90Render.cpp.
class Bfme5Host
{
public:
	void bfmeRunE( const Image *image, float startX, float startY, float endX,
		float endY, int color, int mode );
};

// BFME's Region3D argument is copied by a user copy constructor (its Coord3D
// halves are class types with one in BFME): retail copies the six words
// field by field into the argument slot and spills the slot's address.
// The Zero Hour BaseType.h Region3D above is a plain struct, so the call
// passes this same-layout view of it.
struct BfmeMapPreviewExtent
{
	BfmeMapPreviewExtent( const BfmeMapPreviewExtent &that )
		: loX( that.loX ), loY( that.loY ), loZ( that.loZ ),
		  hiX( that.hiX ), hiY( that.hiY ), hiZ( that.hiZ ) {}
	~BfmeMapPreviewExtent() {}
	Real loX, loY, loZ, hiX, hiY, hiZ;
};
typedef void (*BfmeFindDrawPositionsCall)( Int startX, Int startY, Int width, Int height,
	BfmeMapPreviewExtent extent, ICoord2D *ul, ICoord2D *lr );

// BFME's enabled draw data (12-byte image/color/border entries) starts at
// window offset 0x48, four bytes past the Zero Hour GameWindow.h layout.
inline const Image *mapPreviewEnabledImage( GameWindow *window, Int index )
{
	return *(const Image **)((char *)window + 0x48 + index * 12);
}

// BFME W3DDrawMapPreview: retail 0x0079A330, registered by name in the
// FunctionLexicon table (string "W3DDrawMapPreview" -> ILT 0x0004ABDD).
// Against Zero Hour it returns at once without map data, draws through the
// Real-coordinate display calls, layers the second enabled image under the
// first, and drops the supply/tech icons and the skinny border.
void W3DDrawMapPreview( GameWindow *window, WinInstanceData *instData)
{
	MapMetaData *mmData = (MapMetaData *)window->winGetUserData();
	Int pixelX, pixelY, width, height;
	window->winGetScreenPosition(&pixelX, &pixelY);
	window->winGetSize(&width, &height);
	if(!mmData)
		return;

	ICoord2D ul, lr;
	((BfmeFindDrawPositionsCall)findDrawPositions)( pixelX, pixelY, width, height, *(const BfmeMapPreviewExtent *)&mmData->m_extent, &ul, &lr );

	Color fillColor = GameMakeColor( 0, 0, 0, 255 );
	Color lineColor = GameMakeColor( 50, 50, 50, 255 );

	if( mmData->m_extent.width()/width >= mmData->m_extent.height()/height )
	{
		// draw horizontal bars at top and bottom
		mapPreviewFillRect( (BfmeMapPreviewDisplay *)TheDisplay, pixelX, pixelY, width, ul.y - pixelY - 1, fillColor );
		mapPreviewFillRect( (BfmeMapPreviewDisplay *)TheDisplay, pixelX, lr.y + 1, width, pixelY + height - lr.y - 1, fillColor );
		mapPreviewLine( (BfmeMapPreviewDisplay *)TheDisplay, pixelX, ul.y, pixelX + width, ul.y, 1, lineColor );
		mapPreviewLine( (BfmeMapPreviewDisplay *)TheDisplay, pixelX, lr.y + 1, pixelX + width, lr.y + 1, 1, lineColor );
	}  // end if
	else
	{
		// draw vertical bars to the left and right
		mapPreviewFillRect( (BfmeMapPreviewDisplay *)TheDisplay, pixelX, pixelY, ul.x - pixelX - 1, height, fillColor );
		mapPreviewFillRect( (BfmeMapPreviewDisplay *)TheDisplay, lr.x + 1, pixelY, width - (lr.x - pixelX) - 1, height, fillColor );
		mapPreviewLine( (BfmeMapPreviewDisplay *)TheDisplay, ul.x, pixelY, ul.x, pixelY + height, 1, lineColor );
		mapPreviewLine( (BfmeMapPreviewDisplay *)TheDisplay, lr.x + 1, pixelY, lr.x + 1, pixelY + height, 1, lineColor );
	}  // end else

	if(!BitTest(window->winGetStatus(), WIN_STATUS_IMAGE) || !mapPreviewEnabledImage( window, 0 ))
		mapPreviewFillRect( (BfmeMapPreviewDisplay *)TheDisplay, ul.x, ul.y, lr.x -ul.x, lr.y-ul.y, lineColor );
	else
	{
		if( mapPreviewEnabledImage( window, 1 ) )
			((Bfme5Host *)TheDisplay)->bfmeRunE( mapPreviewEnabledImage( window, 1 ), ul.x, ul.y, lr.x, lr.y, 0xFFFFFFFF, 2 );
		((Bfme5Host *)TheDisplay)->bfmeRunE( mapPreviewEnabledImage( window, 0 ), ul.x, ul.y, lr.x, lr.y, 0xFFFFFFFF, 2 );
	}
}

// W3DCommandBarHelpPopupDraw exact retail body is emitted by
// W3DCommandBarHelpPopupDrawThunk.cpp.

// The out-of-line Render2DSentenceClass::PendingSurfaceStruct dtor no longer
// drags VectorClass<Render2DClass *> into this object implicitly; the three
// ledgered members are asked for by name.
template bool VectorClass<Render2DClass *>::operator==(const VectorClass<Render2DClass *> & vec) const;
template int VectorClass<Render2DClass *>::ID(Render2DClass * const & object);
template bool VectorClass<Render2DClass *>::Resize(int newsize, Render2DClass * const * array);
