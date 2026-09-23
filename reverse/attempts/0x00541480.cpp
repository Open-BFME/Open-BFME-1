// ?d_00541480@@YAXXZ
// partial score=0.224273268 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// PARTIAL research draft, NOT a matched or behavior-complete implementation.
// RVA 00541480, code extent 11593. See build/gap_00540910/GAP.md.
// All retail switch cases are represented. ABI/layout and compiler-shape
// assumptions remain; no semantic or byte-equivalence claim is made.
// All Rva names preserve addresses. Slot and field names assert offsets only.
#define _STLP_USE_STATIC_LIB
#include "ascii_string.h"
#include "unicode_string.h"
#include <string>
#include <sstream>

// Existing canonical string declarations; retail inlines these forwards.
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString& UnicodeString::operator=(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this;
}
template<class T> inline const T* StringBase<T>::str() const { return m_data ? m_data->data : (const T*)L""; }
template<class T> inline int StringBase<T>::getLength() const { return m_data ? m_data->length : 0; }

extern "C" int __cdecl strcmp(const char*,const char*);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
extern "C" __declspec(dllimport) int __cdecl atoi(const char*);
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*,const char*,unsigned);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long);

// These three-pointer string records are read by the caller, but are owned by
// the real out-of-line PeerResponse constructor/destructor (004DAB40/004DAC70).
template<class C> struct RvaPeerString { C *first,*last,*limit; const C* c_str() const {return first;} bool empty() const{return first==last;} };
class PeerResponse {
public:
    PeerResponse(); ~PeerResponse();
    int type;
    RvaPeerString<char> groupRoomName,nick,oldNick;
    RvaPeerString<wchar_t> text;
    RvaPeerString<char> locale,gameOptions;
    RvaPeerString<wchar_t> serverName;
    RvaPeerString<char> ping,ladderIP,map;
    RvaPeerString<char> playerNames[8],command,commandOptions;
    union { int words[143]; unsigned char bytes[572]; } payload;
};
typedef char RvaResponseSize[sizeof(PeerResponse)==0x330?1:-1];
class PeerRequest {
public:
    PeerRequest(); ~PeerRequest();
    int type; std::string nick; std::wstring text; std::string password,email,id,options;
    unsigned char pad4C[0xE4-0x4C]; bool fieldE4; unsigned char padE5[0x194-0xE5];
};
typedef char RvaRequestSize[sizeof(PeerRequest)==0x194?1:-1];

struct GameSlotConnectInfo { unsigned ip; unsigned short port; };
enum SlotState { Slot0,Slot1,Slot2,Slot3,Slot4,Slot5 };
class GameSlot {
public:
    virtual void v00();
    int field04; bool field08,field09; unsigned short field0A;
    int field0C,field10,field14,field18;
    unsigned char pad1C[0x30-0x1C];
    unsigned field30; unsigned short field34; unsigned short field36;
    int field38; unsigned char pad3C[0x44-0x3C];
    int field44; unsigned char pad48[0x58-0x48]; int field58,field5C;
    unsigned char pad60[8]; int field68,field6C;
    void setPlayerTemplate(int);
    void setState(SlotState,UnicodeString,const GameSlotConnectInfo*);
    UnicodeString getName() const;
    void setPingString(AsciiString);
    void setMapAvailability(bool);
    bool isPlayer(AsciiString) const;
    bool isHuman() const; bool isOpen() const; bool isOccupied() const;
    void setName(UnicodeString);
};
class Rva0061F0C0 {
public:
    Rva0061F0C0(); Rva0061F0C0(const Rva0061F0C0&); ~Rva0061F0C0();
    virtual void v00(); unsigned char pad04[0x30-4]; GameSlotConnectInfo field30; unsigned char pad38[12];
    void setState(SlotState,UnicodeString,const GameSlotConnectInfo*);
};
typedef char RvaBaseSlotSize[sizeof(Rva0061F0C0)==0x44?1:-1];
class GameSpyStagingRoom {
public:
    GameSpyStagingRoom(); GameSpyStagingRoom(const GameSpyStagingRoom&); ~GameSpyStagingRoom();
    GameSpyStagingRoom& operator=(const GameSpyStagingRoom&);
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(bool);
    virtual bool v10(); virtual int v14(); virtual void v18();
    unsigned char pad04[8]; bool field0C,field0D; unsigned char pad0E[0x40-0x0E]; unsigned field40;
    unsigned char pad44[0x54-0x44]; int field54;
    unsigned char pad58[0x41C-0x58]; int field41C;
    unsigned char pad420[8]; bool field428,field429; unsigned short pad42A;
    unsigned field42C,field430,field434,field438;
    unsigned char pad43C[0x450-0x43C];
    unsigned short field450; unsigned short pad452;
    int field454,field458,field45C,field460,field464;
    GameSlot* getSlot(int);
    const GameSlot* getConstSlot(int) const;
    GameSlot* Rva00637D10(int);
    void Rva004D4880(UnicodeString);
    void setPingString(AsciiString);
    void Rva004D4810(AsciiString);
    void setMap(AsciiString);
    int getSlotNum(AsciiString) const;
    AsciiString getMap() const;
    void Rva0061F630(int,Rva0061F0C0);
};
typedef char RvaRoomSize[sizeof(GameSpyStagingRoom)==0x468?1:-1];

class Rva004F1280 {
public:
    Rva004F1280(); Rva004F1280(const Rva004F1280&); ~Rva004F1280();
    AsciiString field00,field04,field08;
    int field0C,field10,field14,field18,field1C,field20,field24,field28,field2C,field30;
};
typedef char RvaRowSize[sizeof(Rva004F1280)==0x34?1:-1];
struct Rva004F18C0Node { unsigned char pad00[0x18]; AsciiString field18; };
class Rva004FB170 { public: Rva004F18C0Node* field00; void run(); Rva004F18C0Node* Rva004F18C0(const AsciiString&); };

// Slots are witnessed by the call instructions, not assigned guessed names.
#define V(N) virtual void v##N()
class GameSpyInfo {
public:
    V(00); V(04); V(08); V(0C); V(10); V(14); V(18); V(1C); V(20);
    virtual void v24(int); virtual void v28(int); V(2C); V(30); V(34); virtual void v38(int); V(3C);
    virtual void v40(Rva004F1280,AsciiString); virtual void v44(AsciiString);
    virtual Rva004FB170* v48(); V(4C); V(50); V(54); V(58); V(5C); V(60); V(64);
    virtual AsciiString v68(); V(6C); V(70); V(74); V(78); V(7C); V(80); V(84); V(88); V(8C); V(90);
    V(94); V(98); V(9C); virtual void vA0(GameSpyStagingRoom); virtual void vA4(GameSpyStagingRoom); virtual void vA8(GameSpyStagingRoom);
    V(AC); V(B0); V(B4); V(B8); V(BC); virtual bool vC0(); virtual GameSpyStagingRoom* vC4(); V(C8); V(CC);
    V(D0); V(D4); V(D8); V(DC); V(E0); V(E4); V(E8);
    virtual int vEC(UnicodeString,int,void*);
    virtual int vF0(AsciiString,int,UnicodeString,bool,int,void*);
    V(F4); V(F8); V(FC); V(100); V(104); V(108); V(10C); V(110); V(114); V(118); V(11C); V(120);
    V(124); V(128); V(12C); V(130); V(134); V(138); V(13C); V(140); V(144); V(148); V(14C); V(150); V(154);
    V(158); V(15C); V(160); V(164); V(168); virtual int v16C();
};
class GameSpyPeerMessageQueueInterface {
public:
    V(00); V(04); V(08); V(0C); V(10); V(14); virtual void v18(const PeerRequest&); V(1C); V(20); virtual bool v24(PeerResponse&);
};
class GameText {
public:
    V(00); V(04); V(08); V(0C); V(10); V(14); V(18); V(1C); V(20);
    virtual UnicodeString v24(AsciiString,bool);
    virtual UnicodeString v28(const char*,bool);
};
class RvaMember40 { public: V(00); V(04); void Rva00523380(unsigned short,unsigned char); void Rva00523340(); void Rva005235B0(); };
class PSPlayerStats {
public: PSPlayerStats(const PSPlayerStats&); ~PSPlayerStats(); int field00; unsigned char pad04[0x1C4-4];
};
class PSRequest {
public: PSRequest(); ~PSRequest(); int field00; PSPlayerStats field04; unsigned char tail[0x210-0x1C8];
};
class Rva012F76F0 {
public: V(00); V(04); V(08); V(0C); virtual void v10(const PSRequest&); V(14); V(18); V(1C);
    virtual void v20(PSPlayerStats); virtual PSPlayerStats v24(int);
};
#undef V

extern GameSpyInfo* TheGameSpyInfo;
extern GameSpyStagingRoom* TheGameSpyGame;
extern GameSpyPeerMessageQueueInterface* TheGameSpyPeerMessageQueue;
extern GameText* TheGameText;
extern int Rva012B9200;
extern Rva012F76F0* Rva012F76F0Global;
class NAT { public: void processGlobalMessage(int,const char*); }; extern NAT* TheNAT;
class RvaMapMeta { public: UnicodeString field00; unsigned char pad04[0x26-4]; bool field26; UnicodeString Rva00451240(); };
class MapCache { public: RvaMapMeta* findMap(AsciiString); }; extern MapCache* TheMapCache;
class Rva012ED750 { public: int Rva000863E0(); }; extern Rva012ED750* Rva012ED750Global;
class Rva012ED5FC { public: int Rva00086460(); }; extern Rva012ED5FC* Rva012ED5FCGlobal;
extern const AsciiString Rva01336E50;
extern const UnicodeString Rva01336E54;
class Shell { public: void pop(); }; extern Shell* TheShell;
class GameState { public: AsciiString portableMapPathToRealMapPath(const AsciiString&) const; AsciiString getMapLeafName(const AsciiString&) const; }; extern GameState* TheGameState;

void HandleBuddyResponses();
void Rva004DD2B0();
void GameSpyCloseAllOverlays();
void GSMessageBoxOk(UnicodeString,UnicodeString,void(__cdecl*)());
void TearDownGameSpy();
void SendStatsToOtherPlayers(const GameSpyStagingRoom*);
void __stdcall Rva00538290(const PeerResponse*,Rva004F1280*);
class Rva004675F0 { public: void run(void*,const char*,int,const char*,int,int,int,int); };
extern Rva004675F0* Rva012F19E8;
bool __cdecl Rva000AA230(const AsciiString&,const char*);
PSPlayerStats __cdecl Rva00659670(std::string);
bool WouldMapTransfer(GameSpyStagingRoom*);
void postPeerRequest19();
bool Rva00621C40(GameSpyStagingRoom*,AsciiString,bool);
std::wstring MultiByteToWideCharSingleLine(const char*);

class Rva00541480 {
public:
    void run();
    void Rva005409A0(); void Rva005406E0(); void Rva005397D0(); void Rva0053FC00();
    unsigned char field00[0x34];
    unsigned char* field34;
    unsigned char field38[8];
    RvaMember40 field40;
    unsigned char pad44[0x50-0x44]; bool field50;
    unsigned char pad51[0x188-0x51]; int field188;
    unsigned char pad18C[0x198-0x18C]; void* field198;
    unsigned char pad19C[0x1B4-0x19C]; bool field1B4; unsigned char pad1B5[3];
    int field1B8,field1BC; unsigned field1C0,field1C4; bool field1C8;
};

void Rva00541480::run()
{
    HandleBuddyResponses();
    Rva004DD2B0();
    int remaining=TheGameSpyInfo->v16C();
    PeerResponse response;
    bool important=false;
    while(remaining-- && !important && TheGameSpyPeerMessageQueue->v24(response)) {
        switch(response.type) {
        case 1: {
            important=true;
            UnicodeString title,body;
            AsciiString key;
            key.format("GUI:GSDisconReason%d",response.payload.words[0]);
            title=TheGameText->v28("GUI:GSErrorTitle",false);
            body=TheGameText->v24(key,false);
            GameSpyCloseAllOverlays();
            GSMessageBoxOk(title,body,0);
            TheGameSpyInfo->v04();
            TheShell->pop();
            TearDownGameSpy();
            break;
        }
        case 2:
            if(field198)
                TheGameSpyInfo->vF0(AsciiString(response.nick.c_str()),response.payload.words[1],
                    UnicodeString(response.text.c_str()),!response.payload.bytes[0],
                    *(const int*)&response.payload.bytes[1],field198);
            break;
        case 4: {
            GameSpyStagingRoom room;
            switch(response.payload.words[1]) {
            case 0: case 1: {
                if(response.payload.words[51]==100) TheGameSpyInfo->vBC();
                bool hasMap=!response.map.empty();
                bool own=Rva000AA230(TheGameSpyInfo->v68(),response.playerNames[0].c_str());
                if(own || !hasMap) {
                    room.field41C=response.payload.words[0];
                    TheGameSpyInfo->vA8(room);
                    break;
                }
                room.Rva004D4880(UnicodeString(response.serverName.c_str()));
                room.field41C=response.payload.words[0];
                room.field430=response.payload.words[4];
                room.field428=response.payload.bytes[9]!=0;
                room.field54=response.payload.words[52];
                room.field434=response.payload.words[5];
                room.field429=response.payload.bytes[10]!=0;
                room.field438=response.payload.words[6];
                room.field42C=response.payload.words[3];
                room.setPingString(AsciiString(response.ping.c_str()));
                room.Rva004D4810(AsciiString(response.ladderIP.c_str()));
                room.field450=*(const unsigned short*)&response.payload.bytes[28];
                room.field454=response.payload.words[48];
                room.field45C=response.payload.words[49];
                room.field458=response.payload.words[50];
                AsciiString map(response.map.c_str()),normalised("");
                for(int i=0;i<map.getLength();++i) {
                    char ch=map.getCharAt(i);
                    if(ch=='/') ch='\\';
                    ((StringBase<char>*)&normalised)->concat(&ch,1);
                }
                room.setMap(TheGameState->portableMapPathToRealMapPath(normalised));
                for(int i=0;i<8;++i) {
                    GameSlot* slot=room.Rva00637D10(i);
                    if(slot) {
                        slot->field58=response.payload.words[8+i];
                        slot->field5C=response.payload.words[16+i];
                        slot->field44=response.payload.words[24+i];
                        slot->setPlayerTemplate(response.payload.words[32+i]);
                        slot->field0C=response.payload.words[40+i];
                        int id=response.payload.words[24+i];
                        if(id==2) {GameSlotConnectInfo connect={0,0}; slot->setState(Slot2,Rva01336E54,&connect);}
                        else if(id==3) {GameSlotConnectInfo connect={0,0}; slot->setState(Slot3,Rva01336E54,&connect);}
                        else if(id==4) {GameSlotConnectInfo connect={0,0}; slot->setState(Slot4,Rva01336E54,&connect);}
                        else if(!response.playerNames[i].empty()) {
                            UnicodeString name;
                            name.translate(AsciiString(response.playerNames[i].c_str()));
                            GameSlotConnectInfo connect={0,0}; slot->setState(Slot5,name,&connect);
                        } else {GameSlotConnectInfo connect={0,0}; slot->setState(Slot0,Rva01336E54,&connect);}
                    }
                }
                if(response.payload.words[1]==0) TheGameSpyInfo->vA0(room);
                else TheGameSpyInfo->vA4(room);
                break;
            }
            case 2:
                room.field41C=response.payload.words[0];
                TheGameSpyInfo->vA8(room); break;
            case 3: TheGameSpyInfo->v94(); break;
            }
            break;
        }
        case 5:
            TheGameSpyInfo->vBC(); Rva0053FC00(); break;
        case 7:
            important=true;
            if(response.payload.bytes[4]) {
                TheGameSpyInfo->v28(response.payload.words[0]);
                TheGameSpyInfo->v38(response.payload.words[0]);
                TheGameSpyInfo->v48()->run();
                Rva005397D0();
            } else {
                TheGameSpyInfo->v24(1); Rva005397D0();
            }
            break;
        case 8:
            if(response.payload.words[0]==0) {
                TheGameSpyInfo->vB4(); TheGameSpyInfo->vCC();
                if(TheGameSpyInfo->vC4()) Rva005409A0();
            } else {
                GSMessageBoxOk(TheGameText->v28("APT:CreateGame",false),TheGameText->v28("GUI:GSFailedToHost",false),0);
                Rva005406E0();
            }
            break;
        case 9: {
            important=true;
            if(field1B4) {
                field1B4=false;
                Rva012F19E8->run(*(void**)(field34+0x250),"CallChild",1,"ClosePassword",0,0,0,0);
            }
            if(response.payload.bytes[4]==1) {
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                bool found=false;
                if(room) {
                    for(int i=0;i<8;++i) {
                        AsciiString name;
                        name.translate(room->getConstSlot(0)->getName());
                        char buf[256]={0};
                        strncpy(buf,response.playerNames[i].c_str(),255);
                        if(!strcmp(name.str(),buf)) found=true;
                    }
                }
                if(response.payload.bytes[4]==1 && found) {
                    if(TheGameSpyInfo->vC4()) Rva005409A0();
                    break;
                }
            }
            UnicodeString error;
            switch(response.payload.words[2]) {
            case 1: error=TheGameText->v28("GUI:JoinFailedRoomFull",false); break;
            case 2: error=TheGameText->v28("GUI:JoinFailedInviteOnly",false); break;
            case 3: error=TheGameText->v28("GUI:JoinFailedBannedFromRoom",false); break;
            case 4: error=TheGameText->v28("GUI:JoinFailedBadPassword",false); break;
            case 5: error=TheGameText->v28("GUI:JoinFailedAlreadyInRoom",false); break;
            case 7: error=TheGameText->v28("GUI:JoinFailedNoConnection",false); break;
            case 9: error=TheGameText->v28("GUI:JoinFailedGameInPlay",false); break;
            default: error=TheGameText->v28("GUI:JoinFailedDefault",false); break;
            }
            GSMessageBoxOk(TheGameText->v28("GUI:JoinFailedDefault",false),error,0);
            Rva005406E0();
            break;
        }
        case 10: {
            if(response.payload.words[3]==1) {
                Rva004F1280 row; Rva00538290(&response,&row);
                TheGameSpyInfo->v40(row,Rva01336E50);
            } else if(response.payload.words[3]==2) {
                important=true;
                Rva004F1280 row; Rva00538290(&response,&row);
                TheGameSpyInfo->v40(row,Rva01336E50);
                if(row.field14 && !Rva012F76F0Global->v24(row.field14).field00) {
                    PSRequest request; request.field04.field00=row.field14; request.field00=0;
                    Rva012F76F0Global->v10(request);
                }
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                bool kicked=false;
                if(TheGameSpyInfo->vC0() && room) {
                    if(TheNAT) {
                        PeerRequest request; request.type=13; request.fieldE4=true;
                        request.id="KICK/"; request.nick=row.field00.str(); request.options="GameStarted";
                        TheGameSpyPeerMessageQueue->v18(request);
                    } else {
                        for(int i=0;i<8;++i) if(room->getSlot(i)->isOccupied()) room->getSlot(i);
                        TheMapCache->findMap(room->getMap());
                        int empty=-1;
                        for(int i=0;i<8;++i) if(room->getConstSlot(i) && room->getConstSlot(i)->isOpen()) {empty=i; break;}
                        if(empty>=0) {
                            Rva0061F0C0 slot;
                            UnicodeString name; name.translate(row.field04);
                            GameSlotConnectInfo connect={0,0};
                            slot.setState(Slot5,name,&connect);
                            GameSlotConnectInfo endpoint;
                            endpoint.ip=htonl(response.payload.words[5]); endpoint.port=0x1F98;
                            slot.field30=endpoint;
                            room->Rva0061F630(empty,slot);
                            room->v18();
                        } else {
                            PeerRequest request; request.type=13; request.fieldE4=true;
                            request.id="KICK/"; request.nick=row.field00.str(); request.options="GameFull";
                            TheGameSpyPeerMessageQueue->v18(request); kicked=true;
                        }
                        TheGameSpyInfo->vCC();
                        if(!kicked) postPeerRequest19();
                    }
                } else postPeerRequest19();
                field50=true;
            }
            break;
        }
        case 11: {
            important=true;
            Rva004F1280 row; Rva00538290(&response,&row);
            TheGameSpyInfo->v44(AsciiString(response.nick.c_str()));
            if((TheGameSpyGame && TheGameSpyGame->field0D) || TheNAT) break;
            GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
            if(room && TheGameSpyInfo->vC0()) {
                int which=room->getSlotNum(AsciiString(row.field04.str()));
                if(which>=0) {
                    GameSlotConnectInfo connect={0,0};
                    room->getSlot(which)->setState(Slot0,Rva01336E54,&connect); room->v18();
                }
            }
            TheGameSpyInfo->vCC(); field50=true;
            if(room && !TheGameSpyInfo->vC0() && room->getSlotNum(AsciiString(row.field04.str()))==0) {
                room->v08(); TheGameSpyInfo->vB0(); field40.v04();
                GSMessageBoxOk(TheGameText->v28("GUI:HostLeftTitle",false),TheGameText->v28("GUI:HostLeft",false),0);
                Rva005406E0();
            }
            break;
        }
        case 13: {
            Rva004F1280 row;
            Rva00538290(&response,&row);
            TheGameSpyInfo->v40(row,Rva01336E50);
            field50=true;
            TheGameSpyInfo->vCC();
            break;
        }
        case 14: {
            Rva004F1280 row;
            Rva00538290(&response,&row);
            TheGameSpyInfo->v40(row,Rva01336E50);
            field50=true;
            break;
        }
        case 15: {
            important=true;
            const char* command=response.command.c_str();
            if(!strcmp(command,"SL")) {
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                Rva004F18C0Node* node=TheGameSpyInfo->v48()->Rva004F18C0(AsciiString(response.nick.c_str()));
                AsciiString nick;
                if(node!=TheGameSpyInfo->v48()->field00) nick=node->field18; else nick=response.nick.c_str();
                if(!room) break;
                if(!room->getSlot(0) || !room->getSlot(0)->isPlayer(nick) || TheGameSpyInfo->vC0()) {
                    if(room->getSlot(0)) TheGameSpyInfo->vC0();
                    break;
                }
                AsciiString oldMap=room->getMap();
                unsigned oldCRC=room->field40;
                AsciiString options(response.commandOptions.c_str()); options.trim();
                unsigned ips[8]; unsigned short ports[8];
                for(int i=0;i<8;++i) {
                    if(room->getConstSlot(i)) {
                        ips[i]=room->getConstSlot(i)->field30;
                        ports[i]=room->getConstSlot(i)->field34;
                    } else {ips[i]=0; ports[i]=0;}
                }
                bool ok=Rva00621C40(room,AsciiString(options.str()),false);
                // Unlike ZH, BFME does not restore saved ports/IPs here. The
                // retail retains the read loop even though the arrays are dead.
                bool wasIn=field1BC>=0;
                field1BC=room->field0C ? room->v14() : -1;
                bool isIn=field1BC>=0;
                if(!ok) break;
                if(!isIn) {
                    for(int i=0;i<8;++i) {
                        GameSlot* slot=room->Rva00637D10(i);
                        if(slot && slot->isHuman()) {
                            UnicodeString debug; debug.format(L"\t%d: %ls",i,slot->getName().str());
                        }
                    }
                }
                field50=true;
                unsigned newCRC=room->field40;
                if(isIn) {
                    field1C4=timeGetTime();
                    if((oldCRC^newCRC) || !wasIn) {
                        UnicodeString host=TheGameSpyInfo->vC4()->getSlot(0)->getName();
                        AsciiString ascii; ascii.translate(host);
                        PeerRequest request; request.type=13; request.fieldE4=true;
                        request.id="MAP"; request.nick=ascii.str();
                        request.options=room->getSlot(field1BC)->field09 ? "1":"0";
                        TheGameSpyPeerMessageQueue->v18(request);
                        if(!room->getSlot(field1BC)->field09) {
                            UnicodeString text,display;
                            RvaMapMeta* meta=TheMapCache->findMap(room->getMap());
                            bool transfer;
                            if(meta) {display.format(L"%ls",meta->field00.str()); transfer=!meta->field26;}
                            else {display.format(L"%hs",TheGameState->getMapLeafName(room->getMap()).str()); transfer=WouldMapTransfer(room);}
                            if(transfer) text.format(TheGameText->v28("GUI:LocalPlayerNoMapWillTransfer",false),display.str());
                            else text.format(TheGameText->v28("GUI:LocalPlayerNoMap",false),display.str());
                            TheGameSpyInfo->vEC(text,Rva012B9200,field198);
                        }
                    }
                    if(!field1C8) field1C8=true;
                } else if(field1C4 && field1C4<timeGetTime()-10000) {
                    if(TheGameSpyInfo->vC4()) TheGameSpyInfo->vC4()->v08();
                    TheGameSpyInfo->vB0();
                    GSMessageBoxOk(TheGameText->v28("GUI:GSErrorTitle",false),TheGameText->v28("GUI:GSKicked",false),0);
                    field40.v04(); Rva005406E0();
                }
            } else if(!strcmp(command,"PN")) {
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                AsciiString nick;
                Rva004F18C0Node* node=TheGameSpyInfo->v48()->Rva004F18C0(AsciiString(response.nick.c_str()));
                if(node!=TheGameSpyInfo->v48()->field00) nick=node->field18; else nick=response.nick.c_str();
                if(room && room->getSlot(0) && room->getSlot(0)->isPlayer(nick) && !TheGameSpyInfo->vC0()) {
                    int index=-1; char equal=' '; std::string name;
                    // Hypothesis: the 3-argument constructor includes the
                    // MSVC virtual-base flag, so this is an istringstream.
                    std::istringstream stream(*(const std::string*)&response.commandOptions);
                    stream>>index>>equal>>name;
                    if(index>=0 && index<8 && equal=='=') {
                        GameSlot* slot=room->getSlot(index);
                        if(slot && !name.empty()) {
                            UnicodeString wide(MultiByteToWideCharSingleLine(name.c_str()).c_str());
                            slot->setName(wide);
                        }
                    }
                }
            } else if(!strcmp(command,"HWS")) {
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                if(room && room->field0C && room->getSlot(0) &&
                    room->getSlot(0)->isPlayer(AsciiString(response.nick.c_str()))) {
                    GameSlot* local=room->getSlot(room->v14());
                    if(local && !local->field08)
                        TheGameSpyInfo->vEC(TheGameText->v28("GUI:HostWantsToStart",false),Rva012B9200,field198);
                }
            } else if(!strcmp(command,"DUI")) {
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                if(room && room->field0C && !room->v10() && room->getSlot(0) &&
                    room->getSlot(0)->isPlayer(AsciiString(response.nick.c_str()))) field40.Rva00523340();
            } else if(!strcmp(command,"EUI")) {
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                if(room && room->field0C && !room->v10() && room->getSlot(0) &&
                    room->getSlot(0)->isPlayer(AsciiString(response.nick.c_str()))) field40.Rva005235B0();
            } else if(!_strcmpi(command,"NAT")) {
                if(TheNAT) TheNAT->processGlobalMessage(-1,response.commandOptions.c_str());
            } else if(!_strcmpi(command,"Pings")) {
                GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
                if(room && !TheGameSpyInfo->vC0()) {
                    AsciiString pings(response.commandOptions.c_str()),token;
                    for(int i=0;i<8;++i) {
                        GameSlot* slot=room->Rva00637D10(i);
                        if(pings.nextToken(&token,",")) { token.trim(); slot->setPingString(token); }
                        else slot->setPingString(AsciiString(""));
                    }
                }
            }
            break;
        }
        case 16: {
            important=true;
            if(!strcmp(response.command.c_str(),"STATS")) {
                PSPlayerStats stats=Rva00659670(std::string(response.commandOptions.c_str()));
                if(stats.field00 && !Rva012F76F0Global->v24(stats.field00).field00)
                    Rva012F76F0Global->v20(stats);
                break;
            }
            GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
            if(!room) break;
            Rva004F18C0Node* node=TheGameSpyInfo->v48()->Rva004F18C0(AsciiString(response.nick.c_str()));
            AsciiString nick;
            if(node!=TheGameSpyInfo->v48()->field00) nick=node->field18;
            else nick=response.nick.c_str();
            int sender=room->getSlotNum(nick);
            if(sender>=0 && sender<8 && !_strcmpi(response.command.c_str(),"NAT") && TheNAT)
                TheNAT->processGlobalMessage(sender,response.commandOptions.c_str());
            if(sender<=0) {
                if(!TheGameSpyInfo->vC0() && !strcmp(response.command.c_str(),"KICK")) {
                    if(TheGameSpyInfo->vC4()) TheGameSpyInfo->vC4()->v08();
                    TheGameSpyInfo->vB0();
                    UnicodeString error=TheGameText->v28("GUI:GSKicked",false);
                    AsciiString options(response.commandOptions.c_str()); options.trim();
                    if(!options.compare("GameStarted")) error=TheGameText->v28("GUI:GSKickedGameStarted",false);
                    else if(!options.compare("GameFull")) error=TheGameText->v28("GUI:GSKickedGameFull",false);
                    GSMessageBoxOk(TheGameText->v28("GUI:GSErrorTitle",false),error,0);
                    field40.v04(); Rva005406E0();
                }
                break;
            }
            if(!TheGameSpyInfo->vC0()) break;
            if(!strcmp(response.command.c_str(),"accept")) {
                room->getSlot(sender)->field08=true;
                field40.Rva00523380((unsigned short)sender,1);
                TheGameSpyInfo->vCC(); field50=true;
            } else if(!strcmp(response.command.c_str(),"MAP")) {
                bool available=atoi(response.commandOptions.c_str())!=0;
                room->getSlot(sender)->setMapAvailability(available);
                if(!available) {
                    UnicodeString display;
                    RvaMapMeta* meta=TheMapCache->findMap(room->getMap());
                    bool transfer=WouldMapTransfer(room);
                    if(meta) display.format(L"%ls",meta->Rva00451240().str());
                    else display.format(L"%hs",room->getMap().str());
                    UnicodeString text;
                    if(transfer)
                        text.format(TheGameText->v28("GUI:PlayerNoMapWillTransfer",false),room->getSlot(sender)->getName().str(),display.str());
                    else
                        text.format(TheGameText->v28("GUI:PlayerNoMap",false),room->getSlot(sender)->getName().str(),display.str());
                    TheGameSpyInfo->vEC(text,Rva012B9200,field198);
                }
                field50=true;
            } else if(!strcmp(response.command.c_str(),"REQ")) {
                AsciiString value(response.commandOptions.c_str()); value.trim();
                AsciiString key;
                value.nextToken(&key,"=");
                int number=atoi(value.str()+1);
                unsigned ip=(unsigned)atoi(value.str()+1);
                GameSlot* slot=room->getSlot(sender);
                if(!slot) break;
                if(!key.compare("Color")) {
                    if(number>=-1 && number<Rva012ED5FCGlobal->Rva00086460() &&
                        number!=slot->field0C && slot->field14!=-2) {
                        bool duplicate=false;
                        if(number!=-1) for(int i=0;i<8;++i) {
                            GameSlot* other=room->getSlot(i);
                            if(other->field0C==number && other!=slot) { duplicate=true; break; }
                        }
                        if(!duplicate) slot->field0C=number;
                        TheGameSpyInfo->vCC(); field50=true;
                    }
                } else if(!key.compare("PlayerTemplate")) {
                    if(number>=-2 && number<Rva012ED750Global->Rva000863E0() && number!=slot->field14) {
                        slot->setPlayerTemplate(number);
                        if(number==-2) slot->field0C=slot->field10=slot->field18=-1;
                        room->v18(); TheGameSpyInfo->vCC(); field50=true;
                    }
                } else if(!key.compare("StartPos")) {
                    if(number>=-1 && number<8 && number!=slot->field10 && slot->field14!=-2) {
                        bool duplicate=false;
                        if(number!=-1) for(int i=0;i<8;++i) {
                            GameSlot* other=room->getSlot(i);
                            if(other->field10==number && other!=slot) { duplicate=true; break; }
                        }
                        if(!duplicate) slot->field10=number;
                        room->v18(); TheGameSpyInfo->vCC(); field50=true;
                    }
                } else if(!key.compare("Team")) {
                    if(number>=-1 && number<4 && number!=slot->field18 && slot->field14!=-2) {
                        slot->field18=number;
                        room->v18(); TheGameSpyInfo->vCC(); field50=true;
                    }
                } else if(!key.compare("IP")) {
                    if(ip!=slot->field30) {
                        slot->field30=ip;
                        room->v18(); TheGameSpyInfo->vCC(); field50=true;
                    }
                } else if(!key.compare("NAT")) {
                    if(number>=0 && number<=128) {
                        slot->field38=number; TheGameSpyInfo->vCC(); field50=true;
                    }
                } else if(!key.compare("Ping")) {
                    slot->setPingString(AsciiString(value.str()+1)); TheGameSpyInfo->vCC();
                } else if(!key.compare("LadderRank_1v1")) {
                    slot->field68=atoi(value.str()); TheGameSpyInfo->vCC();
                } else if(!key.compare("LadderRank_2v2")) {
                    slot->field6C=atoi(value.str()); TheGameSpyInfo->vCC();
                }
            }
            break;
        }
        case 18: {
            important=true;
            GameSpyStagingRoom* room=TheGameSpyInfo->vC4();
            if(room && room->field0C && TheGameSpyGame) {
                SendStatsToOtherPlayers(TheGameSpyGame);
                field40.v04();
                room->field460=response.payload.words[0];
                *TheGameSpyGame=*room;
                TheGameSpyGame->v0C(false);
                field188=13;
            }
            break;
        }
        case 19:
            TheGameSpyInfo->vEC(TheGameText->v28("GUI:GSFailedToHost",false),Rva012B9200,field198);
            break;
        case 20:
            if(field198) TheGameSpyInfo->vEC(UnicodeString(response.text.c_str()),Rva012B9200,field198);
            break;
        case 22: {
            Rva004F1280 row;
            Rva00538290(&response,&row);
            TheGameSpyInfo->v40(row,Rva01336E50);
            field50=true;
            break;
        }
        // Default table arms 3,6,12,17,21 really return to the poll loop.
        }
    }
}
