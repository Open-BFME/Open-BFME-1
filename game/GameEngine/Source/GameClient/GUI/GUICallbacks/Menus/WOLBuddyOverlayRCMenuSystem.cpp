// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#include <map>
#include "ascii_string.h"
// Port of EA GPL-3.0 GeneralsMD WOLBuddyOverlay.cpp. FunctionLexicon registers
// WOLBuddyOverlayRCMenuSystem by name; retail matches the message switch and
// add/delete/ignore/stats operations, request IDs 6/7/8 and virtual slots.
// BFME BuddyRequest size 0x2b8: getRequest at 0063C770 copies 0xae dwords.
// BFME PSRequest size 0x210: matched PSRequestCopyCtor.cpp and deque stride.
// GameSpyRCMenuData fields agree with retail reads +0/+4/+8 and the ZH type.
// Native STLport map::erase visibility is required: an opaque tree shim adds
// spills and 61 bytes despite forwarding to the same tree erase function.

#define NULL 0
#define TRUE true
typedef int Int;
typedef unsigned UnsignedInt;
typedef unsigned WindowMsgData;
typedef bool Bool;
typedef int GPProfile;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum { GWM_CREATE = 1, GWM_DESTROY = 2, GGM_CLOSE = 0x4005, GBM_SELECTED = 0x4008 };
enum RCItemType { ITEM_BUDDY, ITEM_REQUEST, ITEM_NONBUDDY, ITEM_NONE };
enum GSOverlayType { GSOVERLAY_PLAYERINFO };
class WindowLayout {
  public:
    virtual void slot0();
    virtual ~WindowLayout();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void destroyWindows();
    void deleteInstance() { delete this; }
};
class GameWindow {
  public:
    int winGetWindowId();
    void *winGetUserData();
    void winSetUserData(void *);
    WindowLayout *winGetLayout();
    void destroyLayout();
};
class GameSpyRCMenuData {
  public:
    AsciiString m_nick;
    int m_id;
    RCItemType m_itemType;
};
struct Gen_t_004ee060_p12cd {
    int a[3];
};
typedef _STL::map<int, Gen_t_004ee060_p12cd> BuddyInfoMap;
class BuddyRequest {
  public:
    enum { BUDDYREQUEST_DELBUDDY = 6, BUDDYREQUEST_OKADD = 7, BUDDYREQUEST_DENYADD = 8 };
    int buddyRequestType;
    union {
        struct {
            int id;
        } profile;
        char bytes[0x2b4];
    } arg;
};
class PSRequest {
  public:
    PSRequest();
    ~PSRequest();
    enum { PSREQUEST_READPLAYERSTATS = 0 };
    int requestType;
    struct {
        int id;
        char rest[0x1c0];
    } player;
    char tail[0x48];
};
class GameSpyInfo {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
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
    virtual void slot20();
    virtual BuddyInfoMap *getBuddyMap();
    virtual BuddyInfoMap *getBuddyRequestMap();
    virtual void slot23();
    virtual bool isBuddy(int);
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void addToSavedIgnoreList(int, AsciiString);
    virtual void removeFromSavedIgnoreList(int);
    virtual bool isSavedIgnored(int);
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void addToIgnoreList(AsciiString);
    virtual void removeFromIgnoreList(AsciiString);
    virtual bool isIgnored(AsciiString);
};
extern GameSpyInfo *TheGameSpyInfo;
class GameSpyBuddyMessageQueueInterface {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void addRequest(const BuddyRequest &);
};
class GameSpyPSMessageQueueInterface {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void addRequest(const PSRequest &);
};
class GameWindowManager {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
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
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void winSetLoneWindow(GameWindow *);
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
extern GameWindowManager *TheWindowManager;
extern GameWindow *rcMenu;
extern int buttonAddID, buttonDeleteID, buttonPlayID, buttonIgnoreID, buttonStatsID;
void RequestBuddyAdd(int, AsciiString);
void updateBuddyInfo();
void PopulateLobbyPlayerListbox();
void refreshIgnoreList();
void GameSpyCloseOverlay(GSOverlayType);
void GameSpyOpenOverlay(GSOverlayType);
void SetLookAtPlayer(int, AsciiString);
static void closeRightClickMenu(GameWindow *win) {
    if (win) {
        WindowLayout *winLay = win->winGetLayout();
        if (!winLay)
            return;
        winLay->destroyWindows();
        winLay->deleteInstance();
        winLay = 0;
    }
}
WindowMsgHandledType WOLBuddyOverlayRCMenuSystem(GameWindow *window, UnsignedInt msg,
                                                 WindowMsgData mData1, WindowMsgData mData2) {

    switch (msg) {

    case GWM_CREATE: {

        break;
    } // case GWM_DESTROY:

    case GWM_DESTROY: {
        rcMenu = NULL;
        break;
    } // case GWM_DESTROY:

    case GGM_CLOSE: {
        closeRightClickMenu(window);
        // rcMenu = NULL;
        break;
    }

    case GBM_SELECTED: {
        GameWindow *control = (GameWindow *)mData1;
        Int controlID = control->winGetWindowId();
        GameSpyRCMenuData *rcData = (GameSpyRCMenuData *)window->winGetUserData();
        if (!rcData)
            break;
        GPProfile profileID = rcData->m_id;
        AsciiString nick = rcData->m_nick;

        Bool isBuddy = false, isRequest = false;
        Bool isGameSpyUser = profileID > 0;
        if (rcData->m_itemType == ITEM_BUDDY)
            isBuddy = TRUE;
        else if (rcData->m_itemType == ITEM_REQUEST)
            isRequest = TRUE;

        if (rcData) {
            delete rcData;
            rcData = NULL;
        }
        window->winSetUserData(NULL);

        if (controlID == buttonAddID) {
            if (!isGameSpyUser)
                break;
            if (isRequest) {
                // ok the request
                BuddyRequest req;
                req.buddyRequestType = BuddyRequest::BUDDYREQUEST_OKADD;
                req.arg.profile.id = profileID;
                TheGameSpyBuddyMessageQueue->addRequest(req);

                BuddyInfoMap *m = TheGameSpyInfo->getBuddyRequestMap();
                m->erase(profileID);
                // if the profile ID is not from a buddy and we're okaying his request, then
                // request to add him to our list automatically CLH 2-18-03
                if (!TheGameSpyInfo->isBuddy(profileID)) {
                    RequestBuddyAdd(profileID, nick);
                }
                updateBuddyInfo();
            } else if (!isBuddy) {
                RequestBuddyAdd(profileID, nick);
            }
        } else if (controlID == buttonDeleteID) {
            if (!isGameSpyUser)
                break;
            if (isBuddy) {
                // delete the buddy
                BuddyRequest req;
                req.buddyRequestType = BuddyRequest::BUDDYREQUEST_DELBUDDY;
                req.arg.profile.id = profileID;
                TheGameSpyBuddyMessageQueue->addRequest(req);
            } else {
                // delete the request
                BuddyRequest req;
                req.buddyRequestType = BuddyRequest::BUDDYREQUEST_DENYADD;
                req.arg.profile.id = profileID;
                TheGameSpyBuddyMessageQueue->addRequest(req);
                BuddyInfoMap *m = TheGameSpyInfo->getBuddyRequestMap();
                m->erase(profileID);
            }
            BuddyInfoMap *buddies =
                (isBuddy) ? TheGameSpyInfo->getBuddyMap() : TheGameSpyInfo->getBuddyRequestMap();
            buddies->erase(profileID);
            updateBuddyInfo();
            PopulateLobbyPlayerListbox();
        } else if (controlID == buttonPlayID) {
        } else if (controlID == buttonIgnoreID) {
            if (isGameSpyUser) {
                if (TheGameSpyInfo->isSavedIgnored(profileID)) {
                    TheGameSpyInfo->removeFromSavedIgnoreList(profileID);
                } else {
                    TheGameSpyInfo->addToSavedIgnoreList(profileID, nick);
                }
            } else {
                if (TheGameSpyInfo->isIgnored(nick)) {
                    TheGameSpyInfo->removeFromIgnoreList(nick);
                } else {
                    TheGameSpyInfo->addToIgnoreList(nick);
                }
            }
            updateBuddyInfo();
            refreshIgnoreList();
            // repopulate our player listboxes now
            PopulateLobbyPlayerListbox();
        } else if (controlID == buttonStatsID) {
            GameSpyCloseOverlay(GSOVERLAY_PLAYERINFO);
            SetLookAtPlayer(profileID, nick);
            GameSpyOpenOverlay(GSOVERLAY_PLAYERINFO);
            PSRequest req;
            req.requestType = PSRequest::PSREQUEST_READPLAYERSTATS;
            req.player.id = profileID;
            TheGameSpyPSMessageQueue->addRequest(req);
        }
        TheWindowManager->winSetLoneWindow(0);
        window->destroyLayout();
        break;
    }
    default:
        return MSG_IGNORED;

    } // Switch
    return MSG_HANDLED;
}
