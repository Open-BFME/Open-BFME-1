// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
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
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
void W3DCameoMovieDraw( GameWindow *window, WinInstanceData *instData )
{
	// draw video buffer
	VideoBuffer *video = TheInGameUI->cameoVideoBuffer();
	if ( video )
	{
		ICoord2D pos, size;
		window->winGetScreenPosition( &pos.x, &pos.y );
		window->winGetSize( &size.x, &size.y );

		TheDisplay->drawVideoBuffer( video, pos.x, pos.y, pos.x + size.x, pos.y + size.y );
	}
}  // end W3DLeftHUDDraw


//-------------------------------------------------------------------------------------------------
void W3DLeftHUDDraw( GameWindow *window, WinInstanceData *instData )
{
	// draw the default stuff
//
	Player *player = ThePlayerList->getLocalPlayer();
	// draw video buffer
	VideoBuffer *video = TheInGameUI->videoBuffer();
	if ( video )
	{
		ICoord2D pos, size;
		window->winGetScreenPosition( &pos.x, &pos.y );
		window->winGetSize( &size.x, &size.y );

		TheDisplay->drawVideoBuffer( video, pos.x, pos.y, pos.x + size.x, pos.y + size.y );
	}
	else if( TheRadar->isRadarForced() || ( TheRadar->isRadarHidden() == false && player->hasRadar() ) )
	{
		ICoord2D pos, size;
		//W3DGameWinDefaultDraw( window, instData );
		// window position and size on the display
		window->winGetScreenPosition( &pos.x, &pos.y );
		window->winGetSize( &size.x, &size.y );
		//TheDisplay->drawOpenRect(pos.x, pos.y, size.x,size.y, 1,GameMakeColor(100,100,255,255));
		// draw the radar on the screen now
		TheRadar->draw( pos.x + 1, pos.y + 1, size.x - 2, size.y - 2 );

	}  // end else if


}  // end W3DLeftHUDDraw

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
void W3DPowerDraw( GameWindow *window, WinInstanceData *instData )
{
	//static const Image *endBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellowEndR");
	//static const Image *beginBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellowEndL");
	static const Image *centerBarYellow = TheMappedImageCollection->findImageByName("PowerPointY");
	//static const Image *endBarRed = TheMappedImageCollection->findImageByName("PowerBarRedEndR");
	//static const Image *beginBarRed = TheMappedImageCollection->findImageByName("PowerBarRedEndL");
	static const Image *centerBarRed = TheMappedImageCollection->findImageByName("PowerPointR");
	//static const Image *endBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreenEndR");
	//static const Image *beginBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreenEndL");
	static const Image *centerBarGreen = TheMappedImageCollection->findImageByName("PowerPointG");
	//const Image *endBar = NULL;
	//const Image *beginBar = NULL;
	const Image *centerBar = NULL;
	static const Image *slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	Player *player = NULL;
	if(TheControlBar->isObserverControlBarOn())
	{
		player = TheControlBar->getObserverLookAtPlayer();
	}
	else
		player = ThePlayerList->getLocalPlayer();
	


	if(!player || !TheGlobalData)
		return;
	Energy *energy = player->getEnergy();
	if( energy == NULL )
		return;

	Int consumption = energy->getConsumption();
	Int production = energy->getProduction();	

	ICoord2D pos, size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );

	static Real pixelsPerInterval = size.x / TheGlobalData->m_powerBarIntervals;
	Int delta = TheGlobalData->m_powerBarYellowRange;
	
	if((consumption > energy->getProduction() - delta) && (consumption <= energy->getProduction()))
	{
		// 6 and 1 is Green, 6 and 2 is yellow, 6 and 6 is yellow
		//endBar = endBarYellow;
		//beginBar = beginBarYellow;
		centerBar = centerBarYellow;
	}
	else if( consumption > production)
	{
	//	endBar = endBarRed;
//		beginBar = beginBarRed;
		centerBar = centerBarRed;
	}
	else
	{
	//	endBar = endBarGreen;
//		beginBar = beginBarGreen;
		centerBar = centerBarGreen;
	}
	//slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	if( !slider || !centerBar)
		return;

	Int range;
	range = logN(production, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
	if(range >= size.x)
		range = size.x;
//	if(range < endBar->getImageWidth() + beginBar->getImageWidth())
//		range = endBar->getImageWidth() + beginBar->getImageWidth();



//	// get image sizes for the ends
//	ICoord2D leftSize, rightSize, start, end;
//	leftSize.x = beginBar->getImageWidth();
//	leftSize.y = beginBar->getImageHeight();
//	rightSize.x = endBar->getImageWidth();
//	rightSize.y = endBar->getImageHeight();
//
//	// get two key points used in the end drawing
//	ICoord2D leftEnd, rightStart;
//	leftEnd.x = pos.x + leftSize.x;
//	leftEnd.y = pos.y + size.y;
//	rightStart.x = pos.x + range - rightSize.x;
//	rightStart.y = pos.y;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = range; //rightStart.x - leftEnd.x;
	
	if( centerWidth > 0)
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageWidth();
		ICoord2D start, end;
		// draw the pieces
		start.x = pos.x;
		start.y = pos.y;
		end.y = start.y + size.y;// + yOffset;
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
		reg.hi.x = pos.x + size.x;//rightStart.x;
		reg.hi.y = pos.y + size.y;
		centerWidth = pos.x +size.x  - start.x;
		if( centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			TheDisplay->enableClipping(FALSE);
		}

//		// draw left end
//		start.x = pos.x;
//		start.y = pos.y;
//		end = leftEnd;
//		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);
//
//		// draw right end
//		start = rightStart;
//		end.x = start.x + rightSize.x;
//		end.y = start.y + size.y;
//		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	Int posXstart;
	Int posXend;
	Real consumptionForNeedle = (consumption == 1) ? 1.5f : INT_TO_REAL(consumption);//Log(1) == 0, but we need to show something for 1 power used.
	range = logN(consumptionForNeedle, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
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
	Player *player = NULL;
	if(TheControlBar->isObserverControlBarOn())
	{
		player = TheControlBar->getObserverLookAtPlayer();
	}
	else
		player = ThePlayerList->getLocalPlayer();
	


	if(!player || !TheGlobalData)
		return;
	Energy *energy = player->getEnergy();
	if( energy == NULL )
		return;

	Int consumption = energy->getConsumption();
	Int production = energy->getProduction();	

	ICoord2D pos, size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );

	static Real pixelsPerInterval = size.x / TheGlobalData->m_powerBarIntervals;
	Int delta = TheGlobalData->m_powerBarYellowRange;
	
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

	Int range;
	range = logN(production, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
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
	rightStart.x = pos.x + range - rightSize.x;
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
			TheDisplay->setClipRegion(&reg);
			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			TheDisplay->enableClipping(FALSE);
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
	range = logN(consumptionForNeedle, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
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

void W3DCommandBarGenExpDraw( GameWindow *window, WinInstanceData *instData )
{
	Player *player = ThePlayerList->getLocalPlayer();
	if(!player->isPlayerActive())
		return;
	static const Image *endBar = TheMappedImageCollection->findImageByName("GenExpBarTop1");
	static const Image *beginBar = TheMappedImageCollection->findImageByName("GenExpBarBottom1");
	static const Image *centerBar = TheMappedImageCollection->findImageByName("GenExpBar1");
	Int progress;
	progress = ((player->getSkillPoints() - player->getSkillPointsLevelDown()) * 100) /(player->getSkillPointsLevelUp() - player->getSkillPointsLevelDown());
	
	if(progress <= 0)
		return;

	// GS This should never be necessary, but scripts can change the points required or even disable a level.
	// A disabled level will be -1 for points required.  Just be totally safe and bind to 100, and we will
	// fix the scripts to bind the points gained later.
	if( progress > 100 )
		progress = 100;

	ICoord2D pos, size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );



	if( !endBar || !beginBar || !centerBar)
		return;

	Int range;
	range = size.y * progress / 100;


	// get image sizes for the ends
	ICoord2D topSize, bottomSize, start, end;
	bottomSize.x = beginBar->getImageWidth();
	bottomSize.y = beginBar->getImageHeight();
	topSize.x = endBar->getImageWidth();
	topSize.y = endBar->getImageHeight();

	// get two key points used in the end drawing
	ICoord2D bottomEnd, topStart;
	bottomEnd.x = pos.x + size.x;
	bottomEnd.y = pos.y + size.y - bottomSize.y;
	topStart.x = pos.x;
	topStart.y = pos.y +size.y - range - topSize.y;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = bottomEnd.y - topStart.y;
	
	if( centerWidth <= 0)
	{
		// draw left end
		start.x = pos.x;
		start.y = pos.y + size.y - bottomSize.y;
		end.y = pos.y + size.y;
		end.x = pos.x + size.x;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.y = pos.y + size.y - bottomSize.y - topSize.y;
		start.x = pos.x;
		end.x = pos.x + size.x;
		end.y = start.y + topSize.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	else
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageHeight();

		// draw the pieces
		start.x = pos.x;
		start.y = topStart.y;
		end.x = start.x + size.x; //centerImage->getImageHeight() + yOffset;
		for( Int i = 0; i < pieces; i++ )
		{

			end.y = start.y + centerBar->getImageHeight();
			TheWindowManager->winDrawImage( centerBar, 
																			start.x, start.y,
																			end.x, end.y );
			start.y += centerBar->getImageHeight();

		}  // end for i

		// we will draw the image but clip the parts we don't want to show
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = bottomEnd.x;
		reg.hi.y = bottomEnd.y;
		centerWidth = bottomEnd.y - start.y;
		if( centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.y = start.y + centerBar->getImageHeight();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			TheDisplay->enableClipping(FALSE);
		}

		// draw left end
		end.x = pos.x + size.x;
		end.y = pos.y + size.y;
		start.x = pos.x;
		start.y = bottomEnd.y;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.x = pos.x;
		start.y = pos.y +size.y - range;
		end.x = pos.x + size.x;
		end.y = pos.y +size.y - range - topSize.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}

}

__declspec(naked) void W3DCommandBarTopDraw( GameWindow *, WinInstanceData * )
{
	__asm {
		_emit 0CCh
		_emit 0A1h
		_emit 040h
		_emit 01Bh
		_emit 02Fh
		_emit 001h
		_emit 08Bh
		_emit 00Dh
		_emit 000h
		_emit 0D6h
		_emit 02Eh
		_emit 001h
		_emit 056h
		_emit 08Bh
		_emit 030h
		_emit 068h
		_emit 044h
		_emit 0B8h
		_emit 00Fh
		_emit 001h
		_emit 0E8h
		_emit 0FFh
		_emit 00Ah
		_emit 08Ah
		_emit 0FFh
		_emit 08Bh
		_emit 00Dh
		_emit 040h
		_emit 01Bh
		_emit 02Fh
		_emit 001h
		_emit 050h
		_emit 06Ah
		_emit 000h
		_emit 0FFh
		_emit 096h
		_emit 0DCh
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 085h
		_emit 0C0h
		_emit 05Eh
		_emit 074h
		_emit 016h
		_emit 08Bh
		_emit 0C8h
		_emit 0E8h
		_emit 0C4h
		_emit 002h
		_emit 08Ah
		_emit 0FFh
		_emit 084h
		_emit 0C0h
		_emit 075h
		_emit 00Bh
		_emit 08Bh
		_emit 00Dh
		_emit 048h
		_emit 0D7h
		_emit 02Eh
		_emit 001h
		_emit 0E9h
		_emit 0DAh
		_emit 08Dh
		_emit 089h
		_emit 0FFh
		_emit 0C3h
		_emit 0CCh
		_emit 0CCh
	}
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
void W3DDrawMapPreview( GameWindow *window, WinInstanceData *instData)
{
	MapMetaData *mmData = (MapMetaData *)window->winGetUserData();
	Int pixelX, pixelY, width, height;
	// if the local player does not have a radar then we can't draw anything
	window->winGetScreenPosition(&pixelX, &pixelY);
	window->winGetSize(&width, &height);
	if(!mmData)
	{
		W3DGameWinDefaultDraw( window, instData );
		drawSkinnyBorder(pixelX - 1, pixelY - 1, width + 2, height + 2);
		return;
	}
	
	
	
		
	//
	// given a upper left corner at pixelX|Y and a width and height to draw into, figure out
	// where we should start and end the image so that the final drawn image has the
	// same ratio as the map and isn't stretched or distorted
	//
	ICoord2D ul, lr;
	findDrawPositions( pixelX, pixelY, width, height, mmData->m_extent, &ul, &lr );

//	Int scaledWidth = lr.x - ul.x;
//	Int scaledHeight = lr.y - ul.y;

	// draw black border areas where we need map
	Color fillColor = GameMakeColor( 0, 0, 0, 255 );
	Color lineColor = GameMakeColor( 50, 50, 50, 255 );
	
	if( mmData->m_extent.width()/width >= mmData->m_extent.height()/height )
	{
		
		// draw horizontal bars at top and bottom
		TheDisplay->drawFillRect( pixelX, pixelY, width, ul.y - pixelY - 1, fillColor );
		TheDisplay->drawFillRect( pixelX, lr.y + 1, width, pixelY + height - lr.y - 1, fillColor);
		TheDisplay->drawLine(pixelX, ul.y, pixelX + width, ul.y, 1, lineColor);
		TheDisplay->drawLine(pixelX, lr.y + 1, pixelX + width, lr.y + 1, 1, lineColor);

	}  // end if
	else
	{

		// draw vertical bars to the left and right
		TheDisplay->drawFillRect( pixelX, pixelY, ul.x - pixelX - 1, height, fillColor );
		TheDisplay->drawFillRect( lr.x + 1, pixelY, width - (lr.x - pixelX) - 1, height, fillColor );
		TheDisplay->drawLine(ul.x, pixelY, ul.x, pixelY + height, 1, lineColor);
		TheDisplay->drawLine(lr.x + 1, pixelY, lr.x + 1, pixelY + height, 1, lineColor);

	}  // end else

	if(!BitTest(window->winGetStatus(), WIN_STATUS_IMAGE) || !window->winGetEnabledImage(0))
		TheDisplay->drawFillRect(ul.x, ul.y, lr.x -ul.x, lr.y-ul.y, lineColor);
	else
		TheDisplay->drawImage(window->winGetEnabledImage(0) , ul.x, ul.y, lr.x, lr.y );

	const Image *image = TheMappedImageCollection->findImageByName("TecBuilding");
	ICoord2DList::iterator it = TheSupplyAndTechImageLocations.m_techPosList.begin();
	if(image)
		while(it != TheSupplyAndTechImageLocations.m_techPosList.end())
		{
			TheDisplay->drawImage(image, pixelX + it->x, pixelY + it->y, pixelX + it->x + SUPPLY_TECH_SIZE, pixelY + it->y +SUPPLY_TECH_SIZE);
			it++;
		}

	image = TheMappedImageCollection->findImageByName("Cash");
	it = TheSupplyAndTechImageLocations.m_supplyPosList.begin();
	if(image)
		while(it != TheSupplyAndTechImageLocations.m_supplyPosList.end())
		{
			TheDisplay->drawImage(image, pixelX + it->x, pixelY + it->y, pixelX + it->x + SUPPLY_TECH_SIZE, pixelY + it->y +SUPPLY_TECH_SIZE);
			it++;
		}
	drawSkinnyBorder(pixelX - 1, pixelY - 1, width + 2, height + 2);
}

__declspec(naked) void drawSkinnyBorder( Int x, Int y, Int width, Int height)
{
	__asm {
	__emit 0x6a;
	__emit 0xff;
	__emit 0x68;
	__emit 0x70;
	__emit 0x1a;
	__emit 0x05;
	__emit 0x01;
	__emit 0x64;
	__emit 0xa1;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x50;
	__emit 0x64;
	__emit 0x89;
	__emit 0x25;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x83;
	__emit 0xec;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x40;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x48;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x44;
	__emit 0x53;
	__emit 0x55;
	__emit 0x03;
	__emit 0xc8;
	__emit 0x56;
	__emit 0x8b;
	__emit 0x74;
	__emit 0x24;
	__emit 0x48;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x34;
	__emit 0x83;
	__emit 0xc0;
	__emit 0xfe;
	__emit 0x57;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x41;
	__emit 0xfb;
	__emit 0x8d;
	__emit 0x7c;
	__emit 0x16;
	__emit 0xfb;
	__emit 0x68;
	__emit 0x48;
	__emit 0x79;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x89;
	__emit 0x74;
	__emit 0x24;
	__emit 0x38;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xe8;
	__emit 0xbe;
	__emit 0xce;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x50;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xec;
	__emit 0x18;
	__emit 0x88;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0xd8;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x44;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0x13;
	__emit 0xbc;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x68;
	__emit 0x40;
	__emit 0x79;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x50;
	__emit 0xe8;
	__emit 0x85;
	__emit 0xce;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xb3;
	__emit 0x18;
	__emit 0x88;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x44;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0xda;
	__emit 0xbb;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x83;
	__emit 0xc6;
	__emit 0x03;
	__emit 0x8d;
	__emit 0x47;
	__emit 0xfb;
	__emit 0x3b;
	__emit 0xf0;
	__emit 0x89;
	__emit 0x74;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x0f;
	__emit 0x8f;
	__emit 0xec;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x83;
	__emit 0xc2;
	__emit 0x05;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x05;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8d;
	__emit 0x4e;
	__emit 0x05;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x54;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x24;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x30;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf9;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x6a;
	__emit 0x02;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x24;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x24;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x60;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x64;
	__emit 0x52;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x68;
	__emit 0x51;
	__emit 0x52;
	__emit 0x53;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x90;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf9;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x20;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x3c;
	__emit 0x52;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x68;
	__emit 0x51;
	__emit 0x52;
	__emit 0x55;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x90;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x83;
	__emit 0xc6;
	__emit 0x05;
	__emit 0x83;
	__emit 0xc2;
	__emit 0x05;
	__emit 0x83;
	__emit 0xc0;
	__emit 0xfb;
	__emit 0x3b;
	__emit 0xf0;
	__emit 0x89;
	__emit 0x74;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x14;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0x55;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0x2b;
	__emit 0xce;
	__emit 0x83;
	__emit 0xf9;
	__emit 0x02;
	__emit 0x0f;
	__emit 0x8c;
	__emit 0xb7;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf9;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x83;
	__emit 0xc6;
	__emit 0x02;
	__emit 0x89;
	__emit 0x74;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x83;
	__emit 0xc1;
	__emit 0x05;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x58;
	__emit 0x6a;
	__emit 0xff;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x54;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x51;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x58;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x64;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x52;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x6c;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x51;
	__emit 0x53;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf9;
	__emit 0xff;
	__emit 0x90;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x05;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x60;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x51;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x55;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x3b;
	__emit 0xf7;
	__emit 0x0f;
	__emit 0x8d;
	__emit 0xc7;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xc7;
	__emit 0x2b;
	__emit 0xc6;
	__emit 0x40;
	__emit 0x83;
	__emit 0xe0;
	__emit 0xfe;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x06;
	__emit 0xfe;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x02;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x6a;
	__emit 0x02;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x58;
	__emit 0x6a;
	__emit 0xff;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x54;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x05;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x60;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x64;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x51;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x53;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x90;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x05;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x60;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x51;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x55;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x68;
	__emit 0x38;
	__emit 0x79;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x54;
	__emit 0xe8;
	__emit 0xbb;
	__emit 0xcb;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x50;
	__emit 0x50;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xe9;
	__emit 0x15;
	__emit 0x88;
	__emit 0xff;
	__emit 0x83;
	__emit 0xce;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xd8;
	__emit 0x89;
	__emit 0x74;
	__emit 0x24;
	__emit 0x44;
	__emit 0xe8;
	__emit 0x11;
	__emit 0xb9;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x68;
	__emit 0x30;
	__emit 0x79;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x54;
	__emit 0xe8;
	__emit 0x83;
	__emit 0xcb;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xb1;
	__emit 0x15;
	__emit 0x88;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0x89;
	__emit 0x74;
	__emit 0x24;
	__emit 0x44;
	__emit 0xe8;
	__emit 0xdc;
	__emit 0xb8;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x34;
	__emit 0x8b;
	__emit 0xd7;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x38;
	__emit 0x83;
	__emit 0xc1;
	__emit 0xfe;
	__emit 0x83;
	__emit 0xc0;
	__emit 0xfb;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x03;
	__emit 0x3b;
	__emit 0xf8;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x14;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x0f;
	__emit 0x8f;
	__emit 0xe1;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x83;
	__emit 0xc1;
	__emit 0x05;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x83;
	__emit 0xc2;
	__emit 0x05;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x54;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x38;
	__emit 0x8d;
	__emit 0x57;
	__emit 0x05;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x54;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x34;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x30;
	__emit 0x8d;
	__emit 0x64;
	__emit 0x24;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x90;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x38;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x6a;
	__emit 0x02;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x54;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x50;
	__emit 0x51;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x64;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x68;
	__emit 0x50;
	__emit 0x51;
	__emit 0x53;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x90;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x34;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x40;
	__emit 0x50;
	__emit 0x51;
	__emit 0x55;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x05;
	__emit 0x83;
	__emit 0xc1;
	__emit 0x05;
	__emit 0x3b;
	__emit 0xf8;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0x58;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0x2b;
	__emit 0xcf;
	__emit 0x83;
	__emit 0xf9;
	__emit 0x02;
	__emit 0x0f;
	__emit 0x8c;
	__emit 0xb7;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x06;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x02;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x60;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x60;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x51;
	__emit 0x83;
	__emit 0xc2;
	__emit 0x05;
	__emit 0x51;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x64;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x60;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x51;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x53;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x90;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x83;
	__emit 0xc1;
	__emit 0x05;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x51;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x50;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x55;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x3b;
	__emit 0xf8;
	__emit 0x0f;
	__emit 0x8d;
	__emit 0xbd;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x2b;
	__emit 0xc7;
	__emit 0x40;
	__emit 0x83;
	__emit 0xe0;
	__emit 0xfe;
	__emit 0x8d;
	__emit 0x7c;
	__emit 0x07;
	__emit 0xfe;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x90;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x02;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x58;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x60;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x60;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x57;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x05;
	__emit 0x51;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x64;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x51;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x53;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x90;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x57;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x05;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x64;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x60;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x51;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x55;
	__emit 0xff;
	__emit 0x92;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x68;
	__emit 0x20;
	__emit 0x79;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x54;
	__emit 0xe8;
	__emit 0x9d;
	__emit 0xc8;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x50;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xcb;
	__emit 0x12;
	__emit 0x88;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x44;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0xf2;
	__emit 0xb5;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x06;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x05;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x83;
	__emit 0xec;
	__emit 0x10;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x70;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x05;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x0c;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x70;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x08;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x68;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x04;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x55;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x68;
	__emit 0x10;
	__emit 0x79;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x54;
	__emit 0xe8;
	__emit 0xfb;
	__emit 0xc7;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x50;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x05;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x29;
	__emit 0x12;
	__emit 0x88;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x44;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0x50;
	__emit 0xb5;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x06;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x05;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x83;
	__emit 0xec;
	__emit 0x10;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x70;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x05;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x0c;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x70;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x08;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x68;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x04;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x55;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x68;
	__emit 0x00;
	__emit 0x79;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x54;
	__emit 0xe8;
	__emit 0x59;
	__emit 0xc7;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x58;
	__emit 0x50;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x87;
	__emit 0x11;
	__emit 0x88;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x58;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x44;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0xae;
	__emit 0xb4;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x06;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x05;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x83;
	__emit 0xec;
	__emit 0x10;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x70;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x05;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x0c;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x70;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x08;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x68;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x04;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x55;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x68;
	__emit 0xf0;
	__emit 0x78;
	__emit 0x12;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x30;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x50;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x54;
	__emit 0xe8;
	__emit 0xb7;
	__emit 0xc6;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x24;
	__emit 0x69;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x50;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x48;
	__emit 0x07;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xe5;
	__emit 0x10;
	__emit 0x88;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x44;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0x0c;
	__emit 0xb4;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x70;
	__emit 0x12;
	__emit 0x2f;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x8b;
	__emit 0xf1;
	__emit 0xff;
	__emit 0x92;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x06;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x05;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x83;
	__emit 0xec;
	__emit 0x10;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x05;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x0c;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x70;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x70;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x08;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x68;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x04;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x64;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0x55;
	__emit 0xff;
	__emit 0x90;
	__emit 0xd4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x16;
	__emit 0x8b;
	__emit 0xce;
	__emit 0xff;
	__emit 0x92;
	__emit 0xdc;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x3c;
	__emit 0x5f;
	__emit 0x5e;
	__emit 0x5d;
	__emit 0x5b;
	__emit 0x64;
	__emit 0x89;
	__emit 0x0d;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x83;
	__emit 0xc4;
	__emit 0x38;
	__emit 0xc3;
	}
#if 0

	enum
	{
		BORDER_CORNER_SIZE	= 5,
		BORDER_LINE_SIZE		= 5,
	};
	Int Offset = 2;
	Int OffsetLower = 5;

	// save original x, y
	Int originalX = x;
	Int originalY = y;
	Int maxX = x + width;
	Int maxY = y + height;
	Int x2, y2;			// used for simultaneous drawing of line pairs
	Int size = 5;
	Int halfSize = size / 2;
	const Image *image1, *image2;
	// Draw Horizontal Lines
	// All border pieces are based on a 10 pixel offset from the centerline
	y = originalY - Offset;
	y2 = maxY - OffsetLower;
	x2 = maxX - (OffsetLower + BORDER_LINE_SIZE);
	image1 = TheMappedImageCollection->findImageByName("FrameT");
	image2 = TheMappedImageCollection->findImageByName("FrameB");
	for( x=(originalX + 3); x <= x2; x += BORDER_LINE_SIZE )
	{

		TheDisplay->drawImage( image1,
													 x, y, x + size, y + size );
		TheDisplay->drawImage( image2,
													 x, y2, x + size, y2 + size );

	}

	x2 = maxX - 5;//BORDER_CORNER_SIZE;

	// x == place to draw remainder if any
	if( (x2 - x) >= (BORDER_LINE_SIZE / 2) )
	{
		
		//Blit Half piece
		TheDisplay->drawImage( image1,
													 x, y, x + halfSize, y + size );
		TheDisplay->drawImage( image2,
													 x, y2, x + halfSize, y2 + size );

		x += (BORDER_LINE_SIZE / 2);

	}

	// x2 - x ... must now be less than a half piece
	// check for equals and if not blit an adjusted half piece border pieces have
	// a two pixel repeat so we will blit one pixel over if necessary to line up
	// the art, but we'll cover-up the overlap with the corners
	if( x < x2 )
	{
		x -= ((BORDER_LINE_SIZE / 2) - (((x2 - x) + 1) & ~1));

		//Blit Half piece
		TheDisplay->drawImage(image1,
													 x, y, x + halfSize, y + size );
		TheDisplay->drawImage( image2,
													 x, y2, x + halfSize, y2 + size );

	}

	// Draw Vertical Lines
	// All border pieces are based on a 10 pixel offset from the centerline
	image1 = TheMappedImageCollection->findImageByName("FrameL");
	image2 = TheMappedImageCollection->findImageByName("FrameR");

	x = originalX - Offset;
	x2 = maxX - OffsetLower;
	y2 = maxY - (OffsetLower + BORDER_LINE_SIZE);

	for( y=(originalY + 3); y <= y2; y += BORDER_LINE_SIZE )
	{

		TheDisplay->drawImage( image1,
													 x, y, x + size, y + size );
		TheDisplay->drawImage( image2,
													 x2, y, x2 + size, y + size );

	}

	y2 = maxY - OffsetLower;//BORDER_CORNER_SIZE;

	// y == place to draw remainder if any
	if( (y2 - y) >= (BORDER_LINE_SIZE / 2) )
	{

		//Blit Half piece
		TheDisplay->drawImage( image1,
													 x, y, x + size, y + halfSize );
		TheDisplay->drawImage( image2,
													 x2, y, x2 + size, y + halfSize );

		y += (BORDER_LINE_SIZE / 2);
	}

	// y2 - y ... must now be less than a half piece
	// check for equals and if not blit an adjusted half piece border pieces have
	// a two pixel repeat so we will blit one pixel over if necessary to line up
	// the art, but we'll cover-up the overlap with the corners
	if( y < y2 )
	{
		y -= ((BORDER_LINE_SIZE / 2) - (((y2 - y) + 1) & ~1));

		//Blit Half piece
		TheDisplay->drawImage( image1,
													 x, y, x + size, y + halfSize );
		TheDisplay->drawImage( image2,
													 x2, y, x2 + size, y + halfSize );

	}

	// Draw Corners
	x = originalX - 2;//BORDER_CORNER_SIZE ;
	y = originalY - 2;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerUL");
	TheDisplay->drawImage( image1,
												 x, y, x + size, y + size );
	x = maxX - 5;//BORDER_CORNER_SIZE;
	y = originalY - 2;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerUR");
	TheDisplay->drawImage(image1,
												 x, y, x + size, y + size );
	x = originalX - 2;//BORDER_CORNER_SIZE;
	y = maxY - 5;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerLL");
	TheDisplay->drawImage( image1,
												 x, y, x + size, y + size );
	x = maxX - 5;//BORDER_CORNER_SIZE;
	y = maxY - 5;//BORDER_CORNER_SIZE;
	image1 = TheMappedImageCollection->findImageByName("FrameCornerLR");
	TheDisplay->drawImage(image1,
												 x, y, x + size, y + size );

#endif
}


// W3DCommandBarHelpPopupDraw exact retail body is emitted by
// W3DCommandBarHelpPopupDrawThunk.cpp.
