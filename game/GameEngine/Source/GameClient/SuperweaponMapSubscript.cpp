// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
//
// STLport _STL::map<AsciiString, list<SuperweaponInfo*> >::operator[] at
// retail 0x0044C120, 242 bytes.  The row keeps the address-derived name
// ?d_0044c120@@YAXXZ; the canonical instantiation mangling is below.
//
// Identity: the matched caller ?addSuperweapon@InGameUI@@UAEXHABVAsciiString@@...
// at 0x0044C970 subscripts the InGameUI member map at +0x5CC (32 maps of
// 12 bytes, constructor-witnessed), and the matched InGameUI::DoXfer at
// 0x0044C250 round-trips the same map.  The body is _map.h operator[]
// verbatim: lower_bound descent, then a pair<const AsciiString, SuperweaponList>
// temporary handed to the hinted insert_unique, then the temporary unwound.
// Its four tree/list helper routes are the retail ILT thunks 0x0000EDEA
// (_M_lower_bound body 0x00448B90), 0x00014376 (insert_unique body 0x0044AA20),
// 0x00041655 (list_base destructor body 0x004406F0) and 0x00887B60/0x0003FA67
// (AsciiString copies), pinned in targets/game/reverse/symbols.csv.
//
// Retail returns with ret 4 at +0xD8 and +0xEF and INT3 padding begins at
// +0xF2, confirming the 242-byte extent.
//
// The definition bodies of InGameUI::DoXfer and InGameUI::findSWInfo are NOT
// repeated here: both are landed in their own TUs (InGameUIDoXfer.cpp,
// InGameUI.cpp) and only their declarations are needed for the layout checks.
#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
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
#include "../../Include/Common/ObjectID.h"
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
void bfmeCalcTGC(void *, int *);
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
// Retail 0x0044C120 constructs its mapped SuperweaponList in place.
template __declspec(noinline) SuperweaponList &SWMap::operator[](const AsciiString &);
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

// Constructor and call-site layout witnesses, checked without shared-header edits.
#include <stddef.h>
typedef char CheckSuperweaponInfoSize[(sizeof(SuperweaponInfo)==0x24)?1:-1];
typedef char CheckSuperweaponMaps[(offsetof(InGameUI,m_superweapons)==0x5cc)?1:-1];
typedef char CheckSuperweaponFont[(offsetof(InGameUI,m_superweaponNormalFont)==0x758)?1:-1];
typedef char CheckNamedTimers[(offsetof(InGameUI,m_namedTimers)==0x77c)?1:-1];
typedef char CheckTimerFrame[(offsetof(InGameUI,m_namedTimerLastFlashFrame)==0x798)?1:-1];
