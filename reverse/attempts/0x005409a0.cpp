// ?d_005409a0@@YAXXZ
// partial score=0.744154676 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Partial natural C++ reconstruction. RVA 005409A0, 2224 bytes.
// Opaque views describe observed offsets; unresolved declarations are NOT pins.
// No behavior/byte-equivalence claim. See build/gap_00540910/GAP.md.
#define _STLP_USE_STATIC_LIB
#include "ascii_string.h"
#include "unicode_string.h"
#include <string>

inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString& UnicodeString::operator=(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this;
}
template<class T> inline const T* StringBase<T>::str() const {
    if(m_data) return m_data->data;
    return (const T*)"";
}

class OptionPreferences {
public: OptionPreferences(); virtual ~OptionPreferences(); int getFirewallBehavior(); unsigned char pad04[16];
};
class CustomMatchPreferences {
public: int getPreferredColor(); int getPreferredFaction(); AsciiString getPreferredMap(); unsigned char data[20];
};
class PeerRequest {
public:
    PeerRequest(); ~PeerRequest();
    int type; std::string nick; std::wstring text; std::string password,email,id,options;
    unsigned char pad4C[0xE4-0x4C]; bool fieldE4; unsigned char padE5[0x194-0xE5];
};
typedef char RvaRequestSize[sizeof(PeerRequest)==0x194?1:-1];
typedef char RvaOptionsSize[sizeof(OptionPreferences)==0x14?1:-1];

struct RvaConnect { unsigned field00; unsigned short field04; };
// The available ZH-derived GameInfo header has unproved BFME field labels.
// These views deliberately retain observed offsets, not that whole layout.
class RvaSlot {
public:
    virtual void v00(); int field04; bool field08,field09; unsigned short field0A;
    int field0C,field10,field14,field18; unsigned char pad1C[0x38-0x1C]; int field38;
    void Rva00638240(AsciiString);
    void setState(int,UnicodeString,const RvaConnect*);
    void setMapAvailability(bool);
    UnicodeString getName() const;
};
#define V(N) virtual void v##N()
class RvaRoom {
public:
    V(00); V(04); V(08); V(0C); V(10); V(14); V(18); V(1C); V(20);
    unsigned char pad04[9]; bool field0D; unsigned char pad0E[0x40-0x0E]; unsigned field40,field44;
    RvaSlot* getSlot(int);
    void setPingString(AsciiString); void setMapCRC(unsigned); void setMapSize(unsigned);
};
class GameSpyInfo {
public:
    V(00); V(04); V(08); V(0C); V(10); V(14); V(18); V(1C); V(20); V(24);
    virtual void v28(int); virtual int v2C(); V(30); V(34); V(38); V(3C);
    V(40); V(44); V(48); V(4C); V(50); V(54); V(58); V(5C); V(60); V(64);
    V(68); V(6C); V(70); V(74); V(78); V(7C); V(80); V(84); V(88); V(8C); V(90);
    V(94); V(98); V(9C); V(A0); V(A4); V(A8); V(AC); V(B0); V(B4); V(B8); V(BC);
    virtual bool vC0(); virtual RvaRoom* vC4(); V(C8); V(CC);
    V(D0); V(D4); V(D8); V(DC); V(E0); virtual void vE4(void*); V(E8); V(EC);
    V(F0); V(F4); V(F8); V(FC); V(100); V(104); V(108); V(10C); V(110);
    virtual const AsciiString& v114(); V(118); V(11C); V(120); V(124); V(128); V(12C);
    V(130); V(134); V(138); V(13C); V(140); V(144); V(148); V(14C); V(150); V(154);
    virtual bool v158(int*);
};
class GameSpyPeerMessageQueueInterface {
public: V(00); V(04); V(08); V(0C); virtual bool v10(); V(14); virtual void v18(const PeerRequest&);
};
class GameText {
public: V(00); V(04); V(08); V(0C); V(10); V(14); V(18); V(1C); V(20);
    virtual UnicodeString v24(AsciiString,bool); virtual UnicodeString v28(const char*,bool);
};
class RvaWindowManager {
public:
    V(00); V(04); V(08); V(0C); V(10); V(14); V(18); V(1C); V(20); V(24); V(28); V(2C);
    V(30); V(34); V(38); V(3C); V(40); V(44); V(48); V(4C); V(50); V(54); V(58); V(5C);
    V(60); V(64); V(68); V(6C); V(70); V(74); V(78); V(7C); V(80); V(84); V(88); V(8C);
    V(90); V(94); V(98); V(9C); V(A0); V(A4); V(A8); V(AC); virtual void vB0(void*);
    V(B4); V(B8); V(BC); V(C0); V(C4); V(C8); V(CC); V(D0);
    virtual void vD4(void*,unsigned,UnicodeString*,int);
};
#undef V
class NAT { public: virtual ~NAT(); };
class Shell { public: void popImmediate(); };
struct RvaMapNode { unsigned char pad00[0x3C]; unsigned field3C,field40; };
class MapCache { public: RvaMapNode* field00; void updateCache(); RvaMapNode* find(const AsciiString&); };
class SkirmishScreenState { public: bool apply(void*,int); unsigned char pad00[0x134]; };
class Rva004675F0 { public: void run(void*,const char*,int,const char*,const char*,int,int,int); };

extern RvaRoom* TheGameSpyGame;
extern GameSpyInfo* TheGameSpyInfo;
extern GameSpyPeerMessageQueueInterface* TheGameSpyPeerMessageQueue;
extern GameText* TheGameText;
extern NAT* TheNAT;
extern Shell* TheShell;
extern MapCache* TheMapCache;
extern RvaWindowManager* TheWindowManager;
extern Rva004675F0* Rva012F19E8;
extern int Rva012F73D0, Rva012F73D4;
extern const UnicodeString Rva01336E54;
void postPeerRequest19();
void GameSpyCloseAllOverlays();
void GSMessageBoxOk(UnicodeString,UnicodeString,void(__cdecl*)());
void GadgetListBoxReset(void*);

class Rva005409A0 {
public:
    void run(); void routeBackToLobby();
    unsigned char pad00[0x34]; unsigned char* field34; unsigned char pad38[8];
    SkirmishScreenState field40;
    CustomMatchPreferences field174;
    int field188; unsigned char pad18C[8]; void* field194; void* field198;
    unsigned char pad19C[0x1B8-0x19C]; int field1B8;
    unsigned char pad1BC[0x1D5-0x1BC]; bool field1D5;
};

void Rva005409A0::run()
{
    if(TheGameSpyGame && TheGameSpyGame->field0D) {
        TheGameSpyGame->field0D=false;
        int reason;
        if(TheGameSpyInfo->v158(&reason)) {
            AsciiString key;
            key.format("GUI:GSDisconReason%d",reason);
            UnicodeString title,body;
            title=TheGameText->v28("GUI:GSErrorTitle",false);
            body=TheGameText->v24(key,false);
            GameSpyCloseAllOverlays();
            GSMessageBoxOk(title,body,0);
            TheGameSpyInfo->v04();
            TheShell->popImmediate();
        } else if(TheGameSpyPeerMessageQueue && TheGameSpyPeerMessageQueue->v10()) {
            routeBackToLobby();
        } else TheShell->popImmediate();
        return;
    }
    postPeerRequest19();
    if(TheNAT) { delete TheNAT; TheNAT=0; }
    field1B8=TheGameSpyInfo->v2C();
    TheGameSpyInfo->v28(0);
    TheGameSpyInfo->vE4(field198);
    TheMapCache->updateCache();
    RvaRoom* room=TheGameSpyInfo->vC4();
    RvaSlot* host=room->getSlot(0);
    host->field08=true;
    if(TheGameSpyInfo->vC0()) {
        OptionPreferences prefs;
        host->field0C=field174.getPreferredColor();
        host->field14=field174.getPreferredFaction();
        if(host->field14<=-2) host->field10=-1;
        host->field38=prefs.getFirewallBehavior();
        host->Rva00638240(TheGameSpyInfo->v114());
        room->setPingString(field174.getPreferredMap());
        for(int i=1;i<8;++i) {
            RvaSlot* slot=room->getSlot(i);
            RvaConnect ci={0,0};
            slot->setState(0,Rva01336E54,&ci);
        }
        AsciiString lowerMap=field174.getPreferredMap();
        lowerMap.toLower();
        RvaMapNode* node=TheMapCache->find(lowerMap);
        if(node!=TheMapCache->field00) {
            host->setMapAvailability(true);
            room->setMapCRC(node->field40);
            room->setMapSize(node->field3C);
            room->v20();
        }
    } else {
        OptionPreferences prefs;
        AsciiString options;
        PeerRequest request;
        UnicodeString name=host->getName();
        AsciiString asciiName;
        asciiName.translate(name);
        request.type=13;
        request.fieldE4=true;
        request.id="REQ/";
        request.nick=asciiName.str();
        options.format("PlayerTemplate=%d",field174.getPreferredFaction());
        request.options=options.str();
        TheGameSpyPeerMessageQueue->v18(request);
        options.format("Color=%d",field174.getPreferredColor());
        request.options=options.str();
        TheGameSpyPeerMessageQueue->v18(request);
        options.format("NAT=%d",prefs.getFirewallBehavior());
        request.options=options.str();
        TheGameSpyPeerMessageQueue->v18(request);
        options.format("Ping=%s",TheGameSpyInfo->v114().str());
        request.options=options.str();
        TheGameSpyPeerMessageQueue->v18(request);
        options.format("LadderRank1v1=%d",Rva012F73D0);
        request.options=options.str();
        TheGameSpyPeerMessageQueue->v18(request);
        options.format("LadderRank2v2=%d",Rva012F73D4);
        request.options=options.str();
        TheGameSpyPeerMessageQueue->v18(request);
        room->setMapCRC(room->field40);
        room->setMapSize(room->field44);
    }
    field40.apply(room,0);
    GadgetListBoxReset(field198);
    { UnicodeString empty=Rva01336E54; TheWindowManager->vD4(field194,0x402F,&empty,0); }
    TheGameSpyInfo->vCC();
    TheWindowManager->vB0(field194);
    if(field188==5) {
        Rva012F19E8->run(*(void**)(field34+0x250),"CallChild",2,"gotoAndPlay","_host",0,0,0);
        field1D5=false;
        Rva012F19E8->run(*(void**)(field34+0x250),"CallChild",1,"DisableButtonPlayGame",0,0,0,0);
        field188=6;
    } else if(field188==11) {
        Rva012F19E8->run(*(void**)(field34+0x250),"CallChild",1,"ClosePassword",0,0,0,0);
        Rva012F19E8->run(*(void**)(field34+0x250),"CallChild",2,"gotoAndPlay","_join",0,0,0);
        field188=12;
    }
}
