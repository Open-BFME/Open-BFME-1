// cl: /DNDEBUG /MD /EHsc
// stlport
// ?WOLBuddyOverlaySystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// WOLBuddyOverlaySystem retail 0x004EFAF0 784 bytes. Inline-forwarder
// AsciiString/UnicodeString over StringBase so by-value EH temps match.

#define _STLP_USE_STATIC_LIB 1
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int NameKeyType;
typedef int GPProfile;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED = 0,
	MSG_HANDLED = 1
};

enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 23,
	GBM_SELECTED = 0x4008,
	GLM_DOUBLE_CLICKED = 0x4015,
	GLM_RIGHT_CLICKED = 0x4016
};

enum GSOverlayType
{
	GSOVERLAY_PLAYERINFO = 0,
	GSOVERLAY_MAPSELECT,
	GSOVERLAY_BUDDY
};

enum RCItemType
{
	ITEM_BUDDY,
	ITEM_REQUEST,
	ITEM_NONBUDDY,
	ITEM_NONE
};

class GameWindow;
class WindowLayout;
class UnicodeString;
class AsciiString;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &o ) : StringBase<unsigned short>( o ) {}
	~UnicodeString() {}
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *s ) : StringBase<char>( s ) {}
	AsciiString( const AsciiString &that ) : StringBase<char>( that ) {}
	~AsciiString() {}
	void translate( const UnicodeString &that );
};

struct RightClickStruct
{
	Int mouseX;
	Int mouseY;
	Int pos;
};

class GameWindow
{
public:
	Int winGetWindowId(void);
	Int winBringToTop(void);
	Int winHide(Bool hide);
	Int winSetPosition(Int x, Int y);
	void winSetUserData(void *userData);
	WindowLayout *winGetLayout(void);
};

class WindowLayout
{
public:
	virtual void runInit(void *userData = 0) = 0;

	GameWindow *getFirstWindow(void) { return m_windowList; }

private:
	void *m_filenameString;
	GameWindow *m_windowList;
};

class GameWindowManager
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual WindowLayout *winCreateLayout(AsciiString filename) = 0;
	virtual void s28() = 0;
	virtual void s29() = 0;
	virtual void s30() = 0;
	virtual void s31() = 0;
	virtual void s32() = 0;
	virtual void s33() = 0;
	virtual void s34() = 0;
	virtual void s35() = 0;
	virtual void s36() = 0;
	virtual void s37() = 0;
	virtual void s38() = 0;
	virtual void s39() = 0;
	virtual void s40() = 0;
	virtual void s41() = 0;
	virtual void s42() = 0;
	virtual void s43() = 0;
	virtual void s44() = 0;
	virtual void s45() = 0;
	virtual void s46() = 0;
	virtual void winSetLoneWindow(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

class BuddyInfo
{
public:
	int pad;
};

typedef std::map<GPProfile, BuddyInfo> BuddyInfoMap;

class GameSpyInfo
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual BuddyInfoMap *getBuddyMap(void) = 0;
	virtual BuddyInfoMap *getBuddyRequestMap(void) = 0;
};

extern GameSpyInfo *TheGameSpyInfo;

class GameSpyRCMenuData
{
public:
	AsciiString m_nick;
	GPProfile m_id;
	RCItemType m_itemType;
};

WindowMsgHandledType BuddyControlSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
void *GadgetListBoxGetItemData(GameWindow *listbox, Int row, Int column = 0);
UnicodeString GadgetListBoxGetText(GameWindow *listbox, Int row, Int column = 0);
void GadgetListBoxSetSelected(GameWindow *listbox, Int row);
void GameSpyCloseOverlay(GSOverlayType t);
void refreshIgnoreList(void);
void setUnignoreText(WindowLayout *layout, AsciiString nick, GPProfile id);

extern NameKeyType buttonHideID;
extern NameKeyType radioButtonBuddiesID;
extern NameKeyType radioButtonIgnoreID;
extern NameKeyType listboxIgnoreID;
extern GameWindow *parentBuddies;
extern GameWindow *parentIgnore;
extern GameWindow *rcMenu;

// ?WOLBuddyOverlaySystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType WOLBuddyOverlaySystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	UnicodeString txtInput;
	if (BuddyControlSystem(window, msg, mData1, mData2) == MSG_HANDLED)
	{
		return MSG_HANDLED;
	}
	switch (msg)
	{
	case GWM_CREATE:
	{
		break;
	}

	case GWM_DESTROY:
	{
		break;
	}

	case GWM_INPUT_FOCUS:
	{
		if (mData1 == 1)
			*(Bool *)mData2 = true;

		return MSG_HANDLED;
	}
	case GLM_RIGHT_CLICKED:
	{
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();

		if (controlID == listboxIgnoreID)
		{
			RightClickStruct *rc = (RightClickStruct *)mData2;
			WindowLayout *rcLayout;
			if (rc->pos < 0)
				break;

			Bool isBuddy = false, isRequest = false;
			GPProfile profileID = (GPProfile)GadgetListBoxGetItemData(control, rc->pos);
			UnicodeString nick = GadgetListBoxGetText(control, rc->pos);
			BuddyInfoMap *buddies = TheGameSpyInfo->getBuddyMap();
			BuddyInfoMap::iterator bIt;
			bIt = buddies->find(profileID);
			if (bIt != buddies->end())
			{
				isBuddy = true;
			}
			else
			{
				buddies = TheGameSpyInfo->getBuddyRequestMap();
				bIt = buddies->find(profileID);
				if (bIt != buddies->end())
				{
					isRequest = true;
				}
			}

			GadgetListBoxSetSelected(control, rc->pos);
			if (isBuddy)
				rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddiesMenu.wnd"));
			else if (isRequest)
				rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddyRequestMenu.wnd"));
			else
				rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCNonBuddiesMenu.wnd"));
			rcMenu = rcLayout->getFirstWindow();
			rcMenu->winGetLayout()->runInit();
			rcMenu->winBringToTop();
			rcMenu->winHide(false);

			rcMenu->winSetPosition(rc->mouseX, rc->mouseY);
			GameSpyRCMenuData *rcData = new GameSpyRCMenuData;
			rcData->m_id = profileID;
			rcData->m_nick.translate(nick);
			rcData->m_itemType = (isBuddy) ? ITEM_BUDDY : ((isRequest) ? ITEM_REQUEST : ITEM_NONBUDDY);
			setUnignoreText(rcLayout, rcData->m_nick, rcData->m_id);
			rcMenu->winSetUserData((void *)rcData);
			TheWindowManager->winSetLoneWindow(rcMenu);
		}
		break;
	}
	case GBM_SELECTED:
	{
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();

		if (controlID == buttonHideID)
		{
			GameSpyCloseOverlay(GSOVERLAY_BUDDY);
		}
		else if (controlID == radioButtonBuddiesID)
		{
			parentBuddies->winHide(false);
			parentIgnore->winHide(true);
		}
		else if (controlID == radioButtonIgnoreID)
		{
			parentBuddies->winHide(true);
			parentIgnore->winHide(false);
			refreshIgnoreList();
		}
		break;
	}
	case GLM_DOUBLE_CLICKED:
	{
		break;
	}

	default:
		return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
