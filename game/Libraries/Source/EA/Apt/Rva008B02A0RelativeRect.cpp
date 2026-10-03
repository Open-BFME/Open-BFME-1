// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008B02A0: byte-verified callback; local layouts retain address-derived identities.
struct Rva008D2950Node { void *m_vtable; unsigned m_flags; Rva008D2950Node *m_next; };
struct Rva00899560Pool {
 int m_capacity,m_count; Rva008D2950Node **m_items;
 __forceinline void addPooled(Rva008D2950Node *node) {
  int &count=m_count;
  if(count>=m_capacity) node->m_flags &= 0xbfffffff;
  else { m_items[count]=node; count++; }
 }
};
// Retail's free-list head at 0x013387CC is the global this TU spells
// Rva008D2950Head; Rva008D29A0Link.cpp defines it as ?g_rva008D29A0, a
// Rva008D29A0*. Only the pointer value is used here, so the defining name is
// referenced by its own class name (forward declared, never defined here).
class Rva008D29A0;
extern Rva008D29A0 *g_rva008D29A0;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
extern const char vtable01135D68[],vtable01136698[];
struct Float008B02A0 {
 void *m_vtable; unsigned m_flags;
 union { Float008B02A0 *m_next; float m_value; };
 static __forceinline Float008B02A0 *create(float value) {
  Float008B02A0 *object=(Float008B02A0*)g_rva008D29A0;
  if(object) {
   g_rva008D29A0=(Rva008D29A0*)object->m_next;
   g_rva8CD130IdleHook->addPooled((Rva008D2950Node*)object);
   object->m_value=value;
   return object;
  }
  return new Float008B02A0(value);
 }
 void *operator new(unsigned size) { return Rva008C5D70Alloc(size); }
 __forceinline Float008B02A0(float value) {
   m_vtable=(void*)vtable01135D68;
   m_flags=(m_flags&0xf0008006)|0x40008006;
   g_rva8CD130IdleHook->addPooled((Rva008D2950Node*)this);
   m_vtable=(void*)vtable01136698;
   m_value=value;
 }

};

class BfmeItemDX;
void bfmePush(BfmeItemDX*);
class Rva00899F00Base {
public:
 Rva00899F00Base(unsigned,int);
 void *operator new(unsigned size) {
  char *raw=(char*)Rva008C5D70Alloc(size+8);
  char *p=raw+8;
  bfmePush((BfmeItemDX*)p); return p;
 }
 void operator delete(void*);
 char m_bytes[32];
};
class BfmeN1235 { public: void bfmeDo1235(void*,void*); };
class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table { public: void add(Rva8D0D80String*,Rva8D0D80Value*); };
struct Value008B02A0 { int m_f0; unsigned m_flags; char pad08[0x18]; float m_f20,m_f24; };
struct Rect008B02A0 { float m_f0,m_f4,m_f8,m_fC; };
// Retail's object at 0x01338748 is the Apt stack, defined by Rva00C6DCC0StaticInit.cpp
// as `struct Rva008AE770Stack` and exported as ?Rva008AE770TheStack@@3U....  MSVC 7.1
// mangles a global's class type 3V for `class` but 3U for `struct`; only the leading
// int (the stack depth) is read here, so the rest of the layout stays out of this TU.
struct Rva008AE770Stack
{
	int count;
	int m_rva0133874C;
	Value008B02A0** m_rva01338750;
};
extern struct Rva008AE770Stack Rva008AE770TheStack;
// 0x013379BC is the fallback value database pointer, defined as AptValue *
// by Bfme5AppendFallback8CAFF0.cpp (?g_bfmeFallbackDB@@3PAVAptValue@@A).
class AptValue;
extern AptValue *g_bfmeFallbackDB;
extern void *global01337A04;
extern char key01338734[],key01338738[],key01338740[],key01338744[];
Rva00899F00Base *aptRelativeRect008B02A0(Value008B02A0 *self,int argc) {
 if(argc>1) return (Rva00899F00Base *)g_bfmeFallbackDB;
 Value008B02A0 *other=self;
 if(argc==1) {
  Rva008AE770Stack& stk = Rva008AE770TheStack;
  Value008B02A0** args = stk.m_rva01338750;
  other=args[stk.count-1];
  if((unsigned char)~(other->m_flags>>15)&1) return (Rva00899F00Base *)g_bfmeFallbackDB;
 }
 Rva00899F00Base *result=new Rva00899F00Base(0x1b,8);
 Rect008B02A0 rect;
 rect.m_f0=1000000000.0f; rect.m_f8=-1000000000.0f;
 rect.m_fC=-1000000000.0f; rect.m_f4=1000000000.0f;
 ((BfmeN1235*)self)->bfmeDo1235(global01337A04,&rect);
 rect.m_f8-=other->m_f20; rect.m_f0-=other->m_f20;
 rect.m_f4-=other->m_f24; rect.m_fC-=other->m_f24;
 Rva8D0D80Value *first=(Rva8D0D80Value*)Float008B02A0::create(rect.m_f8);
 Rva8D0D80Table *table=(Rva8D0D80Table*)((char*)result+8);
 table->add((Rva8D0D80String*)key01338734,first);
 table->add((Rva8D0D80String*)key01338738,(Rva8D0D80Value*)Float008B02A0::create(rect.m_f0));
 table->add((Rva8D0D80String*)key01338740,(Rva8D0D80Value*)Float008B02A0::create(rect.m_fC));
 table->add((Rva8D0D80String*)key01338744,(Rva8D0D80Value*)Float008B02A0::create(rect.m_f4));
 return result;
}
