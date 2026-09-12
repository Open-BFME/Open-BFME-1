// cl: /DNDEBUG /MD /EHsc

// GameSpyInfo::markAsStagingRoomHost, retail RVA0x006313F0, 390 bytes.
// Identity: matched GameSpyInfo ctor0x00636D90 installs vtable0x011188D0;
// slot45 (+0xb4) routes ILT0x00023F7E to this body. Reference PeerDefs host
// sequence agrees: reset/enter, tick seed, local slot/name/IP, map cache/default map.
// GameSlot's implicit member destructor is required: a user-provided empty
// destructor makes VC7 outline it. ConnectInfo lifetime ends at setState so its
// eight-byte stack slot is reused by the later IP/port pair.
template<class T> struct StringData {int refs; unsigned short length,capacity; T text[1];};
template<class T> class StringBase {
 friend class AsciiString;friend class UnicodeString;
protected:
 StringBase():m_data(0){}
 StringBase(const StringBase&);
 ~StringBase(){releaseBuffer();}
 StringData<T>*m_data;
private:
 StringBase(const T*);
 void releaseBuffer();
 void set(const StringBase&);
public:
 void set(const T*,int);
 void concat(const T*,int);
};
class AsciiString:private StringBase<char>{
public:
 AsciiString():StringBase<char>(){}
 AsciiString(const AsciiString&s):StringBase<char>(s){}
 ~AsciiString(){}
 AsciiString&operator=(const AsciiString&s){StringBase<char>::set(s);return *this;}
};
class UnicodeString:private StringBase<unsigned short>{
public:
 UnicodeString():StringBase<unsigned short>(){}
 UnicodeString(const UnicodeString&s):StringBase<unsigned short>(s){}
 ~UnicodeString(){}
 void translate(const AsciiString&);
};
struct GameSlotConnectInfo{int nat;unsigned short port;};
struct NetAddress{unsigned int ip;unsigned short port;};
enum SlotState{SLOT_OPEN,SLOT_CLOSED,SLOT_EASY_AI,SLOT_MED_AI,SLOT_BRUTAL_AI,SLOT_PLAYER};
class GameSlot{
public:
 GameSlot();GameSlot(const GameSlot&);
 virtual void reset();
 char fields[0x24];UnicodeString name;AsciiString serial;NetAddress address;char tail[0xc];
 void setState(SlotState,UnicodeString,const GameSlotConnectInfo*);

};
// Existing ILT1F4A6 writes this+0x4c at61E9D0. The older ZH-named
// setSeed ledger row writes+0x48 instead, so keep this BFME route explicit.
extern void j_0001f4a6();
class GameInfo{
public:
 virtual void v0();virtual void v1();virtual void reset();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void adjustSlotsForMap();
 void enterGame();void setSeed(int value){typedef void(GameInfo::*F)(int);union{void(*entry)();F method;}call;call.entry=j_0001f4a6;(this->*call.method)(value);}void setSlot(int,GameSlot);void setMap(AsciiString);
 char fields[0x30];NetAddress address;char tail[0x1c];
};
class GameSpyStagingRoom:public GameInfo{
public:
 char rest[0x3cc];AsciiString localName;char tail[0x40];
 void setLocalName(AsciiString s){localName=s;}
};
class GameSpyInfo{
public:
 virtual void markAsStagingRoomHost();
 char beforeName[0x68];AsciiString localName;char beforeIP[0x1dc];unsigned int externalIP;int extra250;int joined;bool hosting;char pad[3];GameSpyStagingRoom room;int localStagingRoomID;
};
class MapCache{public:void updateCache();};
extern MapCache*TheMapCache;
extern AsciiString getDefaultMap(bool);
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount();
typedef char SlotSizeCheck[sizeof(GameSlot)==0x44?1:-1];
typedef char RoomSizeCheck[sizeof(GameSpyStagingRoom)==0x468?1:-1];

void GameSpyInfo::markAsStagingRoomHost()
{
    localStagingRoomID = 0;
    joined = 0;
    hosting = true;
    room.reset();
    room.enterGame();
    room.setSeed(GetTickCount());

    GameSlot newSlot;
    UnicodeString uName;
    uName.translate(localName);
    {
        GameSlotConnectInfo info;
        info.nat = 0;
        info.port = 0;
        newSlot.setState(SLOT_PLAYER, uName, &info);
    }

    NetAddress address;
    address.ip = externalIP;
    address.port = 8088;
    room.address = address;
    newSlot.address = address;
    room.setSlot(0, newSlot);
    room.setLocalName(localName);

    TheMapCache->updateCache();
    room.setMap(getDefaultMap(true));
    room.adjustSlotsForMap();
}
