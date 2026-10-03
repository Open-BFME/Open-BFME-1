// ?handleRequestJoinRva0068C400@LANAPI@@QAEXPAULANMessage@@PAUBfmeNetAddress@@@Z
// partial score=0.5074 date=2026-10-03
// ?handleRequestJoinRva0068C400@LANAPI@@QAEXPAULANMessage@@PAUBfmeNetAddress@@@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Gap-seat reconstruction of LAN join-request handler RVA 0x0068C400.
// Boundary: INT3 before the prologue; ILT RVA 0x00006A87; RET 8 at
// 0x0068CCC5, then INT3 through 0x0068CF00. Size 2248.
// This is NOT byte-exact. Probe: 2288 bytes, 1091 masked differences.
// The eight normalized structural differences are chiefly conditional-name
// temporary EH bookkeeping and a reset temporary. No callee pins added.
// Method semantic declarations below remain candidate ABI models; the ILT
// inventory in build/astra_seat/callees_c400.txt is the call-route authority.
// Canonical AsciiString/UnicodeString headers are used; no shared files edited.
// Compared with the older 1517-byte bank this restores the pointer address,
// packed port fields, skip-CRC virtual, three CRC results, and slot copy/dtors.
// RET_GAME_STARTED intentionally leaves CRC-result fields untouched in retail.


typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

#include "string_base.h"
template<> inline StringBase<char>::~StringBase(){releaseBuffer();}
template<> inline void StringBase<char>::clear(){releaseBuffer();}
template<> inline const char *StringBase<char>::str()const{return m_data?m_data->data:"";}
template<> inline const unsigned short *StringBase<unsigned short>::str()const{static const unsigned short empty=0;return m_data?m_data->data:&empty;}
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString():m_text(0){}
inline UnicodeString::UnicodeString(const wchar_t*p){((StringBase<wchar_t>*)this)->StringBase<wchar_t>::StringBase(p);}
inline UnicodeString::UnicodeString(const UnicodeString&o){((StringBase<wchar_t>*)this)->StringBase<wchar_t>::StringBase(*(const StringBase<wchar_t>*)&o);}
inline UnicodeString::~UnicodeString(){((StringBase<wchar_t>*)this)->releaseBuffer();}
inline int Rva0010EB40Compare(const UnicodeString &s,const unsigned short*p){return ((const StringBase<unsigned short>*)&s)->compare(p);}
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
 BfmeNetAddress(UnsignedInt ip=0,UnsignedShort port=0):m_ip(ip),m_port(port){}
 bool operator==(const BfmeNetAddress &r)const{return m_ip==r.m_ip && m_port==r.m_port;}
};

#pragma pack(push, 1)
struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

#pragma pack(pop)
class GameSlot
{
public:
 GameSlot(const GameSlot&);
 virtual void slot0(){} virtual void slot1(){} virtual void slot2(){}
 bool isHuman()const; bool isOccupied()const; bool isOpen()const;
	void setState(SlotState state, UnicodeString name,
		const GameSlotConnectInfo *connectInfo);

	UnicodeString getName(void) const;
	void setIP(UnsignedInt ip) { m_address.m_ip = ip; }
	void setPort(UnsignedInt port) { m_address.m_port = port; }
 void setAddress(const BfmeNetAddress &a){m_address=a;}

public:
 Int m_state; Bool m_isAccepted,m_hasMap,m_isMuted; Int m_color,m_startPos,m_playerTemplate,m_team,m_oldColor,m_oldStart,m_oldTemplate;
 UnicodeString m_name; AsciiString m_ipString;
 BfmeNetAddress m_address; unsigned m_x38,m_x3c; unsigned char m_x40;

};

class LANPlayer
{
public:
 LANPlayer(const LANPlayer&);
	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedByte m_bfmeTail[0x1c - 0x0c];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot(void);
	LANGameSlot(const LANGameSlot &o): GameSlot(o),m_user(o.m_user),m_serial(o.m_serial),m_lastHeard(o.m_lastHeard) {}
	~LANGameSlot(void) {}
 AsciiString getSerial()const;
 void setSerial(AsciiString s){m_serial=s;}

	void setLogin(AsciiString name);
	void setHost(AsciiString name);
	void setLastHeard(UnsignedInt time) { m_lastHeard = time; }
	UnicodeString getName(void) const;

private:
	LANPlayer m_user;
	AsciiString m_serial;
	UnsignedInt m_lastHeard;
};

typedef char BfmeGameSlotSizeCheck[sizeof(GameSlot) == 0x44 ? 1 : -1];
typedef char BfmeLANGameSlotSizeCheck[sizeof(LANGameSlot) == 0x68 ? 1 : -1];

class GameInfo
{
public:
	void enterGame(void);
	void setMapForwarder(AsciiString mapName);

protected:
	void *m_vptr;
	Int m_preorderMask;
	Int m_crcInterval;
	Bool m_inGame;
	Bool m_inProgress;
	Bool m_surrendered;
	Int m_gameID;
	GameSlot *m_slots[8];
	UnsignedInt m_localIP;
	Int m_extra38;
	AsciiString m_mapName;
	UnsignedInt m_mapCRC;
	UnsignedInt m_mapSize;
	Int m_mapMask;
	Int m_seed;
	Int m_useStats;
	Int m_tail;
};

class LANGameInfo : public GameInfo
{
public:
	LANGameInfo(void);
	~LANGameInfo(void);

	void setSlot(Int slot, LANGameSlot slotInfo);
 LANGameSlot *getLANSlot(int);
 AsciiString getMap()const;
 BfmeNetAddress *hostAddress(){return (BfmeNetAddress*)((char*)this+0x88);}
 bool inProgress(){return *(bool*)((char*)this+0xd);}
	GameSlot *getSlot(Int slot);
	void setName(UnicodeString name);

	Int getSeed(void) const { return m_seed; }
	void setNext(LANGameInfo *next) { m_next = next; }
	void setIsDirectConnect(Bool direct) { m_isDirectConnect = direct; }
	void setLastHeard(UnsignedInt time) { m_lastHeard = time; }
	UnicodeString getName(void) const;

private:
	LANGameSlot m_LANSlot[8];
	LANGameInfo *m_next;
	UnsignedInt m_lastHeard;
	UnicodeString m_gameName;
	Bool m_isDirectConnect;
};

typedef char BfmeGameInfoSizeCheck[sizeof(GameInfo) == 0x58 ? 1 : -1];
typedef char BfmeLANGameInfoSizeCheck[sizeof(LANGameInfo) == 0x3a8 ? 1 : -1];


extern "C" __declspec(dllimport) int __cdecl strncmp(const char*,const char*,unsigned);
extern "C" __declspec(dllimport) WideChar* __cdecl wcsncpy(WideChar*,const WideChar*,unsigned);
struct LANMessage;
class LANAPI { public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void slot15()=0;
virtual void slot16()=0;
virtual void slot17()=0;
virtual void slot18()=0;
virtual void slot19()=0;
virtual void slot20()=0;
virtual void requestOptions(bool,BfmeNetAddress*)=0;
virtual void slot22()=0;
virtual void slot23()=0;
virtual void slot24()=0;
virtual void slot25()=0;
virtual void slot26()=0;
virtual void slot27()=0;
virtual void slot28()=0;
virtual void slot29()=0;
virtual void onJoin(int,UnicodeString)=0;
virtual void slot31()=0;
virtual void slot32()=0;
virtual void slot33()=0;
virtual void slot34()=0;
virtual void slot35()=0;
virtual void slot36()=0;
virtual void slot37()=0;
virtual void slot38()=0;
virtual void slot39()=0;
virtual void slot40()=0;
virtual void slot41()=0;
virtual void slot42()=0;
virtual void slot43()=0;
virtual void slot44()=0;
virtual void slot45()=0;
virtual void slot46()=0;
virtual void slot47()=0;
virtual void slot48()=0;
virtual void fillInLANMessage(LANMessage*)=0;
virtual void slot50()=0;
virtual bool skipCRC()=0;
virtual void slot52()=0;
virtual void slot53()=0;
virtual void slot54()=0;
virtual BfmeNetAddress *localAddress()=0;

 void handleRequestJoinRva0068C400(LANMessage*,BfmeNetAddress*);
 void sendMessage(LANMessage*,BfmeNetAddress*);
 char pad[0x3d-4]; bool inLobby; char pad3e[2]; LANGameInfo *current;
};
#pragma pack(push,1)
struct LANMessage {
 unsigned type; WideChar name[13]; char user[2],host[2];
 union {
  struct {unsigned gameIP,exeCRC,iniCRC,extraCRC; char serial[23];} request;
  struct {WideChar gameName[17];unsigned gameIP;unsigned short gamePort; unsigned playerIP;unsigned short playerPort;int reason;bool exeOK,iniOK,extraOK;} reply;
  char body[442];
 };
};
#pragma pack(pop)
typedef char CheckMessage[sizeof(LANMessage)==476?1:-1];
struct Rva0068C400Global { char prefix[0xbc8]; unsigned iniCRC; unsigned xBCC; unsigned exeCRC; unsigned extraCRC; };
extern Rva0068C400Global *g_Rva0068C400Global;
struct MapMetaData { char prefix[0x20]; int players; };
class Rva0068C400Cache {public: MapMetaData *find(AsciiString);};
extern Rva0068C400Cache *g_Rva0068C400Cache;
int Rva0009B4B0(int,int);
bool GetStringFromRegistry(AsciiString,AsciiString,AsciiString&);
void LANAPI::handleRequestJoinRva0068C400(LANMessage *msg,BfmeNetAddress *sender) {
 BfmeNetAddress response=*sender;
 if(msg->request.gameIP != localAddress()->m_ip) return;
 LANMessage reply; fillInLANMessage(&reply);
 if(!inLobby && current && *current->hostAddress()==*localAddress()) {
  if(current->inProgress()) {
   reply.type=5;reply.reply.reason=6;
   reply.reply.gameIP=localAddress()->m_ip;reply.reply.gamePort=(unsigned short)localAddress()->m_port;
   reply.reply.playerIP=sender->m_ip;reply.reply.playerPort=(unsigned short)sender->m_port;
  } else {
   bool canJoin=true;
   if(!skipCRC()) {
    bool exeOK=msg->request.exeCRC==Rva0009B4B0(g_Rva0068C400Global->exeCRC,g_Rva0068C400Global->exeCRC);
    bool iniOK=msg->request.iniCRC==g_Rva0068C400Global->iniCRC;
    bool extraOK=msg->request.extraCRC==g_Rva0068C400Global->extraCRC;
    if(!exeOK||!iniOK||!extraOK) {
     reply.type=5;reply.reply.reason=4;
     reply.reply.gameIP=localAddress()->m_ip;reply.reply.gamePort=(unsigned short)localAddress()->m_port;
     reply.reply.playerIP=sender->m_ip;reply.reply.playerPort=(unsigned short)sender->m_port;
     reply.reply.exeOK=exeOK;reply.reply.iniOK=iniOK;reply.reply.extraOK=extraOK;canJoin=false;
    }
   }
   int player; AsciiString serial;
   for(player=0;canJoin && player<8;++player) {
    LANGameSlot *slot=current->getLANSlot(player);serial.clear();
    if(player==0) GetStringFromRegistry("\\ergc","",serial);
    else if(slot->isHuman()) {serial=slot->getSerial();if(serial.isEmpty())serial="<Munkee>";}
    if(serial.isNotEmpty() && !strncmp(serial.str(),msg->request.serial,23)) {
     reply.type=5;reply.reply.reason=5;
     reply.reply.gameIP=localAddress()->m_ip;reply.reply.gamePort=(unsigned short)localAddress()->m_port;
     reply.reply.playerIP=sender->m_ip;reply.reply.playerPort=(unsigned short)sender->m_port;
     reply.reply.exeOK=false;reply.reply.iniOK=false;reply.reply.extraOK=false;canJoin=false;break;
    }
   }
   for(player=0;canJoin && player<8;++player) {
    LANGameSlot *slot=current->getLANSlot(player);
    if(slot->isHuman() && Rva0010EB40Compare(slot->GameSlot::getName(),msg->name)==0) {
     reply.type=5;reply.reply.reason=3;
     reply.reply.gameIP=localAddress()->m_ip;reply.reply.gamePort=(unsigned short)localAddress()->m_port;
     reply.reply.playerIP=sender->m_ip;reply.reply.playerPort=(unsigned short)sender->m_port;
     reply.reply.exeOK=false;reply.reply.iniOK=false;reply.reply.extraOK=false;canJoin=false;break;
    }
   }
   int numPlayers=0;
   for(player=0;player<8;++player) {
    if(current->getLANSlot(player)->isOccupied() && current->getLANSlot(player)->m_playerTemplate!=-2) ++numPlayers;
   }
   int spots=8; const MapMetaData *map=g_Rva0068C400Cache->find(current->getMap());
   if(map)spots=map->players;
   if(numPlayers<spots) {
    for(player=0;canJoin&&player<8;++player) {
     if(current->getLANSlot(player)->isOpen()) {
      reply.type=4;wcsncpy(reply.reply.gameName,current->getName().str(),16);reply.reply.gameName[16]=0;
      reply.reply.reason=player;
      reply.reply.gameIP=localAddress()->m_ip;reply.reply.gamePort=(unsigned short)localAddress()->m_port;
      reply.reply.playerIP=sender->m_ip;reply.reply.playerPort=(unsigned short)sender->m_port;
      LANGameSlot newSlot;
      GameSlotConnectInfo info;info.m_nat=0;info.m_port=0;
      newSlot.setState(SLOT_PLAYER,UnicodeString(msg->name),&info);
      newSlot.setAddress(*sender);
      newSlot.setLastHeard(timeGetTime());newSlot.setSerial(msg->request.serial);
      current->setSlot(player,newSlot);onJoin(player,UnicodeString(msg->name));
      response=BfmeNetAddress();break;
     }
    }
   }
   if(canJoin&&player==8) {
    reply.type=5;wcsncpy(reply.reply.gameName,current->getName().str(),16);reply.reply.gameName[16]=0;
    reply.reply.reason=2;
    reply.reply.gameIP=localAddress()->m_ip;reply.reply.gamePort=(unsigned short)localAddress()->m_port;
    reply.reply.playerIP=sender->m_ip;reply.reply.playerPort=(unsigned short)sender->m_port;
    reply.reply.exeOK=false;reply.reply.iniOK=false;reply.reply.extraOK=false;
   }
  }
 } else {
  reply.type=5;reply.reply.reason=8;
  reply.reply.gameIP=localAddress()->m_ip;reply.reply.gamePort=(unsigned short)localAddress()->m_port;
  reply.reply.playerIP=sender->m_ip;reply.reply.playerPort=(unsigned short)sender->m_port;
  reply.reply.exeOK=false;reply.reply.iniOK=false;reply.reply.extraOK=false;
 }
 sendMessage(&reply,&response); { BfmeNetAddress empty;requestOptions(true,&empty); }
}
