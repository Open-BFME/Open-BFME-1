// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
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

// Retail [0x00480090,0x004827DF): complete GameWindowManager gadget-style initializer.
// Identity: the matched base/derived manager constructors install vtables
// 0x010F8B60/0x01126ED0; both slot25 (+0x64) entries route here. The Zero Hour
// body supplies the same gadget branches and image strings. See
// targets/game/reverse/identity_evidence/00480090.md for boundary/ABI evidence.
// BFME initializes IME white and its border through winMakeColor, applies them
// before the assignVisual guard, and stores DefaultWindowFont at +0xA0.
// The canonical string model reproduces retail's StringBase constructors.
// The existing gamewindow shim supplies the witnessed +0x30 instance data.

#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTabControl.h"
#include "GameClient/GadgetProgressBar.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GlobalLanguage.h"

// GlobalLanguage+0xA0 is m_defaultWindowFont in field_names.csv.
struct Rva00480090LanguageView
{
    char prefix[0xa0];
    FontDesc m_defaultWindowFont;
};

// Existing manager shim declares winFindFont nonvirtual. Retail vtable slot71
// reaches ILT0x0002668E -> matched winFindFont0x0047A190 (ret12).
class Rva00480090ManagerFontView
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual GameFont *winFindFont(AsciiString name, Int size, Bool bold);
};

void GameWindowManager::assignDefaultGadgetLook( GameWindow *gadget,
																								 GameFont *defaultFont,
																								 Bool assignVisual )
{
	UnsignedByte alpha = 255;
	static Color red				= TheWindowManager->winMakeColor( 255,   0,   0, alpha );
	static Color darkRed		= TheWindowManager->winMakeColor( 128,   0,   0, alpha );
	static Color lightRed		= TheWindowManager->winMakeColor( 255, 128, 128, alpha );
	static Color green			= TheWindowManager->winMakeColor(   0, 255,   0, alpha );
	static Color darkGreen	= TheWindowManager->winMakeColor(   0, 128,   0, alpha );
	static Color lightGreen	= TheWindowManager->winMakeColor( 128, 255, 128, alpha );
	static Color blue				= TheWindowManager->winMakeColor(   0,   0, 255, alpha );
	static Color darkBlue		= TheWindowManager->winMakeColor(   0,   0, 128, alpha );
	static Color lightBlue	= TheWindowManager->winMakeColor( 128, 128, 255, alpha );
	static Color purple			= TheWindowManager->winMakeColor( 255,   0, 255, alpha );
	static Color darkPurple	= TheWindowManager->winMakeColor( 128,   0, 128, alpha );
	static Color lightPurple= TheWindowManager->winMakeColor( 255, 128, 255, alpha );
	static Color yellow			= TheWindowManager->winMakeColor( 255, 255,   0, alpha );
	static Color darkYellow	= TheWindowManager->winMakeColor( 128, 128,   0, alpha );
	static Color lightYellow= TheWindowManager->winMakeColor( 255, 255, 128, alpha );
	static Color cyan				= TheWindowManager->winMakeColor(   0, 255, 255, alpha );
	static Color darkCyan		= TheWindowManager->winMakeColor(  64, 128, 128, alpha );
	static Color lightCyan	= TheWindowManager->winMakeColor( 128, 255, 255, alpha );
	static Color gray				= TheWindowManager->winMakeColor( 128, 128, 128, alpha );
	static Color darkGray		= TheWindowManager->winMakeColor(  64,  64,  64, alpha );
	static Color lightGray	= TheWindowManager->winMakeColor( 192, 192, 192, alpha );
	static Color black			= TheWindowManager->winMakeColor(   0,   0,   0, alpha );
	static Color white			= TheWindowManager->winMakeColor( 254, 254, 254, alpha );
	static Color enabledText					= white;
	static Color enabledTextBorder		= darkGray;
	static Color disabledText					= darkGray;
	static Color disabledTextBorder		= black;
	static Color hiliteText						= lightBlue;
	static Color hiliteTextBorder			= blue;
	static Color imeCompositeText				= TheWindowManager->winMakeColor( 255, 255, 255, alpha );
	static Color imeCompositeTextBorder	= TheWindowManager->winMakeColor( 205, 136, 60, alpha );
	WinInstanceData *instData;

	// sanity
	if( gadget == NULL )
		return;

	// get instance data
	instData = gadget->winGetInstanceData();

	// set default font
	if( defaultFont )
		gadget->GameWindow::winSetFont( defaultFont );
	else
	{
		Rva00480090LanguageView *language = reinterpret_cast<Rva00480090LanguageView *>(TheGlobalLanguageData);
		if (language && language->m_defaultWindowFont.name.isNotEmpty())
		{		gadget->GameWindow::winSetFont( reinterpret_cast<Rva00480090ManagerFontView *>(TheWindowManager)->winFindFont(
				language->m_defaultWindowFont.name,
				language->m_defaultWindowFont.size,
				language->m_defaultWindowFont.bold) );
		}
		else
			gadget->GameWindow::winSetFont( reinterpret_cast<Rva00480090ManagerFontView *>(TheWindowManager)->winFindFont( AsciiString("Times New Roman"), 14, FALSE ) );
	}

	gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	// if we don't want to assign default colors/images get out of here
	if( assignVisual == FALSE )
		return;

	// create images for the correct gadget type
	if( BitTest( instData->getStyle(), GWS_PUSH_BUTTON ) )
	{

		// enabled background
		GadgetButtonSetEnabledImage( gadget, winFindImage( "PushButtonEnabled" ) );
		GadgetButtonSetEnabledColor( gadget, red );
		GadgetButtonSetEnabledBorderColor( gadget, lightRed );
		// enabled selected button
		GadgetButtonSetEnabledSelectedImage( gadget, winFindImage( "PushButtonEnabledSelected" ) );
		GadgetButtonSetEnabledSelectedColor( gadget, yellow );
		GadgetButtonSetEnabledSelectedBorderColor( gadget, white );

		// Disabled background
		GadgetButtonSetDisabledImage( gadget, winFindImage( "PushButtonDisabled" ) );
		GadgetButtonSetDisabledColor( gadget, gray );
		GadgetButtonSetDisabledBorderColor( gadget, lightGray );
		// Disabled selected button
		GadgetButtonSetDisabledSelectedImage( gadget, winFindImage( "PushButtonDisabledSelected" ) );
		GadgetButtonSetDisabledSelectedColor( gadget, lightGray );
		GadgetButtonSetDisabledSelectedBorderColor( gadget, gray );

		// Hilite background
		GadgetButtonSetHiliteImage( gadget, winFindImage( "PushButtonHilite" ) );
		GadgetButtonSetHiliteColor( gadget, green );
		GadgetButtonSetHiliteBorderColor( gadget, darkGreen );
		// Hilite selected button
		GadgetButtonSetHiliteSelectedImage( gadget, winFindImage( "PushButtonHiliteSelected" ) );
		GadgetButtonSetHiliteSelectedColor( gadget, yellow );
		GadgetButtonSetHiliteSelectedBorderColor( gadget, white );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end if
	else if( BitTest( instData->getStyle(), GWS_CHECK_BOX ) )
	{

		// enabled background
		GadgetCheckBoxSetEnabledImage( gadget, winFindImage( "CheckBoxEnabled" ) );
		GadgetCheckBoxSetEnabledColor( gadget, red );
		GadgetCheckBoxSetEnabledBorderColor( gadget, lightRed );
		// enabled CheckBox unselected
		GadgetCheckBoxSetEnabledUncheckedBoxImage( gadget, winFindImage( "CheckBoxEnabledBoxUnselected" ) );
		GadgetCheckBoxSetEnabledUncheckedBoxColor( gadget, WIN_COLOR_UNDEFINED );
		GadgetCheckBoxSetEnabledUncheckedBoxBorderColor( gadget, lightBlue );
		// enabled CheckBox selected
		GadgetCheckBoxSetEnabledCheckedBoxImage( gadget, winFindImage( "CheckBoxEnabledBoxSelected" ) );
		GadgetCheckBoxSetEnabledCheckedBoxColor( gadget, blue );
		GadgetCheckBoxSetEnabledCheckedBoxBorderColor( gadget, lightBlue );

		// disabled background
		GadgetCheckBoxSetDisabledImage( gadget, winFindImage( "CheckBoxDisabled" ) );
		GadgetCheckBoxSetDisabledColor( gadget, gray );
		GadgetCheckBoxSetDisabledBorderColor( gadget, lightGray );
		// Disabled CheckBox unselected
		GadgetCheckBoxSetDisabledUncheckedBoxImage( gadget, winFindImage( "CheckBoxDisabledBoxUnselected" ) );
		GadgetCheckBoxSetDisabledUncheckedBoxColor( gadget, WIN_COLOR_UNDEFINED );
		GadgetCheckBoxSetDisabledUncheckedBoxBorderColor( gadget, lightGray );
		// Disabled CheckBox selected
		GadgetCheckBoxSetDisabledCheckedBoxImage( gadget, winFindImage( "CheckBoxDisabledBoxSelected" ) );
		GadgetCheckBoxSetDisabledCheckedBoxColor( gadget, darkGray );
		GadgetCheckBoxSetDisabledCheckedBoxBorderColor( gadget, white );

		// Hilite background
		GadgetCheckBoxSetHiliteImage( gadget, winFindImage( "CheckBoxHilite" ) );
		GadgetCheckBoxSetHiliteColor( gadget, green );
		GadgetCheckBoxSetHiliteBorderColor( gadget, lightGreen );
		// Hilite CheckBox unselected
		GadgetCheckBoxSetHiliteUncheckedBoxImage( gadget, winFindImage( "CheckBoxHiliteBoxUnselected" ) );
		GadgetCheckBoxSetHiliteUncheckedBoxColor( gadget, WIN_COLOR_UNDEFINED );
		GadgetCheckBoxSetHiliteUncheckedBoxBorderColor( gadget, lightBlue );
		// Hilite CheckBox selected
		GadgetCheckBoxSetHiliteCheckedBoxImage( gadget, winFindImage( "CheckBoxHiliteBoxSelected" ) );
		GadgetCheckBoxSetHiliteCheckedBoxColor( gadget, yellow );
		GadgetCheckBoxSetHiliteCheckedBoxBorderColor( gadget, white );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_RADIO_BUTTON ) )
	{

		// enabled background
		GadgetRadioSetEnabledImage( gadget, winFindImage( "RadioButtonEnabled" ) );
		GadgetRadioSetEnabledColor( gadget, red );
		GadgetRadioSetEnabledBorderColor( gadget, lightRed );
		// enabled radio unselected
		GadgetRadioSetEnabledUncheckedBoxImage( gadget, winFindImage( "RadioButtonEnabledBoxUnselected" ) );
		GadgetRadioSetEnabledUncheckedBoxColor( gadget, darkRed );
		GadgetRadioSetEnabledUncheckedBoxBorderColor( gadget, black );
		// enabled radio selected
		GadgetRadioSetEnabledCheckedBoxImage( gadget, winFindImage( "RadioButtonEnabledBoxSelected" ) );
		GadgetRadioSetEnabledCheckedBoxColor( gadget, blue );
		GadgetRadioSetEnabledCheckedBoxBorderColor( gadget, lightBlue );

		// disabled background
		GadgetRadioSetDisabledImage( gadget, winFindImage( "RadioButtonDisabled" ) );
		GadgetRadioSetDisabledColor( gadget, gray );
		GadgetRadioSetDisabledBorderColor( gadget, lightGray );
		// Disabled radio unselected
		GadgetRadioSetDisabledUncheckedBoxImage( gadget, winFindImage( "RadioButtonDisabledBoxUnselected" ) );
		GadgetRadioSetDisabledUncheckedBoxColor( gadget, gray );
		GadgetRadioSetDisabledUncheckedBoxBorderColor( gadget, lightGray );
		// Disabled radio selected
		GadgetRadioSetDisabledCheckedBoxImage( gadget, winFindImage( "RadioButtonDisabledBoxSelected" ) );
		GadgetRadioSetDisabledCheckedBoxColor( gadget, darkGray );
		GadgetRadioSetDisabledCheckedBoxBorderColor( gadget, white );

		// Hilite background
		GadgetRadioSetHiliteImage( gadget, winFindImage( "RadioButtonHilite" ) );
		GadgetRadioSetHiliteColor( gadget, green );
		GadgetRadioSetHiliteBorderColor( gadget, lightGreen );
		// Hilite radio unselected
		GadgetRadioSetHiliteUncheckedBoxImage( gadget, winFindImage( "RadioButtonHiliteBoxUnselected" ) );
		GadgetRadioSetHiliteUncheckedBoxColor( gadget, darkGreen );
		GadgetRadioSetHiliteUncheckedBoxBorderColor( gadget, lightGreen );
		// Hilite radio selected
		GadgetRadioSetHiliteCheckedBoxImage( gadget, winFindImage( "RadioButtonHiliteBoxSelected" ) );
		GadgetRadioSetHiliteCheckedBoxColor( gadget, yellow );
		GadgetRadioSetHiliteCheckedBoxBorderColor( gadget, white );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_HORZ_SLIDER ) )
	{

		// enabled
		GadgetSliderSetEnabledImageLeft( gadget, winFindImage( "HSliderEnabledLeftEnd" ) );
		GadgetSliderSetEnabledImageRight( gadget, winFindImage( "HSliderEnabledRightEnd" ) );
		GadgetSliderSetEnabledImageCenter( gadget, winFindImage( "HSliderEnabledRepeatingCenter" ) );
		GadgetSliderSetEnabledImageSmallCenter( gadget, winFindImage( "HSliderEnabledSmallRepeatingCenter" ) );
		GadgetSliderSetEnabledColor( gadget, red );
		GadgetSliderSetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetSliderSetDisabledImageLeft( gadget, winFindImage( "HSliderDisabledLeftEnd" ) );
		GadgetSliderSetDisabledImageRight( gadget, winFindImage( "HSliderDisabledRightEnd" ) );
		GadgetSliderSetDisabledImageCenter( gadget, winFindImage( "HSliderDisabledRepeatingCenter" ) );
		GadgetSliderSetDisabledImageSmallCenter( gadget, winFindImage( "HSliderDisabledSmallRepeatingCenter" ) );
		GadgetSliderSetDisabledColor( gadget, red );
		GadgetSliderSetDisabledBorderColor( gadget, lightRed );

		// hilite
		GadgetSliderSetHiliteImageLeft( gadget, winFindImage( "HSliderHiliteLeftEnd" ) );
		GadgetSliderSetHiliteImageRight( gadget, winFindImage( "HSliderHiliteRightEnd" ) );
		GadgetSliderSetHiliteImageCenter( gadget, winFindImage( "HSliderHiliteRepeatingCenter" ) );
		GadgetSliderSetHiliteImageSmallCenter( gadget, winFindImage( "HSliderHiliteSmallRepeatingCenter" ) );
		GadgetSliderSetHiliteColor( gadget, red );
		GadgetSliderSetHiliteBorderColor( gadget, lightRed );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

		//
		// set the default colors and images for the slider thumb
		//
		// enabled
		GadgetSliderSetEnabledThumbImage( gadget, winFindImage( "HSliderThumbEnabled" ) );
		GadgetSliderSetEnabledThumbColor( gadget, GadgetSliderGetEnabledColor( gadget ) );
		GadgetSliderSetEnabledThumbBorderColor( gadget, GadgetSliderGetEnabledBorderColor( gadget ) );
		GadgetSliderSetEnabledSelectedThumbImage( gadget, winFindImage( "HSliderThumbEnabled" ) );
		GadgetSliderSetEnabledSelectedThumbColor( gadget, GadgetSliderGetEnabledBorderColor( gadget ) );
		GadgetSliderSetEnabledSelectedThumbBorderColor( gadget, GadgetSliderGetEnabledColor( gadget ) );

		// disabled
		GadgetSliderSetDisabledThumbImage( gadget, winFindImage( "HSliderThumbDisabled" ) );
		GadgetSliderSetDisabledThumbColor( gadget, GadgetSliderGetDisabledColor( gadget ) );
		GadgetSliderSetDisabledThumbBorderColor( gadget, GadgetSliderGetDisabledBorderColor( gadget ) );
		GadgetSliderSetDisabledSelectedThumbImage( gadget, winFindImage( "HSliderThumbDisabled" ) );
		GadgetSliderSetDisabledSelectedThumbColor( gadget, GadgetSliderGetDisabledBorderColor( gadget ) );
		GadgetSliderSetDisabledSelectedThumbBorderColor( gadget, GadgetSliderGetDisabledColor( gadget ) );

		// hilite
		GadgetSliderSetHiliteThumbImage( gadget, winFindImage( "HSliderThumbHilite" ) );
		GadgetSliderSetHiliteThumbColor( gadget, GadgetSliderGetHiliteColor( gadget ) );
		GadgetSliderSetHiliteThumbBorderColor( gadget, GadgetSliderGetHiliteBorderColor( gadget ) );
		GadgetSliderSetHiliteSelectedThumbImage( gadget, winFindImage( "HSliderThumbHiliteSelected" ) );
		GadgetSliderSetHiliteSelectedThumbColor( gadget, GadgetSliderGetHiliteBorderColor( gadget ) );
		GadgetSliderSetHiliteSelectedThumbBorderColor( gadget, GadgetSliderGetHiliteColor( gadget ) );


	}  // end if
	else if( BitTest( instData->getStyle(), GWS_VERT_SLIDER ) )
	{
		// enabled
		GadgetSliderSetEnabledImageTop( gadget, winFindImage( "VSliderEnabledTopEnd" ) );
		GadgetSliderSetEnabledImageBottom( gadget, winFindImage( "VSliderEnabledBottomEnd" ) );
		GadgetSliderSetEnabledImageCenter( gadget, winFindImage( "VSliderEnabledRepeatingCenter" ) );
		GadgetSliderSetEnabledImageSmallCenter( gadget, winFindImage( "VSliderEnabledSmallRepeatingCenter" ) );
		GadgetSliderSetEnabledColor( gadget, red );
		GadgetSliderSetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetSliderSetDisabledImageTop( gadget, winFindImage( "VSliderDisabledTopEnd" ) );
		GadgetSliderSetDisabledImageBottom( gadget, winFindImage( "VSliderDisabledBottomEnd" ) );
		GadgetSliderSetDisabledImageCenter( gadget, winFindImage( "VSliderDisabledRepeatingCenter" ) );
		GadgetSliderSetDisabledImageSmallCenter( gadget, winFindImage( "VSliderDisabledSmallRepeatingCenter" ) );
		GadgetSliderSetDisabledColor( gadget, red );
		GadgetSliderSetDisabledBorderColor( gadget, lightRed );

		// hilite
		GadgetSliderSetHiliteImageTop( gadget, winFindImage( "VSliderHiliteTopEnd" ) );
		GadgetSliderSetHiliteImageBottom( gadget, winFindImage( "VSliderHiliteBottomEnd" ) );
		GadgetSliderSetHiliteImageCenter( gadget, winFindImage( "VSliderHiliteRepeatingCenter" ) );
		GadgetSliderSetHiliteImageSmallCenter( gadget, winFindImage( "VSliderHiliteSmallRepeatingCenter" ) );
		GadgetSliderSetHiliteColor( gadget, red );
		GadgetSliderSetHiliteBorderColor( gadget, lightRed );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

		//
		// set the default colors and images for the slider thumb
		//
		// enabled
		GadgetSliderSetEnabledThumbImage( gadget, winFindImage( "VSliderThumbEnabled" ) );
		GadgetSliderSetEnabledThumbColor( gadget, GadgetSliderGetEnabledColor( gadget ) );
		GadgetSliderSetEnabledThumbBorderColor( gadget, GadgetSliderGetEnabledBorderColor( gadget ) );
		GadgetSliderSetEnabledSelectedThumbImage( gadget, winFindImage( "VSliderThumbEnabled" ) );
		GadgetSliderSetEnabledSelectedThumbColor( gadget, GadgetSliderGetEnabledBorderColor( gadget ) );
		GadgetSliderSetEnabledSelectedThumbBorderColor( gadget, GadgetSliderGetEnabledColor( gadget ) );

		// disabled
		GadgetSliderSetDisabledThumbImage( gadget, winFindImage( "VSliderThumbDisabled" ) );
		GadgetSliderSetDisabledThumbColor( gadget, GadgetSliderGetDisabledColor( gadget ) );
		GadgetSliderSetDisabledThumbBorderColor( gadget, GadgetSliderGetDisabledBorderColor( gadget ) );
		GadgetSliderSetDisabledSelectedThumbImage( gadget, winFindImage( "VSliderThumbDisabled" ) );
		GadgetSliderSetDisabledSelectedThumbColor( gadget, GadgetSliderGetDisabledBorderColor( gadget ) );
		GadgetSliderSetDisabledSelectedThumbBorderColor( gadget, GadgetSliderGetDisabledColor( gadget ) );

		// hilite
		GadgetSliderSetHiliteThumbImage( gadget, winFindImage( "VSliderThumbHilite" ) );
		GadgetSliderSetHiliteThumbColor( gadget, GadgetSliderGetHiliteColor( gadget ) );
		GadgetSliderSetHiliteThumbBorderColor( gadget, GadgetSliderGetHiliteBorderColor( gadget ) );
		GadgetSliderSetHiliteSelectedThumbImage( gadget, winFindImage( "VSliderThumbHiliteSelected" ) );
		GadgetSliderSetHiliteSelectedThumbColor( gadget, GadgetSliderGetHiliteBorderColor( gadget ) );
		GadgetSliderSetHiliteSelectedThumbBorderColor( gadget, GadgetSliderGetHiliteColor( gadget ) );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_SCROLL_LISTBOX ) )
	{
		ListboxData *listboxData = (ListboxData *)gadget->winGetUserData();

		// set the colors
		GadgetListBoxSetColors( gadget,
														red,							// enabled
														lightRed,					// enabled border
														yellow,						// enabled selected item
														white,						// enabled selected item border
														gray,							// disabled
														lightGray,				// disabled border
														lightGray,				// disabled selected item
														white,						// disabled selected item border
														green,						// hilite
														darkGreen,				// hilite border
														white,						// hilite selected item
														darkGreen );			// hilite selected item border

		// now set the images

		// enabled
		GadgetListBoxSetEnabledImage( gadget, winFindImage( "ListBoxEnabled" ) );
		GadgetListBoxSetEnabledSelectedItemImageLeft( gadget, winFindImage( "ListBoxEnabledSelectedItemLeftEnd" ) );
		GadgetListBoxSetEnabledSelectedItemImageRight( gadget, winFindImage( "ListBoxEnabledSelectedItemRightEnd" ) );
		GadgetListBoxSetEnabledSelectedItemImageCenter( gadget, winFindImage( "ListBoxEnabledSelectedItemRepeatingCenter" ) );
		GadgetListBoxSetEnabledSelectedItemImageSmallCenter( gadget, winFindImage( "ListBoxEnabledSelectedItemSmallRepeatingCenter" ) );

		// disabled
		GadgetListBoxSetDisabledImage( gadget, winFindImage( "ListBoxDisabled" ) );
		GadgetListBoxSetDisabledSelectedItemImageLeft( gadget, winFindImage( "ListBoxDisabledSelectedItemLeftEnd" ) );
		GadgetListBoxSetDisabledSelectedItemImageRight( gadget, winFindImage( "ListBoxDisabledSelectedItemRightEnd" ) );
		GadgetListBoxSetDisabledSelectedItemImageCenter( gadget, winFindImage( "ListBoxDisabledSelectedItemRepeatingCenter" ) );
		GadgetListBoxSetDisabledSelectedItemImageSmallCenter( gadget, winFindImage( "ListBoxDisabledSelectedItemSmallRepeatingCenter" ) );


		// hilited
		GadgetListBoxSetHiliteImage( gadget, winFindImage( "ListBoxHilite" ) );
		GadgetListBoxSetHiliteSelectedItemImageLeft( gadget, winFindImage( "ListBoxHiliteSelectedItemLeftEnd" ) );
		GadgetListBoxSetHiliteSelectedItemImageRight( gadget, winFindImage( "ListBoxHiliteSelectedItemRightEnd" ) );
		GadgetListBoxSetHiliteSelectedItemImageCenter( gadget, winFindImage( "ListBoxHiliteSelectedItemRepeatingCenter" ) );
		GadgetListBoxSetHiliteSelectedItemImageSmallCenter( gadget, winFindImage( "ListBoxHiliteSelectedItemSmallRepeatingCenter" ) );

		// assign default slider colors and images as part of the list box
		GameWindow *slider = listboxData->slider;
		if( slider )
		{
			GameWindow *upButton = listboxData->upButton;
			GameWindow *downButton = listboxData->downButton;

			// slider and slider thumb ----------------------------------------------

			// enabled
			GadgetSliderSetEnabledImageTop( slider, winFindImage( "VSliderLargeEnabledTopEnd" ) );
			GadgetSliderSetEnabledImageBottom( slider, winFindImage( "VSliderLargeEnabledBottomEnd" ) );
			GadgetSliderSetEnabledImageCenter( slider, winFindImage( "VSliderLargeEnabledRepeatingCenter" ) );
			GadgetSliderSetEnabledImageSmallCenter( slider, winFindImage( "VSliderLargeEnabledSmallRepeatingCenter" ) );
			GadgetSliderSetEnabledThumbImage( slider, winFindImage( "VSliderLargeThumbEnabled" ) );
			GadgetSliderSetEnabledSelectedThumbImage( slider, winFindImage( "VSliderLargeThumbEnabled" ) );

			// disabled
			GadgetSliderSetDisabledImageTop( slider, winFindImage( "VSliderLargeDisabledTopEnd" ) );
			GadgetSliderSetDisabledImageBottom( slider, winFindImage( "VSliderLargeDisabledBottomEnd" ) );
			GadgetSliderSetDisabledImageCenter( slider, winFindImage( "VSliderLargeDisabledRepeatingCenter" ) );
			GadgetSliderSetDisabledImageSmallCenter( slider, winFindImage( "VSliderLargeDisabledSmallRepeatingCenter" ) );
			GadgetSliderSetDisabledThumbImage( slider, winFindImage( "VSliderLargeThumbDisabled" ) );
			GadgetSliderSetDisabledSelectedThumbImage( slider, winFindImage( "VSliderLargeThumbDisabled" ) );

			// hilite
			GadgetSliderSetHiliteImageTop( slider, winFindImage( "VSliderLargeHiliteTopEnd" ) );
			GadgetSliderSetHiliteImageBottom( slider, winFindImage( "VSliderLargeHiliteBottomEnd" ) );
			GadgetSliderSetHiliteImageCenter( slider, winFindImage( "VSliderLargeHiliteRepeatingCenter" ) );
			GadgetSliderSetHiliteImageSmallCenter( slider, winFindImage( "VSliderLargeHiliteSmallRepeatingCenter" ) );
			GadgetSliderSetHiliteThumbImage( slider, winFindImage( "VSliderLargeThumbHilite" ) );
			GadgetSliderSetHiliteSelectedThumbImage( slider, winFindImage( "VSliderLargeThumbHilite" ) );

			// up button ------------------------------------------------------------

			// enabled
			GadgetButtonSetEnabledImage( upButton, winFindImage( "VSliderLargeUpButtonEnabled" ) );
			GadgetButtonSetEnabledSelectedImage( upButton, winFindImage( "VSliderLargeUpButtonEnabled" ) );

			// disabled
			GadgetButtonSetDisabledImage( upButton, winFindImage( "VSliderLargeUpButtonDisabled" ) );
			GadgetButtonSetDisabledSelectedImage( upButton, winFindImage( "VSliderLargeUpButtonDisabled" ) );

			// hilite
			GadgetButtonSetHiliteImage( upButton, winFindImage( "VSliderLargeUpButtonHilite" ) );
			GadgetButtonSetHiliteSelectedImage( upButton, winFindImage( "VSliderLargeUpButtonHiliteSelected" ) );

			// down button ----------------------------------------------------------

			// enabled
			GadgetButtonSetEnabledImage( downButton, winFindImage( "VSliderLargeDownButtonEnabled" ) );
			GadgetButtonSetEnabledSelectedImage( downButton, winFindImage( "VSliderLargeDownButtonEnabled" ) );

			// disabled
			GadgetButtonSetDisabledImage( downButton, winFindImage( "VSliderLargeDownButtonDisabled" ) );
			GadgetButtonSetDisabledSelectedImage( downButton, winFindImage( "VSliderLargeDownButtonDisabled" ) );

			// hilite
			GadgetButtonSetHiliteImage( downButton, winFindImage( "VSliderLargeDownButtonHilite" ) );
			GadgetButtonSetHiliteSelectedImage( downButton, winFindImage( "VSliderLargeDownButtonHiliteSelected" ) );

		}  // end if

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_COMBO_BOX ) )
	{
//		ComboBoxData *comboBoxData = (ComboBoxData *)gadget->winGetUserData();

		GadgetComboBoxSetColors( gadget,
														red,							// enabled
														lightRed,					// enabled border
														yellow,						// enabled selected item
														white,						// enabled selected item border
														gray,							// disabled
														lightGray,				// disabled border
														lightGray,				// disabled selected item
														white,						// disabled selected item border
														green,						// hilite
														darkGreen,				// hilite border
														white,						// hilite selected item
														darkGreen );			// hilite selected item border

		// enabled
		GadgetComboBoxSetEnabledImage( gadget, winFindImage( "ListBoxEnabled" ) );
		GadgetComboBoxSetEnabledSelectedItemImageLeft( gadget, winFindImage( "ListBoxEnabledSelectedItemLeftEnd" ) );
		GadgetComboBoxSetEnabledSelectedItemImageRight( gadget, winFindImage( "ListBoxEnabledSelectedItemRightEnd" ) );
		GadgetComboBoxSetEnabledSelectedItemImageCenter( gadget, winFindImage( "ListBoxEnabledSelectedItemRepeatingCenter" ) );
		GadgetComboBoxSetEnabledSelectedItemImageSmallCenter( gadget, winFindImage( "ListBoxEnabledSelectedItemSmallRepeatingCenter" ) );

		// disabled
		GadgetComboBoxSetDisabledImage( gadget, winFindImage( "ListBoxDisabled" ) );
		GadgetComboBoxSetDisabledSelectedItemImageLeft( gadget, winFindImage( "ListBoxDisabledSelectedItemLeftEnd" ) );
		GadgetComboBoxSetDisabledSelectedItemImageRight( gadget, winFindImage( "ListBoxDisabledSelectedItemRightEnd" ) );
		GadgetComboBoxSetDisabledSelectedItemImageCenter( gadget, winFindImage( "ListBoxDisabledSelectedItemRepeatingCenter" ) );
		GadgetComboBoxSetDisabledSelectedItemImageSmallCenter( gadget, winFindImage( "ListBoxDisabledSelectedItemSmallRepeatingCenter" ) );


		// hilited
		GadgetComboBoxSetHiliteImage( gadget, winFindImage( "ListBoxHilite" ) );
		GadgetComboBoxSetHiliteSelectedItemImageLeft( gadget, winFindImage( "ListBoxHiliteSelectedItemLeftEnd" ) );
		GadgetComboBoxSetHiliteSelectedItemImageRight( gadget, winFindImage( "ListBoxHiliteSelectedItemRightEnd" ) );
		GadgetComboBoxSetHiliteSelectedItemImageCenter( gadget, winFindImage( "ListBoxHiliteSelectedItemRepeatingCenter" ) );
		GadgetComboBoxSetHiliteSelectedItemImageSmallCenter( gadget, winFindImage( "ListBoxHiliteSelectedItemSmallRepeatingCenter" ) );

		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

		GameWindow *dropDownButton = GadgetComboBoxGetDropDownButton( gadget );
		if ( dropDownButton )
		{
			// enabled background
			GadgetButtonSetEnabledImage( dropDownButton, winFindImage( "PushButtonEnabled" ) );
			// enabled selected button
			GadgetButtonSetEnabledSelectedImage( dropDownButton, winFindImage( "PushButtonEnabledSelected" ) );

			// Disabled background
			GadgetButtonSetDisabledImage( dropDownButton, winFindImage( "PushButtonDisabled" ) );
			// Disabled selected button
			GadgetButtonSetDisabledSelectedImage( dropDownButton, winFindImage( "PushButtonDisabledSelected" ) );

			// Hilite background
			GadgetButtonSetHiliteImage( dropDownButton, winFindImage( "PushButtonHilite" ) );
			// Hilite selected button
			GadgetButtonSetHiliteSelectedImage( dropDownButton, winFindImage( "PushButtonHiliteSelected" ) );

		}

		GameWindow *editBox = GadgetComboBoxGetEditBox( gadget );
		if ( editBox )
		{
			// enabled
			GadgetTextEntrySetEnabledImageLeft( editBox, winFindImage( "TextEntryEnabledLeftEnd" ) );
			GadgetTextEntrySetEnabledImageRight( editBox, winFindImage( "TextEntryEnabledRightEnd" ) );
			GadgetTextEntrySetEnabledImageCenter( editBox, winFindImage( "TextEntryEnabledRepeatingCenter" ) );
			GadgetTextEntrySetEnabledImageSmallCenter( editBox, winFindImage( "TextEntryEnabledSmallRepeatingCenter" ) );

			// disabled
			GadgetTextEntrySetDisabledImageLeft( editBox, winFindImage( "TextEntryDisabledLeftEnd" ) );
			GadgetTextEntrySetDisabledImageRight( editBox, winFindImage( "TextEntryDisabledRightEnd" ) );
			GadgetTextEntrySetDisabledImageCenter( editBox, winFindImage( "TextEntryDisabledRepeatingCenter" ) );
			GadgetTextEntrySetDisabledImageSmallCenter( editBox, winFindImage( "TextEntryDisabledSmallRepeatingCenter" ) );

			// hilited
			GadgetTextEntrySetHiliteImageLeft( editBox, winFindImage( "TextEntryHiliteLeftEnd" ) );
			GadgetTextEntrySetHiliteImageRight( editBox, winFindImage( "TextEntryHiliteRightEnd" ) );
			GadgetTextEntrySetHiliteImageCenter( editBox, winFindImage( "TextEntryHiliteRepeatingCenter" ) );
			GadgetTextEntrySetHiliteImageSmallCenter( editBox, winFindImage( "TextEntryHiliteSmallRepeatingCenter" ) );

		}

		GameWindow * listBox = GadgetComboBoxGetListBox( gadget );
		if ( listBox )
		{

			// now set the images

			// enabled
			GadgetListBoxSetEnabledImage( listBox, winFindImage( "ListBoxEnabled" ) );
			GadgetListBoxSetEnabledSelectedItemImageLeft( listBox, winFindImage( "ListBoxEnabledSelectedItemLeftEnd" ) );
			GadgetListBoxSetEnabledSelectedItemImageRight( listBox, winFindImage( "ListBoxEnabledSelectedItemRightEnd" ) );
			GadgetListBoxSetEnabledSelectedItemImageCenter( listBox, winFindImage( "ListBoxEnabledSelectedItemRepeatingCenter" ) );
			GadgetListBoxSetEnabledSelectedItemImageSmallCenter( listBox, winFindImage( "ListBoxEnabledSelectedItemSmallRepeatingCenter" ) );

			// disabled
			GadgetListBoxSetDisabledImage( listBox, winFindImage( "ListBoxDisabled" ) );
			GadgetListBoxSetDisabledSelectedItemImageLeft( listBox, winFindImage( "ListBoxDisabledSelectedItemLeftEnd" ) );
			GadgetListBoxSetDisabledSelectedItemImageRight( listBox, winFindImage( "ListBoxDisabledSelectedItemRightEnd" ) );
			GadgetListBoxSetDisabledSelectedItemImageCenter( listBox, winFindImage( "ListBoxDisabledSelectedItemRepeatingCenter" ) );
			GadgetListBoxSetDisabledSelectedItemImageSmallCenter( listBox, winFindImage( "ListBoxDisabledSelectedItemSmallRepeatingCenter" ) );


			// hilited
			GadgetListBoxSetHiliteImage( listBox, winFindImage( "ListBoxHilite" ) );
			GadgetListBoxSetHiliteSelectedItemImageLeft( listBox, winFindImage( "ListBoxHiliteSelectedItemLeftEnd" ) );
			GadgetListBoxSetHiliteSelectedItemImageRight( listBox, winFindImage( "ListBoxHiliteSelectedItemRightEnd" ) );
			GadgetListBoxSetHiliteSelectedItemImageCenter( listBox, winFindImage( "ListBoxHiliteSelectedItemRepeatingCenter" ) );
			GadgetListBoxSetHiliteSelectedItemImageSmallCenter( listBox, winFindImage( "ListBoxHiliteSelectedItemSmallRepeatingCenter" ) );

			// assign default slider colors and images as part of the list box
			GameWindow *slider = GadgetListBoxGetSlider( listBox );
			if( slider )
			{
				GameWindow *upButton = GadgetListBoxGetUpButton( listBox );
				GameWindow *downButton = GadgetListBoxGetDownButton( listBox );

				// slider and slider thumb ----------------------------------------------

				// enabled
				GadgetSliderSetEnabledImageTop( slider, winFindImage( "VSliderLargeEnabledTopEnd" ) );
				GadgetSliderSetEnabledImageBottom( slider, winFindImage( "VSliderLargeEnabledBottomEnd" ) );
				GadgetSliderSetEnabledImageCenter( slider, winFindImage( "VSliderLargeEnabledRepeatingCenter" ) );
				GadgetSliderSetEnabledImageSmallCenter( slider, winFindImage( "VSliderLargeEnabledSmallRepeatingCenter" ) );
				GadgetSliderSetEnabledThumbImage( slider, winFindImage( "VSliderLargeThumbEnabled" ) );
				GadgetSliderSetEnabledSelectedThumbImage( slider, winFindImage( "VSliderLargeThumbEnabled" ) );

				// disabled
				GadgetSliderSetDisabledImageTop( slider, winFindImage( "VSliderLargeDisabledTopEnd" ) );
				GadgetSliderSetDisabledImageBottom( slider, winFindImage( "VSliderLargeDisabledBottomEnd" ) );
				GadgetSliderSetDisabledImageCenter( slider, winFindImage( "VSliderLargeDisabledRepeatingCenter" ) );
				GadgetSliderSetDisabledImageSmallCenter( slider, winFindImage( "VSliderLargeDisabledSmallRepeatingCenter" ) );
				GadgetSliderSetDisabledThumbImage( slider, winFindImage( "VSliderLargeThumbDisabled" ) );
				GadgetSliderSetDisabledSelectedThumbImage( slider, winFindImage( "VSliderLargeThumbDisabled" ) );

				// hilite
				GadgetSliderSetHiliteImageTop( slider, winFindImage( "VSliderLargeHiliteTopEnd" ) );
				GadgetSliderSetHiliteImageBottom( slider, winFindImage( "VSliderLargeHiliteBottomEnd" ) );
				GadgetSliderSetHiliteImageCenter( slider, winFindImage( "VSliderLargeHiliteRepeatingCenter" ) );
				GadgetSliderSetHiliteImageSmallCenter( slider, winFindImage( "VSliderLargeHiliteSmallRepeatingCenter" ) );
				GadgetSliderSetHiliteThumbImage( slider, winFindImage( "VSliderLargeThumbHilite" ) );
				GadgetSliderSetHiliteSelectedThumbImage( slider, winFindImage( "VSliderLargeThumbHilite" ) );

				// up button ------------------------------------------------------------

				// enabled
				GadgetButtonSetEnabledImage( upButton, winFindImage( "VSliderLargeUpButtonEnabled" ) );
				GadgetButtonSetEnabledSelectedImage( upButton, winFindImage( "VSliderLargeUpButtonEnabled" ) );

				// disabled
				GadgetButtonSetDisabledImage( upButton, winFindImage( "VSliderLargeUpButtonDisabled" ) );
				GadgetButtonSetDisabledSelectedImage( upButton, winFindImage( "VSliderLargeUpButtonDisabled" ) );

				// hilite
				GadgetButtonSetHiliteImage( upButton, winFindImage( "VSliderLargeUpButtonHilite" ) );
				GadgetButtonSetHiliteSelectedImage( upButton, winFindImage( "VSliderLargeUpButtonHiliteSelected" ) );

				// down button ----------------------------------------------------------

				// enabled
				GadgetButtonSetEnabledImage( downButton, winFindImage( "VSliderLargeDownButtonEnabled" ) );
				GadgetButtonSetEnabledSelectedImage( downButton, winFindImage( "VSliderLargeDownButtonEnabled" ) );

				// disabled
				GadgetButtonSetDisabledImage( downButton, winFindImage( "VSliderLargeDownButtonDisabled" ) );
				GadgetButtonSetDisabledSelectedImage( downButton, winFindImage( "VSliderLargeDownButtonDisabled" ) );

				// hilite
				GadgetButtonSetHiliteImage( downButton, winFindImage( "VSliderLargeDownButtonHilite" ) );
				GadgetButtonSetHiliteSelectedImage( downButton, winFindImage( "VSliderLargeDownButtonHiliteSelected" ) );

			}  // end if
		}
	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_PROGRESS_BAR ) )
	{

		// enabled
		GadgetProgressBarSetEnabledColor( gadget, red );
		GadgetProgressBarSetEnabledBorderColor( gadget, lightRed );
		GadgetProgressBarSetEnabledImageLeft( gadget, winFindImage( "ProgressBarEnabledLeftEnd" ) );
		GadgetProgressBarSetEnabledImageRight( gadget, winFindImage( "ProgressBarEnabledRightEnd" ) );
		GadgetProgressBarSetEnabledImageCenter( gadget, winFindImage( "ProgressBarEnabledRepeatingCenter" ) );
		GadgetProgressBarSetEnabledImageSmallCenter( gadget, winFindImage( "ProgressBarEnabledSmallRepeatingCenter" ) );
		GadgetProgressBarSetEnabledBarColor( gadget, yellow );
		GadgetProgressBarSetEnabledBarBorderColor( gadget, white );
		GadgetProgressBarSetEnabledBarImageLeft( gadget, winFindImage( "ProgressBarEnabledBarLeftEnd" ) );
		GadgetProgressBarSetEnabledBarImageRight( gadget, winFindImage( "ProgressBarEnabledBarRightEnd" ) );
		GadgetProgressBarSetEnabledBarImageCenter( gadget, winFindImage( "ProgressBarEnabledBarRepeatingCenter" ) );
		GadgetProgressBarSetEnabledBarImageSmallCenter( gadget, winFindImage( "ProgressBarEnabledBarSmallRepeatingCenter" ) );

		// disabled
		GadgetProgressBarSetDisabledColor( gadget, darkGray );
		GadgetProgressBarSetDisabledBorderColor( gadget, lightGray );
		GadgetProgressBarSetDisabledImageLeft( gadget, winFindImage( "ProgressBarDisabledLeftEnd" ) );
		GadgetProgressBarSetDisabledImageRight( gadget, winFindImage( "ProgressBarDisabledRightEnd" ) );
		GadgetProgressBarSetDisabledImageCenter( gadget, winFindImage( "ProgressBarDisabledRepeatingCenter" ) );
		GadgetProgressBarSetDisabledImageSmallCenter( gadget, winFindImage( "ProgressBarDisabledSmallRepeatingCenter" ) );
		GadgetProgressBarSetDisabledBarColor( gadget, lightGray );
		GadgetProgressBarSetDisabledBarBorderColor( gadget, white );
		GadgetProgressBarSetDisabledBarImageLeft( gadget, winFindImage( "ProgressBarDisabledBarLeftEnd" ) );
		GadgetProgressBarSetDisabledBarImageRight( gadget, winFindImage( "ProgressBarDisabledBarRightEnd" ) );
		GadgetProgressBarSetDisabledBarImageCenter( gadget, winFindImage( "ProgressBarDisabledBarRepeatingCenter" ) );
		GadgetProgressBarSetDisabledBarImageSmallCenter( gadget, winFindImage( "ProgressBarDisabledBarSmallRepeatingCenter" ) );

		// Hilite
		GadgetProgressBarSetHiliteColor( gadget, green );
		GadgetProgressBarSetHiliteBorderColor( gadget, darkGreen );
		GadgetProgressBarSetHiliteImageLeft( gadget, winFindImage( "ProgressBarHiliteLeftEnd" ) );
		GadgetProgressBarSetHiliteImageRight( gadget, winFindImage( "ProgressBarHiliteRightEnd" ) );
		GadgetProgressBarSetHiliteImageCenter( gadget, winFindImage( "ProgressBarHiliteRepeatingCenter" ) );
		GadgetProgressBarSetHiliteImageSmallCenter( gadget, winFindImage( "ProgressBarHiliteSmallRepeatingCenter" ) );
		GadgetProgressBarSetHiliteBarColor( gadget, yellow );
		GadgetProgressBarSetHiliteBarBorderColor( gadget, white );
		GadgetProgressBarSetHiliteBarImageLeft( gadget, winFindImage( "ProgressBarHiliteBarLeftEnd" ) );
		GadgetProgressBarSetHiliteBarImageRight( gadget, winFindImage( "ProgressBarHiliteBarRightEnd" ) );
		GadgetProgressBarSetHiliteBarImageCenter( gadget, winFindImage( "ProgressBarHiliteBarRepeatingCenter" ) );
		GadgetProgressBarSetHiliteBarImageSmallCenter( gadget, winFindImage( "ProgressBarHiliteBarSmallRepeatingCenter" ) );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_STATIC_TEXT ) )
	{

		// enabled
		GadgetStaticTextSetEnabledImage( gadget, winFindImage( "StaticTextEnabled" ) );
		GadgetStaticTextSetEnabledColor( gadget, red );
		GadgetStaticTextSetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetStaticTextSetDisabledImage( gadget, winFindImage( "StaticTextDisabled" ) );
		GadgetStaticTextSetDisabledColor( gadget, darkGray );
		GadgetStaticTextSetDisabledBorderColor( gadget, lightGray );

		// hilite
		GadgetStaticTextSetHiliteImage( gadget, winFindImage( "StaticTextHilite" ) );
		GadgetStaticTextSetHiliteColor( gadget, darkGreen );
		GadgetStaticTextSetHiliteBorderColor( gadget, lightGreen );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_ENTRY_FIELD ) )
	{

		// enabled
		GadgetTextEntrySetEnabledImageLeft( gadget, winFindImage( "TextEntryEnabledLeftEnd" ) );
		GadgetTextEntrySetEnabledImageRight( gadget, winFindImage( "TextEntryEnabledRightEnd" ) );
		GadgetTextEntrySetEnabledImageCenter( gadget, winFindImage( "TextEntryEnabledRepeatingCenter" ) );
		GadgetTextEntrySetEnabledImageSmallCenter( gadget, winFindImage( "TextEntryEnabledSmallRepeatingCenter" ) );
		GadgetTextEntrySetEnabledColor( gadget, red );
		GadgetTextEntrySetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetTextEntrySetDisabledImageLeft( gadget, winFindImage( "TextEntryDisabledLeftEnd" ) );
		GadgetTextEntrySetDisabledImageRight( gadget, winFindImage( "TextEntryDisabledRightEnd" ) );
		GadgetTextEntrySetDisabledImageCenter( gadget, winFindImage( "TextEntryDisabledRepeatingCenter" ) );
		GadgetTextEntrySetDisabledImageSmallCenter( gadget, winFindImage( "TextEntryDisabledSmallRepeatingCenter" ) );
		GadgetTextEntrySetDisabledColor( gadget, gray );
		GadgetTextEntrySetDisabledBorderColor( gadget, black );

		// hilited
		GadgetTextEntrySetHiliteImageLeft( gadget, winFindImage( "TextEntryHiliteLeftEnd" ) );
		GadgetTextEntrySetHiliteImageRight( gadget, winFindImage( "TextEntryHiliteRightEnd" ) );
		GadgetTextEntrySetHiliteImageCenter( gadget, winFindImage( "TextEntryHiliteRepeatingCenter" ) );
		GadgetTextEntrySetHiliteImageSmallCenter( gadget, winFindImage( "TextEntryHiliteSmallRepeatingCenter" ) );
		GadgetTextEntrySetHiliteColor( gadget, green );
		GadgetTextEntrySetHiliteBorderColor( gadget, darkGreen );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if

}  // end assignDefaultGadgetLook
