// ?system@BfmeAptScreenQuickMatchMenu@@QAE?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.23 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/QuickmatchPreferences.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/Image.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpyOverlay.h"

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	char m_bfmeBody[0x190];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread();
	virtual void endThread();
	virtual int isThreadRunning();
	virtual int isConnected();
	virtual int isConnecting();
	virtual void addRequest(const PeerRequest &request);
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern Color GameSpyColor[];

class BfmeAptScreenQuickMatchMenu
{
public:
	WindowMsgHandledType system(GameWindow *window, UnsignedInt msg,
		WindowMsgData mData1, WindowMsgData mData2);

private:
	char m_unmodelled[0x218];
	bool m_isMatching;
	char m_pad219[3];
	int m_matchingLevel;
	bool m_isStopping;
	char m_pad221[3];
	int m_selectedMap;
	NameKeyType m_parentOptionsKey;
	GameWindow *m_parentOptions;
	NameKeyType m_maxPingKey;
	GameWindow *m_maxPing;
	NameKeyType m_numPlayersKey;
	GameWindow *m_numPlayers;
	NameKeyType m_ladderKey;
	GameWindow *m_ladder;
	NameKeyType m_maxDisconnectsKey;
	GameWindow *m_maxDisconnects;
	NameKeyType m_sideKey;
	GameWindow *m_side;
	NameKeyType m_colorKey;
	GameWindow *m_color;
	NameKeyType m_backKey;
	GameWindow *m_back;
	NameKeyType m_startKey;
	GameWindow *m_start;
	NameKeyType m_currentMatchingLevelKey;
	GameWindow *m_currentMatchingLevel;
	NameKeyType m_personalInfoKey;
	GameWindow *m_personalInfo;
	NameKeyType m_mapSelectKey;
	GameWindow *m_mapSelect;
	NameKeyType m_parentProgressKey;
	GameWindow *m_parentProgress;
	NameKeyType m_quickMatchListKey;
	GameWindow *m_quickMatchList;
	NameKeyType m_widenKey;
	GameWindow *m_widen;
	NameKeyType m_stopKey;
	GameWindow *m_stop;
	NameKeyType m_parentStatsKey;
	GameWindow *m_parentStats;
};

class Rva005063E0SaveOptions
{
public:
	void saveQuickMatchOptions();
};

class Rva005082D0PopulateSide
{
public:
	void populateQMSideComboBox(Int side, const LadderInfo *ladder);
};

class Rva00507F70PopulateMaps
{
public:
	void populateQuickMatchMapSelectListbox(QuickMatchPreferences &pref);
};

class Rva005053C0GetLadderInfo
{
public:
	const LadderInfo *getLadderInfo();
};

class Rva00505570UpdateStartButton
{
public:
	void updateStartButton();
};

class Rva00509B30StartRequest
{
public:
	void sendStartQuickMatchRequest(GameWindow *control);
};

class BfmeQuickMatchStopBody
{
public:
	void stop();
};

class BfmeQuickMatchHideOptionsGadgetsBody
{
public:
	void showInfo(Bool unused);
};

class Rva505C80WindowVisibilityThunk
{
public:
	void updateAt00505B40();
};

void PopulateQMLadderComboBox();

class Image;

WindowMsgHandledType BfmeAptScreenQuickMatchMenu::system(GameWindow *, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	UnicodeString txtInput;

	switch (msg)
	{
	case GWM_CREATE:
	case GWM_DESTROY:
		break;

	case GWM_INPUT_FOCUS:
		if (mData1 == TRUE)
			*(Bool *)mData2 = TRUE;
		return MSG_HANDLED;

	case 0x4025:
		if (*(volatile Bool *)0x012F4801u)
			break;

		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
			Int pos = -1;
			GadgetComboBoxGetSelectedPos(control, &pos);
			((Rva005063E0SaveOptions *)this)->saveQuickMatchOptions();

			if (controlID == m_ladderKey && !*(volatile bool *)0x012F4814u)
			{
				if (pos >= 0)
				{
					QuickMatchPreferences pref;
					Int ladderID = (Int)GadgetComboBoxGetItemData(control, pos);
					if (ladderID == 0)
					{
						GadgetComboBoxSetSelectedPos(m_numPlayers,
							max(0, pref.getNumPlayers() / 2 - 1), FALSE);
						m_numPlayers->winEnable(TRUE);
						((Rva005082D0PopulateSide *)this)->populateQMSideComboBox(
							pref.getSide(), (const LadderInfo *)0);
					}
					else if (ladderID > 0)
					{
						const LadderInfo *li = TheLadderList->findLadderByIndex(ladderID);
						if (li)
							GadgetComboBoxSetSelectedPos(m_numPlayers,
								li->playersPerTeam - 1, FALSE);
						else
							GadgetComboBoxSetSelectedPos(m_numPlayers, 0, FALSE);
						m_numPlayers->winEnable(FALSE);
						((Rva005082D0PopulateSide *)this)->populateQMSideComboBox(
							pref.getSide(), li);
					}
					else
					{
						PopulateQMLadderComboBox();
						GameSpyOpenOverlay(GSOVERLAY_LADDERSELECT);
					}
				}
			}

			if (!*(volatile bool *)0x012F4809u)
			{
				QuickMatchPreferences pref;
				((Rva00507F70PopulateMaps *)this)->populateQuickMatchMapSelectListbox(pref);
				((Rva00505570UpdateStartButton *)this)->updateStartButton();
			}
		}
		break;

	case GBM_SELECTED:
		if (*(volatile Bool *)0x012F4801u)
			break;

		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();

			if (controlID == m_stopKey)
				((BfmeQuickMatchStopBody *)this)->stop();
			else if (controlID == m_personalInfoKey)
				((BfmeQuickMatchHideOptionsGadgetsBody *)this)->showInfo(TRUE);
			else if (controlID == m_widenKey)
			{
				PeerRequest req;
				req.peerRequestType = 0x12;
				TheGameSpyPeerMessageQueue->addRequest(req);
				m_widen->winEnable(FALSE);
			}
			else if (controlID == m_startKey)
				((Rva00509B30StartRequest *)this)->sendStartQuickMatchRequest(control);
			else if (controlID == *(volatile Int *)0x012F47F8u)
				GameSpyToggleOverlay(GSOVERLAY_BUDDY);
			else if (controlID == m_backKey)
				((Rva505C80WindowVisibilityThunk *)this)->updateAt00505B40();
		}
		break;

	case GBM_MOUSE_ENTERING:
	case GBM_MOUSE_LEAVING:
		break;

	case 0x4014:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
			Int selected = (Int)mData2;

			if (controlID == m_mapSelectKey)
			{
				const LadderInfo *li = ((Rva005053C0GetLadderInfo *)this)->getLadderInfo();
				if (selected >= 0 && (!li || !li->randomMaps))
				{
					Bool wasSelected = (Bool)GadgetListBoxGetItemData(control, selected, 0);
					GadgetListBoxSetItemData(control, (void *)(!wasSelected), selected, 0);
					Int width = 10;
					Int height = 10;
					const Image *img = (!wasSelected)
						? *(const Image **)0x012F480Cu
						: *(const Image **)0x012F4810u;
					if (img)
					{
						width = min(GadgetListBoxGetColumnWidth(control, 0), img->getImageWidth());
						height = width;
					}
					GadgetListBoxAddEntryImage(control, img, selected, 0, height, width, TRUE, -1);
					GadgetListBoxAddEntryText(control,
						GadgetListBoxGetText(control, selected, 1),
						GameSpyColor[(wasSelected) ? GSCOLOR_MAP_UNSELECTED : GSCOLOR_MAP_SELECTED],
						selected, 1);
				}
				if (selected >= 0)
					GadgetListBoxSetSelected(control, -1);
			}
			((Rva00505570UpdateStartButton *)this)->updateStartButton();
		}
		break;

	case 0x4030:
		break;

	default:
		return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
