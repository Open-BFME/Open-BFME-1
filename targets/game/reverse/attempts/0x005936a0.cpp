// ??0BfmeThingCDA@@QAE@XZ
// partial score=0.4743 date=2026-10-03
// Retail constructor 0x005936A0..0x005938E7; complete RET followed by INT3.
// Draft only: callback vtables and EH destructor bindings remain unpromoted.
// The existing BfmeThingCDA refresh at58B840 receives the same unchanged this.
// Table110BC7C slot1->440705->58CF40 tail-dispatches the bound method;
// callback40BB68->5917E0 is the existing BfmeHostDN::bfmeNotifyDN(void*).
// Table110BC88 slot1->414105->593310 reads owner+8/index+C (not a PMF).
// Table110BC94 slot1->40935E->58CFB0 dereferences two pointers into sret.
// FuncInfoE26E34 state0 destroys this+8 through58B820; state3 destroys
// the outgoing holder through45F170. These views do not establish new pins.
// Explicit record reset countdown reproduces retail62..80 and preserves
// state0 before the body stores portrait+28; native array ctors were unrolled.
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class BfmeLayoutVHH;
void bfmeGoVHH(char, BfmeLayoutVHH *);
extern void j_0000bb68();
class __single_inheritance BfmeThingCDA;
class __single_inheritance BfmeHostDN { public: void bfmeNotifyDN(void *); };
typedef void (BfmeHostDN::*Rva005936A0MethodPtr)(void *);
struct Rva005936A0MethodBinding { BfmeThingCDA *p; Rva005936A0MethodPtr m; Rva005936A0MethodBinding(Rva005936A0MethodPtr b,BfmeThingCDA *a):p(a),m(b){} };
struct Rva005936A0IndexBinding { BfmeThingCDA *p; int m; Rva005936A0IndexBinding(BfmeThingCDA *a,int b):p(a),m(b){} };
struct Rva005936A0TimerBinding { float *p; int *m; Rva005936A0TimerBinding(float *a,int *b):p(a),m(b){} };
struct Rva005936A0State {
 bool m_00; void *m_04; bool m_08; void *m_0c; float m_10;
 bool m_14,m_15,m_16; void *m_18,*m_1c;
 Rva005936A0State():m_00(0),m_04(0),m_08(0),m_0c(0),m_10(-1.0f),m_14(0),m_15(0),m_16(0),m_18(0),m_1c(0){}
 ~Rva005936A0State(); // EH state 0 calls native 58B820 on this+8; binding pending.
};
struct Rva005936A0Record {
 void *m_00,*m_04,*m_08,*m_0c; float m_10; int m_14,m_18; bool m_1c,m_1d;
 void reset() { m_00=0; m_04=0; m_08=0; m_0c=0; m_10=1.0f; m_14=0; m_18=0; m_1c=0; m_1d=0; }
};
class Rva005936A0Head {
public:
 Rva005936A0Head():m_refCount(0){}
 virtual ~Rva005936A0Head();
 virtual void invoke()=0;
 int m_refCount;
};
class Rva005936A0Method : public Rva005936A0Head {
public:
 Rva005936A0Method(const Rva005936A0MethodBinding &b):m_target(b.p),m_method(b.m){}
 virtual void invoke();
 BfmeThingCDA *m_target; Rva005936A0MethodPtr m_method;
};
class Rva005936A0Index : public Rva005936A0Head {
public:
 Rva005936A0Index(const Rva005936A0IndexBinding &b):m_target(b.p),m_index(b.m){}
 virtual void invoke();
 BfmeThingCDA *m_target; int m_index;
};
class Rva005936A0Timer : public Rva005936A0Head {
public:
 Rva005936A0Timer(const Rva005936A0TimerBinding &b):m_08(b.p),m_0c(b.m){}
 virtual void invoke();
 float *m_08; int *m_0c;
};
class Rva0050F8B0FunctorHolder {
public:
 Rva0050F8B0FunctorHolder(Rva005936A0MethodBinding b) { m_ptr=new Rva005936A0Method(b); if(m_ptr) ++m_ptr->m_refCount; }
Rva0050F8B0FunctorHolder(Rva005936A0IndexBinding b) { m_ptr=new Rva005936A0Index(b); if(m_ptr) ++m_ptr->m_refCount; }
Rva0050F8B0FunctorHolder(Rva005936A0TimerBinding b) { m_ptr=new Rva005936A0Timer(b); if(m_ptr) ++m_ptr->m_refCount; }
 Rva0050F8B0FunctorHolder(const Rva0050F8B0FunctorHolder &p);
 ~Rva0050F8B0FunctorHolder();
 Rva005936A0Head *m_ptr;
};
class WindowManager {
public:
 void bfmeBindRva004650F0(const AsciiString &,Rva0050F8B0FunctorHolder);
 void registerPalantirCallback(const AsciiString &,Rva0050F8B0FunctorHolder);
};
extern WindowManager *g_rva012F19E8WindowManager;
class BfmeThingCDA {
public:
 BfmeThingCDA();
 void bfmeStepCDA();
 bool m_bfmeFlag,m_bfmeReady; void *m_bfmeVal;
 Rva005936A0State m_08;
 void *m_bfmePortrait;
 Rva005936A0Record m_2c[6];
};
BfmeThingCDA::BfmeThingCDA():m_bfmeFlag(0),m_bfmeReady(0),m_bfmeVal(0) {
 m_bfmePortrait=0;
 Rva005936A0Record *entry=m_2c;
 int count=6;
 do { entry->reset(); ++entry; } while(--count);
 {
  AsciiString name("Palantir/CommandUI/PortraitBackground");
  g_rva012F19E8WindowManager->bfmeBindRva004650F0(name,Rva0050F8B0FunctorHolder(Rva005936A0MethodBinding(&BfmeHostDN::bfmeNotifyDN,this)));
 }
 for(int i=0;i<6;++i) {
  AsciiString name;
  bfmeGoVHH((char)i,(BfmeLayoutVHH *)&name);
  { char slash='/'; name.StringBase<char>::concat(&slash,1); }
  g_rva012F19E8WindowManager->bfmeBindRva004650F0(AsciiString("Palantir/")+name,Rva0050F8B0FunctorHolder(Rva005936A0IndexBinding(this,i)));
  name.StringBase<char>::concat("Timer",5);
  g_rva012F19E8WindowManager->registerPalantirCallback(name,Rva0050F8B0FunctorHolder(Rva005936A0TimerBinding(&m_2c[i].m_10,&m_2c[i].m_14)));
 }
 bfmeStepCDA();
}
