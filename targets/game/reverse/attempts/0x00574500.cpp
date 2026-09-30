// ?_bfme_checkMsg@BfmeAptScreenScoreScreen@@QAEHHPAX0@Z
// partial score=0.9583 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const UnicodeString& s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString& UnicodeString::operator=(const UnicodeString& s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this; }
class BfmeMsgHandler { public: int defaultHandler(int,void*,void*); };
class GameWindow { public: int winEnable(bool); };
void* GadgetListBoxGetItemData(GameWindow*,int,int);
int GadgetListBoxGetEntryBasedOnXY(GameWindow*,int,int,int&,int&);
void GadgetTextEntrySetText(GameWindow*,UnicodeString);
class LivingWorldArmy { public: AsciiString getName() const; };
struct ScoreRecord00574500 { char at00[0x78]; UnicodeString at78; };
enum KindOfType { Kind00574500=0x59 };
class ThingTemplate { public: bool isKindOf(KindOfType) const; };
struct Template00574500 { char at00[0xc]; UnicodeString at0c; };
class BfmeThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
extern BfmeThingFactory* TheThingFactory;
class WindowManager { public: void unidentified_00015235(int,const char*,int,const void*,int,int,int,int); };
extern WindowManager* g_theWindowManager;
class GameWindowManager { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual int winSetFocus(GameWindow*);
};
extern GameWindowManager* TheWindowManager;
class GameTextInterface { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual UnicodeString fetch(AsciiString,bool* =0);
};
extern GameTextInterface* TheGameText;
struct RGBColor;
class Mouse { public: void setCursorTooltip(UnicodeString,int,const RGBColor*,float); };
extern Mouse* TheMouse;
class BfmeAptScreenScoreScreen : public BfmeMsgHandler {
public:
 int _bfme_checkMsg(int message,void* argument,void* data);
 void _bfme_renameAccept(const char*);
 char at00[0x250]; int m_movie; char at254[0xbc];
 GameWindow* m_listBox; GameWindow* m_textEntry; ScoreRecord00574500* m_record; int m_row;
 int at320; int m_x; int m_y; int m_hoverTicks; AsciiString m_tooltip;
};
int BfmeAptScreenScoreScreen::_bfme_checkMsg(int message,void* argument,void* data) {
 switch(message) {
 case 0x18:
  if(argument==m_listBox) {
   int x=(unsigned int)data&0xffff; int y=(unsigned int)data>>16;
   if(x==m_x && y==m_y) ++m_hoverTicks; else m_hoverTicks=0;
   int row,column;
   GadgetListBoxGetEntryBasedOnXY((GameWindow*)argument,x,y,row,column);
   if(m_hoverTicks==10) {
    if(column!=0) {
     AsciiString label("APT:NULL");
     TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
     m_tooltip=label;
    }
    if(column==0) {
     AsciiString label;
     m_record=(ScoreRecord00574500*)GadgetListBoxGetItemData(m_listBox,row,0);
     if(m_record) {
      const ThingTemplate* type=0;
      if(TheThingFactory) type=TheThingFactory->findTemplate(((const LivingWorldArmy*)m_record)->getName());
      if(type && type->isKindOf(Kind00574500)) label="TOOLTIP:YouMayNotRenameAHero";
      else label="TOOLTIP:ClickToRenameThisUnit";
      TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
     }
     m_tooltip=label;
    }
   } else if(m_hoverTicks>7 && column==0) {
    // The refresh arm leaves through its own position update; retail places it after the epilogue.
    TheMouse->setCursorTooltip(TheGameText->fetch(m_tooltip),-1,0,1.0f);
    m_x=x; m_y=y; break;
   }
   m_x=x; m_y=y;
  }
  break;
 case 0x4014:
  if(argument==m_listBox && m_listBox && m_textEntry && (int)data>=0) {
   int row=(int)data;
   m_record=(ScoreRecord00574500*)GadgetListBoxGetItemData(m_listBox,row,0);
   if(m_record) {
    m_row=row;
    const ThingTemplate* type=0;
    if(TheThingFactory) {
     type=TheThingFactory->findTemplate(((const LivingWorldArmy*)m_record)->getName());
     if(type && type->isKindOf(Kind00574500)) { m_record=0; m_row=-1; break; }
    }
    UnicodeString name;
    ScoreRecord00574500* record=m_record;
    const UnicodeString& recordName=record->at78;
    if(recordName.isNotEmpty()) name=recordName;
    else if(type) name=((const Template00574500*)type)->at0c;
    GadgetTextEntrySetText(m_textEntry,name);
    TheWindowManager->winSetFocus(m_textEntry);
    m_listBox->winEnable(false);
    int movie=m_movie;
    g_theWindowManager->unidentified_00015235(movie,"openRenamePersistentUnit",0,0,0,0,0,0);
   }
  }
  break;
 case 0x4030:
  if(argument==m_textEntry && !data && m_record) {
   _bfme_renameAccept(0);
   g_theWindowManager->unidentified_00015235(m_movie,"closeRenamePersistentUnit",0,0,0,0,0,0);
  }
  break;
 default: return defaultHandler(message,argument,data);
 }
 return 1;
}
