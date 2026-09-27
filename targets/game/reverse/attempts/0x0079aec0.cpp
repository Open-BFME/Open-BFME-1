// ?W3DPowerDrawA@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.960604425256341 date=2026-09-27
// Near match for RVA 0x0079AEC0: 1853 bytes; shape 1.000; 73 differing stack displacement bytes.
// Zero Hour W3DPowerDrawA body with retail StringBase temporary ABI, direct local-player call,
// Player+0xA4 energy view, FieldParse-backed power settings, and Display slots +0x88/+0x90.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
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
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


// Partial BFME views, backed by this body and GlobalData's FieldParse table.
struct EnergyView0079AEC0 {
 void *field00; int m_energyProduction, m_energyConsumption;
 int getConsumption() const { return m_energyConsumption; }
 int getProduction() const { return m_energyProduction; }
};
struct PowerGlobals0079AEC0 {
 char pad0000[0xC5C]; int m_powerBarBase; float m_powerBarIntervals; int m_powerBarYellowRange;
};
Real logN(Real value, Real logBase) { return (Real)log10(value)/log10(logBase); }
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
	Int posX, posY; ICoord2D size;
	window->winGetScreenPosition( &posX, &posY );
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
	leftEnd.x = posX + leftSize.x;
	leftEnd.y = posY + size.y;
	rightStart.x = posX + (range - rightSize.x);
	rightStart.y = posY;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;
	
	if( centerWidth <= 0)
	{
		// draw left end
		start.x = posX;
		start.y = posY;
		end.y = leftEnd.y;
		end.x = posX + range/2;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.y = rightStart.y;
		start.x = end.x;
		end.x = posX + range;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	else
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageWidth();

		// draw the pieces
		start.x = leftEnd.x;
		start.y = posY;
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
		start.x = posX;
		start.y = posY;
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
		posXstart = posX + (size.x - slider->getImageWidth());
		posXend = posX + size.x;
	}
	else
	{
		posXstart = posX + (range - slider->getImageWidth()/2);
		posXend = posX + (range + slider->getImageWidth()/2);
	}
	if(posXstart <=posX)
	{
		posXstart	 = posX;
		posXend	= posX + slider->getImageWidth();
	}
	TheWindowManager->winDrawImage(slider, posXstart, posY + size.y - slider->getImageHeight(), posXend, posY + size.y);
}
