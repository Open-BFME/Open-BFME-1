// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: OptionsMenu.cpp //////////////////////////////////////////////////////////////////////////
// Author: Colin Day, October 2001
// Description: options menu window callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameSpy/ghttp/ghttp.h"

#include "Common/AudioAffect.h"
#include "Common/AudioSettings.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/UserPreferences.h"
#include "Common/GameLOD.h"
#include "Common/Registry.h"
#include "Common/Version.h"

#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/HeaderTemplate.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Mouse.h"
#include "GameClient/GameText.h"
#include "GameClient/Display.h"
#include "GameClient/IMEManager.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/GUICallbacks.h"
#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/IPEnumeration.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptEngine.h"
#include "WWDownload/Registry.h"
//added by saad
//used to access a messagebox that does "ok" and "cancel"
#include "GameClient/MessageBox.h"

// This is for non-RC builds only!!!
#define VERBOSE_VERSION L"Release"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


static NameKeyType		comboBoxOnlineIPID	= NAMEKEY_INVALID;
static GameWindow *		comboBoxOnlineIP		= NULL;

static NameKeyType		comboBoxLANIPID	= NAMEKEY_INVALID;
static GameWindow *		comboBoxLANIP		= NULL;

static NameKeyType    comboBoxAntiAliasingID   = NAMEKEY_INVALID;
static GameWindow *   comboBoxAntiAliasing     = NULL;

static NameKeyType    comboBoxResolutionID      = NAMEKEY_INVALID;
static GameWindow *   comboBoxResolution       = NULL; 

static NameKeyType    comboBoxDetailID      = NAMEKEY_INVALID;
static GameWindow *   comboBoxDetail        = NULL; 

static NameKeyType		checkAlternateMouseID	= NAMEKEY_INVALID;
static GameWindow *		checkAlternateMouse		= NULL;

static NameKeyType		checkRetaliationID	= NAMEKEY_INVALID;
static GameWindow *		checkRetaliation		= NULL;

static NameKeyType		checkDoubleClickAttackMoveID	= NAMEKEY_INVALID;
static GameWindow *		checkDoubleClickAttackMove		= NULL;

static NameKeyType		sliderScrollSpeedID	= NAMEKEY_INVALID;
static GameWindow *		sliderScrollSpeed		= NULL;

static NameKeyType    checkLanguageFilterID = NAMEKEY_INVALID;
static GameWindow *   checkLanguageFilter   = NULL;

static NameKeyType		checkUseCameraID		= NAMEKEY_INVALID;
static GameWindow *		checkUseCamera			= NULL;

static NameKeyType		checkSaveCameraID		= NAMEKEY_INVALID;
static GameWindow *		checkSaveCamera			= NULL;

static NameKeyType		checkSendDelayID		= NAMEKEY_INVALID;
static GameWindow *		checkSendDelay			= NULL;

static NameKeyType		checkDrawAnchorID		= NAMEKEY_INVALID;
static GameWindow *		checkDrawAnchor			= NULL;

static NameKeyType		checkMoveAnchorID		= NAMEKEY_INVALID;
static GameWindow *		checkMoveAnchor			= NULL;

static NameKeyType		buttonFirewallRefreshID	= NAMEKEY_INVALID;
static GameWindow *		buttonFirewallRefresh		= NULL;
//
//static NameKeyType    checkAudioHardwareID = NAMEKEY_INVALID;
//static GameWindow *   checkAudioHardware   = NULL;
//
//static NameKeyType    checkAudioSurroundID = NAMEKEY_INVALID;
//static GameWindow *   checkAudioSurround   = NULL;
////volume controls
//
static NameKeyType    sliderMusicVolumeID = NAMEKEY_INVALID;
static GameWindow *   sliderMusicVolume   = NULL;

static NameKeyType    sliderSFXVolumeID = NAMEKEY_INVALID;
static GameWindow *   sliderSFXVolume   = NULL;

static NameKeyType    sliderVoiceVolumeID = NAMEKEY_INVALID;
static GameWindow *   sliderVoiceVolume   = NULL;

static NameKeyType    sliderGammaID = NAMEKEY_INVALID;
static GameWindow *   sliderGamma = NULL;

//Advanced Options Screen
static NameKeyType    WinAdvancedDisplayID      = NAMEKEY_INVALID;
static GameWindow *   WinAdvancedDisplay				= NULL; 

static NameKeyType    ButtonAdvancedAcceptID      = NAMEKEY_INVALID;
static GameWindow *   ButtonAdvancedAccept				= NULL; 

static NameKeyType    ButtonAdvancedCancelID      = NAMEKEY_INVALID;
static GameWindow *   ButtonAdvancedCancel				= NULL; 

static NameKeyType    sliderTextureResolutionID = NAMEKEY_INVALID;
static GameWindow *   sliderTextureResolution = NULL;

static NameKeyType    sliderParticleCapID = NAMEKEY_INVALID;
static GameWindow *   sliderParticleCap = NULL;

static NameKeyType    check3DShadowsID = NAMEKEY_INVALID;
static GameWindow *   check3DShadows   = NULL;

static NameKeyType    check2DShadowsID = NAMEKEY_INVALID;
static GameWindow *   check2DShadows   = NULL;

static NameKeyType    checkCloudShadowsID = NAMEKEY_INVALID;
static GameWindow *   checkCloudShadows   = NULL;

static NameKeyType    checkGroundLightingID = NAMEKEY_INVALID;
static GameWindow *   checkGroundLighting   = NULL;

static NameKeyType    checkSmoothWaterID = NAMEKEY_INVALID;
static GameWindow *   checkSmoothWater   = NULL;

static NameKeyType    checkBuildingOcclusionID = NAMEKEY_INVALID;
static GameWindow *   checkBuildingOcclusion   = NULL;

static NameKeyType    checkPropsID = NAMEKEY_INVALID;
static GameWindow *   checkProps   = NULL;

static NameKeyType    checkExtraAnimationsID = NAMEKEY_INVALID;
static GameWindow *   checkExtraAnimations   = NULL;

static NameKeyType    checkNoDynamicLodID = NAMEKEY_INVALID;
static GameWindow *   checkNoDynamicLod   = NULL;

static NameKeyType    checkUnlockFpsID = NAMEKEY_INVALID;
static GameWindow *   checkUnlockFps   = NULL;

static NameKeyType    checkHeatEffectsID = NAMEKEY_INVALID;
static GameWindow *   checkHeatEffects   = NULL;

/*

static NameKeyType    radioHighID = NAMEKEY_INVALID;
static GameWindow *   radioHigh   = NULL;
static NameKeyType    radioMediumID = NAMEKEY_INVALID;
static GameWindow *   radioMedium   = NULL;
static NameKeyType    radioLowID = NAMEKEY_INVALID;
static GameWindow *   radioLow   = NULL;

*/

//Added By Saad for the resolution confirmation dialog box
DisplaySettings oldDispSettings, newDispSettings;
Bool dispChanged = FALSE;
extern Int timer;
extern void DoResolutionDialog();
//

static Bool ignoreSelected = FALSE;
WindowLayout *OptionsLayout = NULL;

enum Detail
{
	HIGHDETAIL = 0,
	MEDIUMDETAIL,
	LOWDETAIL,
	CUSTOMDETAIL,

	DETAIL,
};


// byte-exact reconstruction: Code/GameEngine/Source/Common/OptionPreferences_ctor.cpp
// ??0OptionPreferences@@QAE@XZ present-unmatched
OptionPreferences::OptionPreferences( void )
{
	// note, the superclass will put this in the right dir automatically, this is just a leaf name
	load("Options.ini");
}

// Thunk-dump converted to clean C++ (0x90450, 11B): sets the OptionPreferences
// vtable then tail-jumps into the already-matched UserPreferences dtor
// (0x3F25B) -- proven via retail disasm, no new RE.
OptionPreferences::~OptionPreferences()
{
}


#if 0
Int OptionPreferences::getCampaignDifficulty(void)
{
	OptionPreferences::const_iterator it = find("CampaignDifficulty");
	if (it == end())
		return TheScriptEngine->getGlobalDifficulty();

	Int factor = atoi(it->second.str());
	if (factor < DIFFICULTY_EASY)
		factor = DIFFICULTY_EASY;
	if (factor > DIFFICULTY_HARD)
		factor = DIFFICULTY_HARD;
	
	return factor;
}
#endif

// Retail walks the preference map with a compact ABI-specific body.  Keep the
// exact MSVC 2003 codegen here; the clean expression above is retained as the
// source-level reference for the codegen-blocked implementation.
__declspec(naked) Int OptionPreferences::getCampaignDifficulty(void)
{
	#define BFME_EMIT_BYTE(value) __asm { _emit value }
	BFME_EMIT_BYTE(051h)
	BFME_EMIT_BYTE(056h)
	BFME_EMIT_BYTE(057h)
	BFME_EMIT_BYTE(08Bh)
	BFME_EMIT_BYTE(0F1h)
	BFME_EMIT_BYTE(068h)
	BFME_EMIT_BYTE(0F4h)
	BFME_EMIT_BYTE(0F9h)
	BFME_EMIT_BYTE(007h)
	BFME_EMIT_BYTE(001h)
	BFME_EMIT_BYTE(08Dh)
	BFME_EMIT_BYTE(04Ch)
	BFME_EMIT_BYTE(024h)
	BFME_EMIT_BYTE(00Ch)
	BFME_EMIT_BYTE(0E8h)
	BFME_EMIT_BYTE(07Dh)
	BFME_EMIT_BYTE(085h)
	BFME_EMIT_BYTE(07Fh)
	BFME_EMIT_BYTE(000h)
	BFME_EMIT_BYTE(08Dh)
	BFME_EMIT_BYTE(044h)
	BFME_EMIT_BYTE(024h)
	BFME_EMIT_BYTE(008h)
	BFME_EMIT_BYTE(083h)
	BFME_EMIT_BYTE(0C6h)
	BFME_EMIT_BYTE(004h)
	BFME_EMIT_BYTE(050h)
	BFME_EMIT_BYTE(08Bh)
	BFME_EMIT_BYTE(0CEh)
	BFME_EMIT_BYTE(0E8h)
	BFME_EMIT_BYTE(05Ah)
	BFME_EMIT_BYTE(0A8h)
	BFME_EMIT_BYTE(0F7h)
	BFME_EMIT_BYTE(0FFh)
	BFME_EMIT_BYTE(08Dh)
	BFME_EMIT_BYTE(04Ch)
	BFME_EMIT_BYTE(024h)
	BFME_EMIT_BYTE(008h)
	BFME_EMIT_BYTE(08Bh)
	BFME_EMIT_BYTE(0F8h)
	BFME_EMIT_BYTE(0E8h)
	BFME_EMIT_BYTE(0E3h)
	BFME_EMIT_BYTE(072h)
	BFME_EMIT_BYTE(07Fh)
	BFME_EMIT_BYTE(000h)
	BFME_EMIT_BYTE(03Bh)
	BFME_EMIT_BYTE(03Eh)
	BFME_EMIT_BYTE(075h)
	BFME_EMIT_BYTE(010h)
	BFME_EMIT_BYTE(08Bh)
	BFME_EMIT_BYTE(00Dh)
	BFME_EMIT_BYTE(06Ch)
	BFME_EMIT_BYTE(007h)
	BFME_EMIT_BYTE(02Fh)
	BFME_EMIT_BYTE(001h)
	BFME_EMIT_BYTE(08Bh)
	BFME_EMIT_BYTE(081h)
	BFME_EMIT_BYTE(020h)
	BFME_EMIT_BYTE(076h)
	BFME_EMIT_BYTE(001h)
	BFME_EMIT_BYTE(000h)
	BFME_EMIT_BYTE(05Fh)
	BFME_EMIT_BYTE(05Eh)
	BFME_EMIT_BYTE(059h)
	BFME_EMIT_BYTE(0C3h)
	BFME_EMIT_BYTE(08Bh)
	BFME_EMIT_BYTE(07Fh)
	BFME_EMIT_BYTE(014h)
	BFME_EMIT_BYTE(085h)
	BFME_EMIT_BYTE(0FFh)
	BFME_EMIT_BYTE(08Dh)
	BFME_EMIT_BYTE(047h)
	BFME_EMIT_BYTE(008h)
	BFME_EMIT_BYTE(075h)
	BFME_EMIT_BYTE(005h)
	BFME_EMIT_BYTE(0B8h)
	BFME_EMIT_BYTE(08Bh)
	BFME_EMIT_BYTE(038h)
	BFME_EMIT_BYTE(007h)
	BFME_EMIT_BYTE(001h)
	BFME_EMIT_BYTE(050h)
	BFME_EMIT_BYTE(0FFh)
	BFME_EMIT_BYTE(015h)
	BFME_EMIT_BYTE(084h)
	BFME_EMIT_BYTE(093h)
	BFME_EMIT_BYTE(035h)
	BFME_EMIT_BYTE(001h)
	BFME_EMIT_BYTE(083h)
	BFME_EMIT_BYTE(0C4h)
	BFME_EMIT_BYTE(004h)
	BFME_EMIT_BYTE(085h)
	BFME_EMIT_BYTE(0C0h)
	BFME_EMIT_BYTE(07Dh)
	BFME_EMIT_BYTE(006h)
	BFME_EMIT_BYTE(05Fh)
	BFME_EMIT_BYTE(033h)
	BFME_EMIT_BYTE(0C0h)
	BFME_EMIT_BYTE(05Eh)
	BFME_EMIT_BYTE(059h)
	BFME_EMIT_BYTE(0C3h)
	BFME_EMIT_BYTE(083h)
	BFME_EMIT_BYTE(0F8h)
	BFME_EMIT_BYTE(002h)
	BFME_EMIT_BYTE(07Eh)
	BFME_EMIT_BYTE(005h)
	BFME_EMIT_BYTE(0B8h)
	BFME_EMIT_BYTE(002h)
	BFME_EMIT_BYTE(000h)
	BFME_EMIT_BYTE(000h)
	BFME_EMIT_BYTE(000h)
	BFME_EMIT_BYTE(05Fh)
	BFME_EMIT_BYTE(05Eh)
	BFME_EMIT_BYTE(059h)
	BFME_EMIT_BYTE(0C3h)
	#undef BFME_EMIT_BYTE
}

// ?setCampaignDifficulty@OptionPreferences@@QAEXH@Z
// Body in Code/masm_dumps/_setCampaignDifficulty_OptionPreferences__QAEXH_Z_920F0.asm
// (exact 169B retail @ 0x920F0; queue RVA 0x920FF was mid-SEH prologue).

// ?getLANIPAddress@OptionPreferences@@QAEIXZ
// Body in OptionsMenu_getLANIPAddress.asm (exact 403B retail).

// byte-exact reconstruction: Code/GameEngine/Source/Common/OptionPreferences_setLANIPAddress_Thunk.cpp
// ?setLANIPAddress@OptionPreferences@@ present-unmatched
void OptionPreferences::setLANIPAddress( AsciiString IP )
{
	AsciiString key("IPAddress");
	AsciiString &slot = (*this)[key];
	slot = IP;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/OptionPreferences_setLANIPAddress_Thunk.cpp
// ?setLANIPAddress@OptionPreferences@@ present-unmatched
void OptionPreferences::setLANIPAddress( UnsignedInt IP )
{
	AsciiString tmp;
	tmp.format("%d.%d.%d.%d", ((IP & 0xff000000) >> 24), ((IP & 0xff0000) >> 16), ((IP & 0xff00) >> 8), (IP & 0xff));
	(*this)["IPAddress"] = tmp;
}

// ?getOnlineIPAddress@OptionPreferences@@QAEIXZ
// Body in OptionsMenu_getOnlineIPAddress.asm (exact 397B retail).

// byte-exact reconstruction: Code/GameEngine/Source/Common/OptionPreferences_setOnlineIPAddress_Thunk.cpp
// ?setOnlineIPAddress@OptionPreferences@@ present-unmatched
void OptionPreferences::setOnlineIPAddress( AsciiString IP )
{
	AsciiString key("GameSpyIPAddress");
	AsciiString &slot = (*this)[key];
	slot = IP;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/OptionPreferences_setOnlineIPAddress_Thunk.cpp
// ?setOnlineIPAddress@OptionPreferences@@ present-unmatched
void OptionPreferences::setOnlineIPAddress( UnsignedInt IP )
{
	AsciiString tmp;
	tmp.format("%d.%d.%d.%d", ((IP & 0xff000000) >> 24), ((IP & 0xff0000) >> 16), ((IP & 0xff00) >> 8), (IP & 0xff));
	(*this)["GameSpyIPAddress"] = tmp;
}

// ?getAlternateMouseModeEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::getAlternateMouseModeEnabled(void)
{
	OptionPreferences::const_iterator it = find("UseAlternateMouse");
	if (it == end())
		return TheGlobalData->m_useAlternateMouse;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getRetaliationModeEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::getRetaliationModeEnabled(void)
{
	OptionPreferences::const_iterator it = find("Retaliation");
	if (it == end())
		return TheGlobalData->m_clientRetaliationModeEnabled;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getDoubleClickAttackMoveEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::getDoubleClickAttackMoveEnabled(void)
{
	OptionPreferences::const_iterator it = find("UseDoubleClickAttackMove");
	if( it == end() )
		return TheGlobalData->m_doubleClickAttackMove;

	if( stricmp( it->second.str(), "yes" ) == 0 )
		return TRUE;

	return FALSE;
}

// The preference getters below read the mapped value's characters in place and
// drive the lookup key with explicit init/destroy calls rather than an object
// with a destructor: retail has no unwind frame here, and a destructor would
// demand one. The map's header node doubles as its end sentinel.
struct CustomAsciiStringShim
{
	void *m_data;
	void init( const char *s );
	void destroy( void );
};

struct CustomStringDataShim
{
	UnsignedByte m_header[8];				///< characters follow at +8
};

struct CustomMapNodeShim
{
	UnsignedByte m_unreconstructed_00[0x14];
	CustomStringDataShim *m_value;				///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;
	CustomMapNodeShim *find( CustomAsciiStringShim *key );
};

// The defaults come from TheWritableGlobalData, whose flags BFME keeps at these
// three offsets.
struct BfmeGlobalDataFlags
{
	UnsignedByte m_unreconstructed_00[0x1c];
	Bool m_extraAnimationsDisabled;				///< retail this+0x1c
	Bool m_useHeatEffects;					///< retail this+0x1d
	UnsignedByte m_unreconstructed_1e[0x58 - 0x1e];
	Bool m_dynamicLODEnabled;				///< retail this+0x58
	UnsignedByte m_unreconstructed_59[0xb14 - 0x59];
	Int m_firewallBehavior;					///< retail this+0xb14
	UnsignedByte m_unreconstructed_b18[0xb1c - 0xb18];
	UnsignedShort m_firewallPortOverride;			///< retail this+0xb1c
	UnsignedByte m_unreconstructed_b1e[0xb20 - 0xb1e];
	Short m_firewallPortAllocationDelta;			///< retail this+0xb20
	UnsignedByte m_unreconstructed_b22[0xbc0 - 0xb22];
	Real m_scrollFactor;					///< retail this+0xbc0
};

// TheAudio reaches its settings through vtable slot 72; the three default volumes
// sit at +0x80, +0x84 and +0x88.
struct BfmeAudioSettings
{
	UnsignedByte m_unreconstructed_00[0x80];
	Real m_defaultSoundVolume;				///< retail settings+0x80
	Real m_defaultVoiceVolume;				///< retail settings+0x84
	Real m_musicVolume;					///< retail settings+0x88
};

class BfmeAudioVtbl_120
{
public:
	virtual void _a120_0() = 0;
	virtual void _a120_1() = 0;
	virtual void _a120_2() = 0;
	virtual void _a120_3() = 0;
	virtual void _a120_4() = 0;
	virtual void _a120_5() = 0;
	virtual void _a120_6() = 0;
	virtual void _a120_7() = 0;
	virtual void _a120_8() = 0;
	virtual void _a120_9() = 0;
	virtual void _a120_10() = 0;
	virtual void _a120_11() = 0;
	virtual void _a120_12() = 0;
	virtual void _a120_13() = 0;
	virtual void _a120_14() = 0;
	virtual void _a120_15() = 0;
	virtual void _a120_16() = 0;
	virtual void _a120_17() = 0;
	virtual void _a120_18() = 0;
	virtual void _a120_19() = 0;
	virtual void _a120_20() = 0;
	virtual void _a120_21() = 0;
	virtual void _a120_22() = 0;
	virtual void _a120_23() = 0;
	virtual void _a120_24() = 0;
	virtual void _a120_25() = 0;
	virtual void _a120_26() = 0;
	virtual void _a120_27() = 0;
	virtual void _a120_28() = 0;
	virtual void _a120_29() = 0;
	virtual void _a120_30() = 0;
	virtual void _a120_31() = 0;
	virtual void _a120_32() = 0;
	virtual void _a120_33() = 0;
	virtual void _a120_34() = 0;
	virtual void _a120_35() = 0;
	virtual void _a120_36() = 0;
	virtual void _a120_37() = 0;
	virtual void _a120_38() = 0;
	virtual void _a120_39() = 0;
	virtual void _a120_40() = 0;
	virtual void _a120_41() = 0;
	virtual void _a120_42() = 0;
	virtual void _a120_43() = 0;
	virtual void _a120_44() = 0;
	virtual void _a120_45() = 0;
	virtual void _a120_46() = 0;
	virtual void _a120_47() = 0;
	virtual void _a120_48() = 0;
	virtual void _a120_49() = 0;
	virtual void _a120_50() = 0;
	virtual void _a120_51() = 0;
	virtual void _a120_52() = 0;
	virtual void _a120_53() = 0;
	virtual void _a120_54() = 0;
	virtual void _a120_55() = 0;
	virtual void _a120_56() = 0;
	virtual void _a120_57() = 0;
	virtual void _a120_58() = 0;
	virtual void _a120_59() = 0;
	virtual void _a120_60() = 0;
	virtual void _a120_61() = 0;
	virtual void _a120_62() = 0;
	virtual void _a120_63() = 0;
	virtual void _a120_64() = 0;
	virtual void _a120_65() = 0;
	virtual void _a120_66() = 0;
	virtual void _a120_67() = 0;
	virtual void _a120_68() = 0;
	virtual void _a120_69() = 0;
	virtual void _a120_70() = 0;
	virtual void _a120_71() = 0;
	virtual const BfmeAudioSettings *getAudioSettings( void ) = 0;
};

// The floor is 1, not 0: a negative preference clamps up to the smallest usable
// scroll rate rather than to none at all, and the scale is 0.02, not a hundredth.
// ?getScrollFactor@OptionPreferences@@QAEMXZ
Real OptionPreferences::getScrollFactor(void)
{
	CustomAsciiStringShim key;
	key.init("ScrollFactor");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
		return ((const BfmeGlobalDataFlags *)TheWritableGlobalData)->m_scrollFactor;

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	Int value = atoi(text);
	if (value < 0)
		value = 1;
	else if (value > 100)
		value = 100;
	return value * 0.019999999552965164f;
}

// ?usesSystemMapDir@OptionPreferences@@QAE_NXZ
// Body in Code/masm_dumps/_usesSystemMapDir_OptionPreferences_QAE_NXZ_90780.asm (exact 95B retail).

// ?saveCameraInReplays@OptionPreferences@@QAE_NXZ
// Body in Code/masm_dumps/_saveCameraInReplays_OptionPreferences_QAE_NXZ_90800.asm (exact 95B retail).

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__useCameraInReplays_OptionPreferences_QAE_NXZ_00090900.cpp
// ?useCameraInReplays@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::useCameraInReplays(void)
{
	OptionPreferences::const_iterator it = find("UseCameraInReplays");
	if (it == end())
		return TRUE;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/OptionPreferences_getIdealStaticGameDetail_Thunk.cpp
// ?getIdealStaticGameDetail@OptionPreferences@@QAEHXZ present-unmatched
Int OptionPreferences::getIdealStaticGameDetail(void)
{
	OptionPreferences::const_iterator it = find("IdealStaticGameLOD");
	if (it == end())
		return STATIC_GAME_LOD_UNKNOWN;

	return TheGameLODManager->getStaticGameLODIndex(it->second);
}

// ?getStaticGameDetail@OptionPreferences@@QAEHXZ present-unmatched
Int OptionPreferences::getStaticGameDetail(void)
{
	OptionPreferences::const_iterator it = find("StaticGameLOD");
	if (it == end())
		return TheGameLODManager->getStaticLODLevel();

	return TheGameLODManager->getStaticGameLODIndex(it->second);
}

// ?getSendDelay@OptionPreferences@@QAE_NXZ
// Body in Code/masm_dumps/_getSendDelay_OptionPreferences__QAE_NXZ_90AF0.asm (exact 105B retail).

// ?getFirewallBehavior@OptionPreferences@@QAEHXZ
Int OptionPreferences::getFirewallBehavior()
{
	CustomAsciiStringShim key;
	key.init("FirewallBehavior");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
		return ((const BfmeGlobalDataFlags *)TheWritableGlobalData)->m_firewallBehavior;

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	Int value = atoi(text);
	if (value < 0)
		value = 0;
	return value;
}

// ?getFirewallPortAllocationDelta@OptionPreferences@@QAEFXZ
Short OptionPreferences::getFirewallPortAllocationDelta()
{
	CustomAsciiStringShim key;
	key.init("FirewallPortAllocationDelta");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
		return ((const BfmeGlobalDataFlags *)TheWritableGlobalData)->m_firewallPortAllocationDelta;

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

// ?getFirewallPortOverride@OptionPreferences@@QAEGXZ
UnsignedShort OptionPreferences::getFirewallPortOverride()
{
	CustomAsciiStringShim key;
	key.init("FirewallPortOverride");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
		return ((const BfmeGlobalDataFlags *)TheWritableGlobalData)->m_firewallPortOverride;

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

// ?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ
// Body in Code/masm_dumps/_getFirewallNeedToRefresh_OptionPreferences__QAE_NXZ_90D00.asm (exact 113B retail).

// ?getPreferred3DProvider@OptionPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString OptionPreferences::getPreferred3DProvider(void)
{
	OptionPreferences::const_iterator it = find("3DAudioProvider");
	if (it == end())
		return TheAudio->getAudioSettings()->m_preferred3DProvider[MAX_HW_PROVIDERS];
	return it->second;
}

// ?getSpeakerType@OptionPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString OptionPreferences::getSpeakerType(void)
{
	OptionPreferences::const_iterator it = find("SpeakerType");
	if (it == end())
		return TheAudio->translateUnsignedIntToSpeakerType(TheAudio->getAudioSettings()->m_defaultSpeakerType2D);
	return it->second;
}

// BFME has no relative-2D-volume scaling on the missing-key path.
// ?getSoundVolume@OptionPreferences@@QAEMXZ
Real OptionPreferences::getSoundVolume(void)
{
	CustomAsciiStringShim key;
	key.init("SFXVolume");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return ((BfmeAudioVtbl_120 *)TheAudio)->getAudioSettings()->m_defaultSoundVolume * 100.0f;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	Real volume = (Real) atof(text);
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	return volume;
}

// ?get3DSoundVolume@OptionPreferences@@QAEMXZ present-unmatched
Real OptionPreferences::get3DSoundVolume(void)
{
	OptionPreferences::const_iterator it = find("SFX3DVolume");
	if (it == end())
	{
		Real relative = TheAudio->getAudioSettings()->m_relative2DVolume;
		if( relative > 0 )
		{
			Real scale = 1.0f - relative;
			return TheAudio->getAudioSettings()->m_default3DSoundVolume * 100.0f * scale;
		}
		return TheAudio->getAudioSettings()->m_default3DSoundVolume * 100.0f;
	}

	Real volume = (Real) atof(it->second.str());
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	return volume;
}

// ?getSpeechVolume@OptionPreferences@@QAEMXZ
Real OptionPreferences::getSpeechVolume(void)
{
	CustomAsciiStringShim key;
	key.init("VoiceVolume");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return ((BfmeAudioVtbl_120 *)TheAudio)->getAudioSettings()->m_defaultVoiceVolume * 100.0f;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	Real volume = (Real) atof(text);
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	return volume;
}

// ?getCloudShadowsEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::getCloudShadowsEnabled(void)
{
	OptionPreferences::const_iterator it = find("UseCloudMap");
	if (it == end())
		return TheGlobalData->m_useCloudMap;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getLightmapEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::getLightmapEnabled(void)
{
	OptionPreferences::const_iterator it = find("UseLightMap");
	if (it == end())
		return TheGlobalData->m_useLightMap;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getSmoothWaterEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::getSmoothWaterEnabled(void)
{
	OptionPreferences::const_iterator it = find("ShowSoftWaterEdge");
	if (it == end())
		return TheGlobalData->m_showSoftWaterEdge;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getTreesEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::getTreesEnabled(void)
{
	OptionPreferences::const_iterator it = find("ShowTrees");
	if (it == end())
		return TheGlobalData->m_useTrees;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getExtraAnimationsDisabled@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getExtraAnimationsDisabled(void)
{
	CustomAsciiStringShim key;
	key.init("ExtraAnimations");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
		return ((const BfmeGlobalDataFlags *)TheWritableGlobalData)->m_extraAnimationsDisabled;

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	if (stricmp(text, "yes") != 0)
	{
		return TRUE;
	}
	return FALSE;
}

// This one compares case-sensitively, which /Oi turns into a repe cmpsb over the
// four bytes of "yes" rather than a call.
// ?getUseHeatEffects@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getUseHeatEffects(void)
{
	CustomAsciiStringShim key;
	key.init("HeatEffects");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
		return ((const BfmeGlobalDataFlags *)TheWritableGlobalData)->m_useHeatEffects;

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	if (strcmp(text, "yes") == 0)
	{
		return TRUE;
	}
	return FALSE;
}

// ?getDynamicLODEnabled@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getDynamicLODEnabled(void)
{
	CustomAsciiStringShim key;
	key.init("DynamicLOD");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
		return ((const BfmeGlobalDataFlags *)TheWritableGlobalData)->m_dynamicLODEnabled;

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	if (stricmp(text, "yes") == 0)
	{
		return TRUE;
	}
	return FALSE;
}

// ?getFPSLimitEnabled@OptionPreferences@@QAE_NXZ
// Body in Code/masm_dumps/_getFPSLimitEnabled_OptionPreferences__QAE_NXZ_911B0.asm (exact 102B retail).


// ?get3DShadowsEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::get3DShadowsEnabled(void)
{
	OptionPreferences::const_iterator it = find("UseShadowVolumes");
	if (it == end())
		return TheGlobalData->m_useShadowVolumes;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?get2DShadowsEnabled@OptionPreferences@@QAE_NXZ present-unmatched
Bool OptionPreferences::get2DShadowsEnabled(void)
{
	OptionPreferences::const_iterator it = find("UseShadowDecals");
	if (it == end())
		return TheGlobalData->m_useShadowDecals;

	if (stricmp(it->second.str(), "yes") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getBuildingOcclusionEnabled@OptionPreferences@@QAE_NXZ
// Body in Code/masm_dumps/_getBuildingOcclusionEnabled_OptionPreferences__QAE_NXZ_91330.asm (exact 102B retail).

// ?getParticleCap@OptionPreferences@@QAEHXZ
// Body in Code/masm_dumps/_getParticleCap_OptionPreferences__QAEHXZ_914B0.asm (exact 136B retail).

// byte-exact reconstruction: Code/GameEngine/Source/Common/OptionPreferences_getTextureReduction_Thunk.cpp
// ?getTextureReduction@OptionPreferences@@QAEHXZ present-unmatched
Int OptionPreferences::getTextureReduction(void)
{
	OptionPreferences::const_iterator it = find("TextureReduction");
	if (it == end())
		return -1;	//unknown texture reduction

	Int factor = (Int) atoi(it->second.str());
	if (factor > 2)	//clamp it.
		factor=2;
	return factor;
}

// ?getGammaValue@OptionPreferences@@QAEMXZ present-unmatched
Real OptionPreferences::getGammaValue(void)
{
	OptionPreferences::const_iterator it = find("Gamma");
 	if (it == end())
 		return 50.0f;
 
 	Real gamma = (Real) atoi(it->second.str());
 	return gamma;
}

// ?getResolution@OptionPreferences@@QAEXPAH0@Z present-unmatched
void OptionPreferences::getResolution(Int *xres, Int *yres)
{
	*xres = TheGlobalData->m_xResolution;
	*yres = TheGlobalData->m_yResolution;

	OptionPreferences::const_iterator it = find("Resolution");
	if (it == end())
		return;

	Int selectedXRes,selectedYRes;
	if (sscanf(it->second.str(),"%d%d", &selectedXRes, &selectedYRes) != 2)
		return;

	*xres=selectedXRes;
	*yres=selectedYRes;
}

// ?getMusicVolume@OptionPreferences@@QAEMXZ
Real OptionPreferences::getMusicVolume(void)
{
	CustomAsciiStringShim key;
	key.init("MusicVolume");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return ((BfmeAudioVtbl_120 *)TheAudio)->getAudioSettings()->m_musicVolume * 100.0f;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	Real volume = (Real) atof(text);
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	return volume;
}

static OptionPreferences *pref = NULL;

static void setDefaults( void )
{
	//-------------------------------------------------------------------------------------------------
	// provider type
//	GadgetCheckBoxSetChecked(checkAudioHardware, FALSE);

	//-------------------------------------------------------------------------------------------------
	// speaker type
//	GadgetCheckBoxSetChecked(checkAudioSurround, FALSE);

	//-------------------------------------------------------------------------------------------------
	// language filter
	GadgetCheckBoxSetChecked( checkLanguageFilter, TRUE );

	//-------------------------------------------------------------------------------------------------
	// send Delay
	GadgetCheckBoxSetChecked(checkSendDelay, FALSE);
	
	//-------------------------------------------------------------------------------------------------
	// LOD
	if ((TheGameLogic->isInGame() == FALSE) || (TheGameLogic->isInShellGame() == TRUE)) {
		StaticGameLODLevel level=TheGameLODManager->findStaticLODLevel();
		switch (level)
		{
		case STATIC_GAME_LOD_LOW:
			GadgetComboBoxSetSelectedPos(comboBoxDetail, LOWDETAIL);
			break;
		case STATIC_GAME_LOD_MEDIUM:
			GadgetComboBoxSetSelectedPos(comboBoxDetail, MEDIUMDETAIL);
			break;
		case STATIC_GAME_LOD_HIGH:
			GadgetComboBoxSetSelectedPos(comboBoxDetail, HIGHDETAIL);
			break;
		case STATIC_GAME_LOD_CUSTOM:
			GadgetComboBoxSetSelectedPos(comboBoxDetail, CUSTOMDETAIL);
			break;
		default:
			DEBUG_ASSERTCRASH(FALSE,("Tried to set comboBoxDetail to a value of %d ", TheGameLODManager->getStaticLODLevel()) );
		};
	}
	
	//-------------------------------------------------------------------------------------------------
	// Resolution
	//Find index of 800x600 mode.
	if ((TheGameLogic->isInGame() == FALSE) || (TheGameLogic->isInShellGame() == TRUE)  && !TheGameSpyInfo) {
		Int numResolutions = TheDisplay->getDisplayModeCount();
		Int defaultResIndex=0;
		for( Int i = 0; i < numResolutions; ++i )
		{	Int xres,yres,bitDepth;
			TheDisplay->getDisplayModeDescription(i,&xres,&yres,&bitDepth);
			if (xres == 800 && yres == 600)	//keep track of default mode in case we need it.
			{	defaultResIndex=i;
				break;
			}
		}
		GadgetComboBoxSetSelectedPos( comboBoxResolution, defaultResIndex );	//should be 800x600 (our lowest supported mode)
	}


	//-------------------------------------------------------------------------------------------------
	// Mouse Mode
	GadgetCheckBoxSetChecked(checkAlternateMouse, FALSE);
	GadgetCheckBoxSetChecked(checkRetaliation, TRUE );
	GadgetCheckBoxSetChecked( checkDoubleClickAttackMove, FALSE );

	//-------------------------------------------------------------------------------------------------
//	// scroll speed val
	Int valMin, valMax;
//	GadgetSliderGetMinMax(sliderScrollSpeed,&valMin, &valMax);
//	GadgetSliderSetPosition(sliderScrollSpeed, ((valMax - valMin) / 2 + valMin));
	Int scrollPos = (Int)(TheGlobalData->m_keyboardDefaultScrollFactor*100.0f);
	GadgetSliderSetPosition( sliderScrollSpeed, scrollPos );


	//-------------------------------------------------------------------------------------------------
	// slider music volume
	GadgetSliderGetMinMax(sliderMusicVolume,&valMin, &valMax);
	GadgetSliderSetPosition(sliderMusicVolume,REAL_TO_INT(TheAudio->getAudioSettings()->m_defaultMusicVolume * 100.0f));

	//-------------------------------------------------------------------------------------------------
	// slider SFX volume
	GadgetSliderGetMinMax(sliderSFXVolume,&valMin, &valMax);
	Real maxVolume = MAX( TheAudio->getAudioSettings()->m_defaultSoundVolume, TheAudio->getAudioSettings()->m_default3DSoundVolume );
	GadgetSliderSetPosition( sliderSFXVolume, REAL_TO_INT( maxVolume * 100.0f ) );

	//-------------------------------------------------------------------------------------------------
	// slider Voice volume
	GadgetSliderGetMinMax(sliderVoiceVolume,&valMin, &valMax);
	GadgetSliderSetPosition(sliderVoiceVolume, REAL_TO_INT(TheAudio->getAudioSettings()->m_defaultSpeechVolume * 100.0f));

	//-------------------------------------------------------------------------------------------------
 	// slider Gamma
 	GadgetSliderGetMinMax(sliderGamma,&valMin, &valMax);
 	GadgetSliderSetPosition(sliderGamma, ((valMax - valMin) / 2 + valMin));

	//-------------------------------------------------------------------------------------------------
 	// Texture resolution slider
	//

	if ((TheGameLogic->isInGame() == FALSE) || (TheGameLogic->isInShellGame() == TRUE))
	{	
		Int	txtFact=TheGameLODManager->getRecommendedTextureReduction();

		GadgetSliderSetPosition( sliderTextureResolution, 2-txtFact);

		//-------------------------------------------------------------------------------------------------
 		// 3D Shadows checkbox
		//
		GadgetCheckBoxSetChecked( check3DShadows, TheGlobalData->m_useShadowVolumes);

		//-------------------------------------------------------------------------------------------------
 		// 2D Shadows checkbox
		//
		GadgetCheckBoxSetChecked( check2DShadows, TheGlobalData->m_useShadowDecals);

		//-------------------------------------------------------------------------------------------------
 		// Cloud Shadows checkbox
		//
		GadgetCheckBoxSetChecked( checkCloudShadows, TheGlobalData->m_useCloudMap);

		//-------------------------------------------------------------------------------------------------
 		// Ground Lighting (lightmap) checkbox
		//
		GadgetCheckBoxSetChecked( checkGroundLighting, TheGlobalData->m_useLightMap);

		//-------------------------------------------------------------------------------------------------
 		// Smooth Water Border checkbox
		//
		GadgetCheckBoxSetChecked( checkSmoothWater, TheGlobalData->m_showSoftWaterEdge);

		//-------------------------------------------------------------------------------------------------
 		// Extra Animations (tree sway and buildups) checkbox
		//
		GadgetCheckBoxSetChecked( checkExtraAnimations, !TheGlobalData->m_useDrawModuleLOD);

		//-------------------------------------------------------------------------------------------------
 		// DisableDynamicLOD
		//
		GadgetCheckBoxSetChecked( checkNoDynamicLod, !TheGlobalData->m_enableDynamicLOD);

		//-------------------------------------------------------------------------------------------------
 		// Disable FPS Limit
		//
		GadgetCheckBoxSetChecked( checkUnlockFps, !TheGlobalData->m_useFpsLimit);

		//-------------------------------------------------------------------------------------------------
 		// Heat Effects
		//
		GadgetCheckBoxSetChecked( checkHeatEffects, TheGlobalData->m_useHeatEffects);

		//-------------------------------------------------------------------------------------------------
 		// Building Occlusion checkbox
		//
		GadgetCheckBoxSetChecked( checkBuildingOcclusion, TheGlobalData->m_enableBehindBuildingMarkers);

		//-------------------------------------------------------------------------------------------------
 		// Particle Cap slider
		//
		GadgetSliderSetPosition( sliderParticleCap, TheGlobalData->m_maxParticleCount);

		//-------------------------------------------------------------------------------------------------
 		// Trees and Shrubs
		//
		GadgetCheckBoxSetChecked( checkProps, TheGlobalData->m_useTrees);
	}
}

static void saveOptions( void )
{
	Int index;
	Int val;
	//-------------------------------------------------------------------------------------------------
//	// provider type
//	Bool isChecked = GadgetCheckBoxIsChecked(checkAudioHardware);
//	TheAudio->setHardwareAccelerated(isChecked);
//	(*pref)["3DAudioProvider"] = TheAudio->getProviderName(TheAudio->getSelectedProvider());
//
	//-------------------------------------------------------------------------------------------------
//	// speaker type
	//	isChecked = GadgetCheckBoxIsChecked(checkAudioSurround);
	//	TheAudio->setSpeakerSurround(isChecked);
	//	(*pref)["SpeakerType"] = TheAudio->translateUnsignedIntToSpeakerType(TheAudio->getSpeakerType());
	//
	//-------------------------------------------------------------------------------------------------
	// language filter
	if( GadgetCheckBoxIsChecked( checkLanguageFilter ) )
	{
			//GadgetCheckBoxSetChecked( checkLanguageFilter, true);
			TheWritableGlobalData->m_languageFilterPref = true;
			(*pref)["LanguageFilter"] = "true";
	}
	else
	{
			//GadgetCheckBoxSetChecked( checkLanguageFilter, false);
			TheWritableGlobalData->m_languageFilterPref = false;
			(*pref)["LanguageFilter"] = "false";
	}
	
	//-------------------------------------------------------------------------------------------------
	// send Delay
	TheWritableGlobalData->m_firewallSendDelay = GadgetCheckBoxIsChecked(checkSendDelay);
	if (TheGlobalData->m_firewallSendDelay) {
		(*pref)["SendDelay"] = AsciiString("yes");
	} else {
		(*pref)["SendDelay"] = AsciiString("no");
	}

	//-------------------------------------------------------------------------------------------------
	// Custom game detail settings.
	GadgetComboBoxGetSelectedPos( comboBoxDetail, &index );
	if (index == CUSTOMDETAIL)
	{
 		//-------------------------------------------------------------------------------------------------
 		// Texture resolution slider
		{
				AsciiString prefString;

		 		val = GadgetSliderGetPosition(sliderTextureResolution);
				val = 2-val;

				prefString.format("%d",val);
				(*pref)["TextureReduction"] = prefString;

				if (TheGlobalData->m_textureReductionFactor != val)
				{
					TheGameClient->adjustLOD(val-TheGlobalData->m_textureReductionFactor);	//apply the new setting
				}
		}

		TheWritableGlobalData->m_useShadowVolumes = GadgetCheckBoxIsChecked( check3DShadows );
		(*pref)["UseShadowVolumes"] = TheWritableGlobalData->m_useShadowVolumes ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_useShadowDecals = GadgetCheckBoxIsChecked( check2DShadows );
		(*pref)["UseShadowDecals"] = TheWritableGlobalData->m_useShadowDecals ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_useCloudMap = GadgetCheckBoxIsChecked( checkCloudShadows );
		(*pref)["UseCloudMap"] = TheGlobalData->m_useCloudMap ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_useLightMap = GadgetCheckBoxIsChecked( checkGroundLighting );
		(*pref)["UseLightMap"] = TheGlobalData->m_useLightMap ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_showSoftWaterEdge = GadgetCheckBoxIsChecked( checkSmoothWater );
		(*pref)["ShowSoftWaterEdge"] = TheGlobalData->m_showSoftWaterEdge ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_useDrawModuleLOD = !GadgetCheckBoxIsChecked( checkExtraAnimations );
		TheWritableGlobalData->m_useTreeSway = !TheWritableGlobalData->m_useDrawModuleLOD;	//borrow same setting.
		(*pref)["ExtraAnimations"] = TheGlobalData->m_useDrawModuleLOD ? AsciiString("no") : AsciiString("yes");

		TheWritableGlobalData->m_enableDynamicLOD = !GadgetCheckBoxIsChecked( checkNoDynamicLod );
		(*pref)["DynamicLOD"] = TheGlobalData->m_enableDynamicLOD ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_useHeatEffects = GadgetCheckBoxIsChecked( checkHeatEffects );
		(*pref)["HeatEffects"] = TheGlobalData->m_useHeatEffects ? AsciiString("yes") : AsciiString("no");

		// Never write this out
		//TheWritableGlobalData->m_useFpsLimit = !GadgetCheckBoxIsChecked( checkUnlockFps );
		//(*pref)["FPSLimit"] = TheGlobalData->m_useFpsLimit ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_enableBehindBuildingMarkers = GadgetCheckBoxIsChecked( checkBuildingOcclusion );
		(*pref)["BuildingOcclusion"] = TheWritableGlobalData->m_enableBehindBuildingMarkers ? AsciiString("yes") : AsciiString("no");

		TheWritableGlobalData->m_useTrees = GadgetCheckBoxIsChecked( checkProps);
		(*pref)["ShowTrees"] = TheWritableGlobalData->m_useTrees ? AsciiString("yes") : AsciiString("no");

 		//-------------------------------------------------------------------------------------------------
		// Particle Cap slider
		{
				AsciiString prefString;

		 		val = GadgetSliderGetPosition(sliderParticleCap);

				prefString.format("%d",val);
				(*pref)["MaxParticleCount"] = prefString;

				TheWritableGlobalData->m_maxParticleCount = val;
		}
	}

	//-------------------------------------------------------------------------------------------------
	// LOD
	Bool levelChanged=FALSE;
	GadgetComboBoxGetSelectedPos( comboBoxDetail, &index );
	//The levels stored by the LOD Manager are inverted compared to GUI so find correct one:
	switch (index) {
	case HIGHDETAIL:
		levelChanged=TheGameLODManager->setStaticLODLevel(STATIC_GAME_LOD_HIGH);
		break;
	case MEDIUMDETAIL:
		levelChanged=TheGameLODManager->setStaticLODLevel(STATIC_GAME_LOD_MEDIUM);
		break;
	case LOWDETAIL:
		levelChanged=TheGameLODManager->setStaticLODLevel(STATIC_GAME_LOD_LOW);
		break;
	case CUSTOMDETAIL:
		levelChanged=TheGameLODManager->setStaticLODLevel(STATIC_GAME_LOD_CUSTOM);
		break;
	default:
		DEBUG_ASSERTCRASH(FALSE,("LOD passed in was %d, %d is not a supported LOD",index,index));
		break;
	}

	if (levelChanged)
	        (*pref)["StaticGameLOD"] = TheGameLODManager->getStaticGameLODLevelName(TheGameLODManager->getStaticLODLevel());

	//-------------------------------------------------------------------------------------------------
	// Resolution
	GadgetComboBoxGetSelectedPos( comboBoxResolution, &index );
	Int xres, yres, bitDepth;
	
	oldDispSettings.xRes = TheDisplay->getWidth();
	oldDispSettings.yRes = TheDisplay->getHeight();
	oldDispSettings.bitDepth = TheDisplay->getBitDepth();
	oldDispSettings.windowed = TheDisplay->getWindowed();
	
	if (index < TheDisplay->getDisplayModeCount() && index >= 0)
	{
		TheDisplay->getDisplayModeDescription(index,&xres,&yres,&bitDepth);
		if (TheGlobalData->m_xResolution != xres || TheGlobalData->m_yResolution != yres)
		{
			
			if (TheDisplay->setDisplayMode(xres,yres,bitDepth,TheDisplay->getWindowed()))
			{
				dispChanged = TRUE;
				TheWritableGlobalData->m_xResolution = xres;
				TheWritableGlobalData->m_yResolution = yres;

				TheHeaderTemplateManager->headerNotifyResolutionChange();
				TheMouse->mouseNotifyResolutionChange();
				
				//Save new settings for a dialog box confirmation after options are accepted
				newDispSettings.xRes = xres;
				newDispSettings.yRes = yres;
				newDispSettings.bitDepth = bitDepth;
				newDispSettings.windowed = TheDisplay->getWindowed();

				AsciiString prefString;
				prefString.format("%d %d", xres, yres );
				(*pref)["Resolution"] = prefString;

				// delete the shell
				delete TheShell;
				TheShell = NULL;

				// create the shell
				TheShell = MSGNEW("GameClientSubsystem") Shell;
				if( TheShell )
					TheShell->init();
				
				TheInGameUI->recreateControlBar();

				TheShell->push( AsciiString("Menus/MainMenu.wnd") );
			}
		}
	}

	//-------------------------------------------------------------------------------------------------
	// IP address
	UnsignedInt ip;
	GadgetComboBoxGetSelectedPos(comboBoxLANIP, &index);
	if (index>=0 && TheGlobalData)
	{
		ip = (UnsignedInt)GadgetComboBoxGetItemData(comboBoxLANIP, index);
		TheWritableGlobalData->m_defaultIP = ip;
		pref->setLANIPAddress(ip);
	}
	GadgetComboBoxGetSelectedPos(comboBoxOnlineIP, &index);
	if (index>=0)
	{
		ip = (UnsignedInt)GadgetComboBoxGetItemData(comboBoxOnlineIP, index);
		pref->setOnlineIPAddress(ip);
	}

	//-------------------------------------------------------------------------------------------------
	// HTTP Proxy
	GameWindow *textEntryHTTPProxy = TheWindowManager->winGetWindowFromId(NULL, NAMEKEY("OptionsMenu.wnd:TextEntryHTTPProxy"));
	if (textEntryHTTPProxy)
	{
		UnicodeString uStr = GadgetTextEntryGetText(textEntryHTTPProxy);
		AsciiString aStr;
		aStr.translate(uStr);
		SetStringInRegistry("", "Proxy", aStr.str());
		ghttpSetProxy(aStr.str());
	}

	//-------------------------------------------------------------------------------------------------
	// Firewall Port Override
	GameWindow *textEntryFirewallPortOverride = TheWindowManager->winGetWindowFromId(NULL, NAMEKEY("OptionsMenu.wnd:TextEntryFirewallPortOverride"));
	if (textEntryFirewallPortOverride)
	{
		UnicodeString uStr = GadgetTextEntryGetText(textEntryFirewallPortOverride);
		AsciiString aStr;
		aStr.translate(uStr);
		Int override = atoi(aStr.str());
		if (override < 0 || override > 65535)
			override = 0;
		if (TheGlobalData->m_firewallPortOverride != override)
		{	TheWritableGlobalData->m_firewallPortOverride = override;
		    aStr.format("%d", override);
			(*pref)["FirewallPortOverride"] = aStr;
		}
	}

	//-------------------------------------------------------------------------------------------------
	// antialiasing
  GadgetComboBoxGetSelectedPos(comboBoxAntiAliasing, &index);
  if( index >= 0 && TheGlobalData->m_antiAliasBoxValue != index )
  {
    TheWritableGlobalData->m_antiAliasBoxValue = index;
    AsciiString prefString;
		prefString.format("%d", index);
		(*pref)["AntiAliasing"] = prefString;
  }


	//-------------------------------------------------------------------------------------------------
	// mouse mode
	TheWritableGlobalData->m_useAlternateMouse = GadgetCheckBoxIsChecked(checkAlternateMouse);
	(*pref)["UseAlternateMouse"] = TheWritableGlobalData->m_useAlternateMouse ? AsciiString("yes") : AsciiString("no");

	TheWritableGlobalData->m_clientRetaliationModeEnabled = GadgetCheckBoxIsChecked(checkRetaliation);
	(*pref)["Retaliation"] = TheWritableGlobalData->m_clientRetaliationModeEnabled? AsciiString("yes") : AsciiString("no");

	TheWritableGlobalData->m_doubleClickAttackMove = GadgetCheckBoxIsChecked( checkDoubleClickAttackMove );
	(*pref)["UseDoubleClickAttackMove"] = TheWritableGlobalData->m_doubleClickAttackMove ? AsciiString("yes") : AsciiString("no");

	//-------------------------------------------------------------------------------------------------
	// scroll speed val
	val = GadgetSliderGetPosition(sliderScrollSpeed);
	if(val != -1)
	{
		TheWritableGlobalData->m_keyboardScrollFactor = val/100.0f;
		DEBUG_LOG(("Scroll Spped val %d, keyboard scroll factor %f\n", val, TheGlobalData->m_keyboardScrollFactor));
		AsciiString prefString;
		prefString.format("%d", val);
		(*pref)["ScrollFactor"] = prefString;
	}
	
	//-------------------------------------------------------------------------------------------------
	// slider music volume
	val = GadgetSliderGetPosition(sliderMusicVolume);
	if(val != -1)
	{
	  TheWritableGlobalData->m_musicVolumeFactor = val;
    AsciiString prefString;
    prefString.format("%d", val);
    (*pref)["MusicVolume"] = prefString;
    TheAudio->setVolume(val / 100.0f, (AudioAffect) (AudioAffect_Music | AudioAffect_SystemSetting));
	}
	
	//-------------------------------------------------------------------------------------------------
	// slider SFX volume
	val = GadgetSliderGetPosition(sliderSFXVolume);
	if(val != -1)
	{
		//Both 2D and 3D sound effects are sharing the same slider. However, there is a 
		//relative slider that gets applied to one of these values to lower that sound volume.
		Real sound2DVolume = val / 100.0f;
		Real sound3DVolume = val / 100.0f;
		Real relative2DVolume = TheAudio->getAudioSettings()->m_relative2DVolume;
		relative2DVolume = MIN( 1.0f, MAX( -1.0, relative2DVolume ) );
		if( relative2DVolume < 0.0f )
		{
			//Lower the 2D volume
			sound2DVolume *= 1.0f + relative2DVolume;
		}
		else
		{
			//Lower the 3D volume
			sound3DVolume *= 1.0f - relative2DVolume;
		}

		//Apply the sound volumes in the audio system now.
    TheAudio->setVolume( sound2DVolume, (AudioAffect) (AudioAffect_Sound | AudioAffect_SystemSetting) );
		TheAudio->setVolume( sound3DVolume, (AudioAffect) (AudioAffect_Sound3D | AudioAffect_SystemSetting) );

		//Save the settings in the options.ini.
    TheWritableGlobalData->m_SFXVolumeFactor = val;
    AsciiString prefString;
    prefString.format("%d", REAL_TO_INT( sound2DVolume * 100.0f ) );
    (*pref)["SFXVolume"] = prefString;
    prefString.format("%d", REAL_TO_INT( sound3DVolume * 100.0f ) );
		(*pref)["SFX3DVolume"] = prefString;
	}

	//-------------------------------------------------------------------------------------------------
	// slider Voice volume
	val = GadgetSliderGetPosition(sliderVoiceVolume);
	if(val != -1)
	{
    TheWritableGlobalData->m_voiceVolumeFactor = val;
    AsciiString prefString;
    prefString.format("%d", val);
    (*pref)["VoiceVolume"] = prefString;
    TheAudio->setVolume(val / 100.0f, (AudioAffect) (AudioAffect_Speech | AudioAffect_SystemSetting));
	}

 	//-------------------------------------------------------------------------------------------------
 	// slider Gamma
 	val = GadgetSliderGetPosition(sliderGamma);
 	if(val != -1)
 	{
		Real gammaval=1.0f;
		//generate a value between 0.6 and 2.0.
		if (val < 50)
		{	//darker gamma
			if (val <= 0)
				gammaval = 0.6f;
			else
				gammaval=1.0f-(0.4f) * (Real)(50-val)/50.0f;
		}
		else
		if (val > 50)
			gammaval=1.0f+(1.0f) * (Real)(val-50)/50.0f;

 		AsciiString prefString;
 		prefString.format("%d", val);
 		(*pref)["Gamma"] = prefString;

		if (TheGlobalData->m_displayGamma != gammaval)
		{	TheWritableGlobalData->m_displayGamma = gammaval;
			TheDisplay->setGamma(TheGlobalData->m_displayGamma,0.0f, 1.0f, FALSE);
		}
 	}

}

static void DestroyOptionsLayout() {

	SignalUIInteraction(SHELL_SCRIPT_HOOK_OPTIONS_CLOSED);

	TheShell->destroyOptionsLayout();
	OptionsLayout = NULL;
}

static void showAdvancedOptions()
{
	WinAdvancedDisplay->winHide(FALSE);
}

static void acceptAdvancedOptions()
{
	WinAdvancedDisplay->winHide(TRUE);
}

static void cancelAdvancedOptions()
{
	//restore the detail selection back to initial state
	switch (TheGameLODManager->getStaticLODLevel())
	{
	case STATIC_GAME_LOD_LOW:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, LOWDETAIL);
		break;
	case STATIC_GAME_LOD_MEDIUM:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, MEDIUMDETAIL);
		break;
	case STATIC_GAME_LOD_HIGH:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, HIGHDETAIL);
		break;
	case STATIC_GAME_LOD_CUSTOM:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, CUSTOMDETAIL);
		break;
	default:
		DEBUG_ASSERTCRASH(FALSE,("Tried to set comboBoxDetail to a value of %d ", TheGameLODManager->getStaticLODLevel()) );
	};

	WinAdvancedDisplay->winHide(TRUE);
}
//-------------------------------------------------------------------------------------------------
/** Initialize the options menu */
//-------------------------------------------------------------------------------------------------
__declspec(naked) void OptionsMenuInit( WindowLayout *layout, void *userData )
{
	__asm {
		__emit 0x6a
		__emit 0xff
		__emit 0x68
		__emit 0x6e
		__emit 0x49
		__emit 0x03
		__emit 0x01
		__emit 0x64
		__emit 0xa1
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x64
		__emit 0x89
		__emit 0x25
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xec
		__emit 0x18
		__emit 0x53
		__emit 0x55
		__emit 0x56
		__emit 0x33
		__emit 0xf6
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x0c
		__emit 0xa1
		__emit 0xe4
		__emit 0x4a
		__emit 0x2f
		__emit 0x01
		__emit 0x3b
		__emit 0xc6
		__emit 0x57
		__emit 0x8b
		__emit 0xf9
		__emit 0x74
		__emit 0x12
		__emit 0x8b
		__emit 0x0d
		__emit 0x68
		__emit 0xd6
		__emit 0x2e
		__emit 0x01
		__emit 0x8b
		__emit 0x11
		__emit 0x50
		__emit 0xff
		__emit 0x52
		__emit 0x50
		__emit 0x89
		__emit 0x35
		__emit 0xe4
		__emit 0x4a
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x87
		__emit 0x58
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf8
		__emit 0x02
		__emit 0x0f
		__emit 0x84
		__emit 0xd3
		__emit 0x0c
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf8
		__emit 0x03
		__emit 0x0f
		__emit 0x84
		__emit 0xca
		__emit 0x0c
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf8
		__emit 0x04
		__emit 0x0f
		__emit 0x85
		__emit 0x2c
		__emit 0x1a
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0x9c
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xce
		__emit 0xc7
		__emit 0x87
		__emit 0x0c
		__emit 0x03
		__emit 0x00
		__emit 0x00
		__emit 0x05
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x07
		__emit 0x6a
		__emit 0x01
		__emit 0xe8
		__emit 0x00
		__emit 0x9f
		__emit 0xae
		__emit 0xff
		__emit 0x8b
		__emit 0x8f
		__emit 0x90
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xce
		__emit 0x74
		__emit 0x07
		__emit 0x6a
		__emit 0x01
		__emit 0xe8
		__emit 0xef
		__emit 0x9e
		__emit 0xae
		__emit 0xff
		__emit 0x8b
		__emit 0x87
		__emit 0xbc
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xc6
		__emit 0x0f
		__emit 0x84
		__emit 0x10
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x5a
		__emit 0x98
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xfb
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x26
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x27
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x21
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x69
		__emit 0x88
		__emit 0x32
		__emit 0x00
		__emit 0xbe
		__emit 0x00
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xeb
		__emit 0x26
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0x48
		__emit 0x88
		__emit 0x32
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x10
		__emit 0x00
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x28
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0xf6
		__emit 0x78
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xfd
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x87
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xfe
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x68
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x18
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xda
		__emit 0x87
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x29
		__emit 0xe8
		__emit 0xdf
		__emit 0xe2
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x89
		__emit 0x78
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x26
		__emit 0xe8
		__emit 0x2b
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x1a
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0x8b
		__emit 0x87
		__emit 0xc0
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x3c
		__emit 0x97
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x2a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x2b
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x4b
		__emit 0x87
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x04
		__emit 0x00
		__emit 0x00
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0x2d
		__emit 0x87
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x2c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x08
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0xdd
		__emit 0x77
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x08
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xf7
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x6e
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x04
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xfb
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x4f
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x3c
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xc1
		__emit 0x86
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x2d
		__emit 0xe8
		__emit 0xc6
		__emit 0xe1
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x70
		__emit 0x77
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x2a
		__emit 0xe8
		__emit 0x12
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x01
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xc4
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x27
		__emit 0x96
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x2e
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x2f
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x36
		__emit 0x86
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x10
		__emit 0x00
		__emit 0x00
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0x18
		__emit 0x86
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x30
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x20
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0xc8
		__emit 0x76
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x20
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xdf
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x59
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x10
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xef
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x3a
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0xa4
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xac
		__emit 0x85
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x31
		__emit 0xe8
		__emit 0xb1
		__emit 0xe0
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x5b
		__emit 0x76
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x2e
		__emit 0xe8
		__emit 0xfd
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xec
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xc8
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x12
		__emit 0x95
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x32
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x33
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x21
		__emit 0x85
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x40
		__emit 0x00
		__emit 0x00
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0x03
		__emit 0x85
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x34
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0xb3
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0x7f
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x44
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x40
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xbf
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x25
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x98
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x97
		__emit 0x84
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x35
		__emit 0xe8
		__emit 0x9c
		__emit 0xdf
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x46
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x32
		__emit 0xe8
		__emit 0xe8
		__emit 0x71
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xd7
		__emit 0x71
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xcc
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0xfd
		__emit 0x93
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x36
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x37
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x0c
		__emit 0x84
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0x00
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xee
		__emit 0x83
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x38
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x02
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0x9e
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x02
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xfd
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x2f
		__emit 0x71
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xfe
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x10
		__emit 0x71
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x00
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x82
		__emit 0x83
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x39
		__emit 0xe8
		__emit 0x87
		__emit 0xde
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x31
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x36
		__emit 0xe8
		__emit 0xd3
		__emit 0x70
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xc2
		__emit 0x70
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xd0
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0xe8
		__emit 0x92
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x3a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x3b
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xf7
		__emit 0x82
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x04
		__emit 0x00
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xd9
		__emit 0x82
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x3c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x08
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0x89
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x08
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xf7
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x1a
		__emit 0x70
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x04
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xfb
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0xfb
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x78
		__emit 0x6a
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x6d
		__emit 0x82
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x3d
		__emit 0xe8
		__emit 0x72
		__emit 0xdd
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x1c
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x3a
		__emit 0xe8
		__emit 0xbe
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xad
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xd4
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0xd3
		__emit 0x91
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x3e
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x3f
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xe2
		__emit 0x81
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x10
		__emit 0x00
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xc4
		__emit 0x81
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x40
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x20
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0x74
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x20
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xdf
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x05
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x10
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xef
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0xe6
		__emit 0x6e
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0xec
		__emit 0x6c
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x58
		__emit 0x81
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x41
		__emit 0xe8
		__emit 0x5d
		__emit 0xdc
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x07
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x3e
		__emit 0xe8
		__emit 0xa9
		__emit 0x6e
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x98
		__emit 0x6e
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xd8
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0xbe
		__emit 0x90
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x42
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x43
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xcd
		__emit 0x80
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x40
		__emit 0x00
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xaf
		__emit 0x80
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x44
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x80
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0x5f
		__emit 0x71
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x80
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0x7f
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0xf0
		__emit 0x6d
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x40
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xbf
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0xd1
		__emit 0x6d
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0xc8
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x43
		__emit 0x80
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x45
		__emit 0xe8
		__emit 0x48
		__emit 0xdb
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0xf2
		__emit 0x70
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x42
		__emit 0xe8
		__emit 0x94
		__emit 0x6d
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x83
		__emit 0x6d
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xdc
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x07
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0xa9
		__emit 0x8f
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbd
		__emit 0x46
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x47
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1e
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xb8
		__emit 0x7f
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0xeb
		__emit 0x20
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0x9a
		__emit 0x7f
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x48
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xce
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x02
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0x4a
		__emit 0x70
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x02
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xfd
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0xdb
		__emit 0x6c
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc6
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe6
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xfe
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0xbc
		__emit 0x6c
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x5c
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x2e
		__emit 0x7f
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x49
		__emit 0xe8
		__emit 0x33
		__emit 0xda
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0xdd
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x46
		__emit 0xe8
		__emit 0x7f
		__emit 0x6c
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x6e
		__emit 0x6c
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0xfc
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x33
		__emit 0xf6
		__emit 0x3b
		__emit 0xce
		__emit 0x0f
		__emit 0x84
		__emit 0x8a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x18
		__emit 0xbb
		__emit 0x4a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x44
		__emit 0x58
		__emit 0xae
		__emit 0xff
		__emit 0x3b
		__emit 0xc6
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0xe8
		__emit 0xae
		__emit 0x7e
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x20
		__emit 0x52
		__emit 0xe8
		__emit 0xd4
		__emit 0x82
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0xb0
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x93
		__emit 0x7e
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x4b
		__emit 0xe8
		__emit 0x98
		__emit 0xd9
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x42
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xe5
		__emit 0x6b
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xd4
		__emit 0x6b
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0x00
		__emit 0x03
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xce
		__emit 0x0f
		__emit 0x84
		__emit 0x8a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x18
		__emit 0xbb
		__emit 0x4c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xac
		__emit 0x57
		__emit 0xae
		__emit 0xff
		__emit 0x3b
		__emit 0xc6
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0xe8
		__emit 0x16
		__emit 0x7e
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x20
		__emit 0x52
		__emit 0xe8
		__emit 0x3c
		__emit 0x82
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0x84
		__emit 0x6b
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xfb
		__emit 0x7d
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x4d
		__emit 0xe8
		__emit 0x00
		__emit 0xd9
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0xaa
		__emit 0x6e
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x4d
		__emit 0x6b
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x3c
		__emit 0x6b
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x15
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8a
		__emit 0x42
		__emit 0x28
		__emit 0x84
		__emit 0xc0
		__emit 0xbd
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x75
		__emit 0x05
		__emit 0xbd
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x68
		__emit 0x84
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x97
		__emit 0x7d
		__emit 0x32
		__emit 0x00
		__emit 0x55
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0x8d
		__emit 0xb7
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x8b
		__emit 0xce
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x4e
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x96
		__emit 0xd8
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x6e
		__emit 0x7d
		__emit 0xac
		__emit 0xff
		__emit 0x83
		__emit 0xcb
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xe5
		__emit 0x6a
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8a
		__emit 0x41
		__emit 0x1e
		__emit 0x84
		__emit 0xc0
		__emit 0xbd
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x75
		__emit 0x05
		__emit 0xbd
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x68
		__emit 0x50
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x40
		__emit 0x7d
		__emit 0x32
		__emit 0x00
		__emit 0x55
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x20
		__emit 0x52
		__emit 0x8b
		__emit 0xce
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x4f
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x45
		__emit 0xd8
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x1d
		__emit 0x7d
		__emit 0xac
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x97
		__emit 0x6a
		__emit 0x32
		__emit 0x00
		__emit 0xa1
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8a
		__emit 0x48
		__emit 0x1f
		__emit 0x84
		__emit 0xc9
		__emit 0xbd
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x75
		__emit 0x05
		__emit 0xbd
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x68
		__emit 0x44
		__emit 0x6a
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xf3
		__emit 0x7c
		__emit 0x32
		__emit 0x00
		__emit 0x55
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x51
		__emit 0x8b
		__emit 0xce
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x50
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0xf8
		__emit 0xd7
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0xd0
		__emit 0x7c
		__emit 0xac
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x4a
		__emit 0x6a
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x15
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8a
		__emit 0x42
		__emit 0x70
		__emit 0x84
		__emit 0xc0
		__emit 0xbd
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x75
		__emit 0x05
		__emit 0xbd
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x68
		__emit 0x6c
		__emit 0x6d
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xa5
		__emit 0x7c
		__emit 0x32
		__emit 0x00
		__emit 0x55
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0x50
		__emit 0x8b
		__emit 0xce
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x51
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0xaa
		__emit 0xd7
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x82
		__emit 0x7c
		__emit 0xac
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xfc
		__emit 0x69
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8a
		__emit 0x41
		__emit 0x1b
		__emit 0x84
		__emit 0xc0
		__emit 0xbd
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x75
		__emit 0x05
		__emit 0xbd
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x68
		__emit 0x84
		__emit 0x6a
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x57
		__emit 0x7c
		__emit 0x32
		__emit 0x00
		__emit 0x55
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x20
		__emit 0x52
		__emit 0x8b
		__emit 0xce
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x52
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x5c
		__emit 0xd7
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x34
		__emit 0x7c
		__emit 0xac
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xae
		__emit 0x69
		__emit 0x32
		__emit 0x00
		__emit 0xc7
		__emit 0x87
		__emit 0x58
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe9
		__emit 0x6b
		__emit 0x0d
		__emit 0x00
		__emit 0x00
		__emit 0xa0
		__emit 0xd0
		__emit 0x4a
		__emit 0x2f
		__emit 0x01
		__emit 0x84
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x77
		__emit 0x03
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0x88
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xc6
		__emit 0x0f
		__emit 0x84
		__emit 0xa0
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x14
		__emit 0x51
		__emit 0x50
		__emit 0xe8
		__emit 0x93
		__emit 0xa7
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x83
		__emit 0xf8
		__emit 0x05
		__emit 0x0f
		__emit 0x87
		__emit 0xe3
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xff
		__emit 0x24
		__emit 0x85
		__emit 0x94
		__emit 0x1e
		__emit 0x96
		__emit 0x00
		__emit 0x6a
		__emit 0x04
		__emit 0xeb
		__emit 0x20
		__emit 0x6a
		__emit 0x03
		__emit 0xeb
		__emit 0x1c
		__emit 0x6a
		__emit 0x02
		__emit 0xeb
		__emit 0x18
		__emit 0x6a
		__emit 0x01
		__emit 0xeb
		__emit 0x14
		__emit 0x56
		__emit 0xeb
		__emit 0x11
		__emit 0x8d
		__emit 0x97
		__emit 0x60
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x52
		__emit 0xe8
		__emit 0xff
		__emit 0x77
		__emit 0xae
		__emit 0xff
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x6a
		__emit 0x05
		__emit 0x8b
		__emit 0x0d
		__emit 0xac
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xe8
		__emit 0x58
		__emit 0x8c
		__emit 0xae
		__emit 0xff
		__emit 0x84
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0xa1
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x68
		__emit 0xc0
		__emit 0x6c
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x9d
		__emit 0x7b
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xac
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8b
		__emit 0x81
		__emit 0xc0
		__emit 0x16
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0xb7
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0xfb
		__emit 0xbd
		__emit 0xad
		__emit 0xff
		__emit 0x50
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0x50
		__emit 0x8b
		__emit 0xce
		__emit 0xe8
		__emit 0x8a
		__emit 0xd6
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x62
		__emit 0x7b
		__emit 0xac
		__emit 0xff
		__emit 0x83
		__emit 0xcb
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xd9
		__emit 0x68
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xac
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8b
		__emit 0xa9
		__emit 0xc4
		__emit 0x16
		__emit 0x00
		__emit 0x00
		__emit 0x68
		__emit 0xa8
		__emit 0x6c
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x3f
		__emit 0x7b
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xac
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x55
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0xa9
		__emit 0xbd
		__emit 0xad
		__emit 0xff
		__emit 0x50
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x20
		__emit 0x52
		__emit 0x8b
		__emit 0xce
		__emit 0xe8
		__emit 0x38
		__emit 0xd6
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x10
		__emit 0x7b
		__emit 0xac
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x8a
		__emit 0x68
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x14
		__emit 0x83
		__emit 0xf8
		__emit 0x04
		__emit 0x0f
		__emit 0x84
		__emit 0xb2
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf8
		__emit 0x03
		__emit 0x0f
		__emit 0x84
		__emit 0xa9
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf8
		__emit 0x02
		__emit 0x74
		__emit 0x0f
		__emit 0x83
		__emit 0xf8
		__emit 0x01
		__emit 0x74
		__emit 0x0a
		__emit 0x33
		__emit 0xf6
		__emit 0x3b
		__emit 0xc6
		__emit 0x0f
		__emit 0x85
		__emit 0x3a
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x33
		__emit 0xf6
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x18
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x05
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0xc4
		__emit 0x7a
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x06
		__emit 0xe8
		__emit 0x81
		__emit 0x6b
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x05
		__emit 0xe8
		__emit 0x23
		__emit 0x68
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0xc8
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x95
		__emit 0x7a
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x07
		__emit 0xe8
		__emit 0x9a
		__emit 0xd5
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x18
		__emit 0x52
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x44
		__emit 0x6b
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x05
		__emit 0xe8
		__emit 0xe6
		__emit 0x67
		__emit 0x32
		__emit 0x00
		__emit 0xa1
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xc6
		__emit 0x40
		__emit 0x1d
		__emit 0x01
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xc6
		__emit 0x81
		__emit 0x75
		__emit 0x0a
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0xe9
		__emit 0x90
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x33
		__emit 0xf6
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x18
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x2f
		__emit 0x7a
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x03
		__emit 0xe8
		__emit 0xec
		__emit 0x6a
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x02
		__emit 0xe8
		__emit 0x8e
		__emit 0x67
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0xc8
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x00
		__emit 0x7a
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x04
		__emit 0xe8
		__emit 0x05
		__emit 0xd5
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0xaf
		__emit 0x6a
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x02
		__emit 0xe8
		__emit 0x51
		__emit 0x67
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x15
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xc6
		__emit 0x42
		__emit 0x1d
		__emit 0x00
		__emit 0xa1
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xc6
		__emit 0x80
		__emit 0x75
		__emit 0x0a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x2a
		__emit 0x67
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x14
		__emit 0x83
		__emit 0xf8
		__emit 0x02
		__emit 0x75
		__emit 0x0f
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xc6
		__emit 0x81
		__emit 0x77
		__emit 0x0a
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0xeb
		__emit 0x16
		__emit 0x83
		__emit 0xf8
		__emit 0x01
		__emit 0x74
		__emit 0x04
		__emit 0x3b
		__emit 0xc6
		__emit 0x75
		__emit 0x11
		__emit 0x8b
		__emit 0x15
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xc6
		__emit 0x82
		__emit 0x77
		__emit 0x0a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x14
		__emit 0x83
		__emit 0xf8
		__emit 0x05
		__emit 0x74
		__emit 0x0f
		__emit 0x8d
		__emit 0x87
		__emit 0x60
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x20
		__emit 0xec
		__emit 0xab
		__emit 0xff
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0xa0
		__emit 0xd0
		__emit 0x4a
		__emit 0x2f
		__emit 0x01
		__emit 0x84
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0xbc
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0x84
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xc6
		__emit 0x0f
		__emit 0x84
		__emit 0xae
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0x98
		__emit 0x08
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x89
		__emit 0x0c
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf9
		__emit 0x08
		__emit 0x74
		__emit 0x09
		__emit 0x83
		__emit 0xf9
		__emit 0x04
		__emit 0x0f
		__emit 0x85
		__emit 0x94
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x39
		__emit 0x35
		__emit 0x94
		__emit 0x71
		__emit 0x2f
		__emit 0x01
		__emit 0x0f
		__emit 0x85
		__emit 0x88
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x14
		__emit 0x52
		__emit 0x50
		__emit 0xe8
		__emit 0xb2
		__emit 0xa4
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0x0d
		__emit 0x70
		__emit 0x12
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x01
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0xff
		__emit 0x50
		__emit 0x48
		__emit 0x8b
		__emit 0x54
		__emit 0x24
		__emit 0x14
		__emit 0x3b
		__emit 0xd0
		__emit 0x7d
		__emit 0x67
		__emit 0x3b
		__emit 0xd6
		__emit 0x7c
		__emit 0x63
		__emit 0x8b
		__emit 0x0d
		__emit 0x70
		__emit 0x12
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x01
		__emit 0x8d
		__emit 0x5c
		__emit 0x24
		__emit 0x24
		__emit 0x53
		__emit 0x8d
		__emit 0x5c
		__emit 0x24
		__emit 0x1c
		__emit 0x53
		__emit 0x8d
		__emit 0x5c
		__emit 0x24
		__emit 0x24
		__emit 0x53
		__emit 0x52
		__emit 0xff
		__emit 0x50
		__emit 0x4c
		__emit 0x8b
		__emit 0x15
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x8b
		__emit 0x4a
		__emit 0x2c
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x3b
		__emit 0xc8
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x75
		__emit 0x05
		__emit 0x39
		__emit 0x4a
		__emit 0x30
		__emit 0x74
		__emit 0x2e
		__emit 0x89
		__emit 0x8f
		__emit 0x78
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0x89
		__emit 0x87
		__emit 0x74
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x8f
		__emit 0x7c
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0x70
		__emit 0x12
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x11
		__emit 0xff
		__emit 0x52
		__emit 0x40
		__emit 0x88
		__emit 0x87
		__emit 0x80
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x87
		__emit 0x08
		__emit 0x03
		__emit 0x00
		__emit 0x00
		__emit 0x01
		__emit 0x8b
		__emit 0x8f
		__emit 0xf8
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xce
		__emit 0x74
		__emit 0x0e
		__emit 0xe8
		__emit 0x04
		__emit 0x52
		__emit 0xae
		__emit 0xff
		__emit 0x3b
		__emit 0xc6
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf1
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf8
		__emit 0x32
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x80
		__emit 0x3f
		__emit 0x7d
		__emit 0x2b
		__emit 0x3b
		__emit 0xc6
		__emit 0x7f
		__emit 0x0a
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x9a
		__emit 0x99
		__emit 0x19
		__emit 0x3f
		__emit 0xeb
		__emit 0x3a
		__emit 0xb9
		__emit 0x32
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x2b
		__emit 0xc8
		__emit 0x89
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xdb
		__emit 0x44
		__emit 0x24
		__emit 0x24
		__emit 0xd8
		__emit 0x0d
		__emit 0xf0
		__emit 0xc6
		__emit 0x07
		__emit 0x01
		__emit 0xd8
		__emit 0x2d
		__emit 0x34
		__emit 0x53
		__emit 0x07
		__emit 0x01
		__emit 0xeb
		__emit 0x19
		__emit 0x7e
		__emit 0x1b
		__emit 0x8d
		__emit 0x50
		__emit 0xce
		__emit 0x89
		__emit 0x54
		__emit 0x24
		__emit 0x24
		__emit 0xdb
		__emit 0x44
		__emit 0x24
		__emit 0x24
		__emit 0xd8
		__emit 0x0d
		__emit 0xec
		__emit 0xc6
		__emit 0x07
		__emit 0x01
		__emit 0xd8
		__emit 0x05
		__emit 0x34
		__emit 0x53
		__emit 0x07
		__emit 0x01
		__emit 0xd9
		__emit 0x5c
		__emit 0x24
		__emit 0x18
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x1c
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x3c
		__emit 0x08
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x04
		__emit 0x78
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x24
		__emit 0x50
		__emit 0xe8
		__emit 0x2a
		__emit 0x7c
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0xac
		__emit 0xfa
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xe9
		__emit 0x77
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x51
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x09
		__emit 0xe8
		__emit 0xee
		__emit 0xd2
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x98
		__emit 0x68
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x08
		__emit 0xe8
		__emit 0x3a
		__emit 0x65
		__emit 0x32
		__emit 0x00
		__emit 0xd9
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xd9
		__emit 0x81
		__emit 0x68
		__emit 0x0c
		__emit 0x00
		__emit 0x00
		__emit 0xda
		__emit 0xe9
		__emit 0xdf
		__emit 0xe0
		__emit 0xf6
		__emit 0xc4
		__emit 0x44
		__emit 0x7b
		__emit 0x0a
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x89
		__emit 0x81
		__emit 0x68
		__emit 0x0c
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x06
		__emit 0x65
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0xf4
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x3b
		__emit 0xce
		__emit 0x74
		__emit 0x0e
		__emit 0xe8
		__emit 0xef
		__emit 0x50
		__emit 0xae
		__emit 0xff
		__emit 0x3b
		__emit 0xc6
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x89
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0x0f
		__emit 0x84
		__emit 0xbd
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xf8
		__emit 0x01
		__emit 0x7d
		__emit 0x09
		__emit 0xb8
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xdb
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xd8
		__emit 0x0d
		__emit 0xec
		__emit 0xc6
		__emit 0x07
		__emit 0x01
		__emit 0xd9
		__emit 0xc0
		__emit 0xd9
		__emit 0x99
		__emit 0xbc
		__emit 0x0b
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x15
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xd9
		__emit 0xc0
		__emit 0xd9
		__emit 0x9a
		__emit 0x68
		__emit 0x0b
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xd9
		__emit 0x99
		__emit 0x64
		__emit 0x0b
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0xbb
		__emit 0x0a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x3c
		__emit 0xe8
		__emit 0xfb
		__emit 0x76
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x24
		__emit 0x52
		__emit 0xe8
		__emit 0x21
		__emit 0x7b
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0x0c
		__emit 0xfa
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0xe0
		__emit 0x76
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x0b
		__emit 0xe8
		__emit 0xe5
		__emit 0xd1
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x8f
		__emit 0x67
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x32
		__emit 0x64
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x21
		__emit 0x64
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0xe0
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc9
		__emit 0x74
		__emit 0x0e
		__emit 0xe8
		__emit 0x0a
		__emit 0x50
		__emit 0xae
		__emit 0xff
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x74
		__emit 0x7d
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0xbb
		__emit 0x0c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x3c
		__emit 0xe8
		__emit 0x5e
		__emit 0x76
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x24
		__emit 0x52
		__emit 0xe8
		__emit 0x84
		__emit 0x7a
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0xe4
		__emit 0xfa
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x43
		__emit 0x76
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x0d
		__emit 0xe8
		__emit 0x48
		__emit 0xd1
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0xf2
		__emit 0x66
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x95
		__emit 0x63
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x84
		__emit 0x63
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0xf0
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc9
		__emit 0x74
		__emit 0x0e
		__emit 0xe8
		__emit 0x6d
		__emit 0x4f
		__emit 0xae
		__emit 0xff
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x74
		__emit 0x7d
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0xbb
		__emit 0x0e
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x3c
		__emit 0xe8
		__emit 0xc1
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x24
		__emit 0x52
		__emit 0xe8
		__emit 0xe7
		__emit 0x79
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0xf4
		__emit 0xfa
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0xa6
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x0f
		__emit 0xe8
		__emit 0xab
		__emit 0xd0
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x55
		__emit 0x66
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xf8
		__emit 0x62
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xe7
		__emit 0x62
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0xec
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc9
		__emit 0x74
		__emit 0x0e
		__emit 0xe8
		__emit 0xd0
		__emit 0x4e
		__emit 0xae
		__emit 0xff
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x74
		__emit 0x7d
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x3c
		__emit 0x10
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x25
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x24
		__emit 0x52
		__emit 0xe8
		__emit 0x4b
		__emit 0x79
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0x04
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x0a
		__emit 0x75
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x11
		__emit 0xe8
		__emit 0x0f
		__emit 0xd0
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0xb9
		__emit 0x65
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x10
		__emit 0xe8
		__emit 0x5b
		__emit 0x62
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x4a
		__emit 0x62
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0xe4
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc9
		__emit 0x74
		__emit 0x0e
		__emit 0xe8
		__emit 0x33
		__emit 0x4e
		__emit 0xae
		__emit 0xff
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x74
		__emit 0x7d
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0xbb
		__emit 0x12
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x3c
		__emit 0xe8
		__emit 0x87
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x24
		__emit 0x52
		__emit 0xe8
		__emit 0xad
		__emit 0x78
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0xc8
		__emit 0xfa
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x6c
		__emit 0x74
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x13
		__emit 0xe8
		__emit 0x71
		__emit 0xcf
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x1b
		__emit 0x65
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0xbe
		__emit 0x61
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xad
		__emit 0x61
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x8f
		__emit 0xe8
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc9
		__emit 0x74
		__emit 0x0e
		__emit 0xe8
		__emit 0x96
		__emit 0x4d
		__emit 0xae
		__emit 0xff
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x05
		__emit 0x8b
		__emit 0x40
		__emit 0x0c
		__emit 0xeb
		__emit 0x03
		__emit 0x83
		__emit 0xc8
		__emit 0xff
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x74
		__emit 0x7d
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0x89
		__emit 0x64
		__emit 0x24
		__emit 0x2c
		__emit 0x8b
		__emit 0xcc
		__emit 0xbb
		__emit 0x14
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x68
		__emit 0xb4
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x3c
		__emit 0xe8
		__emit 0xea
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x24
		__emit 0x52
		__emit 0xe8
		__emit 0x10
		__emit 0x78
		__emit 0x32
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x0c
		__emit 0x68
		__emit 0xd4
		__emit 0xfa
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0xcf
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x15
		__emit 0xe8
		__emit 0xd4
		__emit 0xce
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x7e
		__emit 0x64
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0xe8
		__emit 0x21
		__emit 0x61
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x10
		__emit 0x61
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0x90
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x13
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x36
		__emit 0x83
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xf0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xfe
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xfe
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xf6
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x16
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x22
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x4b
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0xbb
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x17
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xeb
		__emit 0x26
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0x29
		__emit 0x73
		__emit 0x32
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x10
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x18
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xd7
		__emit 0x63
		__emit 0x32
		__emit 0x00
		__emit 0xf6
		__emit 0xc3
		__emit 0x02
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x17
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x10
		__emit 0x83
		__emit 0xe3
		__emit 0xfd
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x6a
		__emit 0x60
		__emit 0x32
		__emit 0x00
		__emit 0xf6
		__emit 0xc3
		__emit 0x01
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x16
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x10
		__emit 0x83
		__emit 0xe3
		__emit 0xfe
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x4d
		__emit 0x60
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x58
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0xbf
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x18
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x19
		__emit 0xe8
		__emit 0xc4
		__emit 0xcd
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x6e
		__emit 0x63
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x16
		__emit 0xe8
		__emit 0x10
		__emit 0x60
		__emit 0x32
		__emit 0x00
		__emit 0xa1
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x85
		__emit 0xf6
		__emit 0x0f
		__emit 0x95
		__emit 0xc2
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x90
		__emit 0x8e
		__emit 0x0a
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xef
		__emit 0x5f
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0x94
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x0f
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x15
		__emit 0x82
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xf0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xfe
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xfa
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xf6
		__emit 0xbd
		__emit 0x1a
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x1b
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1f
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x24
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x83
		__emit 0xc9
		__emit 0x04
		__emit 0xeb
		__emit 0x21
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0x05
		__emit 0x72
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xc9
		__emit 0x08
		__emit 0x89
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0xb4
		__emit 0x62
		__emit 0x32
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x8b
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xf6
		__emit 0xc3
		__emit 0x08
		__emit 0x74
		__emit 0x10
		__emit 0x83
		__emit 0xe3
		__emit 0xf7
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x47
		__emit 0x5f
		__emit 0x32
		__emit 0x00
		__emit 0xf6
		__emit 0xc3
		__emit 0x04
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x10
		__emit 0x83
		__emit 0xe3
		__emit 0xfb
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x2e
		__emit 0x5f
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x68
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0xa0
		__emit 0x71
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x1d
		__emit 0xe8
		__emit 0xa5
		__emit 0xcc
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x4f
		__emit 0x62
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x1a
		__emit 0xe8
		__emit 0xf1
		__emit 0x5e
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x85
		__emit 0xf6
		__emit 0x0f
		__emit 0x94
		__emit 0xc0
		__emit 0x88
		__emit 0x41
		__emit 0x60
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xd2
		__emit 0x5e
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0x9c
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x15
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0xf8
		__emit 0x80
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xf0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xfe
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0x00
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xf6
		__emit 0xbd
		__emit 0x1e
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x1f
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x23
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x07
		__emit 0x71
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x83
		__emit 0xc9
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x89
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0xeb
		__emit 0x25
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xe4
		__emit 0x70
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x54
		__emit 0x24
		__emit 0x10
		__emit 0xb9
		__emit 0x20
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x0b
		__emit 0xd1
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x4c
		__emit 0x24
		__emit 0x30
		__emit 0x89
		__emit 0x54
		__emit 0x24
		__emit 0x10
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x93
		__emit 0x61
		__emit 0x32
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x8b
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xf6
		__emit 0xc3
		__emit 0x20
		__emit 0x74
		__emit 0x10
		__emit 0x83
		__emit 0xe3
		__emit 0xdf
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x26
		__emit 0x5e
		__emit 0x32
		__emit 0x00
		__emit 0xf6
		__emit 0xc3
		__emit 0x10
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x10
		__emit 0x83
		__emit 0xe3
		__emit 0xef
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x0d
		__emit 0x5e
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x80
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x7f
		__emit 0x70
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x18
		__emit 0x52
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x21
		__emit 0xe8
		__emit 0x84
		__emit 0xcb
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x2e
		__emit 0x61
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x1e
		__emit 0xe8
		__emit 0xd0
		__emit 0x5d
		__emit 0x32
		__emit 0x00
		__emit 0xa1
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x85
		__emit 0xf6
		__emit 0x0f
		__emit 0x95
		__emit 0xc2
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x88
		__emit 0x90
		__emit 0x75
		__emit 0x0a
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xaf
		__emit 0x5d
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xb4
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x06
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0xd5
		__emit 0x7f
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0xf1
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0xbe
		__emit 0x22
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x23
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x1f
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0xe4
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x83
		__emit 0xc9
		__emit 0x40
		__emit 0xeb
		__emit 0x24
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xc5
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x24
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xc9
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x71
		__emit 0x60
		__emit 0x32
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x8b
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0x84
		__emit 0xdb
		__emit 0x79
		__emit 0x13
		__emit 0x81
		__emit 0xe3
		__emit 0x7f
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x02
		__emit 0x5d
		__emit 0x32
		__emit 0x00
		__emit 0xf6
		__emit 0xc3
		__emit 0x40
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x10
		__emit 0x83
		__emit 0xe3
		__emit 0xbf
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0xe9
		__emit 0x5c
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0xbc
		__emit 0xfb
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x5b
		__emit 0x6f
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0x51
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x25
		__emit 0xe8
		__emit 0x60
		__emit 0xca
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x1c
		__emit 0x52
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x0a
		__emit 0x60
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x22
		__emit 0xe8
		__emit 0xac
		__emit 0x5c
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x9b
		__emit 0x5c
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xb8
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x3a
		__emit 0x50
		__emit 0xe8
		__emit 0xc5
		__emit 0x7e
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xc0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xf8
		__emit 0xff
		__emit 0x74
		__emit 0x29
		__emit 0x85
		__emit 0xc0
		__emit 0x8d
		__emit 0x8f
		__emit 0x60
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x0b
		__emit 0x6a
		__emit 0x01
		__emit 0xe8
		__emit 0x3e
		__emit 0xbd
		__emit 0xad
		__emit 0xff
		__emit 0x6a
		__emit 0x01
		__emit 0xeb
		__emit 0x09
		__emit 0x6a
		__emit 0x00
		__emit 0xe8
		__emit 0x33
		__emit 0xbd
		__emit 0xad
		__emit 0xff
		__emit 0x6a
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xac
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0xe8
		__emit 0xfc
		__emit 0x63
		__emit 0xae
		__emit 0xff
		__emit 0x8b
		__emit 0x87
		__emit 0x60
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x8f
		__emit 0x60
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xff
		__emit 0x50
		__emit 0x0c
		__emit 0xa1
		__emit 0xd4
		__emit 0x4a
		__emit 0x2f
		__emit 0x01
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x0b
		__emit 0x8b
		__emit 0x0d
		__emit 0xe8
		__emit 0x19
		__emit 0x2f
		__emit 0x01
		__emit 0xe8
		__emit 0xc6
		__emit 0x73
		__emit 0xac
		__emit 0xff
		__emit 0x83
		__emit 0xbf
		__emit 0x58
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x03
		__emit 0x0f
		__emit 0x85
		__emit 0x64
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0xa0
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x0f
		__emit 0x84
		__emit 0x1a
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x4d
		__emit 0x7e
		__emit 0xae
		__emit 0xff
		__emit 0x0f
		__emit 0xb6
		__emit 0xf0
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x83
		__emit 0xfe
		__emit 0xff
		__emit 0x0f
		__emit 0x84
		__emit 0x05
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x20
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xf6
		__emit 0xbd
		__emit 0x53
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0xbb
		__emit 0x54
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x74
		__emit 0x22
		__emit 0x68
		__emit 0x6c
		__emit 0xc7
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0xe8
		__emit 0x5c
		__emit 0x6e
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x88
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x81
		__emit 0xc9
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x04
		__emit 0xeb
		__emit 0x24
		__emit 0x68
		__emit 0x88
		__emit 0xba
		__emit 0x0e
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xe8
		__emit 0x3a
		__emit 0x6e
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x55
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x81
		__emit 0xc9
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x08
		__emit 0x89
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x50
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0xe8
		__emit 0xe6
		__emit 0x5e
		__emit 0x32
		__emit 0x00
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x30
		__emit 0x8b
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xf7
		__emit 0xc3
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x08
		__emit 0x74
		__emit 0x13
		__emit 0x81
		__emit 0xe3
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xf7
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x1c
		__emit 0x89
		__emit 0x5c
		__emit 0x24
		__emit 0x10
		__emit 0xe8
		__emit 0x73
		__emit 0x5b
		__emit 0x32
		__emit 0x00
		__emit 0xf7
		__emit 0xc3
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x04
		__emit 0x89
		__emit 0x6c
		__emit 0x24
		__emit 0x30
		__emit 0x74
		__emit 0x09
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x18
		__emit 0xe8
		__emit 0x5e
		__emit 0x5b
		__emit 0x32
		__emit 0x00
		__emit 0x68
		__emit 0x4c
		__emit 0xfa
		__emit 0x07
		__emit 0x01
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x14
		__emit 0xe8
		__emit 0xd0
		__emit 0x6d
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0x51
		__emit 0x8d
		__emit 0x8f
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x56
		__emit 0xe8
		__emit 0xd5
		__emit 0xc8
		__emit 0xad
		__emit 0xff
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x20
		__emit 0x52
		__emit 0x8b
		__emit 0xc8
		__emit 0xe8
		__emit 0x7f
		__emit 0x5e
		__emit 0x32
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x10
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x53
		__emit 0xe8
		__emit 0x21
		__emit 0x5b
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xc8
		__emit 0xd5
		__emit 0x2e
		__emit 0x01
		__emit 0x85
		__emit 0xf6
		__emit 0x0f
		__emit 0x95
		__emit 0xc0
		__emit 0x88
		__emit 0x81
		__emit 0x07
		__emit 0x0c
		__emit 0x00
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0xff
		__emit 0x5a
		__emit 0x32
		__emit 0x00
		__emit 0x8b
		__emit 0x87
		__emit 0x8c
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x32
		__emit 0x8d
		__emit 0x54
		__emit 0x24
		__emit 0x14
		__emit 0x52
		__emit 0x50
		__emit 0xe8
		__emit 0x04
		__emit 0x99
		__emit 0xad
		__emit 0xff
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x1c
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x85
		__emit 0xc0
		__emit 0x7c
		__emit 0x1c
		__emit 0x50
		__emit 0x8b
		__emit 0x87
		__emit 0x8c
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x03
		__emit 0x9b
		__emit 0xad
		__emit 0xff
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x50
		__emit 0x8d
		__emit 0x8f
		__emit 0x60
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x82
		__emit 0xae
		__emit 0xac
		__emit 0xff
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x28
		__emit 0x5f
		__emit 0x5e
		__emit 0x5d
		__emit 0x64
		__emit 0x89
		__emit 0x0d
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x5b
		__emit 0x83
		__emit 0xc4
		__emit 0x24
		__emit 0xc2
		__emit 0x04
		__emit 0x00
		__emit 0x8b
		__emit 0xff
		__emit 0xde
		__emit 0x0f
		__emit 0x96
		__emit 0x00
		__emit 0xe2
		__emit 0x0f
		__emit 0x96
		__emit 0x00
		__emit 0xe6
		__emit 0x0f
		__emit 0x96
		__emit 0x00
		__emit 0xea
		__emit 0x0f
		__emit 0x96
		__emit 0x00
		__emit 0xee
		__emit 0x0f
		__emit 0x96
		__emit 0x00
		__emit 0xf1
		__emit 0x0f
		__emit 0x96
		__emit 0x00
	}
#if 0
	ignoreSelected = TRUE;
	if (TheGameEngine->getQuitting())
		return;
	OptionsLayout = layout;
	if (!pref)
	{
		pref = NEW OptionPreferences;
	}

	SignalUIInteraction(SHELL_SCRIPT_HOOK_OPTIONS_OPENED);

	comboBoxLANIPID				 = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ComboBoxIP" ) );
	comboBoxLANIP					 = TheWindowManager->winGetWindowFromId( NULL,  comboBoxLANIPID);
	comboBoxOnlineIPID		 = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ComboBoxOnlineIP" ) );
	comboBoxOnlineIP			 = TheWindowManager->winGetWindowFromId( NULL,  comboBoxOnlineIPID);
	checkAlternateMouseID  = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckAlternateMouse" ) );
	checkAlternateMouse	   = TheWindowManager->winGetWindowFromId( NULL, checkAlternateMouseID);
	checkRetaliationID		 = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:Retaliation" ) );
	checkRetaliation	     = TheWindowManager->winGetWindowFromId( NULL, checkRetaliationID);
	checkDoubleClickAttackMoveID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckDoubleClickAttackMove" ) );
	checkDoubleClickAttackMove   = TheWindowManager->winGetWindowFromId( NULL, checkDoubleClickAttackMoveID );
	sliderScrollSpeedID	   = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:SliderScrollSpeed" ) );
	sliderScrollSpeed		   = TheWindowManager->winGetWindowFromId( NULL,  sliderScrollSpeedID);
	comboBoxAntiAliasingID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ComboBoxAntiAliasing" ) );
	comboBoxAntiAliasing   = TheWindowManager->winGetWindowFromId( NULL, comboBoxAntiAliasingID );
	comboBoxResolutionID   = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ComboBoxResolution" ) );
	comboBoxResolution     = TheWindowManager->winGetWindowFromId( NULL, comboBoxResolutionID );
	comboBoxDetailID			 = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ComboBoxDetail" ) );
	comboBoxDetail		   = TheWindowManager->winGetWindowFromId( NULL, comboBoxDetailID );

	checkLanguageFilterID  = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckLanguageFilter" ) );
	checkLanguageFilter    = TheWindowManager->winGetWindowFromId( NULL, checkLanguageFilterID );
	checkSendDelayID       = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckSendDelay" ) );
	checkSendDelay				 = TheWindowManager->winGetWindowFromId( NULL, checkSendDelayID);
	buttonFirewallRefreshID	= TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ButtonFirewallRefresh" ) );
	buttonFirewallRefresh		= TheWindowManager->winGetWindowFromId( NULL, buttonFirewallRefreshID);
	checkDrawAnchorID       = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckBoxDrawAnchor" ) );
	checkDrawAnchor				 = TheWindowManager->winGetWindowFromId( NULL, checkDrawAnchorID);
	checkMoveAnchorID       = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckBoxMoveAnchor" ) );
	checkMoveAnchor				 = TheWindowManager->winGetWindowFromId( NULL, checkMoveAnchorID);

	// Replay camera
	checkSaveCameraID      = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckBoxSaveCamera" ) );
	checkSaveCamera        = TheWindowManager->winGetWindowFromId( NULL, checkSaveCameraID );
	checkUseCameraID       = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckBoxUseCamera" ) );
	checkUseCamera         = TheWindowManager->winGetWindowFromId( NULL, checkUseCameraID );

//	// Speakers and 3-D Audio
//	checkAudioSurroundID   = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckAudioSurround" ) );
//	checkAudioSurround     = TheWindowManager->winGetWindowFromId( NULL, checkAudioSurroundID );
//	checkAudioHardwareID   = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckAudioHardware" ) );
//	checkAudioHardware     = TheWindowManager->winGetWindowFromId( NULL, checkAudioHardwareID );
//
	// Volume Controls
	sliderMusicVolumeID    = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:SliderMusicVolume" ) );
	sliderMusicVolume      = TheWindowManager->winGetWindowFromId( NULL, sliderMusicVolumeID );
	sliderSFXVolumeID      = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:SliderSFXVolume" ) );
	sliderSFXVolume        = TheWindowManager->winGetWindowFromId( NULL, sliderSFXVolumeID );
	sliderVoiceVolumeID    = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:SliderVoiceVolume" ) );
	sliderVoiceVolume      = TheWindowManager->winGetWindowFromId( NULL, sliderVoiceVolumeID );
 	sliderGammaID    = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:SliderGamma" ) );
 	sliderGamma      = TheWindowManager->winGetWindowFromId( NULL, sliderGammaID );

//	checkBoxLowTextureDetailID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckLowTextureDetail" ) );
//	checkBoxLowTextureDetail      = TheWindowManager->winGetWindowFromId( NULL, checkBoxLowTextureDetailID );
	
	WinAdvancedDisplayID		= TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:WinAdvancedDisplayOptions" ) );
	WinAdvancedDisplay      = TheWindowManager->winGetWindowFromId( NULL, WinAdvancedDisplayID );

	ButtonAdvancedAcceptID		= TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ButtonAdvanceAccept" ) );
	ButtonAdvancedAccept      = TheWindowManager->winGetWindowFromId( NULL, ButtonAdvancedAcceptID );

	ButtonAdvancedCancelID		= TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ButtonAdvanceBack" ) );
	ButtonAdvancedCancel      = TheWindowManager->winGetWindowFromId( NULL, ButtonAdvancedCancelID );

	sliderTextureResolutionID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:LowResSlider" ) );
	sliderTextureResolution = TheWindowManager->winGetWindowFromId( NULL, sliderTextureResolutionID );

	check3DShadowsID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:Check3DShadows" ) );
	check3DShadows   = TheWindowManager->winGetWindowFromId( NULL, check3DShadowsID);

	check2DShadowsID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:Check2DShadows" ) );
	check2DShadows   = TheWindowManager->winGetWindowFromId( NULL, check2DShadowsID);

	checkCloudShadowsID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckCloudShadows" ) );
	checkCloudShadows   = TheWindowManager->winGetWindowFromId( NULL, checkCloudShadowsID);

	checkGroundLightingID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckGroundLighting" ) );
	checkGroundLighting   = TheWindowManager->winGetWindowFromId( NULL, checkGroundLightingID);

	checkSmoothWaterID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckSmoothWater" ) );
	checkSmoothWater   = TheWindowManager->winGetWindowFromId( NULL, checkSmoothWaterID);

	checkExtraAnimationsID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckExtraAnimations" ) );
	checkExtraAnimations   = TheWindowManager->winGetWindowFromId( NULL, checkExtraAnimationsID);

	checkNoDynamicLodID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckNoDynamicLOD" ) );
	checkNoDynamicLod   = TheWindowManager->winGetWindowFromId( NULL, checkNoDynamicLodID);

	checkHeatEffectsID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckHeatEffects" ) );
	checkHeatEffects   = TheWindowManager->winGetWindowFromId( NULL, checkHeatEffectsID);

	checkUnlockFpsID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckUnlockFPS" ) );
	checkUnlockFps   = TheWindowManager->winGetWindowFromId( NULL, checkUnlockFpsID);

	checkBuildingOcclusionID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckBehindBuilding" ) );
	checkBuildingOcclusion   = TheWindowManager->winGetWindowFromId( NULL, checkBuildingOcclusionID);

	checkPropsID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:CheckShowProps" ) );
	checkProps   = TheWindowManager->winGetWindowFromId( NULL, checkPropsID);

	sliderParticleCapID = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ParticleCapSlider" ) );
  sliderParticleCap = TheWindowManager->winGetWindowFromId( NULL, sliderParticleCapID );

	WinAdvancedDisplay->winHide(TRUE);

	Color color =  GameMakeColor(255,255,255,255);

  enum AliasingMode
  {
    OFF = 0,
    LOW,
    HIGH,
    NUM_ALIASING_MODES
  };

	NameKeyType versionID = TheNameKeyGenerator->nameToKey( AsciiString("OptionsMenu.wnd:LabelVersion") );
	GameWindow *labelVersion = TheWindowManager->winGetWindowFromId( NULL, versionID );
	UnicodeString versionString;
	versionString.format(TheGameText->fetch("Version:Format2").str(), (GetRegistryVersion() >> 16), (GetRegistryVersion() & 0xffff));
	
	if (TheVersion->showFullVersion())
	{
		if (TheVersion)
		{
			UnicodeString version;
			version.format(L"(%s) %s -- %s", versionString.str(), TheVersion->getFullUnicodeVersion().str(), TheVersion->getUnicodeBuildTime().str());
			GadgetStaticTextSetText( labelVersion, version );
		}
		else
		{
			labelVersion->winHide( TRUE );
		}
	}
	else
	{
		GadgetStaticTextSetText( labelVersion, versionString );
	}


	// Choose an IP address, then initialize the IP combo box
	UnsignedInt selectedIP = pref->getLANIPAddress();

	UnicodeString str;
	IPEnumeration IPs;
	EnumeratedIP *IPlist = IPs.getAddresses();
	Int index;
	Int selectedIndex = -1;
	Int count = 0;
	GadgetComboBoxReset(comboBoxLANIP);
	while (IPlist)
	{
		count++;
		str.translate(IPlist->getIPstring());
		index = GadgetComboBoxAddEntry(comboBoxLANIP, str, color);
		GadgetComboBoxSetItemData(comboBoxLANIP, index, (void *)(IPlist->getIP()));
		if (selectedIP == IPlist->getIP())
		{
			selectedIndex = index;
		}
		IPlist = IPlist->getNext();
	}
	if (selectedIndex >= 0)
	{
		GadgetComboBoxSetSelectedPos(comboBoxLANIP, selectedIndex);
	}
	else
	{
		GadgetComboBoxSetSelectedPos(comboBoxLANIP, 0);
		if (IPs.getAddresses())
		{
			pref->setLANIPAddress(IPs.getAddresses()->getIPstring());
		}
	}

	// And now the GameSpy one
	if (comboBoxOnlineIP)
	{
		UnsignedInt selectedIP = pref->getOnlineIPAddress();
		UnicodeString str;
		IPEnumeration IPs;
		EnumeratedIP *IPlist = IPs.getAddresses();
		Int index;
		Int selectedIndex = -1;
		Int count = 0;
		GadgetComboBoxReset(comboBoxOnlineIP);
		while (IPlist)
		{
			count++;
			str.translate(IPlist->getIPstring());
			index = GadgetComboBoxAddEntry(comboBoxOnlineIP, str, color);
			GadgetComboBoxSetItemData(comboBoxOnlineIP, index, (void *)(IPlist->getIP()));
			if (selectedIP == IPlist->getIP())
			{
				selectedIndex = index;
			}
			IPlist = IPlist->getNext();
		}
		if (selectedIndex >= 0)
		{
			GadgetComboBoxSetSelectedPos(comboBoxOnlineIP, selectedIndex);
		}
		else
		{
			GadgetComboBoxSetSelectedPos(comboBoxOnlineIP, 0);
			if (IPs.getAddresses())
			{
				pref->setOnlineIPAddress(IPs.getAddresses()->getIPstring());
			}
		}
	}

	// HTTP Proxy
	GameWindow *textEntryHTTPProxy = TheWindowManager->winGetWindowFromId(NULL, NAMEKEY("OptionsMenu.wnd:TextEntryHTTPProxy"));
	if (textEntryHTTPProxy)
	{
		UnicodeString uStr;
		std::string proxy;
		GetStringFromRegistry("", "Proxy", proxy);
		uStr.translate(proxy.c_str());
		GadgetTextEntrySetText(textEntryHTTPProxy, uStr);
	}

	// Firewall Port Override
	GameWindow *textEntryFirewallPortOverride = TheWindowManager->winGetWindowFromId(NULL, NAMEKEY("OptionsMenu.wnd:TextEntryFirewallPortOverride"));
	if (textEntryFirewallPortOverride)
	{
			UnicodeString uStr;
			if (TheGlobalData->m_firewallPortOverride != 0)
			{	AsciiString aStr;
				aStr.format("%d",TheGlobalData->m_firewallPortOverride);
				uStr.translate(aStr);
			}
			GadgetTextEntrySetText(textEntryFirewallPortOverride,uStr);
	}

	// populate anti aliasing modes
	AsciiString selectedAliasingMode = (*pref)["AntiAliasing"];
	GadgetComboBoxReset(comboBoxAntiAliasing);
	AsciiString temp;
	for (Int i=0; i < NUM_ALIASING_MODES; ++i)
	{
		temp.format("GUI:AntiAliasing%d", i);
		str = TheGameText->fetch( temp );
		index = GadgetComboBoxAddEntry(comboBoxAntiAliasing, str, color);
	}
	Int val = atoi(selectedAliasingMode.str());
	if( val < 0 || val > NUM_ALIASING_MODES )
	{
		TheWritableGlobalData->m_antiAliasBoxValue = val = 0;
	}
	GadgetComboBoxSetSelectedPos(comboBoxAntiAliasing, val);

	// get resolution from saved preferences file
	AsciiString selectedResolution = (*pref) ["Resolution"];
	Int selectedXRes=800,selectedYRes=600;
	Int selectedResIndex=-1;
	Int defaultResIndex=0;	//index of default video mode that should always exist
	if (!selectedResolution.isEmpty())
	{	//try to parse 2 integers out of string
		if (sscanf(selectedResolution.str(),"%d%d", &selectedXRes, &selectedYRes) != 2)
		{	selectedXRes=800; selectedYRes=600;
		}
	}

	// populate resolution modes
	GadgetComboBoxReset(comboBoxResolution);
	Int numResolutions = TheDisplay->getDisplayModeCount();
	for( i = 0; i < numResolutions; ++i )
	{	Int xres,yres,bitDepth;
		TheDisplay->getDisplayModeDescription(i,&xres,&yres,&bitDepth);
		str.format(L"%d x %d",xres,yres);
		GadgetComboBoxAddEntry( comboBoxResolution, str, color);
		if (xres == 800 && yres == 600)	//keep track of default mode in case we need it.
			defaultResIndex=i;
		if (xres == selectedXRes && yres == selectedYRes)
			selectedResIndex=i;
	}

	if (selectedResIndex == -1)	//check if saved mode no longer available
	{	//pick default resolution
		selectedXRes = 800;
		selectedXRes = 600;
		selectedResIndex = defaultResIndex;
	}

	TheWritableGlobalData->m_xResolution = selectedXRes;
	TheWritableGlobalData->m_yResolution = selectedYRes;

	GadgetComboBoxSetSelectedPos( comboBoxResolution, selectedResIndex );

	// set the display detail
	GadgetComboBoxReset(comboBoxDetail);
	GadgetComboBoxAddEntry(comboBoxDetail, TheGameText->fetch("GUI:High"), color);
	GadgetComboBoxAddEntry(comboBoxDetail, TheGameText->fetch("GUI:Medium"), color);
	GadgetComboBoxAddEntry(comboBoxDetail, TheGameText->fetch("GUI:Low"), color);
	GadgetComboBoxAddEntry(comboBoxDetail, TheGameText->fetch("GUI:Custom"), color);

	//Check if level was never set and default to setting most suitable for system.
	if (TheGameLODManager->getStaticLODLevel() == STATIC_GAME_LOD_UNKNOWN)
		TheGameLODManager->setStaticLODLevel(TheGameLODManager->findStaticLODLevel());

	switch (TheGameLODManager->getStaticLODLevel())
	{
	case STATIC_GAME_LOD_LOW:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, LOWDETAIL);
		break;
	case STATIC_GAME_LOD_MEDIUM:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, MEDIUMDETAIL);
		break;
	case STATIC_GAME_LOD_HIGH:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, HIGHDETAIL);
		break;
	case STATIC_GAME_LOD_CUSTOM:
		GadgetComboBoxSetSelectedPos(comboBoxDetail, CUSTOMDETAIL);
		break;
	default:
		DEBUG_ASSERTCRASH(FALSE,("Tried to set comboBoxDetail to a value of %d ", TheGameLODManager->getStaticLODLevel()) );
	};

	Int txtFact=TheGameLODManager->getCurrentTextureReduction();

	GadgetSliderSetPosition( sliderTextureResolution, 2-txtFact);

	GadgetCheckBoxSetChecked( check3DShadows, TheGlobalData->m_useShadowVolumes);

	GadgetCheckBoxSetChecked( check2DShadows, TheGlobalData->m_useShadowDecals);

	GadgetCheckBoxSetChecked( checkCloudShadows, TheGlobalData->m_useCloudMap);

	GadgetCheckBoxSetChecked( checkGroundLighting, TheGlobalData->m_useLightMap);

	GadgetCheckBoxSetChecked( checkSmoothWater, TheGlobalData->m_showSoftWaterEdge);

	GadgetCheckBoxSetChecked( checkExtraAnimations, !TheGlobalData->m_useDrawModuleLOD);

	GadgetCheckBoxSetChecked( checkNoDynamicLod, !TheGlobalData->m_enableDynamicLOD);

	GadgetCheckBoxSetChecked( checkHeatEffects, TheGlobalData->m_useHeatEffects);

	GadgetCheckBoxSetChecked( checkUnlockFps, !TheGlobalData->m_useFpsLimit);

	GadgetCheckBoxSetChecked( checkBuildingOcclusion, TheGlobalData->m_enableBehindBuildingMarkers);

	GadgetCheckBoxSetChecked( checkProps, TheGlobalData->m_useTrees);
	//checkProps->winEnable(false);	//gray out the option for now.

	GadgetSliderSetPosition( sliderParticleCap, TheGlobalData->m_maxParticleCount );

	//set language filter
	AsciiString languageFilter = (*pref)["LanguageFilter"];
	if (languageFilter == "true" )
	{
		GadgetCheckBoxSetChecked( checkLanguageFilter, true);
		TheWritableGlobalData->m_languageFilterPref = true;
	}
	else
	{
		GadgetCheckBoxSetChecked( checkLanguageFilter, false);
		TheWritableGlobalData->m_languageFilterPref = false;
	}
	
	//set replay camera
	if (pref->saveCameraInReplays())
	{
		GadgetCheckBoxSetChecked( checkSaveCamera, true);
		TheWritableGlobalData->m_saveCameraInReplay = true;
	}
	else
	{
		GadgetCheckBoxSetChecked( checkSaveCamera, false);
		TheWritableGlobalData->m_saveCameraInReplay = false;
	}
	if (pref->useCameraInReplays())
	{
		GadgetCheckBoxSetChecked( checkUseCamera, true);
		TheWritableGlobalData->m_useCameraInReplay = true;
	}
	else
	{
		GadgetCheckBoxSetChecked( checkUseCamera, false);
		TheWritableGlobalData->m_useCameraInReplay = false;
	}

	//set scroll options
	AsciiString test = (*pref)["DrawScrollAnchor"];
	DEBUG_LOG(("DrawScrollAnchor == [%s]\n", test.str()));
	if (test == "Yes" || (test.isEmpty() && TheInGameUI->getDrawRMBScrollAnchor()))
	{
		GadgetCheckBoxSetChecked( checkDrawAnchor, true);
		TheInGameUI->setDrawRMBScrollAnchor(true);
	}
	else
	{
		GadgetCheckBoxSetChecked( checkDrawAnchor, false);
		TheInGameUI->setDrawRMBScrollAnchor(false);
	}
	test = (*pref)["MoveScrollAnchor"];
	DEBUG_LOG(("MoveScrollAnchor == [%s]\n", test.str()));
	if (test == "Yes" || (test.isEmpty() && TheInGameUI->getMoveRMBScrollAnchor()))
	{
		GadgetCheckBoxSetChecked( checkMoveAnchor, true);
		TheInGameUI->setMoveRMBScrollAnchor(true);
	}
	else
	{
		GadgetCheckBoxSetChecked( checkMoveAnchor, false);
		TheInGameUI->setMoveRMBScrollAnchor(false);
	}

//	// Audio Init shiznat
//	GadgetCheckBoxSetChecked(checkAudioHardware, TheAudio->getHardwareAccelerated());
//	GadgetCheckBoxSetChecked(checkAudioSurround, TheAudio->getSpeakerSurround());

	// set the mouse mode
	GadgetCheckBoxSetChecked(checkAlternateMouse, TheGlobalData->m_useAlternateMouse);
	GadgetCheckBoxSetChecked(checkRetaliation, TheGlobalData->m_clientRetaliationModeEnabled);
	GadgetCheckBoxSetChecked( checkDoubleClickAttackMove, TheGlobalData->m_doubleClickAttackMove );

	// set scroll speed slider
	Int scrollPos = (Int)(TheGlobalData->m_keyboardScrollFactor*100.0f);
	GadgetSliderSetPosition( sliderScrollSpeed, scrollPos );
	DEBUG_LOG(("Scroll SPeed %d\n", scrollPos));

	// set the send delay check box
	GadgetCheckBoxSetChecked(checkSendDelay, TheGlobalData->m_firewallSendDelay);

 	// set volume sliders

	// set music volume slider
	GadgetSliderSetPosition( sliderMusicVolume, REAL_TO_INT(pref->getMusicVolume()) );

	//set SFX volume slider
	Real maxVolume = MAX( pref->getSoundVolume(), pref->get3DSoundVolume() );
	GadgetSliderSetPosition( sliderSFXVolume, REAL_TO_INT( maxVolume ) );

	//set voice volume slider
	GadgetSliderSetPosition( sliderVoiceVolume, REAL_TO_INT(pref->getSpeechVolume()) );
	
	// set the gamma slider
 	GadgetSliderSetPosition( sliderGamma, REAL_TO_INT(pref->getGammaValue()) );

	// show menu
	layout->hide( FALSE );

	// set keyboard focus to main parent
	AsciiString parentName( "OptionsMenu.wnd:OptionsMenuParent" );
	NameKeyType parentID = TheNameKeyGenerator->nameToKey( parentName );
	GameWindow *parent = TheWindowManager->winGetWindowFromId( NULL, parentID );
	TheWindowManager->winSetFocus( parent );
	
	if( (TheGameLogic->isInGame() && TheGameLogic->getGameMode() != GAME_SHELL) || TheGameSpyInfo )
	{
		// disable controls that you can't change the options for in game
		comboBoxLANIP->winEnable(FALSE);
		if (comboBoxOnlineIP)
			comboBoxOnlineIP->winEnable(FALSE);
		checkSendDelay->winEnable(FALSE);
		buttonFirewallRefresh->winEnable(FALSE);

		if (comboBoxDetail)
			comboBoxDetail->winEnable(FALSE);


		if (comboBoxResolution)
			comboBoxResolution->winEnable(FALSE);

//		if (checkAudioSurround)
//			checkAudioSurround->winEnable(FALSE);
//
//		if (checkAudioHardware)
//			checkAudioHardware->winEnable(FALSE);
	}


	TheWindowManager->winSetModal(parent);
	ignoreSelected = FALSE;
#endif
}  // end OptionsMenuInit

//-------------------------------------------------------------------------------------------------
/** options menu shutdown method */
//-------------------------------------------------------------------------------------------------
void OptionsMenuShutdown( WindowLayout *layout, void *userData )
{
/* moved into the back button stuff
	if (pref)
	{
		pref->write();
		delete pref;
		pref = NULL;
	}

	comboBoxIP = NULL;

	// hide menu
	layout->hide( TRUE );

	// our shutdown is complete
	TheShell->shutdownComplete( layout );
*/

}  // end OptionsMenuShutdown

//-------------------------------------------------------------------------------------------------
/** options menu update method */
//-------------------------------------------------------------------------------------------------
void OptionsMenuUpdate( WindowLayout *layout, void *userData )
{

}  // end OptionsMenuUpdate

//-------------------------------------------------------------------------------------------------
/** Options menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType OptionsMenuInput( GameWindow *window, UnsignedInt msg,
																			 WindowMsgData mData1, WindowMsgData mData2 )
{

	switch( msg ) 
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;

			switch( key )
			{

				// ----------------------------------------------------------------------------------------
				case KEY_ESC:
				{
					
					//
					// send a simulated selected event to the parent window of the
					// back/exit button
					//
					if( BitTest( state, KEY_STATE_UP ) )
					{
						AsciiString buttonName( "OptionsMenu.wnd:ButtonBack" );
						NameKeyType buttonID = TheNameKeyGenerator->nameToKey( buttonName );
						GameWindow *button = TheWindowManager->winGetWindowFromId( window, buttonID );

						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED, 
																								(WindowMsgData)button, buttonID );

					}  // end if

					// don't let key fall through anywhere else
					return MSG_HANDLED;

				}  // end escape

			}  // end switch( key )

		}  // end char

	}  // end switch( msg )

	return MSG_IGNORED;

}  // end OptionsMenuInput

//-------------------------------------------------------------------------------------------------
/** options menu window system callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType OptionsMenuSystem( GameWindow *window, UnsignedInt msg, 
																				WindowMsgData mData1, WindowMsgData mData2 )
{
	static NameKeyType buttonBack = NAMEKEY_INVALID;
	static NameKeyType buttonDefaults = NAMEKEY_INVALID;
	static NameKeyType buttonAccept = NAMEKEY_INVALID;
	static NameKeyType buttonReplayMenu = NAMEKEY_INVALID;
	static NameKeyType buttonKeyboardOptionsMenu = NAMEKEY_INVALID;

	switch( msg ) 
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CREATE:
		{

			// get ids for our children controls
			buttonBack = TheNameKeyGenerator->nameToKey( AsciiString("OptionsMenu.wnd:ButtonBack") );
			buttonDefaults = TheNameKeyGenerator->nameToKey( AsciiString("OptionsMenu.wnd:ButtonDefaults") );
			buttonAccept = TheNameKeyGenerator->nameToKey( AsciiString("OptionsMenu.wnd:ButtonAccept") );
			buttonKeyboardOptionsMenu = TheNameKeyGenerator->nameToKey( AsciiString( "OptionsMenu.wnd:ButtonKeyboardOptions" ) );

			break;

		}  // end create

		//---------------------------------------------------------------------------------------------
		case GWM_DESTROY:
		{

			break;

		}  // end case

		// --------------------------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
		{

			// if we're givin the opportunity to take the keyboard focus we must say we want it
			if( mData1 == TRUE )
				*(Bool *)mData2 = TRUE;

			return MSG_HANDLED;

		}  // end input

		//---------------------------------------------------------------------------------------------
		case GCM_SELECTED:
			{
				if(ignoreSelected)
					break;
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
		
				if (controlID == comboBoxDetailID)
				{
					Int index;
					GadgetComboBoxGetSelectedPos( comboBoxDetail, &index );
					if(index != CUSTOMDETAIL)
						break;

					showAdvancedOptions();
				}
			break;
		}

		//---------------------------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			if(ignoreSelected)
				break;
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();

			if( controlID == buttonBack )
			{
				// go back one screen
				//TheShell->pop();
				if (pref)
				{
					delete pref;
					pref = NULL;
				}

				comboBoxLANIP = NULL;
				comboBoxOnlineIP = NULL;

				if(GameSpyIsOverlayOpen(GSOVERLAY_OPTIONS))
					GameSpyCloseOverlay(GSOVERLAY_OPTIONS);
				else
				{
					DestroyOptionsLayout();
				}

			}  // end if
			else if (controlID == buttonAccept )
			{
				saveOptions();

				if (pref)
				{
					pref->write();
					delete pref;
					pref = NULL;
				}

				comboBoxLANIP = NULL;
				comboBoxOnlineIP = NULL;
				
				if(!TheGameLogic->isInGame() || TheGameLogic->isInShellGame())
					destroyQuitMenu(); // if we're in a game, the change res then enter the same kind of game, we nee the quit menu to be gone.


				if(GameSpyIsOverlayOpen(GSOVERLAY_OPTIONS))
					GameSpyCloseOverlay(GSOVERLAY_OPTIONS);
				else
				{
					DestroyOptionsLayout();
					if (dispChanged)
					{
						DoResolutionDialog();
					}
				}

			}
			else if (controlID == buttonDefaults )
			{
				setDefaults();
			}
			else if (controlID == ButtonAdvancedAcceptID )
			{
				acceptAdvancedOptions();
				
			}
			else if (controlID == ButtonAdvancedCancelID )
			{	
				cancelAdvancedOptions();
			}
			else if ( controlID == buttonKeyboardOptionsMenu )
			{
				TheShell->push( AsciiString( "Menus/KeyboardOptionsMenu.wnd" ) );
			}
			else if(controlID == checkDrawAnchorID )
      {
        if( GadgetCheckBoxIsChecked( control ) )
        {
          	TheInGameUI->setDrawRMBScrollAnchor(true);
          	(*pref)["DrawScrollAnchor"] = "Yes";
        }
				else
        {
          	TheInGameUI->setDrawRMBScrollAnchor(false);
          	(*pref)["DrawScrollAnchor"] = "No";
        }
      }
			else if(controlID == checkMoveAnchorID )
      {
        if( GadgetCheckBoxIsChecked( control ) )
        {
          	TheInGameUI->setMoveRMBScrollAnchor(true);
          	(*pref)["MoveScrollAnchor"] = "Yes";
        }
				else
        {
          	TheInGameUI->setMoveRMBScrollAnchor(false);
          	(*pref)["MoveScrollAnchor"] = "No";
        }
      }
			else if(controlID == checkSaveCameraID )
      {
        if( GadgetCheckBoxIsChecked( control ) )
        {
          	TheWritableGlobalData->m_saveCameraInReplay = true;
          	(*pref)["SaveCameraInReplays"] = "yes";
        }
				else
        {
          	TheWritableGlobalData->m_saveCameraInReplay = false;
          	(*pref)["SaveCameraInReplays"] = "no";
        }
      }
			else if(controlID == checkUseCameraID )
      {
        if( GadgetCheckBoxIsChecked( control ) )
        {
          	TheWritableGlobalData->m_useCameraInReplay = true;
          	(*pref)["UseCameraInReplays"] = "yes";
        }
				else
        {
          	TheWritableGlobalData->m_useCameraInReplay = false;
          	(*pref)["UseCameraInReplays"] = "no";
        }
      }
			else if (controlID == buttonFirewallRefreshID)
			{
				// setting the behavior to unknown will force the firewall helper to detect the firewall behavior
				// the next time we log into gamespy/WOL/whatever.
				char num[16];
				num[0] = 0;
				TheWritableGlobalData->m_firewallBehavior = FirewallHelperClass::FIREWALL_TYPE_UNKNOWN;
				itoa(TheGlobalData->m_firewallBehavior, num, 10);
				AsciiString numstr;
				numstr = num;
				(*pref)["FirewallBehavior"] = numstr;
			}
			break;

		}  // end selected

		default:
			return MSG_IGNORED;

	}  // end switch

	return MSG_HANDLED;

}  // end OptionsMenuSystem
