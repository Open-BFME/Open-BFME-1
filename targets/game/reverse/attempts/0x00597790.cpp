// ??0Rva00597790@@QAE@XZ
// partial score=0.6071 date=2026-10-03
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Address-qualified constructor at 00597790: twelve 24-byte records and
// two callback registrations per record. No original owner name is asserted.
#include "ascii_string.h"
#include <algorithm>
typedef int (__cdecl *BigObfHook)(void*,void*,__int64);
struct BigObfSlot { BigObfHook m_hook,m_alt; char m_pad[0x80]; void *m_a,*m_b; };
extern BigObfSlot g_Slot012BC6C8;
class Obf00590B50 { public: __declspec(noinline) Obf00590B50(int*,int*); unsigned m_bits[8]; };
// Authentic helper from BigObfHookWrappers.cpp, independently matched at
// 00590B50. The one-instruction frame selector has no portable C++ equivalent.
struct BigObfSelectorRecord { unsigned m_key[5],m_seed[5]; };
extern BigObfSelectorRecord g_ObfRecord012B82C4;
Obf00590B50::Obf00590B50(int *a,int *b) {
 unsigned selector=0;
 __asm { mov selector, ebp }
 unsigned index=selector&3;
 unsigned key=g_ObfRecord012B82C4.m_key[index];
 m_bits[0]=g_ObfRecord012B82C4.m_seed[index];
 m_bits[1]=0x04A85801; m_bits[2]=0x04A85805; m_bits[3]=0x04A85801;
 m_bits[4]=*a; m_bits[5]=*b;
 m_bits[1]^=key*key; m_bits[2]^=m_bits[1]*key; m_bits[3]^=m_bits[2]*key;
 m_bits[4]^=m_bits[3]*key; m_bits[5]^=m_bits[4]*key;
 m_bits[6]^=m_bits[5]*key; m_bits[7]^=m_bits[6]*key;
}
int __cdecl Gen0058C7F0(int,int);
static __forceinline int Rva00597790Arithmetic(int a,int b) {
 BigObfHook hook=g_Slot012BC6C8.m_hook;
 if(hook) goto hot;
 if(g_Slot012BC6C8.m_alt) {
 hot:
  void *pa=g_Slot012BC6C8.m_a,*pb=g_Slot012BC6C8.m_b;
  Obf00590B50 o(&a,&b);
  return hook(pa,pb,(__int64)(int)&o);
 }
 return Gen0058C7F0(a,b);
}
struct Rva00597790Record {
 int at00,at04,at08;
 float at0c;
 int at10;
 bool at14;
 __forceinline Rva00597790Record():at00(0),at08(Rva00597790Arithmetic(0,0)),at0c(1.0f),at10(0),at14(false) {}
};
class Rva00597790;
class FunctorWrapperHead { public: virtual ~FunctorWrapperHead(); int m_refCount; FunctorWrapperHead():m_refCount(0) {} };
struct Rva0046C000Mapped { FunctorWrapperHead *m_ptr; ~Rva0046C000Mapped(); };
class Rva0050F8B0FunctorHolder {
 FunctorWrapperHead *value;
public:
 ~Rva0050F8B0FunctorHolder() { reinterpret_cast<Rva0046C000Mapped*>(&value)->~Rva0046C000Mapped(); }
 Rva0050F8B0FunctorHolder(Rva00597790*,int);
 Rva0050F8B0FunctorHolder(float&,int&);
 Rva0050F8B0FunctorHolder(const Rva0050F8B0FunctorHolder &other) { value=other.value; if(value)++value->m_refCount; }
 Rva0050F8B0FunctorHolder(FunctorWrapperHead *p) { value=p; if(p)++p->m_refCount; }
};
class Rva0110BCA0Callback:public FunctorWrapperHead {
 Rva00597790 *owner; int index;
public:
 Rva0110BCA0Callback(Rva00597790 *p,int i):owner(p),index(i) {}
 virtual ~Rva0110BCA0Callback(); virtual void invoke();
};
class Rva0110BC94Callback:public FunctorWrapperHead {
 float *first; int *second;
public:
 Rva0110BC94Callback(float *p,int *q):first(p),second(q) {}
 virtual ~Rva0110BC94Callback(); virtual void invoke();
};
__forceinline Rva0050F8B0FunctorHolder::Rva0050F8B0FunctorHolder(Rva00597790 *owner,int index) {
 FunctorWrapperHead *p=new Rva0110BCA0Callback(owner,index); value=p; if(p)++p->m_refCount;
}
__forceinline Rva0050F8B0FunctorHolder::Rva0050F8B0FunctorHolder(float &first,int &second) {
 FunctorWrapperHead *p=new Rva0110BC94Callback(&first,&second); value=p; if(p)++p->m_refCount;
}
class WindowManager { public:
 void bfmeBindRva004650F0(const AsciiString&,Rva0050F8B0FunctorHolder);
 void registerPalantirCallback(const AsciiString&,Rva0050F8B0FunctorHolder);
};
extern WindowManager *TheWindowManager;
class Rva00597790 {
 int at00,at04;
 bool at08[20];
 Rva00597790Record at1c[12];
public: Rva00597790();
};
Rva00597790::Rva00597790():at00(0),at04(0) {
 std::fill(at08,at08+20,true);
 for(int i=0;i<12;++i) {
  AsciiString name;
  name.format("SpellBookUI/Spell%d/",i+1);
  TheWindowManager->bfmeBindRva004650F0(AsciiString("Palantir/")+name,Rva0050F8B0FunctorHolder(this,i));
  name.StringBase<char>::concat("Timer",5);
  TheWindowManager->registerPalantirCallback(name,Rva0050F8B0FunctorHolder(at1c[i].at0c,at1c[i].at10));
 }
}
