// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008A5BF0: byte-verified callback; local layouts retain address-derived identities.
struct BfmeStringData3AF0 { unsigned short m_refCount; unsigned short m_length; unsigned m_capacity; };
struct BfmeStringPool3AF0 { void *unused; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class Rva8CD130String {
public:
 Rva8CD130String() { m_data=&g_bfmeDefaultString1284; ++m_data->m_refCount; }
 ~Rva8CD130String() { BfmeStringData3AF0 *old=m_data; if(--old->m_refCount==0) g_rva01337A30AllocPair->free(old); }
 const char *text() const { return (const char*)m_data+8; }
 BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value { public: void getName(Rva8CD130String*); };
class KeyValuePairs00898D80 { public: Rva8CD130String keyValuePairs00898D80(); };
struct Rva008D2A30Node { void *m_vtable; unsigned m_flags; Rva008D2A30Node *m_next; };
struct Rva00899560Pool {
 int m_capacity,m_count; Rva008D2A30Node **m_items;
 __forceinline void addPooled(Rva008D2A30Node *node) {
  int &count=m_count;
  if(count>=m_capacity) node->m_flags &= 0xbfffffff;
  else { m_items[count]=node; count++; }
 }
};
class Rva008D2A80;
extern Rva008D2A80 *g_rva008D2A80;
extern Rva00899560Pool *g_rva01337810GcRoots;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
extern const char vtable01135D68[];
// 0x011360A8 is Rva008995E0Value's vftable, emitted as a COMDAT by
// Rva008995E0AptBoolValueCtor.cpp; the stand-in name declared here resolved
// nothing.  __identifier spells the compiler-emitted symbol, and the array
// type keeps the decay-to-pointer that retail's `mov dword ptr [eax], imm32`
// needs (a plain int declaration would load the vftable's first slot instead).
extern "C" const char __identifier("??_7Rva008995E0Value@@6B@")[];
struct Boolean008A58C0 {
 void *m_vtable; unsigned m_flags;
 union { Boolean008A58C0 *m_next; bool m_value; };
 static __forceinline Boolean008A58C0 *create(bool value) {
  Boolean008A58C0 *object=(Boolean008A58C0*)g_rva008D2A80;
  if(object) {
   g_rva008D2A80=(Rva008D2A80*)object->m_next;
   g_rva01337810GcRoots->addPooled((Rva008D2A30Node*)object);
   object->m_value=value;
   return object;
  }
  return new Boolean008A58C0(value);
 }
 void *operator new(unsigned size) { return Rva008C5D70Alloc(size); }
 __forceinline Boolean008A58C0(bool value) {
   m_vtable=(void*)vtable01135D68;
   m_flags=(m_flags&0xf0008005)|0x40008005;
   g_rva01337810GcRoots->addPooled((Rva008D2A30Node*)this);
   m_vtable=(void*)__identifier("??_7Rva008995E0Value@@6B@");
   m_value=value;
 }

};
extern Rva8CD130Value **g_bfmeArr1233;
// Retail's object at 0x01338748 is the Apt stack, defined by Rva00C6DCC0StaticInit.cpp
// as `struct Rva008AE770Stack` and exported as ?Rva008AE770TheStack@@3U....  MSVC 7.1
// mangles a global's class type 3V for `class` but 3U for `struct`; only the leading
// int (the stack depth) is read here, and the address is then cast as before.
struct Rva008AE770Stack { int count; };
extern struct Rva008AE770Stack Rva008AE770TheStack;
extern void (__cdecl *callback0133786C)(const char*,const char*,const char*,const char*,int);

extern "C" int __cdecl strcmp(const char*,const char*);
#pragma intrinsic(strcmp)
struct BfmeIterator1285 { Rva8CD130String m_key; unsigned m_taggedValue; };
class BfmeIteratorList1285 { public: BfmeIterator1285 *bfmeFirst1285(); BfmeIterator1285 *bfmeNext1285(BfmeIterator1285*); };
struct BfmeKey1279;
class BfmeLookup1279 { public: void bfmeErase1279(BfmeKey1279&); };
class Rva008CF3C0String;
class Rva008CF3C0State { public: void parseAndAppend(void*,void*,Rva008CF3C0String*); };
struct Owner008A5BF0 {
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual void slot10(); virtual void slot14(); virtual BfmeIteratorList1285 *slot18();
 char pad04[0x1c]; int m_f20;
};
Boolean008A58C0 *aptReplacePairs008A5BF0(Owner008A5BF0 *self,int argc) {
 self->m_f20=0;
 if(argc>0 && argc<=3) {
  Rva8CD130Value *v=g_bfmeArr1233[Rva008AE770TheStack.count-1];
  Rva8CD130String a; v->getName(&a);
  Rva8CD130Value *target=0;
  Rva8CD130String b;
  if(argc>1) target=g_bfmeArr1233[Rva008AE770TheStack.count-2];
  Rva8CD130String c;
  if(argc>2) { Rva8CD130Value *v3=g_bfmeArr1233[Rva008AE770TheStack.count-3]; v3->getName(&c); }
  Rva8CD130String pairs=((KeyValuePairs00898D80*)self)->keyValuePairs00898D80();
  callback0133786C(a.text(),b.text(),c.text(),pairs.text(),1);
  BfmeIteratorList1285 *list=self->slot18();
  if(!list) return Boolean008A58C0::create(false);
  BfmeIterator1285 *it=list->bfmeFirst1285();
  while(it) {
   if(strcmp(it->m_key.text(),"__proto__") && strcmp(it->m_key.text(),"prototype"))
    ((BfmeLookup1279*)list)->bfmeErase1279(*(BfmeKey1279*)it);
   it=list->bfmeNext1285(it);
  }
  ((Rva008CF3C0State*)&Rva008AE770TheStack)->parseAndAppend(target,0,0);
  self->m_f20=1;
  return Boolean008A58C0::create(true);
 }
 return Boolean008A58C0::create(false);
}
