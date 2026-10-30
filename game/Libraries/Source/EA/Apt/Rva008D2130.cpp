// Retail008D2130,393bytes: matched counter callbacks reach this existing
// opaque BfmeThingCBC::bfmeStepCBC spelling. No EA class identity asserted.
// Two constructor-expression lifetimes recover the native EH states.
// Evidence: targets/game/reverse/identity_evidence/008d2130-round57-native-lifetime.md
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
extern void *(*Rva008C5D70Alloc)(unsigned int);
extern "C" void (*TheBfmeFree)(void *, unsigned int);
class BfmeThingBE {
public:
 BfmeThingBE();
 static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
 static void operator delete(void *p,unsigned n) { TheBfmeFree(p,n); }
 void *m_nested;
};
// Retail unwind state 0 pushes 16 and the allocation, then calls the 0x008976D0 thunk.
struct Gen_uws16_008976d0 { static void operator delete(void *,unsigned); };
class Rva0089C860State : public Gen_uws16_008976d0 {
public:
 Rva0089C860State(int value) { initialize(value); }
 Rva0089C860State *initialize(int);
 static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
 int m_value,m_first,m_second,m_third;
};
class Gen_008bd690 { public:int m(); };
class Gen_008bd6a0 { public:void m(int); };
class BfmeD1046 { public:void bfmeReset1046(int); };
class BfmeA1227 {
public:
 void bfmeDump1227(void *,int);
 int m_bfme00;
 void *m_bfme04;
};
struct Rva008D2130Table { unsigned m_00,m_04; BfmeA1227 m_08; };
struct Rva008D2130List { BfmeThingBE *m_00; int m_04; };
struct BfmeCounter8C5700 {
 char m_reserved[0x0c];
 Rva008D2130Table *m_0c;
 Rva0089C860State *m_10;
 int m_14;
 int m_count;
 unsigned m_flags;
 int m_20;
 Rva008D2130List m_24;
};
class BfmeThingCBC {
public:
 void bfmeStepCBC(int count);
 char m_reserved[0x50];
 BfmeCounter8C5700 *m_counter;
};
class BfmeNode1236List {
public:
 void bfmeProcess1236(void *walk,void *owner,int frame);
};
extern void d_008bde60();
static __forceinline void Rva008D2130Dispatch(BfmeA1227 *frames,Rva008D2130List *list,BfmeThingCBC *owner,int index) {
 ((BfmeNode1236List *)frames)->bfmeProcess1236(list,owner,index);
}
static __forceinline void Rva008D2130Merge(Rva008D2130List *list,BfmeThingBE *value,Rva0089C860State *temporary,Rva0089C860State *previous) {
 typedef void (Rva008D2130List::*Call)(BfmeThingBE *,Rva0089C860State *,Rva0089C860State *);
 union { void (*raw)(); Call member; } f;
 f.raw=d_008bde60;
 (list->*f.member)(value,temporary,previous);
}
void BfmeThingCBC::bfmeStepCBC(int count) {
 BfmeCounter8C5700 *counter=m_counter;
 if(count<0 || count>=counter->m_0c->m_08.m_bfme00 || count==counter->m_count) return;
 if(count==counter->m_count+1) {
  counter->m_count=count;
  Rva008D2130Dispatch(&counter->m_0c->m_08,&counter->m_24,this,count);
 } else {
  int old=((Gen_008bd690 *)&counter->m_24)->m();
  BfmeThingBE *replacement=new BfmeThingBE;
  Rva0089C860State *temporary=new Rva0089C860State(8);
  ((Gen_008bd6a0 *)&counter->m_24)->m((int)replacement);
  Rva0089C860State *previous=counter->m_10;
  counter->m_10=temporary;
  ((BfmeD1046 *)&counter->m_24)->bfmeReset1046(0);
  for(counter->m_count=0;counter->m_count<=count && counter->m_count<counter->m_0c->m_08.m_bfme00;++counter->m_count)
   Rva008D2130Dispatch(&counter->m_0c->m_08,&counter->m_24,this,counter->m_count);
  counter->m_count=count;
  ((Gen_008bd6a0 *)&counter->m_24)->m(old);
  counter->m_10=previous;
  Rva008D2130Merge(&counter->m_24,replacement,temporary,previous);
 }
 counter->m_24.m_04=counter->m_count;
 counter->m_0c->m_08.bfmeDump1227(this,counter->m_count);
}
