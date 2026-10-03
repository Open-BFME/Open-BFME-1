// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "unicode_string.h"
// Retail-only interface views. Every offset and slot below is address-qualified.
extern void j_00030d91();
extern void j_0000fb32();
extern void j_000186ba();
extern void j_00031327();
extern void j_0001e957();
extern void j_00017481();
extern void j_00042069();
extern void j_00044733();
extern void j_0003f3af();
extern void j_00006ce4();
extern void j_000080ad();
extern void j_0000ad21();
extern void j_00014709();

class Receiver00544E40 {};
template<class R> inline R invoke0_00544E40(void *obj,void (*entry)()) {
 typedef R (Receiver00544E40::*Method)();
 union { void (*raw)(); Method typed; } f; f.raw=entry;
 return (((Receiver00544E40*)obj)->*f.typed)();
}
template<class R,class A> inline R invoke1_00544E40(void *obj,void (*entry)(),A arg) {
 typedef R (Receiver00544E40::*Method)(A);
 union { void (*raw)(); Method typed; } f; f.raw=entry;
 return (((Receiver00544E40*)obj)->*f.typed)(arg);
}
struct Response00544E40 {
 int type00; char pad04[0xf4-4]; int reasonF4; char tailF8[0x330-0xf8];
 Response00544E40() { invoke0_00544E40<void>(this,j_00042069); }
 ~Response00544E40() { invoke0_00544E40<void>(this,j_00044733); }
};
class GameSpyInfo; class GameSpyStagingRoom; class GameSpyPeerMessageQueueInterface; class GameTextInterface; class NAT; class WindowManager;
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyStagingRoom *TheGameSpyGame;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameTextInterface *TheGameText;
extern NAT *TheNAT;
extern WindowManager *g_rva012F19E8WindowManager;
class GenActionSink { public: void add(void*,const char*,int,const char*,int,int,int,int); };
class RoomSlots00544E40 { public: virtual void s0(); virtual void s1(); virtual void reset(); };
class NatSlots00544E40 { public: virtual ~NatSlots00544E40(); };
class InfoSlots00544E40 { public:
#define S(n) virtual void s##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) virtual void leave();
 S(45) S(46) S(47) S(48) virtual RoomSlots00544E40 *room();
 S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59) S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69) S(70) S(71) S(72) S(73) S(74) S(75) S(76) S(77) S(78) S(79) S(80) S(81) S(82) S(83) S(84) S(85) virtual bool check(bool);
 virtual void disconnected(int);
 S(88) S(89) S(90) virtual int count();

#undef S
};
class QueueSlots00544E40 { public:
#define S(n) virtual void s##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8)
#undef S
 virtual bool get(Response00544E40*);
};
class TextSlots00544E40 { public:
#define S(n) virtual void s##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
#undef S
 virtual UnicodeString fetch(const char*,bool*);
};
void GSMessageBoxOk(UnicodeString,UnicodeString,void(*)());
class OnlineStateUpdate00544E40 { public: void update(); };
void OnlineStateUpdate00544E40::update()
{
 switch(*(int*)((char*)this+0x188)) {
 case 1:
  ((GenActionSink*)g_rva012F19E8WindowManager)->add(*(void**)(*(char**)((char*)this+0x34)+0x250),"CallChild",1,"OnStartLobby",0,0,0,0);
  *(int*)((char*)this+0x188)=2;
 case 2: invoke1_00544E40<void,bool>(this,j_00030d91,false); break;
 case 4: invoke0_00544E40<void>(this,j_0000fb32); break;
 case 6: invoke0_00544E40<void>(this,j_000186ba); break;
 case 7:
  if(invoke1_00544E40<bool,bool>((char*)this+0x40,j_00031327,true)) *(int*)((char*)this+0x188)=8;
  else {
   *(int*)((char*)this+0x188)=6;
   *((char*)this+0x1d5)=1;
   ((GenActionSink*)g_rva012F19E8WindowManager)->add(*(void**)(*(char**)((char*)this+0x34)+0x250),"CallChild",1,"EnableButtonPlayGame",0,0,0,0);
  }
  break;
 case 8:
  if(!invoke0_00544E40<bool>((char*)this+0x40,j_0001e957)) {
   *(int*)((char*)this+0x188)=6;
   *((char*)this+0x1d5)=1;
   ((GenActionSink*)g_rva012F19E8WindowManager)->add(*(void**)(*(char**)((char*)this+0x34)+0x250),"CallChild",1,"EnableButtonPlayGame",0,0,0,0);
  }
  break;
 case 9: invoke0_00544E40<void>(this,j_00017481); break;
 case 13:
  if(TheGameSpyGame && *((bool*)TheGameSpyGame+0xd)) {
   if(!((InfoSlots00544E40*)TheGameSpyInfo)->check(false)) {
    int count=((InfoSlots00544E40*)TheGameSpyInfo)->count();
    bool done=false;
    Response00544E40 response;
    while(count-- && !done && ((QueueSlots00544E40*)TheGameSpyPeerMessageQueue)->get(&response)) {
     switch(response.type00) {
     case 1: {
      done=true;
      AsciiString text;
      text.format(AsciiString("GUI:GSDisconReason%d"),response.reasonF4);
      ((InfoSlots00544E40*)TheGameSpyInfo)->disconnected(response.reasonF4);
      break;
     }
     }
    }
   }
  } else if(TheNAT) {
   int state=invoke0_00544E40<int>(TheNAT,j_0003f3af);
   if(state==3) {
    invoke0_00544E40<void>(TheGameSpyGame,j_00006ce4);
    if(TheGameSpyInfo) {
     RoomSlots00544E40 *room=((InfoSlots00544E40*)TheGameSpyInfo)->room();
     if(room && *((bool*)room+0x428)) ((InfoSlots00544E40*)TheGameSpyInfo)->leave();
    }
    return;
   } else if(state==4) {
    delete (NatSlots00544E40*)TheNAT;
    TheNAT=0;
    RoomSlots00544E40 *room=((InfoSlots00544E40*)TheGameSpyInfo)->room();
    if(room) room->reset();
    ((InfoSlots00544E40*)TheGameSpyInfo)->leave();
    GSMessageBoxOk(((TextSlots00544E40*)TheGameText)->fetch("GUI:Error",0),((TextSlots00544E40*)TheGameText)->fetch("GUI:NATNegotiationFailed",0),0);
    invoke0_00544E40<void>(this,j_000080ad);
   }
  }
  break;
 case 0: invoke0_00544E40<void>(this,j_000080ad); break;
 }
 if(invoke0_00544E40<bool>((char*)this+0x40,j_0000ad21)) invoke0_00544E40<void>(this,j_00014709);
}
