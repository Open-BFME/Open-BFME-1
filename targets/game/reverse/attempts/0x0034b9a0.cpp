// ?update@ScriptEngine@@UAEXXZ
// partial score=0.9455445545 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <map>
// Retail RVA 0034B9A0, 1212 bytes. ScriptEngine::update: ZH twin, first-update
// flag 170a8, close/end timers 17084/17080 and subsystem order establish identity.
// Vtable 010E7A30 slot 5 -> ILT 00025A3B -> 0034B9A0 proves virtual update.
#include "ascii_string.h"
#include "Common/LatchRestore.h"
template<class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template<class T> inline const T *StringBase<T>::str() const { return m_data ? m_data->data : (const T*)""; }
template<class T> inline int StringBase<T>::getLength() const { return m_data ? m_data->length : 0; }
template<class T> inline void StringBase<T>::concat(T c) { concat(&c,1); }
template<class T> inline void StringBase<T>::concat(const StringBase<T>& s) { concat(s.str(),s.getLength()); }
template<class T> inline bool StringBase<T>::startsWith(const StringBase<T>& s) const { return startsWith(s.str(),s.getLength()); }

typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(void*,const char*);
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
enum NameKeyType;
extern AsciiString KEYNAME(NameKeyType);
struct Update0034B9A0Counter { AsciiString at10,at14; int at18; bool at1c,at1d; };
struct Update0034B9A0Flag { AsciiString at10,at14; bool at18; };
typedef _STL::_Rb_tree_node<Update0034B9A0Counter> CounterNode;
typedef _STL::_Rb_tree_node<Update0034B9A0Flag> FlagNode;
typedef _STL::_Rb_tree_iterator<Update0034B9A0Counter,_STL::_Nonconst_traits<Update0034B9A0Counter> > CounterIterator;
typedef _STL::_Rb_tree_iterator<Update0034B9A0Flag,_STL::_Nonconst_traits<Update0034B9A0Flag> > FlagIterator;
struct Update0034B9A0List { Update0034B9A0List *next,*prev; AsciiString value; };
class ScriptActionsInterface {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void update();
 virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
 virtual void closeWindows(bool);
};
class ScriptConditionsInterface {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void update();
 virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
 virtual void closeWindows(bool);
};
struct Rva003412E0Node;
class Rva00355950Arr;
class Rva003558C0Arr;
struct Update0034B9A0ScriptList { int at0; Rva003412E0Node *at4,*at8; };
struct Update0034B9A0Side { char at0[8]; Update0034B9A0ScriptList *at8; char atc[12]; };
class SidesList {
public:
 char at0[0x28]; int at28; Update0034B9A0Side at2c[1];
 int getNumSides() const { return at28; }
 Update0034B9A0Side *at(int i) { return i>=0 && i<at28 ? &at2c[i] : 0; }
};
class Player { public: char at0[0x20]; NameKeyType at20; NameKeyType getNameKey() const { return at20; } };
class PlayerList { public: Player *getNthPlayer(int); void updateTeamStates(); };
// Layout offsets read directly from the retail update and corroborated by newMap.
class ScriptEngine {
public:
 virtual void update(); void createNamedCache(); void _bfme_finishEndGame(); bool isTimeFast();
 void walkNamed(Rva00355950Arr*,Rva003412E0Node*,bool);
 void walkChild(Rva003558C0Arr*,Rva003412E0Node*);
 char at00004[0x16040-4];
 _STL::_Rb_tree_node_base *at16040; char at16044[8];
 _STL::_Rb_tree_node_base *at1604c; char at16050[0x17080-0x16050];
 int at17080,at17084; AsciiString at17088; char at1708c[0x170a8-0x1708c];
 bool at170a8; char at170a9[3]; Player *at170ac; int at170b0,at170b4;
 char at170b8[0x17270-0x170b8]; Update0034B9A0List *at17270;
 char at17274[0x17637-0x17274]; bool at17637;
protected:
 void updateFades();
};
extern void j_0003ce98(); extern void j_0000fcbd();
static __forceinline void callUpdateMember(ScriptEngine *p, void (*raw)()) {
 union {void (*raw)(); void (ScriptEngine::*member)();} u;
 u.raw=raw; (p->*u.member)();
}
extern ScriptActionsInterface *TheScriptActions;
extern ScriptConditionsInterface *TheScriptConditions;
#define TheSidesList (*(SidesList**)0x012ef428)
extern PlayerList *ThePlayerList;
extern void *TheScriptDebugWindowDLL;
extern int st_CurrentFrame; // Retail VA 0x012F0760; no new pin landed by this partial.
#define CurrentFrame st_CurrentFrame
#define TheScriptEngine (*(ScriptEngine**)0x012f076c)
struct Update0034B9A0GlobalData { char at0[0x11e0]; AsciiString *begin,*end,*capacity; };
#define TheWritableGlobalData (*(Update0034B9A0GlobalData**)0x012ed5c8)
#define DebugDisabled (*(bool*)0x012ed4d8)
// Existing matched static helper at 0033EB70. Its declaration/implementation is
// derived from ScriptEngine_appendMessage.cpp; no helper row is claimed here.
// Defining it in the caller TU
// is necessary for MSVC 7.1's private EDI argument convention.
static __declspec(noinline) void _adjustVariable(const AsciiString& str,int value,bool shouldPause,bool showSeconds) {
 if(DebugDisabled) return;
 if(TheScriptEngine->isTimeFast()) return;
 if(!TheScriptDebugWindowDLL) return;
 for(AsciiString *name=TheWritableGlobalData->begin; name!=TheWritableGlobalData->end; ++name)
  if(str.StringBase<char>::startsWith(*name)) return;
 char buff[32];
 if(showSeconds) sprintf(buff,"%d (%0.2f secs)",value,value*0.2f);
 else sprintf(buff,"%d ",value);
 void *module=TheScriptDebugWindowDLL;
 if(!module) return;
 FARPROC proc;
 if(shouldPause) proc=GetProcAddress(module,"AdjustVariableAndPause");
 else proc=GetProcAddress(module,"AdjustVariable");
 if(!proc) return;
 ((void (__cdecl*)(const char*,const char*))proc)(str.str(),buff);
}
// Retain both values for the static helper's pause argument during compilation.
void Update0034B9A0HelperCaller(const AsciiString& s,int n,bool pause,bool seconds) { _adjustVariable(s,n,pause,seconds); }

void ScriptEngine::update() {
 if(at170a8) {
  createNamedCache(); callUpdateMember(this,j_0003ce98); at170a8=false;
 } else callUpdateMember(this,j_0003ce98);
 if(at17084>0) { --at17084; if(at17084<1) TheScriptActions->closeWindows(false); }
 if(at17080>0) { --at17080; if(at17080<1) _bfme_finishEndGame(); }
 if(at170b4) updateFades();
 if(at17080>=0) return;
 if(TheScriptActions) TheScriptActions->update();
 if(TheScriptConditions) TheScriptConditions->update();
 // BFME uses ordered trees instead of the ZH fixed counter/flag arrays.
 _STL::_Rb_tree_node_base *end=at16040;
 for(CounterIterator it((CounterNode*)end->_M_left), e((CounterNode*)end); it!=e; ++it) {
  Update0034B9A0Counter *c=&*it;
  if(c->at1c && c->at18>=0) --c->at18;
 }
 // Each player temporarily overrides the current script-name scope.
 int i=0;
 int count=TheSidesList->at28;
 if(i<count) do {
  at170ac=ThePlayerList->getNthPlayer(i);
  LatchRestore<AsciiString> latch(at17088,KEYNAME(at170ac->getNameKey()));
  Update0034B9A0Side *side=0;
  if(i>=0) { if(i<TheSidesList->at28) side=&TheSidesList->at2c[i]; }
  Update0034B9A0ScriptList *sl=side->at8;
  if(sl) { walkNamed((Rva00355950Arr*)sl,sl->at8,true); walkChild((Rva003558C0Arr*)sl,sl->at4); }
  at170ac=0;
  } while(++i<TheSidesList->at28);
 // UI interaction strings are STLport 12-byte list nodes.
 ThePlayerList->updateTeamStates();
 Update0034B9A0List *node=at17270->next;
 while(node!=at17270) {
  Update0034B9A0List *old=node; node=node->next;
  old->value.~AsciiString(); _STL::__node_alloc<true,0>::deallocate(old,12);
 }
 at17270->next=at17270; at17270->prev=at17270;
 at17637=true; callUpdateMember(this,j_0000fcbd);
 at17637=false; CurrentFrame=(CurrentFrame+1);
 // Preserve the three separate temporary AsciiString lifetimes/EH states.
 if(TheScriptDebugWindowDLL && !isTimeFast()) {
  if(TheScriptDebugWindowDLL) {
   FARPROC proc=GetProcAddress(TheScriptDebugWindowDLL,"SetTheSidesList");
   if(proc) ((void (__cdecl*)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*))proc)(
    TheSidesList,TheScriptEngine,*(void**)0x012ed668,TheWritableGlobalData,*(void**)0x012ed600,0,0,
    *(void**)0x012f1600,*(void**)0x012ef4cc,*(void**)0x012ef1d8,*(void**)0x012f0898);
  }
  end=at16040;
  for(CounterIterator it((CounterNode*)end->_M_left), e((CounterNode*)end); it!=e; ++it) {
   Update0034B9A0Counter *c=&*it;
   AsciiString name=c->at10; name.concat('/'); name.concat(c->at14);
   if(c->at1d) _adjustVariable(name.str(),c->at18,false,true);
   else _adjustVariable(name.str(),c->at18,false,false);
  }
  end=at1604c;
  for(FlagIterator it((FlagNode*)end->_M_left), e((FlagNode*)end); it!=e; ++it) {
   Update0034B9A0Flag *f=&*it;
   AsciiString name=f->at10; name.concat('/'); name.concat(f->at14);
   _adjustVariable(name.str(),f->at18,false,false);
  }
 }
}

