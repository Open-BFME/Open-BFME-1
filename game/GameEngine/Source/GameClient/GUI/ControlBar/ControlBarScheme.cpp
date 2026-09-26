// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/controlbarvtables /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define BFME_STLP_NODE_ALLOC 1
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

// FILE: ControlBarScheme.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Apr 2002
//
//	Filename: 	ControlBarScheme.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	Contains all the Command bar goodness in terms of how it looks
//						For instrucitons on how to use, please see it's .h file
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#define _STLP_NO_EXCEPTIONS 1	// Open-BFME7: this TU was built with STLport exceptions off (STLport helpers inline as in retail)
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/Recorder.h"
#include "GameClient/ControlBarScheme.h"
#include "GameClient/Display.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Image.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetPushButton.h"
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
enum{
	COMMAND_BAR_SIZE_OFFSET = 0
};

const FieldParse ControlBarSchemeManager::m_controlBarSchemeFieldParseTable[] = 
{

	{ "ImagePart",						ControlBarSchemeManager::parseImagePart,			NULL, NULL },
	{ "AnimatingPart",				ControlBarSchemeManager::parseAnimatingPart,	NULL, NULL },
	{ "ScreenCreationRes",		INI::parseICoord2D,						NULL, offsetof( ControlBarScheme, m_ScreenCreationRes ) },
	{ "Side",									INI::parseAsciiString,				NULL, offsetof( ControlBarScheme, m_side ) },
	{ "QueueButtonImage",			INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buttonQueueImage ) },
	{ "RightHUDImage",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_rightHUDImage ) },
	{ "BuildUpClockColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_buildUpClockColor ) },
	{ "ButtonBorderBuildColor",			INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderBuildColor ) },
	{ "CommandBarBorderColor",			INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_commandBarBorderColor ) },
	{ "ButtonBorderActionColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderActionColor ) },
	{ "ButtonBorderUpgradeColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderUpgradeColor ) },
	{ "ButtonBorderSystemColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderSystemColor ) },
	{ "OptionsButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonEnable ) },
	{ "OptionsButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonHightlited ) },
	{ "OptionsButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonPushed ) },
	{ "OptionsButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonDisabled ) },
	{ "IdleWorkerButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonEnable ) },
	{ "IdleWorkerButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonHightlited ) },
	{ "IdleWorkerButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonPushed ) },
	{ "IdleWorkerButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonDisabled ) },
	{ "BuddyButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonEnable ) },
	{ "BuddyButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonHightlited ) },
	{ "BuddyButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonPushed ) },
	{ "BuddyButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonDisabled) },
	{ "BeaconButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonEnable ) },
	{ "BeaconButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonHightlited ) },
	{ "BeaconButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonPushed ) },
	{ "BeaconButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonDisabled ) },
	{ "GenBarButtonIn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_genBarButtonIn ) },
	{ "GenBarButtonOn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_genBarButtonOn ) },
	{ "ToggleButtonUpIn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonUpIn ) },
	{ "ToggleButtonUpOn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonUpOn ) },
	{ "ToggleButtonUpPushed",		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonUpPushed ) },
	{ "ToggleButtonDownIn",			INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonDownIn ) },
	{ "ToggleButtonDownOn", 		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonDownOn ) },
	{ "ToggleButtonDownPushed",	INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonDownPushed ) },

	{ "GeneralButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonEnable ) },
	{ "GeneralButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonHightlited ) },
	{ "GeneralButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonPushed ) },
	{ "GeneralButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonDisabled ) },

	{ "UAttackButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_uAttackButtonEnable ) },
	{ "UAttackButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_uAttackButtonHightlited ) },
	{ "UAttackButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_uAttackButtonPushed ) },

	{ "GenArrow",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_genArrow) },

	{ "MinMaxButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_minMaxButtonEnable ) },
	{ "MinMaxButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_minMaxButtonHightlited ) },
	{ "MinMaxButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_minMaxButtonPushed ) },

	{ "MinMaxUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_minMaxUL ) },
	{ "MinMaxLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_minMaxLR ) },

	{ "GeneralUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_generalUL ) },
	{ "GeneralLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_generalLR ) },

	{ "UAttackUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_uAttackUL ) },
	{ "UAttackLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_uAttackLR ) },

	{ "OptionsUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_optionsUL ) },
	{ "OptionsLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_optionsLR ) },

	{ "WorkerUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_workerUL ) },
	{ "WorkerLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_workerLR ) },

	{ "ChatUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_chatUL ) },
	{ "ChatLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_chatLR ) },

	{ "BeaconUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_beaconUL ) },
	{ "BeaconLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_beaconLR ) },

	{ "PowerBarUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_powerBarUL ) },
	{ "PowerBarLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_powerBarLR ) },

	{ "MoneyUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_moneyUL ) },
	{ "MoneyLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_moneyLR ) },

	{ "CommandMarkerImage",		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_commandMarkerImage) },
	{ "ExpBarForegroundImage",		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_expBarForeground) },
	{ "PowerPurchaseImage",			INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_powerPurchaseImage) },

	{ NULL,										NULL,													NULL, 0 }  // keep this last

};

// used to parse the anim types that each animation part of a scheme can have
static const LookupListRec AnimTypeNames[] = 
{
	{ "SLIDE_RIGHT", ControlBarSchemeAnimation::CB_ANIM_SLIDE_RIGHT },
	{ NULL, 0	}
};

static void animSlideRight( ControlBarSchemeAnimation *anim );

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
__declspec(noinline) ControlBarSchemeImage::ControlBarSchemeImage( void )
{
	m_name.clear();
	m_position.x = m_position.y = 0;
	m_size.x = m_size.y = 0;
	m_image = NULL;
	m_layer = 0;
}

ControlBarSchemeImage::~ControlBarSchemeImage( void )
{
	m_image = NULL;
}

ControlBarSchemeAnimation::ControlBarSchemeAnimation( void )
{
	// Added by Sadullah Nader
	// Initializations missing and needed
	
	m_animDuration = 0;
	m_finalPos.x = m_finalPos.y = 0;

	// End Add
	m_name.clear();
	m_animType = 0;
	m_animImage = NULL;
	m_startPos.x = m_startPos.y = 0;
	m_currentFrame = 0;
}

ControlBarSchemeAnimation::~ControlBarSchemeAnimation( void )
{
	m_animImage = NULL;
}


void ControlBarScheme::reset(void)
{
	for (Int i = 0; i < MAX_CONTROL_BAR_SCHEME_IMAGE_LAYERS; i++)
	{
		ControlBarSchemeImageList::iterator it = m_layer[i].begin();

		while (it != m_layer[i].end())
		{
			ControlBarSchemeImage *im = *it;
			if( im )
				delete im;
			im = NULL;
			it ++;	
		}
		m_layer[i].clear();
	
	}


	ControlBarSchemeAnimationList::iterator it = m_animations.begin();

	while (it != m_animations.end())
	{
		ControlBarSchemeAnimation *anim = *it;
		if( anim )
		{
			anim->m_animImage = NULL;
			delete(anim);
		}
		anim = NULL;
		it ++;	
	}
	m_animations.clear();

	m_name.clear();
	m_ScreenCreationRes.x = m_ScreenCreationRes.y = 0;
	m_side.clear();
	m_buttonQueueImage = NULL;
	m_rightHUDImage = NULL;
	m_optionsButtonHightlited = NULL;
	m_optionsButtonPushed = NULL;
	m_optionsButtonDisabled = NULL;

	m_idleWorkerButtonEnable = NULL;
	m_idleWorkerButtonHightlited = NULL;
	m_idleWorkerButtonPushed = NULL;
	m_idleWorkerButtonDisabled = NULL;

	m_buddyButtonEnable = NULL;
	m_buddyButtonHightlited = NULL;
	m_buddyButtonPushed = NULL;
	m_buddyButtonDisabled = NULL;

	m_beaconButtonEnable = NULL;
	m_beaconButtonHightlited = NULL;
	m_beaconButtonPushed = NULL;
	m_beaconButtonDisabled = NULL;

	m_genBarButtonIn = NULL;
	m_genBarButtonOn = NULL;

	m_toggleButtonUpIn = NULL;
	m_toggleButtonUpOn = NULL;
	m_toggleButtonUpPushed = NULL;
	m_toggleButtonDownIn = NULL;
	m_toggleButtonDownOn = NULL;
	m_toggleButtonDownPushed = NULL;

	m_generalButtonEnable = NULL;

	m_powerPurchaseImage = NULL;
	m_commandMarkerImage = NULL;
		
}

ControlBarScheme::~ControlBarScheme(void)
{
	reset();
}

ControlBarScheme::ControlBarScheme(void)
{

	m_animations.clear();
	for (Int i = 0; i < MAX_CONTROL_BAR_SCHEME_IMAGE_LAYERS; i++)
		m_layer[i].clear();
	m_name.clear();
	m_ScreenCreationRes.x = m_ScreenCreationRes.y = 0;
	m_side.clear();
	m_buttonQueueImage = NULL;
	m_rightHUDImage = NULL;
	m_buildUpClockColor = GameMakeColor(0,0,0,128);
	m_borderBuildColor = GAME_COLOR_UNDEFINED;
	m_borderActionColor = GAME_COLOR_UNDEFINED;
	m_borderUpgradeColor = GAME_COLOR_UNDEFINED;
	m_borderSystemColor = GAME_COLOR_UNDEFINED;
	m_commandBarBorderColor = GAME_COLOR_UNDEFINED;
	//m_buttonQueueImage = TheMappedImageCollection("")
	m_optionsButtonHightlited = NULL;
	m_optionsButtonPushed = NULL;
	m_optionsButtonDisabled = NULL;
	m_idleWorkerButtonEnable = NULL;
	m_optionsButtonEnable = NULL;
	m_idleWorkerButtonHightlited = NULL;
	m_idleWorkerButtonPushed = NULL;
	m_idleWorkerButtonDisabled = NULL;

	m_buddyButtonEnable = NULL;
	m_buddyButtonHightlited = NULL;
	m_buddyButtonPushed = NULL;
	m_buddyButtonDisabled= NULL;

	m_beaconButtonEnable = NULL;
	m_beaconButtonHightlited = NULL;
	m_beaconButtonPushed = NULL;
	m_beaconButtonDisabled= NULL;

	m_genBarButtonIn = NULL;
	m_genBarButtonOn = NULL;

	m_toggleButtonUpIn = NULL;
	m_toggleButtonUpOn = NULL;
	m_toggleButtonUpPushed = NULL;
	m_toggleButtonDownIn = NULL;
	m_toggleButtonDownOn = NULL;
	m_toggleButtonDownPushed = NULL;

	m_generalButtonEnable = NULL;
	m_powerPurchaseImage = NULL;
	m_commandMarkerImage = NULL;
	m_generalButtonHightlited = NULL;
	m_generalButtonPushed = NULL;
	m_generalButtonDisabled = NULL;

	m_uAttackButtonEnable = NULL;
	m_uAttackButtonHightlited = NULL;
	m_uAttackButtonPushed = NULL;
	m_minMaxButtonEnable = NULL;
	m_moneyUL.x = 0;
	m_minMaxButtonHightlited = NULL;
	m_minMaxButtonPushed = NULL;
	m_genArrow = NULL;

	m_minMaxUL.y = 0;
	m_minMaxLR.y = 0;
	m_generalUL.y = 0;
	m_generalLR.y = 0;
	m_uAttackUL.y = 0;
	m_uAttackLR.y = 0;
	m_optionsUL.y = 0;
	m_optionsLR.y = 0;
	m_workerUL.y = 0;
	m_workerLR.y = 0;
	m_chatUL.y = 0;
	m_chatLR.y = 0;
	m_beaconUL.y = 0;
	m_beaconLR.y = 0;
	m_powerBarUL.y = 0;
	m_powerBarLR.y = 0;

	m_minMaxLR.x = 0;
	m_generalUL.x = 0;
	m_generalLR.x = 0;
	m_uAttackUL.x = 0;
	m_uAttackLR.x = 0;
	m_optionsUL.x = 0;
	m_optionsLR.x = 0;
	m_workerUL.x = 0;
	m_workerLR.x = 0;
	m_chatUL.x = 0;
	m_chatLR.x = 0;
	m_beaconUL.x = 0;
	m_beaconLR.x = 0;
	m_powerBarUL.x = 0;
	m_powerBarLR.x = 0;

	m_expBarForeground = NULL;
	m_moneyUL.y = 0;
	m_moneyLR.x = 0;
	m_moneyLR.y = 0;
	m_minMaxUL.x = 0;
}


// BFME's ControlBarScheme inserts a fifth button-border colour after
// m_borderSystemColor, so every member from m_commandBarBorderColor on sits
// four bytes later than the Zero Hour header puts it (retail init reads the
// communicator images at +0x54..+0x60, the chat rectangle at +0x120 and the
// command marker at +0x154).
struct BfmeControlBarSchemeInitView
{
	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;
	Image *m_buttonQueueImage;
	Image *m_rightHUDImage;					///< +0x14
	Color m_buildUpClockColor;				///< +0x18
	Color m_borderBuildColor;				///< +0x1c
	Color m_borderActionColor;
	Color m_borderUpgradeColor;
	Color m_borderSystemColor;
	Color m_bfmeBorderFifthColor;			///< +0x2c
	Color m_commandBarBorderColor;			///< +0x30
	Image *m_optionsButtonEnable;			///< +0x34
	Image *m_optionsButtonHightlited;
	Image *m_optionsButtonPushed;
	Image *m_optionsButtonDisabled;
	Image *m_idleWorkerButtonEnable;		///< +0x44
	Image *m_idleWorkerButtonHightlited;
	Image *m_idleWorkerButtonPushed;
	Image *m_idleWorkerButtonDisabled;
	Image *m_buddyButtonEnable;				///< +0x54
	Image *m_buddyButtonHightlited;
	Image *m_buddyButtonPushed;
	Image *m_buddyButtonDisabled;
	Image *m_beaconButtonEnable;			///< +0x64
	Image *m_beaconButtonHightlited;
	Image *m_beaconButtonPushed;
	Image *m_beaconButtonDisabled;
	Image *m_genBarButtonIn;				///< +0x74
	Image *m_genBarButtonOn;
	Image *m_toggleButtonUpIn;				///< +0x7c
	Image *m_toggleButtonUpOn;
	Image *m_toggleButtonUpPushed;
	Image *m_toggleButtonDownIn;
	Image *m_toggleButtonDownOn;
	Image *m_toggleButtonDownPushed;
	Image *m_generalButtonEnable;			///< +0x94
	Image *m_generalButtonHightlited;
	Image *m_generalButtonPushed;
	Image *m_generalButtonDisabled;
	Image *m_uAttackButtonEnable;			///< +0xa4
	Image *m_uAttackButtonHightlited;
	Image *m_uAttackButtonPushed;
	Image *m_minMaxButtonEnable;			///< +0xb0
	Image *m_minMaxButtonHightlited;
	Image *m_minMaxButtonPushed;
	Image *m_genArrow;						///< +0xbc
	ICoord2D m_moneyUL;						///< +0xc0
	ICoord2D m_moneyLR;
	ICoord2D m_minMaxUL;
	ICoord2D m_minMaxLR;
	ICoord2D m_generalUL;
	ICoord2D m_generalLR;
	ICoord2D m_uAttackUL;					///< +0xf0
	ICoord2D m_uAttackLR;
	ICoord2D m_optionsUL;
	ICoord2D m_optionsLR;
	ICoord2D m_workerUL;
	ICoord2D m_workerLR;
	ICoord2D m_chatUL;						///< +0x120
	ICoord2D m_chatLR;
	ICoord2D m_beaconUL;
	ICoord2D m_beaconLR;
	ICoord2D m_powerBarUL;
	ICoord2D m_powerBarLR;
	Image *m_expBarForeground;				///< +0x150
	Image *m_commandMarkerImage;			///< +0x154
};

// ControlBar's BFME border-colour and arrow slots, written inline by retail.
struct BfmeControlBarSchemeInitBar
{
	unsigned char m_unreconstructed_000[ 0x294 ];
	Color m_commandBarBorderColor;			///< retail this+0x294
	unsigned char m_unreconstructed_298[ 0x2bc - 0x298 ];
	const Image *m_genArrow;				///< retail this+0x2bc
};

// updateBuildUpClockColor and the five-colour updateCommanBarBorderColors,
// under the names their matched bodies carry (0x0049D010, 0x0049D020).
class Rva0049D010DwordSlot
{
public:
	void set(Int value);
};

class Gen_0049D020
{
public:
	void bfmeSet(Int build, Int action, Int upgrade, Int system, Int fifth);
};

// ?init@ControlBarScheme@@QAEXXZ -- retail 0x004ABA80, 3107 bytes. Zero Hour's
// body with BFME's scheme layout; BFME drops updateBuildQueueDisabledImages,
// sets the command marker instead of the slot-exit image, passes a fifth
// border colour and no longer sizes GenExpParent.
void ControlBarScheme::init(void)
{
	BfmeControlBarSchemeInitView *self = (BfmeControlBarSchemeInitView *)this;
	if(TheControlBar)
	{
		TheControlBar->switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
		TheControlBar->updateRightHUDImage(self->m_rightHUDImage);
		((Rva0049D010DwordSlot *)TheControlBar)->set( self->m_buildUpClockColor );
		((Gen_0049D020 *)TheControlBar)->bfmeSet(self->m_borderBuildColor, self->m_borderActionColor, self->m_borderUpgradeColor, self->m_borderSystemColor, self->m_bfmeBorderFifthColor);
		((BfmeControlBarSchemeInitBar *)TheControlBar)->m_commandBarBorderColor = self->m_commandBarBorderColor;
		TheControlBar->updateCommandMarkerImage(self->m_commandMarkerImage);
		TheControlBar->updateUpDownImages(self->m_toggleButtonUpIn, self->m_toggleButtonUpOn, self->m_toggleButtonUpPushed, self->m_toggleButtonDownIn, self->m_toggleButtonDownOn, self->m_toggleButtonDownPushed, self->m_generalButtonEnable, self->m_generalButtonHightlited);
		((BfmeControlBarSchemeInitBar *)TheControlBar)->m_genArrow = self->m_genArrow;
	}
	GameWindow *win = NULL;
	Coord2D resMultiplier;
	resMultiplier.x = TheDisplay->getWidth()/INT_TO_REAL(self->m_ScreenCreationRes.x) ;
	resMultiplier.y = TheDisplay->getHeight()/INT_TO_REAL(self->m_ScreenCreationRes.y);

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:PopupCommunicator" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage(win, self->m_buddyButtonEnable);
		GadgetButtonSetHiliteImage(win, self->m_buddyButtonHightlited);
		GadgetButtonSetHiliteSelectedImage(win, self->m_buddyButtonPushed);
		GadgetButtonSetDisabledImage(win, self->m_buddyButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_chatUL.x * resMultiplier.x - parX;
			y = self->m_chatUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_chatUL.x * resMultiplier.x;
			y = self->m_chatUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_chatLR.x - self->m_chatUL.x)*resMultiplier.x + COMMAND_BAR_SIZE_OFFSET,(self->m_chatLR.y - self->m_chatUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonIdleWorker" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage(win, self->m_idleWorkerButtonEnable);
		GadgetButtonSetHiliteImage(win, self->m_idleWorkerButtonHightlited);
		GadgetButtonSetHiliteSelectedImage(win, self->m_idleWorkerButtonPushed);
		GadgetButtonSetDisabledImage(win, self->m_idleWorkerButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_workerUL.x * resMultiplier.x - parX;
			y = self->m_workerUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_workerUL.x * resMultiplier.x;
			y = self->m_workerUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );

		win->winSetSize((self->m_workerLR.x - self->m_workerUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_workerLR.y - self->m_workerUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);

	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ExpBarForeground" ) );
	if(win)
	{
		win->winSetEnabledImage(0, self->m_expBarForeground);
	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonOptions" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage(win, self->m_optionsButtonEnable);
		GadgetButtonSetHiliteImage(win, self->m_optionsButtonHightlited);
		GadgetButtonSetHiliteSelectedImage(win, self->m_optionsButtonPushed);
		GadgetButtonSetDisabledImage(win, self->m_optionsButtonDisabled);
		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_optionsUL.x * resMultiplier.x - parX;
			y = self->m_optionsUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_optionsUL.x * resMultiplier.x;
			y = self->m_optionsUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_optionsLR.x - self->m_optionsUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_optionsLR.y - self->m_optionsUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonPlaceBeacon" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage(win, self->m_beaconButtonEnable);
		GadgetButtonSetHiliteImage(win, self->m_beaconButtonHightlited);
		GadgetButtonSetHiliteSelectedImage(win, self->m_beaconButtonPushed);
		GadgetButtonSetDisabledImage(win, self->m_beaconButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_beaconUL.x * resMultiplier.x - parX;
			y = self->m_beaconUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_beaconUL.x * resMultiplier.x;
			y = self->m_beaconUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_beaconLR.x - self->m_beaconUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_beaconLR.y - self->m_beaconUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:MoneyDisplay" ) );
	if(win)
	{

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_moneyUL.x * resMultiplier.x - parX;
			y = self->m_moneyUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_moneyUL.x * resMultiplier.x;
			y = self->m_moneyUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_moneyLR.x - self->m_moneyUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_moneyLR.y - self->m_moneyUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:PowerWindow" ) );
	if(win)
	{

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_powerBarUL.x * resMultiplier.x - parX;
			y = self->m_powerBarUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_powerBarUL.x * resMultiplier.x;
			y = self->m_powerBarUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_powerBarLR.x - self->m_powerBarUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_powerBarLR.y - self->m_powerBarUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonGeneral" ) );
	if(win)
	{

		GadgetButtonSetEnabledImage(win, self->m_generalButtonEnable);
		GadgetButtonSetHiliteImage(win, self->m_generalButtonHightlited);
		GadgetButtonSetHiliteSelectedImage(win, self->m_generalButtonPushed);
		GadgetButtonSetDisabledImage(win, self->m_generalButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_generalUL.x * resMultiplier.x - parX;
			y = self->m_generalUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_generalUL.x * resMultiplier.x;
			y = self->m_generalUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_generalLR.x - self->m_generalUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_generalLR.y - self->m_generalUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonLarge" ) );
	if(win)
	{
		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_minMaxUL.x * resMultiplier.x - parX;
			y = self->m_minMaxUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_minMaxUL.x * resMultiplier.x;
			y = self->m_minMaxUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_minMaxLR.x - self->m_minMaxUL.x)*resMultiplier.x + COMMAND_BAR_SIZE_OFFSET,(self->m_minMaxLR.y - self->m_minMaxUL.y)*resMultiplier.y + COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:WinUAttack" ) );
	if(win)
	{
		win->winSetEnabledImage(0,self->m_uAttackButtonEnable);
		win->winSetDisabledImage(0,self->m_uAttackButtonHightlited);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_uAttackUL.x * resMultiplier.x - parX;
			y = self->m_uAttackUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_uAttackUL.x * resMultiplier.x;
			y = self->m_uAttackUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_uAttackLR.x - self->m_uAttackUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_uAttackLR.y - self->m_uAttackUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}
}

//
// Add an animation to the animation list
//-----------------------------------------------------------------------------
// ?addAnimation@ControlBarScheme@@QAEXPAVControlBarSchemeAnimation@@@Z present-unmatched
void ControlBarScheme::addAnimation( ControlBarSchemeAnimation *schemeAnim )
{
	if( !schemeAnim )
	{
		DEBUG_ASSERTCRASH(FALSE,("Trying to add a null animation to the controlbarscheme\n"));
		return;
	}
	m_animations.push_back( schemeAnim );
}// addAnimation

//
// Add an image to the proper layer list
//-----------------------------------------------------------------------------
void ControlBarScheme::addImage( ControlBarSchemeImage *schemeImage )
{
	if( !schemeImage )
	{
		DEBUG_ASSERTCRASH(FALSE,("Trying to add a null image to the controlbarscheme\n"));
		return;
	}

	if(schemeImage->m_layer < 0 || schemeImage->m_layer >= MAX_CONTROL_BAR_SCHEME_IMAGE_LAYERS)
	{
		DEBUG_ASSERTCRASH(FALSE,("SchemeImage %s attempted to be added to layer %d which is not Between to %d, %d\n",
								 schemeImage->m_name.str(), schemeImage->m_layer, 0, MAX_CONTROL_BAR_SCHEME_IMAGE_LAYERS));
		// bring the foobar to the front so we make it obvious that something's wrong
		schemeImage->m_layer = 0;
	}

	m_layer[schemeImage->m_layer].push_back(schemeImage);
}// addImage

//
// Update the position of the image that's animating
//-----------------------------------------------------------------------------
void ControlBarScheme::updateAnim (ControlBarSchemeAnimation * anim)
{
	switch(anim->m_animType)
	{
		case ControlBarSchemeAnimation::CB_ANIM_SLIDE_RIGHT:
		{
			animSlideRight( anim );
			break;
		}
		default:
		{
			DEBUG_ASSERTCRASH(FALSE,("We tried to animate but not animate function was found %d", anim->m_animType));
		}
	}
}

//
// Add an image to the proper layer list
//-----------------------------------------------------------------------------
void ControlBarScheme::update( void )
{
	ControlBarSchemeAnimationList::iterator it = m_animations.begin();
	
	while (it != m_animations.end())
	{
		ControlBarSchemeAnimation *anim = *it;
		if( !anim )
		{
			DEBUG_ASSERTCRASH(FALSE,("THere's no Animation in the ControlBarSchemeAnimationList:m_animations"));
			return;
		}
		updateAnim( anim );
		it ++;	
	}
	
}

//
// Loop through the propper lists and draw everything for the forground
//-----------------------------------------------------------------------------
// ?drawForeground@ControlBarScheme@@QAEXUCoord2D@@UICoord2D@@@Z present-unmatched
void ControlBarScheme::drawForeground( Coord2D multi, ICoord2D offset )
{
	for(Int i = CONTROL_BAR_SCHEME_FOREGROUND_IMAGE_LAYERS - 1; i >= 0; i--)
	{
		ControlBarSchemeImageList::iterator it = m_layer[i].begin();
		while (it != m_layer[i].end())
		{	
			ControlBarSchemeImage *schemeImage = *it;
			if( !schemeImage )
			{
				DEBUG_ASSERTCRASH(FALSE,("There is no ControlBarSchemeImage found in the m_layer list"));
				it++;
				continue;
			}
			
			// if we dont' have an image, don't try to draw it
			if(!schemeImage->m_image)
			{
				it++;
				continue;
			}
			
			// draw the image
			TheDisplay->drawImage(schemeImage->m_image, schemeImage->m_position.x * multi.x + offset.x,
														schemeImage->m_position.y * multi.y + offset.y, 
														(schemeImage->m_position.x + schemeImage->m_size.x) * multi.x + offset.x,
														(schemeImage->m_position.y + schemeImage->m_size.y) * multi.y + offset.y);
			
			it ++;	
		}
	}
}

//
// Add an image to the proper layer list
//-----------------------------------------------------------------------------
// ?drawBackground@ControlBarScheme@@QAEXUCoord2D@@UICoord2D@@@Z present-unmatched
void ControlBarScheme::drawBackground( Coord2D multi, ICoord2D offset )
{
	
	for(Int i = MAX_CONTROL_BAR_SCHEME_IMAGE_LAYERS - 1; i >= CONTROL_BAR_SCHEME_FOREGROUND_IMAGE_LAYERS; i--)
	{
		ControlBarSchemeImageList::iterator it = m_layer[i].begin();
		while (it != m_layer[i].end())
		{	
			ControlBarSchemeImage *schemeImage = *it;
			if( !schemeImage )
			{
				DEBUG_ASSERTCRASH(FALSE,("There is no ControlBarSchemeImage found in the m_layer list"));
				it++;
				continue;
			}
			
			// if we don't have an image, don't try to draw it
			if(!schemeImage->m_image)
			{
				it++;
				continue;
			}
			
			// draw it
			TheDisplay->drawImage(schemeImage->m_image, schemeImage->m_position.x * multi.x + offset.x,
														schemeImage->m_position.y * multi.y + offset.y, 
														(schemeImage->m_position.x + schemeImage->m_size.x) * multi.x + offset.x,
														(schemeImage->m_position.y + schemeImage->m_size.y) * multi.y + offset.y);
			
			it ++;	
		}
	}
}


//
// Constructor for the manager
//-----------------------------------------------------------------------------
ControlBarSchemeManager::ControlBarSchemeManager( void )
{
	m_currentScheme = NULL;
	m_schemeList.clear();
	m_multiplyer.x = m_multiplyer.y = 1;
}

//
// Destructor for the Manager
//-----------------------------------------------------------------------------
ControlBarSchemeManager::~ControlBarSchemeManager( void )
{
	ControlBarSchemeList::iterator it = m_schemeList.begin();

	// iterate through the list and return the scheme that we're looking for
	while (it != m_schemeList.end())
	{
		ControlBarScheme *CBScheme = *it;
		if( CBScheme )
			delete CBScheme;
		CBScheme = NULL;
		it ++;	
	}
	m_schemeList.clear();
	m_currentScheme = NULL;

}

//
// Parse the Image Part of the command bar
//-----------------------------------------------------------------------------
// ?parseImagePart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z
// Body in ControlBarScheme_parseImagePart.asm (exact 172B retail @ 0x4AE920).
// Retail inlines addImage + STLport list node alloc; C++ emits call-shaped list insert.

//
// each animation part contains and image, parse it
//-----------------------------------------------------------------------------
void ControlBarSchemeManager::parseAnimatingPartImage(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
{
	static const FieldParse myFieldParse[] = 
		{
			{ "Position",				INI::parseICoord2D,				NULL, offsetof( ControlBarSchemeImage, m_position ) },
			{ "Size",						INI::parseICoord2D,				NULL, offsetof( ControlBarSchemeImage, m_size ) },
      { "ImageName",			INI::parseMappedImage,		NULL, offsetof( ControlBarSchemeImage, m_image ) },
			{ "Layer",					INI::parseInt,						NULL, offsetof( ControlBarSchemeImage, m_layer ) },
			{ NULL,							NULL,											NULL, 0 }  // keep this last
		};

	ControlBarSchemeImage *schemeImage = NEW ControlBarSchemeImage;
	ini->initFromINI(schemeImage, myFieldParse);
	((ControlBarSchemeAnimation*)instance)->m_animImage = schemeImage;

}

//
// parse the animating part of the control bar scheme
//-----------------------------------------------------------------------------
// ?parseAnimatingPart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z
// Body in ControlBarScheme_parseAnimatingPart.asm (exact 219B retail @ 0x4AEA00).
// Retail inlines addAnimation+addImage + STLport list node alloc; C++ cannot match.


//
// Create a new control bar and return it.  Link it into our control bar list
//-----------------------------------------------------------------------------
// Verified retail body at 0x004AEB20 (267 bytes); INI parser is the named caller.
ControlBarScheme *ControlBarSchemeManager::newControlBarScheme( AsciiString name )
{
	ControlBarScheme *cbScheme = 	findControlBarScheme(name);
	if(cbScheme)
	{
		DEBUG_ASSERTCRASH(false,("We're overwriting a previous control bar scheme %s",name.str()));
		cbScheme->reset();
		cbScheme->m_name.set( name );
		cbScheme->m_name.toLower();
		return cbScheme;		
	}

	cbScheme = NEW ControlBarScheme;

	if( !cbScheme  || name.isEmpty() )
	{
		DEBUG_ASSERTCRASH(FALSE,("Could not create controlbar %s", name.str()));
		return NULL;
	}

	cbScheme->m_name.set( name );
	cbScheme->m_name.toLower();

	m_schemeList.push_back(cbScheme);
		
	return cbScheme;
}

//
// Find a scheme based on name
//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/ControlBarScheme_find.cpp
// ?findControlBarScheme@ControlBarSchemeManager@@QAEPAVControlBarScheme@@VAsciiString@@@Z present-unmatched
ControlBarScheme *ControlBarSchemeManager::findControlBarScheme( AsciiString name )
{
	name.toLower();
	
	ControlBarSchemeList::iterator it = m_schemeList.begin();

	// iterate through the list and return the scheme that we're looking for
	while (it != m_schemeList.end())
	{
		ControlBarScheme *CBScheme = *it;
		if( !CBScheme )
		{
			DEBUG_ASSERTCRASH(FALSE,("There's no ControlBarScheme in the ControlBarSchemeList:m_schemeList"));
			return NULL;
		}
		if(CBScheme->m_name.compareNoCase( name ) == 0)
			return CBScheme;
		it ++;	
	}
	return NULL;
}

//
// Preload assets
//-----------------------------------------------------------------------------
// ?preloadAssets@ControlBarSchemeManager@@QAEXW4TimeOfDay@@@Z present-unmatched
void ControlBarSchemeManager::preloadAssets( TimeOfDay timeOfDay )
{
	for (ControlBarSchemeList::iterator it = m_schemeList.begin(); it != m_schemeList.end(); ++it)
	{
		ControlBarScheme *CBScheme = *it;
		if( !CBScheme )
		{
			DEBUG_ASSERTCRASH(FALSE,("There's no ControlBarScheme in the ControlBarSchemeList:m_schemeList"));
			continue;
		}

		if (CBScheme->m_buttonQueueImage)
		{
			TheDisplay->preloadTextureAssets(CBScheme->m_buttonQueueImage->getFilename());
		}

		if (CBScheme->m_rightHUDImage)
		{
			TheDisplay->preloadTextureAssets(CBScheme->m_buttonQueueImage->getFilename());
		}

		for (Int layer = 0; layer < MAX_CONTROL_BAR_SCHEME_IMAGE_LAYERS; ++layer)
		{
			for (ControlBarScheme::ControlBarSchemeImageList::iterator listIt = CBScheme->m_layer[layer].begin(); listIt != CBScheme->m_layer[layer].end(); ++listIt)
			{
				ControlBarSchemeImage *cbImage = *listIt;
				if (cbImage)
				{
					const Image *image = TheMappedImageCollection->findImageByName( cbImage->m_name );
					if (image)
					{
						TheDisplay->preloadTextureAssets(image->getFilename());
					}
				}
			}
		}
	}
}

//
// Find a scheme based on name
//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/ControlBarSchemeManager_initMethodThunk.cpp
// ?init@ControlBarSchemeManager@@QAEXXZ present-unmatched
void ControlBarSchemeManager::init( void )
{

	INI ini;
	// Read from INI all the ControlBarSchemes
	ini.load( AsciiString( "Data\\INI\\Default\\ControlBarScheme.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\ControlBarScheme.ini" ), INI_LOAD_OVERWRITE, NULL );

//	//Load the user modified control bar schemes
//	WIN32_FIND_DATA findData;
//	AsciiString userDataPath;
//	if(TheGlobalData)
//	{
//		userDataPath.format("%sINI\\ControlBarScheme.ini",TheGlobalData->getPath_UserData().str());
//		if	(FindFirstFile(userDataPath.str(), &findData) !=INVALID_HANDLE_VALUE)
//			ini.load(userDataPath,  INI_LOAD_OVERWRITE, NULL );
//	}
	if( m_schemeList.size() <= 0 )
	{
		DEBUG_ASSERTCRASH(FALSE,("There's no ControlBarScheme in the ControlBarSchemeList:m_schemeList that was just read from the INI file"));
		return;
	}

}

//
// only recommended to use if you know what you're doing, cause you could actually load in
// a control bar built for 16x12 into an 8x6 screen which would use a lot more memory then it should
//-----------------------------------------------------------------------------
void ControlBarSchemeManager::setControlBarScheme(AsciiString schemeName)
{
	ControlBarScheme *tempScheme = findControlBarScheme( schemeName );
	if(tempScheme)
	{
		// setup the multiplyer value
		m_multiplyer.x = TheDisplay->getWidth() / tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		DEBUG_ASSERTCRASH(FALSE,("There's no ControlBarScheme in the ControlBarSchemeList:m_schemeList"));
		m_currentScheme = NULL;
	}
	if(m_currentScheme)
		m_currentScheme->init();
}

//
// Update calls all the animation update calls for the
//-----------------------------------------------------------------------------
// ?update@ControlBarSchemeManager@@QAEXXZ present-unmatched
void ControlBarSchemeManager::update( void )
{
	if(m_currentScheme)	
		m_currentScheme->update();
}

//-----------------------------------------------------------------------------
// ?drawForeground@ControlBarSchemeManager@@QAEXUICoord2D@@@Z present-unmatched
void ControlBarSchemeManager::drawForeground( ICoord2D offset )
{
	if(m_currentScheme)	
		m_currentScheme->drawForeground( m_multiplyer, offset);
}
//-----------------------------------------------------------------------------
// ?drawBackground@ControlBarSchemeManager@@QAEXUICoord2D@@@Z present-unmatched
void ControlBarSchemeManager::drawBackground( ICoord2D offset )
{
	if(m_currentScheme)	
		m_currentScheme->drawBackground( m_multiplyer, offset );
}

//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarSchemeManagerSetControlBarSchemeByPlayerTemplate_4ADE40.cpp
// ?setControlBarSchemeByPlayerTemplate@ControlBarSchemeManager@@QAEXPBVPlayerTemplate@@_N@Z present-unmatched
void ControlBarSchemeManager::setControlBarSchemeByPlayerTemplate( const PlayerTemplate *pt, Bool useSmall)
{
	if(!pt)
		return;
	AsciiString side = pt->getSide();
	if(useSmall)
		side.concat("Small");
	if(m_currentScheme && (m_currentScheme->m_side.compare(side) == 0))
	{
		m_currentScheme->init();

		DEBUG_LOG(("setControlBarSchemeByPlayer already is using %s as its side\n", side.str()));
		return;
	}

	// if we don't have a side, set it to Observer shell
	if(side.isEmpty())
		side.set("Observer");
	DEBUG_LOG(("setControlBarSchemeByPlayer used %s as its side\n", side.str()));
	ControlBarScheme *tempScheme = NULL;

	ControlBarSchemeList::iterator it = m_schemeList.begin();
	
	// iterate through the list and return the scheme that we're looking for
	while (it != m_schemeList.end())
	{
		ControlBarScheme *CBScheme = *it;
		if( !CBScheme )
		{
			DEBUG_ASSERTCRASH(FALSE,("There's no ControlBarScheme in the ControlBarSchemeList:m_schemeList"));
			it++;
			continue;
		}
		// find the scheme that best matches our resolution
		if(CBScheme->m_side.compareNoCase( side ) == 0)
		{
		
			if((!tempScheme || tempScheme->m_ScreenCreationRes.x < CBScheme->m_ScreenCreationRes.x) )//&& TheDisplay->getWidth() >= CBScheme->m_ScreenCreationRes.x )
				tempScheme = CBScheme;
		}
		it ++;	
	}
	
	if(tempScheme)
	{
		// setup the multiplyer value
 		m_multiplyer.x = TheDisplay->getWidth() / (Real)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (Real)tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		// well, we couldn't find
		m_currentScheme = findControlBarScheme("Default");
		DEBUG_LOG(("There's no ControlBarScheme with a side of %s", side.str()));
//		m_currentScheme = NULL;
	}
	if(m_currentScheme)
		m_currentScheme->init();
}
//-----------------------------------------------------------------------------
// ?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z
// Body in ControlBarScheme_setControlBarSchemeByPlayer.asm (exact 590B retail).


//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
static void animSlideRight( ControlBarSchemeAnimation *anim )
{
	if(!anim->m_animImage || (anim->m_animDuration == 0))
		return;

	UnsignedInt currentFrame = anim->getCurrentFrame();
	ICoord2D startPos = anim->getStartPos();
	// if we're at the end, bring us to the beginning
	if(currentFrame == anim->m_animDuration)
	{
		anim->m_animImage->m_position.x = startPos.x;
		anim->m_animImage->m_position.y = startPos.y;
		anim->setCurrentFrame( 0 );
		return;
	}
	else if(currentFrame == 0)
	{
		// if we're at the beginning, save off the start position
		startPos.x = anim->m_animImage->m_position.x;
		startPos.y = anim->m_animImage->m_position.y;
		anim->setStartPos(startPos);
	}
	
	// now lets animate this bad boy!
	
	// now increment the frame
	currentFrame++;
	anim->setCurrentFrame(currentFrame);

	// now lets find what position we should be at.
	anim->m_animImage->m_position.x = startPos.x + (((anim->m_finalPos.x - startPos.x) * currentFrame) / anim->m_animDuration);


}

//-------------------------------------------------------------------------------------------------
// The ControlBarScheme block. The scheme manager hangs off TheControlBar at
// +0x30, and it is checked before use -- a scheme block in an INI loaded before
// the control bar exists is skipped rather than crashing.
//
// TheControlBar's layout is reached through a local view: this file compiles
// against Zero Hour's ControlBar, whose members are not BFME's, and only the one
// offset matters here.
void INI::parseControlBarSchemeDefinition( INI *ini )
{
	AsciiString name;
	name = ini->getNextToken();

	struct RetailControlBar
	{
		char m_unknown00[ 0x30 ];
		ControlBarSchemeManager *m_schemeManager;	// 0x30
	};
	ControlBarSchemeManager *manager =
		reinterpret_cast<RetailControlBar *>( TheControlBar )->m_schemeManager;

	if( manager )
	{
		// Split rather than nested: retail calls newControlBarScheme first and
		// pushes the field table after it, which a nested call reverses.
		ControlBarScheme *scheme = manager->newControlBarScheme( name );
		ini->initFromINI( scheme, ControlBarSchemeManager::m_controlBarSchemeFieldParseTable );
	}
}
