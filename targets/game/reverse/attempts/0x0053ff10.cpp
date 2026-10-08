// ?Rva0053FF10@BfmeAptScreenOnlineCustomMatch@@QAEHPAXI00@Z
// partial score=0.9694 date=2026-10-08
// ?Rva0053FF10@BfmeAptScreenOnlineCustomMatch@@QAEHPAXI00@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport

#include "ascii_string.h"
#include "unicode_string.h"
#define ASCIISTRING_H
#define UNICODESTRING_H
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
typedef unsigned int SOCKET;
#include <winsock2.h>
#include <string>
#include <vector>
#include <map>
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/StagingRoomGameInfo.h"

inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }

struct Rva0053FF10Request
{
    PeerRequest value;
    unsigned int field190;
};
typedef char Rva0053FF10RequestSize[sizeof(Rva0053FF10Request) == 0x194 ? 1 : -1];

class GameWindow;
class GameInfo;
class GameSpyStagingRoom;
typedef _STL::map<int, GameSpyStagingRoom*> StagingRoomMap;

void *GadgetListBoxGetItemData(GameWindow*, int, int);
void GadgetComboBoxGetSelectedPos(GameWindow*, int*);
void *GadgetComboBoxGetItemData(GameWindow*, int);
UnicodeString GadgetTextEntryGetText(GameWindow*);
void SignalUIInteraction(int);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

#define SLOT(n) virtual void slot##n() = 0
class Rva0053FF10GameSpySlots
{
public:
    SLOT(0); SLOT(1); SLOT(2); SLOT(3); SLOT(4); SLOT(5);
    virtual void offset18(int) = 0;
    virtual void offset1C() = 0;
    SLOT(8); SLOT(9); SLOT(10);
    virtual int offset2C() = 0;
    SLOT(12); SLOT(13); SLOT(14); SLOT(15); SLOT(16); SLOT(17); SLOT(18); SLOT(19);
    SLOT(20); SLOT(21); SLOT(22); SLOT(23); SLOT(24); SLOT(25); SLOT(26); SLOT(27);
    SLOT(28); SLOT(29); SLOT(30); SLOT(31); SLOT(32); SLOT(33); SLOT(34); SLOT(35); SLOT(36);
    virtual void offset94() = 0;
    virtual StagingRoomMap *offset98() = 0;
};
class Rva0053FF10ConfigSlots
{
public:
    SLOT(0); SLOT(1); SLOT(2); SLOT(3); SLOT(4); SLOT(5); SLOT(6); SLOT(7);
    SLOT(8); SLOT(9); SLOT(10); SLOT(11); SLOT(12); SLOT(13);
    virtual bool offset38() = 0;
};
#undef SLOT
class GameSpyInfoInterface;
class GameSpyConfigInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyConfigInterface *TheGameSpyConfig;
extern int rva012B78C4;
extern unsigned int rva012F4A04;
class WindowManager;
extern WindowManager *g_theWindowManager;

class Rva00529EC0State { public: int dispatch(int, void*, void*); };
class MpGameSetup { public: void bfmeSetSecondGame(GameInfo*); };
class Open2Pref0A9910 { public: void store(int); };
class BfmeLevelAN { public: char *bfmeBuildAN(unsigned int,int,int,int,int,int,int,int); };
struct Rva0053FF10Host { unsigned char pad[0x250]; unsigned int field250; };

class BfmeAptScreenOnlineCustomMatch
{
public:
    int Rva0053FF10(void*, unsigned int, void*, void*);
    void chatEnter(const char*);
    void applyStagingRoomRefresh();
    unsigned char head[0x34];
    Rva0053FF10Host *field034;
    unsigned char gap038[0x188-0x38];
    int field188;
    GameWindow *field18C;
    GameWindow *field190;
    GameWindow *field194;
    unsigned char gap198[8];
    GameWindow *field1A0;
    unsigned char gap1A4[8];
    GameWindow *field1AC;
    unsigned char gap1B0[4];
    bool field1B4;
    unsigned char gap1B5[0x1D4-0x1B5];
    bool field1D4;
    unsigned char field1D5;
    bool field1D6;
};

int BfmeAptScreenOnlineCustomMatch::Rva0053FF10(void *window, unsigned int message, void *data1, void *data2)
{
    int result = ((Rva00529EC0State*)((char*)this+0x40))->dispatch(message,data1,data2);
    GameWindow *control = (GameWindow*)data1;
    switch (message)
    {
    case 0x4031:
        if (control && control == field1A0)
        {
            UnicodeString text = GadgetTextEntryGetText(field1A0);
            bool enable = !text.isEmpty();
            if (field1D6 != enable)
            {
                const char *button = enable ? "EnableButtonCreatePopup" : "DisableButtonCreatePopup";
                field1D6 = enable;
                unsigned int movie = field034->field250;
                ((BfmeLevelAN*)g_theWindowManager)->bfmeBuildAN(movie,(int)"CallChild",1,(int)button,0,0,0,0);
            }
        }
        break;
    case 0x4030:
        if (control == field194 && !data2) chatEnter(0);
        break;
    case 0x4025:
        if (control == field190)
        {
            if (field1B4) break;
            int index = -1;
            GadgetComboBoxGetSelectedPos(field190,&index);
            if (index < 0) break;
            int id = (int)GadgetComboBoxGetItemData(field190,index);
            if (!id || id == ((Rva0053FF10GameSpySlots*)TheGameSpyInfo)->offset2C()) break;
            ((Rva0053FF10GameSpySlots*)TheGameSpyInfo)->offset1C();
            ((Rva0053FF10GameSpySlots*)TheGameSpyInfo)->offset18(id);
            if (((Rva0053FF10ConfigSlots*)TheGameSpyConfig)->offset38())
            {
                ((Rva0053FF10GameSpySlots*)TheGameSpyInfo)->offset94();
                applyStagingRoomRefresh();
                Rva0053FF10Request req;
                *(int*)&req.value.peerRequestType = 7;
                req.value.gameList.restrictGameList = true;
                TheGameSpyPeerMessageQueue->addRequest(req.value);
            }
        }
        else if (control == field1AC)
        {
            int index = -1;
            GadgetComboBoxGetSelectedPos(field1AC,&index);
            if (index >= 0)
                ((Open2Pref0A9910*)((char*)this+0x174))->store((int)GadgetComboBoxGetItemData(field1AC,index));
        }
        break;
    case 1:
        SignalUIInteraction(26);
        break;
    case 2:
        SignalUIInteraction(27);
        break;
    case 0x4015:
        if (control == field18C && (int)data2 >= 0 && field188 == 2) field188 = 9;
        break;
    case 0x4014:
        if (control == field18C)
        {
            int row = (int)data2;
            if (row >= 0)
            {
                StagingRoomMap *rooms = ((Rva0053FF10GameSpySlots*)TheGameSpyInfo)->offset98();
                int id = (int)GadgetListBoxGetItemData(control,row,0);
                StagingRoomMap::iterator it = rooms->find(id);
                GameSpyStagingRoom *game;
                if (it != rooms->end())
                {
                    game = it->second;
                    ((MpGameSetup*)((char*)this+0x40))->bfmeSetSecondGame(game);
                    if (game && *(int*)((char*)game+0x454) != *(int*)((char*)game+0x458))
                    {
                        if (!field1D4)
                        {
                            field1D4 = true;
                            unsigned int movie = field034->field250;
                            ((BfmeLevelAN*)g_theWindowManager)->bfmeBuildAN(movie,(int)"CallChild",1,(int)"EnableButtonJoinGame",0,0,0,0);
                        }
                        goto requestInfo;
                    }
                }
                else
                    ((MpGameSetup*)((char*)this+0x40))->bfmeSetSecondGame(0);
                if (field1D4)
                {
                    field1D4 = false;
                    unsigned int movie = field034->field250;
                            ((BfmeLevelAN*)g_theWindowManager)->bfmeBuildAN(movie,(int)"CallChild",1,(int)"DisableButtonJoinGame",0,0,0,0);
                }
requestInfo:
                unsigned int now = timeGetTime();
                Rva0053FF10Request req;
                *(int*)&req.value.peerRequestType = 20;
                req.value.stagingRoom.id = (int)GadgetListBoxGetItemData(control,row,0);
                if (rva012B78C4 != req.value.stagingRoom.id || now > rva012F4A04+1000)
                    TheGameSpyPeerMessageQueue->addRequest(req.value);
                rva012B78C4 = req.value.stagingRoom.id;
                rva012F4A04 = now;
            }
            else if (field1D4)
            {
                field1D4 = false;
                unsigned int movie = field034->field250;
                            ((BfmeLevelAN*)g_theWindowManager)->bfmeBuildAN(movie,(int)"CallChild",1,(int)"DisableButtonJoinGame",0,0,0,0);
            }
        }
        break;
    default:
        return result;
    }
    return 1;
}
