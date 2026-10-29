// ?Rva00463850@@YAPAVRva0045EF90Object@@PBURva0045DD90FloatPair@@0PBD1@Z
// partial score=0.997 date=2026-10-03
// stlport
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /I. /Iinputs/vendor/stlport /DNDEBUG /DWIN32 /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include <map>
#include <hash_map>
#include "GameClient/GameWindow.h"
#include "Common/NameKeyGenerator.h"
#pragma intrinsic(strcmp)
// The 0x2c-byte window-layout record constructed at 0x00463858 and destroyed at
// 0x00463991/0x004639e3. Its special members are the matched WindowLayoutInfo
// ctor/dtor bodies (0x004888A0/0x00460540), reached through their retail
// incremental-link thunks 0x00025AB8/0x0001566D.
struct WindowLayoutInfo {
    WindowLayoutInfo();
    ~WindowLayoutInfo();
    char storage[44];
};
class GameWindow;
class GameWindowManager;
class WindowManager;
extern GameWindowManager *TheWindowManager;
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager
class BfmeStrVMZ;
int bfmeGoDYG(void *);
char bfmeGetParamVMZ(const char *,const char *,BfmeStrVMZ *);
const char *bfmePathLeafAfterMarker(const char *);
class Rva00465CB0 { public: int get(unsigned); };
class Rva004879A0 { public: GameWindow *rva004879A0(GameWindow *,void *); };
class Rva00478C90Object { public: int store(unsigned); };
struct Rva00463850Window {
    char pad[0x1f4];
    void *field1f4;
};

extern NameKeyGenerator *TheNameKeyGenerator;
class BfmeMade_0045DC70;
struct Rva00463850Param {
    void *field00; unsigned field04,field08,field0c,field10,field14;
    BfmeMade_0045DC70 *(__stdcall *field18)(void *); unsigned field1c,field20,field24,field28,field2c,field30;
    Rva00463850Param() : field00(0),field08(0),field0c(0),field10(0),field14(0),field18(0),field1c(0),field20(0),field24(0),field28(0),field2c(0),field30(0) {field04=0x08000001;}
};
BfmeMade_0045DC70 *__stdcall bfmeMake_0045DC70(void *);
struct Rva00463850Manager {
#define S(n) virtual void slot##n();
S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25)
    virtual GameWindow *slot26(AsciiString,WindowLayoutInfo *,void *);
S(27) S(28)
    virtual GameWindow *slot29(Rva00463850Param *);
};
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString&a,const AsciiString&b)const {return a.compare(b)<0;} }; }
struct Rva004618B0Value { AsciiString m_key; };
struct Rva004618B0KeyOfValue { const AsciiString &operator()(const Rva004618B0Value &x)const{return x.m_key;} };
typedef _STL::_Rb_tree<AsciiString,Rva004618B0Value,Rva004618B0KeyOfValue,_STL::less<AsciiString>,_STL::allocator<Rva004618B0Value> > Rva004618B0Tree;
class Gen_00C70080Target;
class Gen_00C700A0Target;
extern Gen_00C70080Target TheBfmeObject_00C70080;
extern Gen_00C700A0Target TheBfmeObject_00C700A0;
extern void *g_Va012F198C;
#define Rva00463850Tree (*(Rva004618B0Tree *)&TheBfmeObject_00C70080)
#define Rva00463850Map (*(Rva00461BF0Map *)&TheBfmeObject_00C700A0)
struct Rva00463850Node { char pad[0x14]; GameWindow *field14; };
class Rva0045EF90Base { public: virtual ~Rva0045EF90Base(); unsigned m_value; };
class Rva0045EF90Object:public Rva0045EF90Base {
public:
 Rva0045EF90Object(); Rva0045EF90Object(const Rva0045EF90Object&); virtual ~Rva0045EF90Object();
 AsciiString m_first,m_second; GameWindow *m_handle; float m_value14,m_value18,m_value1c,m_value20; unsigned char m_value24,m_padding25[3]; AsciiString m_last;
};

typedef _STL::hash_map<AsciiString,Rva0045EF90Object,rts::hash<AsciiString>,rts::equal_to<AsciiString> > Rva00461BF0Map;
struct Rva0045DD90FloatPair;
struct Rva0045DD90Record;
extern "C" void rva0045DD90UpdateCoordinatePairs(Rva0045DD90Record *,const Rva0045DD90FloatPair *,const Rva0045DD90FloatPair *);
static __forceinline GameWindow *rva00463850Resolve(void *ctx,const char *params,AsciiString &filename)
{
 GameWindow *window;
 char loaded=bfmeGetParamVMZ(params,"_Load",(BfmeStrVMZ *)&filename);
 if(loaded!=0) {
  
  if(strcmp(filename.str(),"BinkGameWindow::Create")==0) {
   Rva00463850Param p;
   p.field18=bfmeMake_0045DC70;
   p.field00=ctx;
   window=((Rva00463850Manager *)TheWindowManager)->slot29(&p);
  } else {
   filename.toLower();
   Rva00463850Node *entry=(Rva00463850Node *)Rva00463850Tree.find(filename)._M_node;
   if(entry==*(Rva00463850Node **)&Rva00463850Tree) {
    WindowLayoutInfo layout;
    window=((Rva00463850Manager *)TheWindowManager)->slot26(filename,&layout,ctx);
   } else {
    if(!entry->field14) {
     WindowLayoutInfo layout;
     entry->field14=((Rva00463850Manager *)TheWindowManager)->slot26(filename,&layout,g_Va012F198C);
    }
    window=((Rva004879A0 *)TheWindowManager)->rva004879A0(entry->field14,ctx);
   }
  }
  return window;
 }
 return 0;
}
Rva0045EF90Object *Rva00463850(const Rva0045DD90FloatPair *a,const Rva0045DD90FloatPair *b,const char *name,const char *params)
{
 int id=bfmeGoDYG((void *)name);
 void *ctx=(void *)((Rva00465CB0 *)g_theWindowManager)->get(id);
 if(ctx) {
 AsciiString filename;
 GameWindow *window=rva00463850Resolve(ctx,params,filename);
 if(!window) return 0;
 {
   const char *leaf=bfmePathLeafAfterMarker(name);
   Rva0045EF90Object *record=&Rva00463850Map[AsciiString(leaf)];
   record->m_value=id;
   record->m_handle=window;
   record->m_first=name;
   window->winHide(false);
   ((Rva00463850Window *)window)->field1f4=0;
   ((Rva00478C90Object *)window)->store(TheNameKeyGenerator->nameToKey(leaf));
   rva0045DD90UpdateCoordinatePairs((Rva0045DD90Record *)record,a,b);
   return record;
  }
 }
 return 0;
}

// Evidence (2026-10-03 b1): retail 00463850..00463AF0 inclusive,
// plain RET at +2A0, and live Ghidra creation independently report 673 bytes.
// FuncInfo E14D4C: states 0/3 own native AsciiStrings; states 1/2 own
// the 44-byte WindowLayoutInfo storage at the same stack address.
// The inline resolver is the measured source-shape lever: without it, the
// success block precedes the failure epilogue (677 bytes/174 differences).
// This form is 673 bytes, 42 relocation sites, only TEST AL,AL instead of
// retail CMP AL,BL at +6D. A bool function-pointer return view does not help.
// The scratch WindowLayoutInfo view is 44 bytes: the retail ctor 4888A0 and
// dtor 460540 both prove strings at +14/+18/+1C/+20/+24 and the list at +28.
// The special members bind to those matched bodies through their thunks; no
// second callee pin is invented.
// The tree at VA12F19CC and map at VA12F19A4 are the recorded singleton
// objects TheBfmeObject_00C70080 / TheBfmeObject_00C700A0 viewed through this
// unit's layouts; VA12F198C is the unowned context slot read as g_Va012F198C.
// Factory pointer is ILT438870 -> body45DC70; compare literal
// BinkGameWindow::Create is 22 chars plus NUL (all 23 bytes were read).
// Manager virtual +68 consumes string/layout/context, +74 one 52-byte record.
