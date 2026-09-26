// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native BuddyControlSystem, retail 004ED400, 1390 bytes.
// Starts from the banked Zero Hour reconstruction; canonical source copyright
// 2025 Electronic Arts, GPL-3.0-or-later. BFME evidence and callee contracts:
// targets/game/reverse/identity_evidence/004ed400-buddy-control.md.
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}
template <> inline const unsigned short *StringBase<unsigned short>::str() const
{
	return m_data ? m_data->data : (const unsigned short *)L"";
}

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}
inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

// The legacy window header embeds its own UnicodeString in unused inline
// accessors. Give that header-only view a distinct name while preserving the
// canonical native strings used by this body.
#undef UNICODESTRING_H
#define UnicodeString Rva004ED400HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <map>
#include <string>
#include <time.h>

typedef int GPProfile;
struct BuddyRequest
{
	enum
	{
		BUDDYREQUEST_MESSAGE = 3
	};
	int buddyRequestType;
	union {
		struct
		{
			int recipient;
			wchar_t text[128];
		} message;
		char extent[0x2b4];
	} arg;
};
class BuddyInfo
{
  public:
	int m_id;
	AsciiString m_name, m_email, m_countryCode;
	int m_status;
	UnicodeString m_statusString, m_locationString;
	BuddyInfo(const BuddyInfo &);
	BuddyInfo &operator=(const BuddyInfo &);
	~BuddyInfo();
};
typedef std::map<int, BuddyInfo> BuddyInfoMap;
class BuddyMessage
{
  public:
	unsigned int m_timestamp;
	int m_senderID;
	AsciiString m_senderNick;
	int m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
	BuddyMessage()
	{
	}
	BuddyMessage(const BuddyMessage &);
	~BuddyMessage();
};

typedef std::list<BuddyMessage> BuddyMessageList;
class GameSpyInfoInterface
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual BuddyInfoMap *getBuddyMap() = 0;
	virtual BuddyInfoMap *getBuddyRequestMap() = 0;
	virtual BuddyMessageList *getBuddyMessages() = 0;
	virtual bool isBuddy(int) = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual int getLocalProfileID() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual AsciiString getLocalBaseName() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void slotF8() = 0;
	virtual void slotFC() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10C() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11C() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual bool isSavedIgnored(int) = 0;
};
class GameSpyBuddyMessageQueueInterface
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual bool isConnected() = 0;
	virtual void slot14() = 0;
	virtual void addRequest(const BuddyRequest &) = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
};
class GameTextInterface
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(const char *, bool * = 0) = 0;
	virtual UnicodeString fetch(AsciiString, bool * = 0) = 0;
};

extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern GameTextInterface *TheGameText;

// BFME listboxBuddies and isInit are at global 012F4268 and 012F4278.
struct BuddyControls
{
	GameWindow *listboxChat;
	int listboxChatID;
	GameWindow *listboxBuddies;
	int listboxBuddiesID;
	GameWindow *textEntryEdit;
	int textEntryEditID;
	bool isInit;
};
static BuddyControls buddyControls;
extern int GameSpyColor[];
enum
{
	GSCOLOR_DEFAULT = 0,
	GSCOLOR_PLAYER_BUDDY = 8,
	GSCOLOR_PLAYER_IGNORED = 11,
	ITEM_BUDDY = 0,
	ITEM_REQUEST = 1
};

const int MAX_SLOTS = 8, MAX_BUDDY_CHAT_LEN = 128;
const unsigned GLM_RIGHT_CLICKED = 0x4016, GEM_EDIT_DONE = 0x4030;
struct RightClickStruct
{
	int mouseX, mouseY, pos;
};
typedef int RCItemType;
class GameSpyRCMenuData
{
  public:
	AsciiString m_nick;
	int m_id;
	RCItemType m_itemType;
};
struct Rva004ED400LayoutView
{
	virtual void runInit(void * = 0) = 0;
	int opaque04;
	GameWindow *first;
	GameWindow *getFirstWindow()
	{
		return first;
	}
};
class Rva004ED400WindowManager
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual WindowLayout *winCreateLayout(AsciiString) = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void winSetLoneWindow(GameWindow *) = 0;
};
extern Rva004ED400WindowManager *TheWindowManager;
class Rva004ED400Display
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;
};
extern Rva004ED400Display *TheDisplay;
class Player
{
  public:
	bool isPlayerActive() const;
};
class Rva004ED400PlayerList
{
  public:
	char opaque00[12];
	Player *m_local;
	Player *getLocalPlayer()
	{
		return m_local;
	}
};
extern Rva004ED400PlayerList *ThePlayerList;
class GameSpyGameSlot
{
  public:
	char opaque00[0x44];
	int m_profileID;
	int getProfileID() const
	{
		return m_profileID;
	}
};
class GameSpyStagingRoom
{
  public:
	char opaque00[12];
	bool m_inGame, m_inProgress;
	bool isInGame() const
	{
		return m_inGame;
	}
	bool isGameInProgress() const
	{
		return m_inProgress;
	}
	GameSpyGameSlot *getGameSpySlot(int);
};
extern GameSpyStagingRoom *TheGameSpyGame;
static GameWindow *rcMenu;
void GadgetListBoxGetSelected(GameWindow *, int *);
void *GadgetListBoxGetItemData(GameWindow *, int, int = 0);
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int = -1, bool = true);
void GadgetListBoxSetSelected(GameWindow *, int);
UnicodeString GadgetListBoxGetText(GameWindow *, int, int = 0);
UnicodeString GadgetTextEntryGetText(GameWindow *);
void GadgetTextEntrySetText(GameWindow *, UnicodeString);
void setUnignoreText(WindowLayout *, AsciiString, int);
void insertChat(BuddyMessage);
extern const UnicodeString Rva01336E54EmptyUnicode;
WindowMsgHandledType BuddyControlSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	if (!TheGameSpyInfo || !buddyControls.isInit)
	{
		return MSG_IGNORED;
	}

	switch (msg)
	{
	case GLM_RIGHT_CLICKED: {
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();

		if (controlID == buddyControls.listboxBuddiesID)
		{
			RightClickStruct *rc = (RightClickStruct *)mData2;
			WindowLayout *rcLayout;
			if (rc->pos < 0)
				break;

			GPProfile profileID = (GPProfile)GadgetListBoxGetItemData(control, rc->pos, 0);
			RCItemType itemType = (RCItemType)(Int)GadgetListBoxGetItemData(control, rc->pos, 1);
			UnicodeString nick = GadgetListBoxGetText(control, rc->pos);

			GadgetListBoxSetSelected(control, rc->pos);
			if (itemType == ITEM_BUDDY)
				rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddiesMenu.wnd"));
			else if (itemType == ITEM_REQUEST)
				rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddyRequestMenu.wnd"));
			else
				rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCNonBuddiesMenu.wnd"));
			rcMenu = ((Rva004ED400LayoutView *)rcLayout)->getFirstWindow();
			((Rva004ED400LayoutView *)rcMenu->winGetLayout())->runInit();
			rcMenu->winBringToTop();
			rcMenu->winHide(FALSE);

			ICoord2D rcSize, rcPos;
			rcMenu->winGetSize(&rcSize.x, &rcSize.y);
			rcPos.x = rc->mouseX;
			rcPos.y = rc->mouseY;
			if (rc->mouseX + rcSize.x > TheDisplay->getWidth())
				rcPos.x = TheDisplay->getWidth() - rcSize.x;
			if (rc->mouseY + rcSize.y > TheDisplay->getHeight())
				rcPos.y = TheDisplay->getHeight() - rcSize.y;
			rcMenu->winSetPosition(rcPos.x, rcPos.y);

			GameSpyRCMenuData *rcData = new GameSpyRCMenuData;
			rcData->m_id = profileID;
			rcData->m_nick.translate(nick);
			rcData->m_itemType = itemType;
			setUnignoreText(rcLayout, rcData->m_nick, rcData->m_id);
			rcMenu->winSetUserData((void *)rcData);
			TheWindowManager->winSetLoneWindow(rcMenu);
		}
		else
			return MSG_IGNORED;
		break;
	}
	case GEM_EDIT_DONE: {
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();
		if (controlID != buddyControls.textEntryEditID)
			return MSG_IGNORED;

		Int selected = -1;
		GadgetListBoxGetSelected(buddyControls.listboxBuddies, &selected);
		if (selected >= 0)
		{
			GPProfile selectedProfile = (GPProfile)GadgetListBoxGetItemData(buddyControls.listboxBuddies, selected);
			BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
			BuddyInfoMap::iterator recipIt = m->find(selectedProfile);
			if (recipIt == m->end())
				break;

			if (TheGameSpyGame && TheGameSpyGame->isInGame() && TheGameSpyGame->isGameInProgress() &&
				!ThePlayerList->getLocalPlayer()->isPlayerActive())
			{
				for (Int i = 0; i < MAX_SLOTS; ++i)
				{
					if (TheGameSpyGame->getGameSpySlot(i)->getProfileID() == selectedProfile)
					{
						if (buddyControls.listboxChat)
						{
							GadgetListBoxAddEntryText(buddyControls.listboxChat,
													  TheGameText->fetch("Buddy:CantTalkToIngameBuddy"),
													  GameSpyColor[GSCOLOR_DEFAULT], -1, -1);
						}
						return MSG_HANDLED;
					}
				}
			}

			UnicodeString txtInput;
			txtInput = GadgetTextEntryGetText(buddyControls.textEntryEdit);
			GadgetTextEntrySetText(buddyControls.textEntryEdit, Rva01336E54EmptyUnicode);
			((StringBase<unsigned short> *)&txtInput)->trim();
			if (!txtInput.isEmpty())
			{
				BuddyRequest req;
				req.buddyRequestType = BuddyRequest::BUDDYREQUEST_MESSAGE;
				wcsncpy(req.arg.message.text, txtInput.str(), MAX_BUDDY_CHAT_LEN);
				req.arg.message.text[MAX_BUDDY_CHAT_LEN - 1] = 0;
				req.arg.message.recipient = selectedProfile;
				TheGameSpyBuddyMessageQueue->addRequest(req);

				BuddyMessageList *messages = TheGameSpyInfo->getBuddyMessages();
				BuddyMessage message;
				message.m_timestamp = time(NULL);
				message.m_senderID = TheGameSpyInfo->getLocalProfileID();
				message.m_senderNick = TheGameSpyInfo->getLocalBaseName();
				message.m_recipientID = selectedProfile;
				message.m_recipientNick = recipIt->second.m_name;
				message.m_message = UnicodeString(req.arg.message.text);
				messages->push_back(message);
				insertChat(message);
			}
		}
		else if (buddyControls.listboxChat)
		{
			GadgetListBoxAddEntryText(buddyControls.listboxChat, TheGameText->fetch("Buddy:SelectBuddyToChat"),
									  GameSpyColor[GSCOLOR_DEFAULT], -1, -1);
		}
		break;
	}
	default:
		return MSG_IGNORED;
	}
	return MSG_HANDLED;
}
