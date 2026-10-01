// RVA 0x00593A30: existing Gen00593A30::handle(void*) call-site identity.
// RegionUI and PalantirRegion literals prove region-help display behavior.
// The opaque region offsets below are directly witnessed loads, not guessed
// CommandButton layout. Its image accessor is called through the existing pin.
// appendBonus00591A60 has a private ESI accumulator ABI and must stay in this TU;
// MSVC optimizes the file-static helper and its four callers together; keeping
// this definition here reproduces the ESI parameter and exact 195-byte body.
// stlport
// cl: /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
#include <set>
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->~StringBase(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s);return *this; }
class GameTextInterface { public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();
 virtual UnicodeString fetch(AsciiString,bool * =0);
};
extern GameTextInterface *TheGameText;
class WindowManager { public: void bfme_setAptText(const AsciiString &,const UnicodeString &); };
extern WindowManager *g_rva012F19E8WindowManager;
class BfmeThingBIF { public: void bfmeGoBIF(void *,void *); };
class Image;
class CommandButton { public: const Image *getButtonImage() const; };
void bfmeGoDZFd(int);
void bfmeGoDZFb(int);
static bool empty00593A30(const AsciiString &s) { const char *p=*(const char *const*)&s;return !p || *(const unsigned short*)(p+4)==0; }
template<> inline void StringBase<unsigned short>::swap(StringBase<unsigned short> &other) { Header *p=m_data; m_data=other.m_data; other.m_data=p; }
static void appendBonus00591A60(UnicodeString &text,const AsciiString &key,int value)
{
 if(value>0) {
  UnicodeString line;
  line.format(TheGameText->fetch(key),value);
  void *p=*(void**)&text;
  bool empty = !p || *(unsigned short*)((char*)p+4)==0; if(empty) {
   ((StringBase<unsigned short>*)&text)->swap(*(StringBase<unsigned short>*)&line);
  } else {
   unsigned short newline=10;
   ((StringBase<unsigned short>*)&text)->concat(&newline,1);
   text+=line;
  }
 }
}
struct Region00593A30 {
 char prefix[0x10]; AsciiString label;
 char gap14[0x78-0x14];
 int value78,value7c,value80;
 bool flag84; char gap85[3];
 int value88; char gap8c[0x98-0x8c];
 AsciiString label98;
};
class Gen00593A30 { public:
 void handle(void *);
 int counter; bool shown; Region00593A30 *active; int current;
 std::set<int> retired;
};
void Gen00593A30::handle(void *argument)
{
 Region00593A30 *region=(Region00593A30*)argument;
 if(region==active) return;
 if(active) { bfmeGoDZFd(current); retired.insert(current); }
 active=region;
 if(!region) return;
 current=counter++;
 bfmeGoDZFb(current);
 const Image *image=((CommandButton*)active)->getButtonImage();
 if(image) {
  AsciiString name;
  name.format("RegionUI/Portrait%d/Portrait",current);
  ((BfmeThingBIF*)g_rva012F19E8WindowManager)->bfmeGoBIF(&name,(void*)image);
 }
 static AsciiString act("LW:ActDisplayString");
 static AsciiString army("LW:RegionBonusArmy");
 static AsciiString resource("LW:RegionBonusResource");
 static AsciiString legendary("LW:RegionLegendaryBonus");
 AsciiString name;
 name.format("APT:PalantirRegionName%d",current);
 AsciiString bonusName;
 bonusName.format("APT:PalantirRegionBonus%d",current);
 UnicodeString text=TheGameText->fetch(active->label);
 g_rva012F19E8WindowManager->bfme_setAptText(name,text);
 ((StringBase<unsigned short>*)&text)->clear();
 if(!empty00593A30(active->label98)) text=TheGameText->fetch(active->label98);
 int actValue=active->value88;
 appendBonus00591A60(text,act,actValue);
 if(!region->flag84) {
  int armyValue=active->value78; appendBonus00591A60(text,army,armyValue);
  int resourceValue=active->value7c; appendBonus00591A60(text,resource,resourceValue);
  int legendaryValue=active->value80; appendBonus00591A60(text,legendary,legendaryValue);
 }
 g_rva012F19E8WindowManager->bfme_setAptText(bonusName,text);
 shown=true;
}
