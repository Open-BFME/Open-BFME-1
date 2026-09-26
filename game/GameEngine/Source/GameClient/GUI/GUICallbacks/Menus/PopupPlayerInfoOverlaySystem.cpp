// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// GameSpyPlayerInfoOverlaySystem at retail 0x004D99C0 (816 bytes): the Zero
// Hour PopupPlayerInfo.cpp window-system callback, ported into its own TU so the
// readable PopupPlayerInfo.cpp keeps its include environment. The window-id and
// window globals are PopupPlayerInfo.cpp statics in Zero Hour; the matched
// GameSpyPlayerInfoOverlayInit (0x004DDD10) stores each one from its
// "PopupPlayerInfo.wnd:..." nameToKey / winGetWindowFromId result.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/CustomMatchPreferences.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/MessageBox.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/LobbyUtils.h"

// PopupPlayerInfo.cpp statics (0x012F3FDC..0x012F3FF0, 0x012F400C, 0x012F4010)
extern NameKeyType buttonCloseID;
extern NameKeyType buttonBuddiesID;
extern NameKeyType buttonSetLocaleID;
extern NameKeyType buttonDeleteAccountID;
extern NameKeyType checkBoxAsianFontID;
extern NameKeyType checkBoxNonAsianFontID;
extern GameWindow *checkBoxAsianFont;
extern GameWindow *checkBoxNonAsianFont;

// The vendored peerdefs shim puts setDisallowAsianText at +0xD0; BFME's
// GameSpyInfo vtable 0x011188D0 holds GameSpyInfo::setDisallowAsianText
// (0x00630760) at slot 53 (+0xD4) and setDisallowNonAsianText (0x00630770) at
// slot 54 (+0xD8). Only the slot index matters here, so the drift is spelled
// TU-locally as a view and a cast at each call site, like PopupPlayerInfo.cpp's
// BfmeGameSpyInfoLocalProfileView.
class BfmeGameSpyInfoDisallowTextView
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void slot39() = 0; virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0;
	virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0;
	virtual void slot51() = 0; virtual void slot52() = 0;
	virtual void setDisallowAsianText( Bool val ) = 0;
	virtual void setDisallowNonAsianText( Bool val ) = 0;
};

void messageBoxYes( void );
// Zero Hour's ReOpenPlayerInfo(); the ledger keeps the body at 0x00627C40
// under its address-derived name.
void Rva00627C40SetFlag( void );

//-------------------------------------------------------------------------------------------------
/** Overlay window system callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType GameSpyPlayerInfoOverlaySystem( GameWindow *window, UnsignedInt msg,
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	UnicodeString txtInput;

	switch( msg )
	{
		case GWM_CREATE:
			{
				break;
			} // case GWM_DESTROY:

		case GWM_DESTROY:
			{
				break;
			} // case GWM_DESTROY:

		case GWM_INPUT_FOCUS:
			{
				// if we're givin the opportunity to take the keyboard focus we must say we want it
				if( mData1 == TRUE )
					*(Bool *)mData2 = TRUE;

				return MSG_HANDLED;
			}//case GWM_INPUT_FOCUS:
		case GBM_SELECTED:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if (controlID == buttonCloseID)
				{
					RefreshGameListBoxes();
					GameSpyCloseOverlay( GSOVERLAY_PLAYERINFO );
				}
				else if (controlID == buttonBuddiesID)
				{
					RefreshGameListBoxes();
					GameSpyOpenOverlay( GSOVERLAY_BUDDY );
				}
				else if (controlID == buttonSetLocaleID)
				{
					RefreshGameListBoxes();
					GameSpyCloseOverlay( GSOVERLAY_PLAYERINFO );
					if (!GameSpyIsOverlayOpen(GSOVERLAY_LOCALESELECT))
						GameSpyOpenOverlay( GSOVERLAY_LOCALESELECT );
					Rva00627C40SetFlag();
				}
				else if (controlID == buttonDeleteAccountID)
				{
					RefreshGameListBoxes();
					GameSpyCloseOverlay( GSOVERLAY_PLAYERINFO );
					MessageBoxYesNo(TheGameText->fetch("GUI:DeleteAccount"), TheGameText->fetch("GUI:AreYouSureDeleteAccount"),messageBoxYes, NULL);
				}
				else if (controlID == checkBoxAsianFontID)
				{
					Bool isChecked = !GadgetCheckBoxIsChecked(control);
					CustomMatchPreferences pref;
					pref.setDisallowAsianText(isChecked);
					pref.write();
					if(TheGameSpyInfo)
						((BfmeGameSpyInfoDisallowTextView *)TheGameSpyInfo)->setDisallowAsianText(isChecked);
					if(isChecked && !GadgetCheckBoxIsChecked(checkBoxNonAsianFont))
					{
						GadgetCheckBoxSetChecked(checkBoxNonAsianFont, TRUE);
						CustomMatchPreferences pref;
						pref.setDisallowNonAsianText(FALSE);
						pref.write();
						if(TheGameSpyInfo)
							((BfmeGameSpyInfoDisallowTextView *)TheGameSpyInfo)->setDisallowNonAsianText(FALSE);
					}

				}
				else if (controlID == checkBoxNonAsianFontID)
				{
					Bool isChecked = !GadgetCheckBoxIsChecked(control);
					CustomMatchPreferences pref;
					pref.setDisallowNonAsianText(isChecked);
					pref.write();
					if(TheGameSpyInfo)
						((BfmeGameSpyInfoDisallowTextView *)TheGameSpyInfo)->setDisallowNonAsianText(isChecked);
					if(isChecked && !GadgetCheckBoxIsChecked(checkBoxAsianFont))
					{
						GadgetCheckBoxSetChecked(checkBoxAsianFont, TRUE);
						CustomMatchPreferences pref;
						pref.setDisallowAsianText(FALSE);
						pref.write();
						if(TheGameSpyInfo)
							((BfmeGameSpyInfoDisallowTextView *)TheGameSpyInfo)->setDisallowAsianText(FALSE);
					}
				}

				break;
			}// case GBM_SELECTED:

		default:
			return MSG_IGNORED;

	}//Switch

	return MSG_HANDLED;
}// GameSpyPlayerInfoOverlaySystem
