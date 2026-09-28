// ?Rva004BEBD0@@YAHPAVGameWindow@@III@Z
// partial score=0.677 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameWindow.h"

// Opaque gap function reached by ILT RVA 0x00028033. Entry after int3;
// final ret at 0x004BF301, dispatch tables through 0x004BF43B.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
static __forceinline const unsigned short *raw(const UnicodeString &s) {
 void *data=*(void* const*)&s;
 extern const char g_bfmeEmptyUnicode[];
 return data ? (unsigned short*)((char*)data+8) : (const unsigned short*)g_bfmeEmptyUnicode;
}
class Rva004BEBD0Text { public:
 virtual void unused00();
 virtual void unused01();
 virtual UnicodeString getText();
 virtual int length();
 virtual void unused04();
 virtual void unused05();
 virtual void unused06();
 virtual void unused07();
 virtual void unused08();
 virtual void unused09();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual void unused15();
 virtual int width(int);
};
class Rva004BEBD0Manager { public:
 virtual void unused00();
 virtual void unused01();
 virtual void unused02();
 virtual void unused03();
 virtual void unused04();
 virtual void unused05();
 virtual void unused06();
 virtual void unused07();
 virtual void unused08();
 virtual void unused09();
 virtual void unused10();
 virtual void unused11();
 virtual void unused12();
 virtual void unused13();
 virtual void unused14();
 virtual void unused15();
 virtual void unused16();
 virtual void unused17();
 virtual void unused18();
 virtual void unused19();
 virtual void unused20();
 virtual void unused21();
 virtual void unused22();
 virtual void unused23();
 virtual void unused24();
 virtual void unused25();
 virtual void unused26();
 virtual void unused27();
 virtual void unused28();
 virtual void unused29();
 virtual void unused30();
 virtual void unused31();
 virtual void unused32();
 virtual void unused33();
 virtual void unused34();
 virtual void unused35();
 virtual void unused36();
 virtual void nextTab(GameWindow*);
 virtual void prevTab(GameWindow*);
 virtual void unused39();
 virtual void unused40();
 virtual void unused41();
 virtual void unused42();
 virtual void unused43();
 virtual int focus(GameWindow*);
 virtual void unused45();
 virtual void unused46();
 virtual void unused47();
 virtual void unused48();
 virtual void unused49();
 virtual void unused50();
 virtual void unused51();
 virtual void unused52();
 virtual int send(GameWindow*,unsigned,unsigned,unsigned);
 virtual void unused54();
 virtual void unused55();
 virtual int capture(GameWindow*);
 virtual int release(GameWindow*);
 virtual GameWindow *getCapture();
};
class Rva004BEBD0IME { public:
 virtual void unused00();
 virtual void unused01();
 virtual void unused02();
 virtual void unused03();
 virtual void unused04();
 virtual void unused05();
 virtual void unused06();
 virtual void unused07();
 virtual void unused08();
 virtual void unused09();
 virtual void unused10();
 virtual void slot2c();
 virtual void slot30();
 virtual void unused13();
 virtual bool attached(GameWindow*);
 virtual void unused15();
 virtual bool composing();
};

extern Rva004BEBD0Manager *g_Rva004BEBD0Manager;
extern Rva004BEBD0IME *g_Rva004BEBD0IME;
class Rva005A6790Object { public: int setValue(int); };
extern Rva005A6790Object *g_Rva004BEBD0Cursor;
struct Rva004BEBD0Entry {
 Rva004BEBD0Text *text,*masked;
 char pad08[0x12-8];
 unsigned char secret,draw,hover;
 char pad15[7];
 unsigned short pos,anchor,composition;
 short pad22;
 int start;
};
extern bool GadgetTextEntryInsertCharacter(GameWindow*,unsigned);
extern void GadgetTextEntrySetCursorPosition(GameWindow*,unsigned);
// The selection-removal callee has a cdecl one-pointer ABI (ret; all callers clean four bytes).
extern bool Rva004BE800(GameWindow*);
int Rva004BEBD0(GameWindow *window,unsigned msg,unsigned data1,unsigned data2) {
 Rva004BEBD0Entry *e=(Rva004BEBD0Entry*)window->winGetUserData();
 WinInstanceData *inst=window->winGetInstanceData();
 if(msg!=6 && g_Rva004BEBD0IME && g_Rva004BEBD0IME->attached(window) && g_Rva004BEBD0IME->composing()) return 1;
 switch(msg) {
 case 0x19:
  if((unsigned short)data1==13) { e->draw=0; g_Rva004BEBD0Manager->send(window->winGetOwner(),0x4030,(unsigned)window,0); return 1; }
  if((unsigned short)data1 && GadgetTextEntryInsertCharacter(window,data1)) g_Rva004BEBD0Manager->send(window->winGetOwner(),0x4031,(unsigned)window,0);
  break;
 case 0x15:
  if((data2&2) && (data2&0xcc)) {
   if(!(data2&12)) return 0;
   if(data1==0xcb) {
    if(e->composition) return 1;
    if(e->pos) {
     const unsigned short *text=raw(e->text->getText());
     int pos=e->pos;
     while(pos>0 && text[pos-1]==' ') --pos;
     while(pos>0 && text[pos-1]!=' ') --pos;
     GadgetTextEntrySetCursorPosition(window,pos);
    }
    if(!(data2&0x430)) e->anchor=e->pos;
    return 1;
   }
   if(data1==0xcd) {
    if(e->composition) return 1;
    if(e->pos<e->text->length()) {
     int len=e->text->length();
     const unsigned short *text=raw(e->text->getText());
     int pos=e->pos;
     while(pos<len && text[pos]==' ') ++pos;
     while(pos<len && text[pos]!=' ') ++pos;
     while(pos<len && text[pos]==' ') ++pos;
     GadgetTextEntrySetCursorPosition(window,pos);
    }
    if(!(data2&0x430)) e->anchor=e->pos;
    return 1;
   }
   return 0;
  }
  switch(data1) {
  case 1: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f: case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x57: case 0x58: case 0xc9: case 0xd1: return 0;
  case 0x1c: case 0x9c: if(data2&12) return 0; break;
  case 0xe:
   if(!(data2&2) || e->composition) return 1;
   if(e->anchor==e->pos) e->anchor=e->pos-1;
   if(Rva004BE800(window)) g_Rva004BEBD0Manager->send(window->winGetOwner(),0x4031,(unsigned)window,0);
   break;
  case 0xf:
   if(data2&2) {
    if(data2&0x430) {
     GameWindow *parent=window->winGetParent();
     if(parent && (parent->winGetStyle()&0x8000)) g_Rva004BEBD0Manager->prevTab(parent);
     else g_Rva004BEBD0Manager->prevTab(window);
    } else {
     GameWindow *parent=window->winGetParent();
     if(parent && (parent->winGetStyle()&0x8000)) g_Rva004BEBD0Manager->nextTab(parent);
     else g_Rva004BEBD0Manager->nextTab(window);
    }
   }
   break;
  case 0xc7:
   if(e->composition) return 1;
   if(data2&2) GadgetTextEntrySetCursorPosition(window,0);
   if(!(data2&0x430)) e->anchor=e->pos;
   break;
  case 0xcb:
   if(!(data2&2) || e->composition) return 1;
   if(e->pos>0) GadgetTextEntrySetCursorPosition(window,e->pos-1);
   if(!(data2&0x430)) e->anchor=e->pos;
   break;
  case 0xcd:
   if((data2&2) && !e->composition) {
    if(e->pos<e->text->length()) GadgetTextEntrySetCursorPosition(window,e->pos+1);
    if(!(data2&0x430)) e->anchor=e->pos;
   }
   break;
  case 0xcf:
   if(!e->composition) {
    if(data2&2) GadgetTextEntrySetCursorPosition(window,e->text->length());
    if(!(data2&0x430)) e->anchor=e->pos;
   }
   break;
  case 0xd3:
   if(!(data2&2) || e->composition) return 1;
   if(e->anchor==e->pos) e->anchor=e->pos+1;
   if(Rva004BE800(window)) g_Rva004BEBD0Manager->send(window->winGetOwner(),0x4031,(unsigned)window,0);
   break;
  }
  break;
 case 5: {
  g_Rva004BEBD0Manager->focus(window);
  if(e->composition && g_Rva004BEBD0IME) { g_Rva004BEBD0IME->slot30(); g_Rva004BEBD0IME->slot2c(); }
  int x,y,w,h; window->winGetScreenPosition(&x,&y); window->winGetSize(&w,&h);
  int click=(data1&0xffff)-x;
  Rva004BEBD0Text *text=e->text;
  if(e->secret) text=e->masked;
  int width=e->text->width(e->start);
  int pos=text->length();
  while(pos>0 && click+width<text->width(pos)) --pos;
  e->anchor=pos;
  GadgetTextEntrySetCursorPosition(window,pos);
  g_Rva004BEBD0Manager->capture(window);
  break;
 }
 case 6:
  if(g_Rva004BEBD0Manager->getCapture()==window) g_Rva004BEBD0Manager->release(window);
  break;
 case 0x18: {
  if(g_Rva004BEBD0Manager->getCapture()!=window) return 0;
  int x,y,w,h; window->winGetScreenPosition(&x,&y); window->winGetSize(&w,&h);
  int click=(data1&0xffff)-x;
  Rva004BEBD0Text *text=e->text;
  if(e->secret) text=e->masked;
  int width=e->text->width(e->start);
  int pos=text->length();
  while(pos>0 && click+width<text->width(pos)) --pos;
  GadgetTextEntrySetCursorPosition(window,pos);
  break;
 }
 case 0x11:
  if(((unsigned*)inst)[3]&0x400) { ((unsigned*)inst)[2]|=2; g_Rva004BEBD0Manager->send(window->winGetOwner(),0x4006,(unsigned)window,0); }
  g_Rva004BEBD0Cursor->setValue(0x2d); if(e) e->hover=1; break;
 case 0x12:
  if(((unsigned*)inst)[3]&0x400) { ((unsigned*)inst)[2]&=~2; g_Rva004BEBD0Manager->send(window->winGetOwner(),0x4007,(unsigned)window,0); }
  g_Rva004BEBD0Cursor->setValue(2); if(e) e->hover=0; break;
 case 8:
  if(((unsigned*)inst)[3]&0x400) g_Rva004BEBD0Manager->send(window->winGetOwner(),0x4000,(unsigned)window,0);
  break;
 default: return 0;
 }
 return 1;
}
