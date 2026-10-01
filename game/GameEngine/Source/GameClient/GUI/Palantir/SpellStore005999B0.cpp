// Spell-store frame update at RVA 005999B0; retains the existing caller-backed name.
// cl: /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const wchar_t *s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->~StringBase(); }
class GameTextInterface { public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();
 virtual UnicodeString fetch(AsciiString,bool * =0);
};
extern GameTextInterface *TheGameText;
class WindowManager { public: void bfme_setAptText(const AsciiString &,const UnicodeString &); };
extern WindowManager *g_theWindowManager;
class GenActionSink { public: void add(void *,const char *,int,const char *,int,int,int,int); };
class BfmeH1065 { public: void bfmeGo1065B(int,int); };
class BfmeH1066 { public: void bfmeGo1066A(int); };
int bfmeAptLevel00465CE0(BfmeH1065 *);
int bfmeQuiet();
class GameLogic;
extern GameLogic *TheGameLogic;
class GameLogicPortraitShim { public: bool isInMultiplayerOrSkirmishGame(); };
extern void *Screen005999B0;
enum ScienceType { INVALID_SCIENCE=-1 };
class Player { public:
 bool hasScience(ScienceType) const;
 bool isScienceDisabled(ScienceType) const;
 bool isScienceHidden(ScienceType) const;
 char pad[0x264]; int m_sciencePurchasePoints;
};
struct Players005999B0 { char pad[12]; Player *player; };
extern Players005999B0 *PlayerList005999B0;
class ScienceStore { public: bool playerHasRootPrereqsForScience(const Player*,ScienceType) const; };
extern ScienceStore *TheScienceStore;
struct Rva0049B010String;
class Rva0049B010Owner { public: const Rva0049B010String &Rva0049B010(); };
struct Rva0049B060Item;
class Rva0049B060Owner { public: const Rva0049B060Item &Rva0049B060(); };
struct CommandData005999B0 { char pad[0x84]; ScienceType *begin,*end; unsigned size()const{return end-begin;} };
class GameWindow { public: bool winIsHidden(); unsigned winGetStatus(); };
void *GadgetButtonGetData(GameWindow *);
struct Entry005999B0 { GameWindow *window; int state; };
class Rva005999B0Screen { public:
 void frameUpdate();
 char pad[0x258]; bool field258; char pad259[3]; int field25c;
 Entry005999B0 entries[12]; char pad2c0[8]; int field2c8,field2cc; bool field2d0,field2d1;
};
void Rva005999B0Screen::frameUpdate()
{
 if(!Screen005999B0 || !(unsigned char)bfmeQuiet()) { ((BfmeH1066*)this)->bfmeGo1066A(0); return; }
 if(!field258) return;
 int mode=((GameLogicPortraitShim *)TheGameLogic)->isInMultiplayerOrSkirmishGame()?1:0;
 if(mode!=field25c) {
  ((GenActionSink*)g_theWindowManager)->add((void*)bfmeAptLevel00465CE0((BfmeH1065*)this),"SetLayout",1,mode==1?"_multiplayer":"_campaign",0,0,0,0);
  field25c=mode; return;
 }
 Player *player=PlayerList005999B0->player;
 bool selected=field2cc>=0;
 if(selected!=field2d0) {
  ((GenActionSink*)g_theWindowManager)->add((void*)bfmeAptLevel00465CE0((BfmeH1065*)this),"ShowSpellHelpText",1,selected?"_on":"_off",0,0,0,0);
  field2d0=selected;
 }
 if(selected && !field2d1) {
  GameWindow *window=entries[field2cc].window;
  if(window) {
   CommandData005999B0 *data=(CommandData005999B0*)GadgetButtonGetData(window);
   if(data) {
    static AsciiString help("APT:SpellHelpText");
    g_theWindowManager->bfme_setAptText(help,TheGameText->fetch((const AsciiString&)((Rva0049B010Owner*)data)->Rva0049B010()));
    static AsciiString desc("APT:SpellDescription");
    static AsciiString disabled("TOOLTIP:ScienceDisabled");
    {
     UnicodeString text=TheGameText->fetch((const AsciiString&)((Rva0049B060Owner*)data)->Rva0049B060());
     for(unsigned i=0;i<data->size();++i) {
      ScienceType science=data->begin[i];
      if(!player->hasScience(science)) {
       if(science!=INVALID_SCIENCE && (player->isScienceDisabled(science)||player->isScienceHidden(science)||!TheScienceStore->playerHasRootPrereqsForScience(player,science))) {
        text+=(wchar_t)10;
        text+=TheGameText->fetch(disabled);
       }
       break;
      }
     }
     g_theWindowManager->bfme_setAptText(desc,text);
    }
    field2d1=true;
   }
  }
 }
 int points=player->m_sciencePurchasePoints;
 if(points!=field2c8) {
  static AsciiString pointsKey("APT:SpellStoreSpellPoints");
  UnicodeString text; text.format(L"%d",points);
  g_theWindowManager->bfme_setAptText(pointsKey,text);
  field2c8=points;
 }
 for(int i=0;i<12;++i) {
  int state=0;
  if(entries[i].window && !entries[i].window->winIsHidden()) {
   if(entries[i].window->winGetStatus()&8) state=4;
   else if(entries[i].window->winGetStatus()&0x1000000) state=entries[i].state==4?3:2;
   else state=1;
  }
  if(state!=entries[i].state) {
   ((BfmeH1065*)this)->bfmeGo1065B(i,state);
   entries[i].state=state;
  }
 }
}
