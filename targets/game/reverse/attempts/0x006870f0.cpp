// ?update@LANAPI@@
// partial score=0.999 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib
// GAP SEAT bank, retail RVA 006870F0, proven full extent 2436 bytes.
// Compile symbol: ?step@Rva006870F0State@@QAEXXZ (the ledger still has the old lift).
// Old extent 2030 cuts mov ecx,esp at 006878DD. Code ends at ret 00687A25;
// alignment 00687A26, nineteen switch pointers 00687A28..00687A74, then int3.
// Probe: exactly one non-relocation byte differs, at +0x7A3: SIB operands of
// lea ecx,[edi+eax+0x88] are reversed. Table relocation bytes are masked.
// THIS IS NOT VERIFIED CODE: opaque callee declarations below still need to
// be mapped to independently witnessed existing contracts before add_match.
// No pins were added for this attempt. Evidence: build/astra_seat/lan.callees.txt.
// Critical levers: packet union with natural double alignment (not declspec
// align), inline StringBase::str bodies, game lastHeard inline accessor,
// and host-drop type8 versus player-drop type6. All are witnessed in retail.
#include <wchar.h>
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
class RvaLANTransport {
public:
 bool update();
 char prefix[0x20704];
 RvaLANIncoming incoming[128];
};
struct RvaLANPlayer { UnicodeString name, login, host; unsigned lastHeard; RvaLANPlayer *next; unsigned ip; };
class RvaLANSlot {
public:
 bool isHuman() const;
 char prefix[0x30];
 RvaLANAddress address;
 char gap38[0x2c];
 unsigned lastHeard;
 unsigned getLastHeard() { return isHuman()?lastHeard:0; }
};
class RvaLANGame {
public:
 ~RvaLANGame();
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
class RvaLANGameText {
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
extern RvaLANGameText *TheGameText;
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
 void removeGame(RvaLANGame *);
 void call0068AEF0(RvaLANPacket *, const RvaLANAddress *);
 void call0068C110(RvaLANPacket *, const RvaLANAddress *);
 void call0068B1E0(RvaLANPacket *, const RvaLANAddress *);
 void call0068B380(RvaLANPacket *, const RvaLANAddress *);
 void call0068C400(RvaLANPacket *, const RvaLANAddress *);
 void call0068CF00(RvaLANPacket *, const RvaLANAddress *);
 void call0068B4C0(RvaLANPacket *, const RvaLANAddress *);
 void call0068AC20(RvaLANPacket *, const RvaLANAddress *);
 void call0068AC80(RvaLANPacket *, const RvaLANAddress *);
 void call0068B540(RvaLANPacket *, const RvaLANAddress *);
 void call0068B6A0(RvaLANPacket *, const RvaLANAddress *);
 void call0068ACF0(RvaLANPacket *, const RvaLANAddress *);
 void call0068BFA0(RvaLANPacket *, const RvaLANAddress *);
 void call0068AD80(RvaLANPacket *, const RvaLANAddress *);
 void call0068B890(RvaLANPacket *, const RvaLANAddress *);
 void call0068B920(RvaLANPacket *, const RvaLANAddress *);
 void call0068ADE0(RvaLANPacket *, const RvaLANAddress *);
 void call0068BAC0(RvaLANPacket *, const RvaLANAddress *, bool);
 void removePlayer(RvaLANPlayer *player) {
  if (m_lobbyPlayers == player) m_lobbyPlayers = m_lobbyPlayers->next;
  else {
   RvaLANPlayer *p = m_lobbyPlayers;
   while (p->next && p->next != player) p = p->next;
   if (p->next == player) p->next = player->next;
  }
 }
};
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline const wchar_t *StringBase<wchar_t>::str() const { return m_data ? m_data->data : L""; }
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
   case 6: call0068BAC0(msg, &sender, leaveFlag); break;
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
   call0068BAC0(&msg, &m_currentGame->slots[0].address, false);
   UnicodeString text;
   text = TheGameText->fetch("LAN:HostNotResponding");
   OnChat(UnicodeString::TheEmptyString, localAddress(), text, 2);
  } else if (AmIHost()) {
   for (int p=1; p<8; ++p) {
    if ((m_currentGame->slots[p].address.ip || m_currentGame->slots[p].address.port) &&
      m_currentGame->getLastHeard(p) + 20000 < now) {
     RvaLANPacket msg;
     fillInLANMessage(&msg);
     UnicodeString text;
     text.format(TheGameText->fetch("LAN:PlayerDropped"),m_currentGame->getPlayerName(p).str());
     msg.type = 6;
     wcsncpy(msg.name,m_currentGame->getPlayerName(p).str(),12);
     msg.name[12]=0;
     call0068BAC0(&msg,&m_currentGame->slots[p].address,false);
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
