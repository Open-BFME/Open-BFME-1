// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt handler, retail 0x008CD740: clear a named object value and
// replace the two stack operands with pooled integer 1. Factory layout and tables
// agree with the existing AptInteger::Create at 0x008A11E0.
struct Rva8CD130StringBlock { unsigned short m_refs; };
extern Rva8CD130StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
class Rva8CD130String {
public:
 Rva8CD130String() { m_block=&g_bfmeDefaultString1284; ++g_bfmeDefaultString1284.m_refs; }
 ~Rva8CD130String() { Rva8CD130StringBlock *block=m_block; --block->m_refs; if(block->m_refs==0) Rva01337A30ReleaseTable[1](block); }
 Rva8CD130StringBlock *m_block;
};
class Rva8CD130Value {
public:
 virtual void addRef(); virtual void release();
 virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual bool slot9();
 void getName(Rva8CD130String *);
 unsigned m_flags;
};
struct Rva008CD740Integer {
 void *m_vtable; unsigned m_flags;
 union { Rva008CD740Integer *m_next; int m_value; };
};
struct Rva00899560Pool {
 int m_capacity,m_count; Rva008CD740Integer **m_items;
 __forceinline void add(Rva008CD740Integer *v) {
  int &count=m_count;
  if(count>=m_capacity) v->m_flags&=0xbfffffff;
  else { m_items[count]=v; ++count; }
 }
};
// The pooled-integer free head at 0x013387D0 is the defining Rva008D2A10 list
// (see game/GameEngine/Source/Common/Rva008D2A10Link.cpp); it has no header,
// so forward-declare it and spell the reference with its defining type.
class Rva008D2A10;
extern Rva008D2A10 *g_rva008D2A10;
extern Rva00899560Pool *g_rva01337810GcRoots;
// Retail's Apt value vftables: AptValue's at VA 0x01135D68 and AptInteger's at
// 0x01136400 (dir32_addresses.csv), each referenced here by its own decorated
// name rather than through a stand-in the linker would have to alias.
extern "C" const char __identifier("??_7AptValue@@6B@")[];
extern "C" const char __identifier("??_7AptInteger@@6B@")[];
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
__forceinline Rva8CD130Value *integerOne008CD740() {
 Rva008CD740Integer *v=(Rva008CD740Integer *)g_rva008D2A10;
 if(v) {
  g_rva008D2A10=(Rva008D2A10 *)v->m_next;
  g_rva01337810GcRoots->add(v);
  v->m_value=1;
  return (Rva8CD130Value *)v;
 }
 v=(Rva008CD740Integer *)Rva008C5D70Alloc(12);
 if(v) {
  v->m_vtable=(void *)__identifier("??_7AptValue@@6B@");
  v->m_flags=(v->m_flags&0xf0008007)|0x40008007;
  g_rva01337810GcRoots->add(v);
  v->m_vtable=(void *)__identifier("??_7AptInteger@@6B@");
  v->m_value=1;
  return (Rva8CD130Value *)v;
 }
 return 0;
}
class Rva008CF3C0String;
class Rva008A9B00;
class Rva008CF3C0State {
public:
 void append(void *,void *,Rva008CF3C0String *,Rva008A9B00 *,int,int,int);
 int m_00; int m_04; Rva8CD130Value **m_08;
};
struct Rva008CD740Context { unsigned m_00; void *m_04; void *m_08; };
void clearObjectName008CD740(Rva008CF3C0State *state,Rva008CD740Context *context) {
 Rva8CD130Value *top=state->m_08[state->m_00-1];
 Rva8CD130Value *under=state->m_08[state->m_00-2];
 if(under->slot9()) {
  Rva8CD130String name;
  top->getName(&name);
  state->append(under,context->m_08,(Rva008CF3C0String *)&name,0,1,1,0);
 }
 for(int i=1;i<=2;++i) {
  Rva8CD130Value *old=state->m_08[state->m_00-i];
  if(!((unsigned char)(old->m_flags>>30)&1)) old->release();
 }
 state->m_00-=2;
 Rva8CD130Value *value=integerOne008CD740();
 state->m_08[state->m_00]=value;
 ++state->m_00;
 if(!((unsigned char)(value->m_flags>>30)&1)) value->addRef();
}
