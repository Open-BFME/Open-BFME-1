// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib
// LAN lobby/game update tick, retail RVA 006870F0, 2436 bytes: code ends at
// ret 00687A25, alignment 00687A26, nineteen switch pointers 00687A28..00687A74,
// then int3 (targets/game/reverse/identity_evidence/006870f0-finishing-ilt.md).
// The body mirrors Zero Hour LANAPI::update; the name stays address-derived
// until a vtable slot proves it. Mirror types are local because lanapi.cpp
// carries the Zero Hour layout. Callees bind through canonical declarations or
// typed routes through recorded ILT symbols. The leave handler at 0068BAC0 is
// LANAPI::handleRequestGameLeave(LANMessage *, const IPAddr &, bool): the
// IPAddr spelling fits all 13 sibling handler ILT windows jointly and this name
// alone fits slot 0001320F.
// Levers: packet union with natural double alignment (not declspec align),
// inline StringBase::str bodies, game lastHeard inline accessor, host-drop
// type8 versus player-drop type6, and a block-scope reference alias for
// m_currentGame in the host-drop loop, which gives retail's base/index order
// in lea ecx,[edi+eax+0x88] at +0x7A1 (the BFME2 0x0052F63F SIB recipe).
#include <wchar.h>
#include "string_base.h"
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline const wchar_t *StringBase<wchar_t>::str() const { return m_data ? m_data->data : L""; }
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include <wchar.h>
extern "C" __declspec(dllimport) unsigned __stdcall timeGetTime();
extern bool LANbuttonPushed;
extern bool LANSocketErrorDetected;
extern unsigned Rva012F772C;
struct RvaLANAddress { unsigned ip; unsigned short port; RvaLANAddress():ip(0),port(0){} RvaLANAddress(unsigned a,unsigned short b):ip(a),port(b){} };
#pragma pack(push,1)
struct RvaLANIncoming { char data[0x400]; unsigned length; unsigned ip; unsigned short port; char gap40A[4]; };
#pragma pack(pop)
struct RvaLANPacket { union { double alignment; struct { int type; wchar_t name[13]; char rest[0x1e0-30]; }; }; };
class Transport {
public:
 bool update();
 char prefix[0x20704];
 RvaLANIncoming incoming[128];
};
typedef Transport RvaLANTransport;
struct RvaLANPlayer { UnicodeString name, login, host; unsigned lastHeard; RvaLANPlayer *next; unsigned ip; };
class GameSlot {
public:
 bool isHuman() const;
 void *m_vptr;
 int m_state;
 bool m_isAccepted, m_hasMap, m_isMuted;
 char prefix[0x30-0x0b];
 RvaLANAddress address;
 char gap38[0x44-0x38];
};
class RvaLANSlot : public GameSlot {
public:
 RvaLANPlayer m_user;
 char m_userTail[4];
 AsciiString m_serial;
 unsigned lastHeard;
 unsigned getLastHeard() { return isHuman()?lastHeard:0; }
};
class LANGameInfo;
typedef LANGameInfo RvaLANGame;
class LANGameInfo {
public:
 ~LANGameInfo();
 UnicodeString getPlayerName(int);
 char prefix[0xd];
 bool inProgress;
 char gapE[0x58-0xe];
 RvaLANSlot slots[8];
 unsigned getLastHeard() const {return lastHeard;}
 unsigned getLastHeard(int p) { return slots[p].isHuman()?slots[p].lastHeard:0; }
 RvaLANGame *next;
 unsigned lastHeard;
};
typedef LANGameInfo RvaLANGame;
class BfmeGameText {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual UnicodeString fetch(const char *, bool = false);
};
typedef BfmeGameText RvaLANGameText;
// Retail 0x012F147C: use the existing data owner; retain the local pointee view.
extern class GameTextInterface *TheGameText;
struct LANMessage;
struct IPAddr;
class LANAPI { friend class Rva006870F0State; protected: void removeGame(LANGameInfo *); void handleRequestGameLeave(LANMessage *, const IPAddr &, bool); };
void j_00011aa9();
void j_0004233e();
void j_00046001();
void j_00028ba5();
void j_00006a87();
void j_00032be1();
void j_0003fdcd();
void j_0003eb44();
void j_0004b529();
void j_0001cc7e();
void j_0004b22c();
void j_0003b2e1();
void j_0001529e();
void j_0001b03b();
void j_0001786e();
void j_00045593();
void j_00046817();
class Rva006870F0State
{
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void RequestGameStart();
 virtual void RequestGameStartTimer(int);
 virtual void RequestGameOptions(AsciiString, bool, const RvaLANAddress & = RvaLANAddress());
 virtual void RequestGeneratedOptions(bool, const RvaLANAddress & = RvaLANAddress());
 virtual void slot58();
 virtual void RequestGameAnnounce();
 virtual void RequestSetName(UnicodeString);
 virtual void RequestLobbyLeave(bool);
 virtual void ResetGameStartTimer();
 virtual void OnGameList(RvaLANGame *);
 virtual void OnPlayerList(RvaLANPlayer *);
 virtual void OnGameJoin(int, RvaLANGame *, void *);
 virtual void slot78();
 virtual void slot7C();
 virtual void OnPlayerLeave(UnicodeString);
 virtual void slot84();
 virtual void slot88();
 virtual void OnChat(UnicodeString, const RvaLANAddress *, UnicodeString, int);
 virtual void slot90();
 virtual void slot94();
 virtual void slot98();
 virtual void slot9C();
 virtual void slotA0();
 virtual void slotA4();
 virtual void slotA8();
 virtual void slotAC();
 virtual void slotB0();
 virtual void slotB4();
 virtual bool AmIHost();
 virtual void slotBC();
 virtual void slotC0();
 virtual void fillInLANMessage(RvaLANPacket *);
 virtual void checkMOTD();
 virtual void slotCC();
 virtual void slotD0();
 virtual void slotD4();
 virtual void slotD8();
 virtual const RvaLANAddress *localAddress();
 unsigned field04;
 RvaLANPlayer *m_lobbyPlayers;
 RvaLANGame *m_games;
 UnicodeString m_name;
 AsciiString m_userName, m_hostName;
 unsigned m_gameStartTime;
 int m_gameStartSeconds;
 int m_pendingAction;
 unsigned m_expiration;
 char gap2C[12];
 unsigned m_lastResendTime;
 bool m_isInLANMenu, m_inLobby;
 char gap3E[2];
 RvaLANGame *m_currentGame;
 char gap44[8];
 RvaLANTransport *m_transport;
 unsigned m_broadcastAddr, m_lastUpdate;
 void step();
 // ?removeGame@Rva006870F0State@@QAEXPAVLANGameInfo@@@Z absent-from-retail
 void removeGame(RvaLANGame *game) { reinterpret_cast<LANAPI *>(this)->removeGame(game); }
 // ?call0068AEF0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068AEF0(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_00011aa9 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068C110@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068C110(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0004233e };
  (this->*route.member)(msg, sender);
 }
 // ?call0068B1E0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068B1E0(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_00046001 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068B380@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068B380(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_00028ba5 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068C400@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068C400(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_00006a87 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068CF00@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068CF00(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_00032be1 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068B4C0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068B4C0(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0003fdcd };
  (this->*route.member)(msg, sender);
 }
 // ?call0068AC20@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068AC20(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0003eb44 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068AC80@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068AC80(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0004b529 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068B540@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068B540(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0001cc7e };
  (this->*route.member)(msg, sender);
 }
 // ?call0068B6A0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068B6A0(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0004b22c };
  (this->*route.member)(msg, sender);
 }
 // ?call0068ACF0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068ACF0(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0003b2e1 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068BFA0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068BFA0(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0001529e };
  (this->*route.member)(msg, sender);
 }
 // ?call0068AD80@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068AD80(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0001b03b };
  (this->*route.member)(msg, sender);
 }
 // ?call0068B890@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068B890(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_0001786e };
  (this->*route.member)(msg, sender);
 }
 // ?call0068B920@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068B920(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_00045593 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068ADE0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@@Z absent-from-retail
 void call0068ADE0(RvaLANPacket *msg, const RvaLANAddress *sender) {
  union { void (*raw)(); void (Rva006870F0State::*member)(RvaLANPacket *, const RvaLANAddress *); }
   route = { j_00046817 };
  (this->*route.member)(msg, sender);
 }
 // ?call0068BAC0@Rva006870F0State@@QAEXPAURvaLANPacket@@PBURvaLANAddress@@_N@Z absent-from-retail

 void removePlayer(RvaLANPlayer *player) {
  if (m_lobbyPlayers == player) m_lobbyPlayers = m_lobbyPlayers->next;
  else {
   RvaLANPlayer *p = m_lobbyPlayers;
   while (p->next && p->next != player) p = p->next;
   if (p->next == player) p->next = player->next;
  }
 }
};
void Rva006870F0State::step()
{
 if (LANbuttonPushed) return;
 unsigned now = timeGetTime();
 if (now > m_lastUpdate + 200) m_lastUpdate = now; else return;
 if (!m_transport->update() && !LANSocketErrorDetected && m_isInLANMenu == true)
  LANSocketErrorDetected = true;
 for (int i=0; i<128 && !LANbuttonPushed; ++i) {
  bool leaveFlag = false;
  if (m_transport->incoming[i].length > 0) {
   RvaLANAddress sender(m_transport->incoming[i].ip, m_transport->incoming[i].port);
   const RvaLANAddress *local = localAddress();
   if (sender.ip == local->ip && sender.port == local->port) {
    m_transport->incoming[i].length = 0;
    continue;
   }
   RvaLANPacket *msg = (RvaLANPacket *)m_transport->incoming[i].data;
   switch (msg->type) {
   case 0: call0068AEF0(msg, &sender); break;
   case 1: call0068C110(msg, &sender); break;
   case 2: call0068B1E0(msg, &sender); break;
   case 17: call0068B380(msg, &sender); break;
   case 3: call0068C400(msg, &sender); break;
   case 4: RequestLobbyLeave(true); call0068CF00(msg, &sender); break;
   case 5: call0068B4C0(msg, &sender); break;
   case 8: leaveFlag = true;
   case 6: reinterpret_cast<LANAPI *>(this)->handleRequestGameLeave(reinterpret_cast<LANMessage *>(msg), reinterpret_cast<const IPAddr &>(sender), leaveFlag); break;
   case 7: call0068AC20(msg, &sender); break;
   case 9: call0068AC80(msg, &sender); break;
   case 10: call0068B540(msg, &sender); break;
   case 11: call0068B6A0(msg, &sender); break;
   case 12: call0068ACF0(msg, &sender); break;
   case 13: call0068BFA0(msg, &sender); break;
   case 14: call0068AD80(msg, &sender); break;
   case 15: call0068B890(msg, &sender); break;
   case 16: call0068B920(msg, &sender); break;
   case 18: call0068ADE0(msg, &sender); break;
   }
   m_transport->incoming[i].length = 0;
  }
 }
 if (LANbuttonPushed) return;
 if (now > 2000 + m_lastResendTime) {
  m_lastResendTime = now;
  if (m_inLobby) RequestSetName(m_name);
  else if (m_currentGame && !m_currentGame->inProgress) {
   if (AmIHost()) { RequestGeneratedOptions(true); RequestGameAnnounce(); }
   else {
    AsciiString text;
    text.format("User=%s", m_userName.str());
    RequestGameOptions(text,true);
    text.format("Host=%s", m_hostName.str());
    RequestGameOptions(text,true);
    RequestGameOptions("HELLO",false);
   }
  } else if (m_currentGame) RequestGameAnnounce();
 }
 bool playerListChanged=false, gameListChanged=false;
 RvaLANPlayer *player = m_lobbyPlayers;
 while (player) {
  if (player->lastHeard + 20000 < now) {
   removePlayer(player);
   RvaLANPlayer *next = player->next;
   delete player;
   player = next;
   playerListChanged = true;
  } else player = player->next;
 }
 RvaLANGame *game = m_games;
 while (game) {
  if (game != m_currentGame && game->getLastHeard() + 20000 < now) {
   removeGame(game);
   RvaLANGame *next = game->next;
   delete game;
   game = next;
   gameListChanged = true;
  } else game = game->next;
 }
 if (m_currentGame && !m_currentGame->inProgress) {
  if (!AmIHost() && m_currentGame->getLastHeard(0) + 20000 < now) {
   RvaLANPacket msg;
   fillInLANMessage(&msg);
   msg.type = 8;
   wcsncpy(msg.name, m_currentGame->getPlayerName(0).str(), 12);
   msg.name[12] = 0;
   reinterpret_cast<LANAPI *>(this)->handleRequestGameLeave(reinterpret_cast<LANMessage *>(&msg), reinterpret_cast<const IPAddr &>(m_currentGame->slots[0].address), false);
   UnicodeString text;
   text = reinterpret_cast<BfmeGameText *>(TheGameText)->fetch("LAN:HostNotResponding");
   OnChat(UnicodeString::TheEmptyString, localAddress(), text, 2);
  } else if (AmIHost()) {
   RvaLANGame *const &cg = m_currentGame;
   for (int p=1; p<8; ++p) {
    if ((cg->slots[p].address.ip || cg->slots[p].address.port) &&
      cg->getLastHeard(p) + 20000 < now) {
     RvaLANPacket msg;
     fillInLANMessage(&msg);
     UnicodeString text;
     text.format(reinterpret_cast<BfmeGameText *>(TheGameText)->fetch("LAN:PlayerDropped"),cg->getPlayerName(p).str());
     msg.type = 6;
     wcsncpy(msg.name,cg->getPlayerName(p).str(),12);
     msg.name[12]=0;
     reinterpret_cast<LANAPI *>(this)->handleRequestGameLeave(reinterpret_cast<LANMessage *>(&msg), reinterpret_cast<const IPAddr &>(cg->slots[p].address), false);
     OnChat(UnicodeString::TheEmptyString,localAddress(),text,2);
    }
   }
  }
 }
 if (playerListChanged) OnPlayerList(m_lobbyPlayers);
 if (gameListChanged) OnGameList(m_games);
 if (m_pendingAction && now > m_expiration) {
  switch(m_pendingAction) {
  case 1: OnGameJoin(1,0,0); m_pendingAction=0; m_currentGame=0; m_inLobby=true; break;
  case 3: OnPlayerLeave(m_name); m_pendingAction=0; m_currentGame=0; m_inLobby=true; break;
  case 2: OnGameJoin(1,0,0); m_pendingAction=0; m_currentGame=0; m_inLobby=true; break;
  default: m_pendingAction=0;
  }
 }
 if (m_gameStartTime && m_gameStartSeconds && m_gameStartTime <= now) RequestGameStartTimer(m_gameStartSeconds);
 else if (m_gameStartTime && m_gameStartTime <= now) { ResetGameStartTimer(); RequestGameStart(); }
 if (now > Rva012F772C + 30000) { checkMOTD(); Rva012F772C=now; }
}
