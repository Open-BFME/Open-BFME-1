// ?gogoGadgetComboBox@GameWindowManager@@UAEPAVGameWindow@@PAV2@IHHHHPAVWinInstanceData@@PAU_ComboBoxData@@PAVGameFont@@_N@Z
// partial score=0.65 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/gamewindowlist /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Retail gogoGadgetComboBox is the 1240-byte function at 0x0047F6E0.  The
// older ledger entry at 0x0047F757 covered only its interior after the EH
// prologue; this source models the complete GameWindowManager factory.

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"

#include <string.h>

#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"

GameWindow *GameWindowManager::gogoGadgetComboBox( GameWindow *parent,
	UnsignedInt status,
	Int x, Int y, Int width, Int height,
	WinInstanceData *instData,
	ComboBoxData *comboBoxDataTemplate,
	GameFont *defaultFont,
	Bool defaultVisual )
{
	GameWindow *comboBox;
	ComboBoxData *comboBoxData;
	Bool title = FALSE;

	if( BitTest( instData->getStyle(), GWS_COMBO_BOX ) == FALSE )
	{
		DEBUG_LOG(( "Cann't create ComboBox gadget, instance data not ComboBox type\n" ));
		assert( 0 );
		return NULL;
	}

	comboBox = winCreate( parent, status, x, y, width, height,
		GadgetComboBoxSystem, instData );
	if( comboBox == NULL )
	{
		DEBUG_LOG(( "Unable to create ComboBox window\n" ));
		assert( 0 );
		return NULL;
	}

	comboBoxData = NEW ComboBoxData;
	memcpy( comboBoxData, comboBoxDataTemplate, sizeof( ComboBoxData ) );
	comboBox->winSetUserData( comboBoxData );
	comboBox->winSetOwner( parent );

	if( instData->getTextLength() )
		title = TRUE;

	if( BitTest( comboBox->winGetStatus(), WIN_STATUS_IMAGE ) )
		comboBox->winSetDrawFunc( getComboBoxImageDrawFunc() );
	else
		comboBox->winSetDrawFunc( getComboBoxDrawFunc() );
	comboBox->winSetInputFunc( GadgetComboBoxInput );

	WinInstanceData winInstData;
	Int buttonWidth;
	Int fontHeight;
	Int top;
	Int bottom;

	if( comboBox->winGetTextLength() )
		title = TRUE;
	status &= ~( WIN_STATUS_BORDER | WIN_STATUS_HIDDEN );
	fontHeight = TheWindowManager->winFontHeight( comboBox->winGetFont() );
	top = title ? ( fontHeight + 1 ) : 0;
	bottom = title ? ( height - ( fontHeight + 1 ) ) : height;

	winInstData.init();
	buttonWidth = 21;

	winInstData.m_owner = comboBox;
	winInstData.m_style = GWS_PUSH_BUTTON;
	if( BitTest( comboBox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );

	comboBoxData->dropDownButton =
		TheWindowManager->gogoGadgetPushButton( comboBox,
			status | WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED,
			width - buttonWidth, 0, buttonWidth, height,
			&winInstData, NULL, TRUE );
	comboBoxData->dropDownButton->winSetTooltipFunc( comboBox->winGetTooltipFunc() );
	comboBoxData->dropDownButton->winSetTooltip( instData->getTooltipText() );
	comboBoxData->dropDownButton->setTooltipDelay( comboBox->getTooltipDelay() );

	UnsignedInt statusTextEntry;
	winInstData.init();
	winInstData.m_owner = comboBox;
	winInstData.m_style |= GWS_ENTRY_FIELD;
	winInstData.m_textLabelString = "Entry";
	if( BitTest( comboBox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	if( comboBoxData->isEditable )
		statusTextEntry = status;
	else
	{
		statusTextEntry = status | WIN_STATUS_NO_INPUT;
		comboBoxData->entryData->drawTextFromStart = TRUE;
	}
	comboBoxData->editBox = TheWindowManager->gogoGadgetTextEntry(
		comboBox, statusTextEntry, 0, 0, width - buttonWidth, height,
		&winInstData, comboBoxData->entryData, winInstData.m_font, FALSE );
	comboBoxData->editBox->winSetTooltipFunc( comboBox->winGetTooltipFunc() );
	comboBoxData->editBox->winSetTooltip( instData->getTooltipText() );
	comboBoxData->editBox->setTooltipDelay( comboBox->getTooltipDelay() );
	delete comboBoxData->entryData;
	comboBoxData->entryData = (EntryData *)comboBoxData->editBox->winGetUserData();

	winInstData.init();
	winInstData.m_owner = comboBox;
	if( BitTest( comboBox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	BitSet( winInstData.m_style, WIN_STATUS_HIDDEN );
	winInstData.m_style |= GWS_SCROLL_LISTBOX;
	status &= ~( WIN_STATUS_IMAGE );
	comboBoxData->listBox = TheWindowManager->gogoGadgetListBox(
		comboBox, status | WIN_STATUS_ABOVE | WIN_STATUS_ONE_LINE,
		0, height, width, height, &winInstData,
		comboBoxData->listboxData, winInstData.m_font, FALSE );
	comboBoxData->listBox->winHide( TRUE );
	delete comboBoxData->listboxData;
	comboBoxData->listboxData = (ListboxData *)comboBoxData->listBox->winGetUserData();
	comboBoxData->listBox->winSetTooltipFunc( comboBox->winGetTooltipFunc() );
	comboBoxData->listBox->winSetTooltip( instData->getTooltipText() );
	comboBoxData->listBox->setTooltipDelay( comboBox->getTooltipDelay() );
	GadgetListBoxSetAudioFeedback( comboBoxData->listBox, TRUE );

	GadgetComboBoxSetIsEditable( comboBox, comboBoxData->isEditable );
	GadgetComboBoxSetMaxChars( comboBox, comboBoxData->maxChars );
	GadgetComboBoxSetMaxDisplay( comboBox, comboBoxData->maxDisplay );

	Color color, border;
	color = comboBox->winGetEnabledTextColor();
	border = comboBox->winGetEnabledTextBorderColor();
	if( comboBoxData->listBox )
		comboBoxData->listBox->winSetEnabledTextColors( color, border );
	if( comboBoxData->editBox )
		comboBoxData->editBox->winSetEnabledTextColors( color, border );
	color = comboBox->winGetDisabledTextColor();
	border = comboBox->winGetDisabledTextBorderColor();
	if( comboBoxData->listBox )
		comboBoxData->listBox->winSetDisabledTextColors( color, border );
	if( comboBoxData->editBox )
		comboBoxData->editBox->winSetDisabledTextColors( color, border );
	color = comboBox->winGetHiliteTextColor();
	border = comboBox->winGetHiliteTextBorderColor();
	if( comboBoxData->listBox )
		comboBoxData->listBox->winSetHiliteTextColors( color, border );
	if( comboBoxData->editBox )
		comboBoxData->editBox->winSetHiliteTextColors( color, border );

	comboBoxData->dontHide = FALSE;
	assignDefaultGadgetLook( comboBox, defaultFont, defaultVisual );
	return comboBox;
}
