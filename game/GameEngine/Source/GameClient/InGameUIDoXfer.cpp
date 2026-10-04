// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// InGameUI::DoXfer, retail RVA 0x0044C250, 1453 bytes.
// Identity: InGameUI constructor 0x0044B800 and destructor 0x0044AE70 install
// Snapshot vtable 0x010F5B24 at +8. Slot 3 routes through ILT 0x00049107 here.
// W3DInGameUI installs 0x0112057C with the same inherited Snapshot slot.
// snapshot.h names slot 3 DoXfer(Xfer&); the ZH InGameUI::xfer implementation
// independently supplies the named-timer and superweapon save/load control flow.
// BFME differences: version pair (1,1), CRC tactical-view float, light-CRC exit,
// 32 players, and three saved superweapon flags (no ZH evaReadyPlayed).
// The complete-object offsets are constructor-witnessed; MSVC's secondary-base
// override receives Snapshot this at +8 and emits subobject-relative accesses.
// The final compiler int3 is padding, excluded from the 1453-byte body extent.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <list>
#include "ascii_string.h"
#include "unicode_string.h"
#include "xfer.h"
typedef bool Bool;
#include "subsystem_interface.h"
#include "snapshot.h"
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
enum ObjectID { OBJECTID_NONE = 0 };
class SpecialPowerTemplate { public: AsciiString getName() const; };
class SpecialPowerStore {
protected:
 SpecialPowerTemplate *findSpecialPowerTemplatePrivate(AsciiString);
public:
 SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString s) { return findSpecialPowerTemplatePrivate(s); }
};
extern SpecialPowerStore *TheSpecialPowerStore;
class Player { public: char pad_000[0x1c4]; int m_playerColor; int getPlayerColor() const { return m_playerColor; } };
class PlayerList { public: Player *getNthPlayer(int); };
extern PlayerList *ThePlayerList;
class View {
public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
 S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
 S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
 S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
 S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
 S(50) S(51) S(52) S(53) S(54) S(55) S(56)
#undef S
 virtual float value_00e4();
};
extern View *TheTacticalView;
class Xfer; class MidVirtualSlot90Receiver;
Xfer & Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);
class XferException {
public:
 XferException(int, const char *, ...);
 XferException(const XferException &);
 ~XferException();
 char *text; int tag;
};
class SuperweaponInfo {
public:
 virtual ~SuperweaponInfo();
 void *m_nameDisplayString, *m_timeDisplayString;
 int m_color;
 const SpecialPowerTemplate *m_powerTemplate;
 AsciiString m_powerName;
 ObjectID m_id;
 unsigned m_timestamp;
 bool m_hiddenByScript, m_hiddenByScience, m_ready, m_forceUpdateText;
 const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_powerTemplate; }
 SuperweaponInfo(ObjectID,unsigned,bool,bool,bool,const AsciiString&,int,bool,int,const SpecialPowerTemplate*);
};
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString &a,const AsciiString &b) const { return a.compare(b)<0; } }; }
typedef _STL::list<SuperweaponInfo*> SuperweaponList;
typedef _STL::map<AsciiString,SuperweaponList> SWMap;
namespace _STL { template<> SuperweaponList &SWMap::operator[](const AsciiString &); }
struct NamedTimer0044C250 {
 void *vptr; AsciiString m_timerName; UnicodeString timerText;
 char pad_0c[12]; bool isCountdown;
};
class InGameUI : public SubsystemInterface, public Snapshot {
public:
 void addNamedTimer(const AsciiString&,const UnicodeString&,bool);
 bool m_superweaponHiddenByScript;
 char pad_005[0x5c4-5];
 SWMap m_superweapons[32];
 char pad_744[12];
 AsciiString m_superweaponNormalFont;
 int m_superweaponNormalPointSize;
 bool m_superweaponNormalBold;
 char pad_759[0x774-0x759];
 _STL::map<AsciiString,NamedTimer0044C250*> m_namedTimers;
 char pad_780[16];
 int m_namedTimerLastFlashFrame;
 unsigned m_namedTimerFlashColor;
 bool m_namedTimerUsedFlashColor, m_showNamedTimers;
 SuperweaponInfo *findSWInfo(int playerIndex,const AsciiString &powerName,ObjectID id,const SpecialPowerTemplate *powerTemplate);
 virtual void DoXfer(Xfer &xferRef);
};
void InGameUI::DoXfer(Xfer &xferRef) {
 Xfer *xfer=&xferRef;
 if(xfer->IsCRC() && TheTacticalView) {
  float value=TheTacticalView->value_00e4(); *xfer==value;
 }
 if(xfer->IsLightCRC()) return;
 { struct Version : Xfer::Version { Version() { data[0]=1; data[1]=1; } } version;
 *xfer==version; }
 *xfer==m_namedTimerLastFlashFrame;
 *xfer==m_namedTimerUsedFlashColor;
 *xfer==m_showNamedTimers;
 if(xfer->IsStoring()) {
  int timerCount=m_namedTimers.size(); *xfer==timerCount;
  for(_STL::map<AsciiString,NamedTimer0044C250*>::iterator it=m_namedTimers.begin();it!=m_namedTimers.end();++it) {
   *xfer==it->second->m_timerName; *xfer==it->second->timerText; *xfer==it->second->isCountdown;
  }
 } else {
  int timerCount; *xfer==timerCount;
  for(int timerIndex=0;timerIndex<timerCount;++timerIndex) {
   AsciiString timerName; UnicodeString timerText; bool isCountdown;
   *xfer==timerName; *xfer==timerText; *xfer==isCountdown;
   addNamedTimer(timerName,timerText,isCountdown);
  }
 }
 *xfer==m_superweaponHiddenByScript;
 if(xfer->IsStoring()) {
  for(int playerIndex=0;playerIndex<32;++playerIndex) {
   for(SWMap::iterator mapIt=m_superweapons[playerIndex].begin();mapIt!=m_superweapons[playerIndex].end();++mapIt) {
    AsciiString powerName=mapIt->first;
    SuperweaponList &swList=mapIt->second;
    for(SuperweaponList::iterator listIt=swList.begin();listIt!=swList.end();++listIt) {
     SuperweaponInfo *swInfo=*listIt;
     *xfer==playerIndex;
     AsciiString templateName=swInfo->getSpecialPowerTemplate()->getName();
     *xfer==templateName; *xfer==powerName;
     Rva0010C3C0((MidVirtualSlot90Receiver *)xfer,(int*)&swInfo->m_id);
     *xfer==swInfo->m_timestamp; *xfer==swInfo->m_hiddenByScript;
     *xfer==swInfo->m_hiddenByScience; *xfer==swInfo->m_ready;
    }
   }
  }
  int noMorePlayers=-1; *xfer==noMorePlayers;
 } else {
  for(;;) {
   int playerIndex; *xfer==playerIndex;
   if(playerIndex==-1) break;
   else if(playerIndex<0 || playerIndex>=32) throw XferException(0,0);
   AsciiString templateName; *xfer==templateName;
   const SpecialPowerTemplate *powerTemplate=TheSpecialPowerStore->findSpecialPowerTemplate(templateName);
   if(!powerTemplate) throw XferException(0,0);
   AsciiString powerName;
   ObjectID id; unsigned timestamp; bool hiddenByScript,hiddenByScience,ready;
   *xfer==powerName; Rva0010C3C0((MidVirtualSlot90Receiver *)xfer,(int*)&id); *xfer==timestamp;
   *xfer==hiddenByScript; *xfer==hiddenByScience; *xfer==ready;
   SuperweaponInfo *swInfo=findSWInfo(playerIndex,powerName,id,powerTemplate);
   if(swInfo==0) {
    const Player *player=ThePlayerList->getNthPlayer(playerIndex);
    swInfo=new SuperweaponInfo(id,timestamp,hiddenByScript,hiddenByScience,ready,m_superweaponNormalFont,m_superweaponNormalPointSize,m_superweaponNormalBold,player->getPlayerColor(),powerTemplate);
    m_superweapons[playerIndex][powerName].push_back(swInfo);
   } else {
    swInfo->m_timestamp=timestamp; swInfo->m_hiddenByScript=hiddenByScript;
    swInfo->m_hiddenByScience=hiddenByScience; swInfo->m_ready=ready;
   }
   swInfo->m_forceUpdateText=true;
  }
 }
}

 SuperweaponInfo *InGameUI::findSWInfo(int playerIndex,const AsciiString &powerName,ObjectID id,const SpecialPowerTemplate *powerTemplate) {
  // Keep the established complete-object array view used by InGameUI.cpp.
 // Accessing a synthetic secondary-base array instead folds the displacement
 // into the first LEA and differs from retail in eight bytes.
 SWMap *superweapons=(SWMap*)((char*)this+0x5cc);
  SWMap::iterator mapIt=superweapons[playerIndex].find(powerName);
  if(mapIt!=superweapons[playerIndex].end())
   for(SuperweaponList::iterator it=mapIt->second.begin();it!=mapIt->second.end();++it)
    if((*it)->m_id==id) return *it;
  return 0;
 }

// Constructor and call-site layout witnesses, checked without shared-header edits.
#include <stddef.h>
typedef char CheckSuperweaponInfoSize[(sizeof(SuperweaponInfo)==0x24)?1:-1];
typedef char CheckSuperweaponMaps[(offsetof(InGameUI,m_superweapons)==0x5cc)?1:-1];
typedef char CheckSuperweaponFont[(offsetof(InGameUI,m_superweaponNormalFont)==0x758)?1:-1];
typedef char CheckNamedTimers[(offsetof(InGameUI,m_namedTimers)==0x77c)?1:-1];
typedef char CheckTimerFrame[(offsetof(InGameUI,m_namedTimerLastFlashFrame)==0x798)?1:-1];
