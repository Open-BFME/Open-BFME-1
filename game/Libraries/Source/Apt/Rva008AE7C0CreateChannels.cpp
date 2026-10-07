// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008AE7C0: byte-verified callback; local layouts retain address-derived identities.
struct BfmeStringData3AF0 { unsigned short m_refCount; unsigned short m_length; unsigned m_capacity; };
struct BfmeStringPool3AF0 { void *unused; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class Rva8CD130String {
public:
 Rva8CD130String() { m_data=&g_bfmeDefaultString1284; ++m_data->m_refCount; }
 ~Rva8CD130String() { BfmeStringData3AF0 *old=m_data; if(--old->m_refCount==0) g_bfmeStringPool1284->free(old); }
 BfmeStringData3AF0 *m_data;
};
class AptValue { public: int toInteger() const; float toNumber(); };
class Rva8CD130Value { public: void getName(Rva8CD130String *); };
class BfmeSubmitter1283 { public: void bfmeSubmit1283(int,int,int,int,int,int,int,float*,int,int,int,int); };
class BfmeQuery1279 { public: void bfmeQuery1279(void*,int,void**,void**); };
class BfmeSlotState1289 { public: void bfmeSetAxis1289(int,float,int); };
class BfmeRef008A4B20;
class BfmePtrTable64_008A4B20 { public: void add(BfmeRef008A4B20*); };
class Rva008ACFC0RegisteredObject;
class Rva008ACFC0PointerRegistry { public: void add(Rva008ACFC0RegisteredObject*); };
struct BfmePickWorld1284;			// retail 0x013377D8 global, defined in BfmePicker1284.cpp
extern BfmePickWorld1284 *g_bfmeHolderBU;
extern unsigned char g_bfmeDispatchEnabled1281;
extern unsigned char flag0133781D;
struct Item008AE7C0 { int m_f0; };
struct Array008AE7C0 { int m_f0,m_f4,m_f8,m_fC; Item008AE7C0 **m_f10; };
struct Data008AE7C0 { int m_f0,m_f4; Array008AE7C0 m_f8; Array008AE7C0 *array() { return &m_f8; } };
struct Link008AE7C0 { int m_f0; Data008AE7C0 *m_f4; };
struct State008AE7C0 {
 int m_f0,m_f4,m_f8; Link008AE7C0 *m_fC;
 int m_f10,m_f14,m_f18,m_f1C,m_f20; BfmeQuery1279 *m_f24;
 int m_f28,m_f2C,m_f30,m_f34,m_f38,m_f3C,m_f40,m_f44,m_f48,m_f4C;
 float m_f50,m_f54,m_f58,m_f5C,m_f60;
 int m_f64,m_f68,m_f6C,m_f70,m_f74;
};
struct Owner008AE7C0 {
 State008AE7C0 *state() { return m_f50; }
 int m_f0; union { unsigned m_flags; struct { unsigned m_type:6; unsigned rest:26; }; };
 char pad08[0x48]; State008AE7C0 *m_f50;
};
struct Node008AE7C0 {
 int m_f0; Data008AE7C0 *m_f4; float m_f8,m_fC,m_f10,m_f14;
 int m_f18,m_f1C,m_f20; float m_f24; int m_f28,m_f2C,m_f30;
 char *m_f34,*m_f38; int m_f3C;
};
struct Rva008AE770Stack
{
	int field00;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
AptValue *aptCreateChannels008AE7C0(Owner008AE7C0 *self,int argc) {
 if(argc!=6) return g_bfmeFallbackDB;
 Rva8CD130Value *v=(Rva8CD130Value*)Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.field00-1];
 AptValue *v2=Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.field00-2];
 AptValue *v3=Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.field00-3];
 AptValue *v4=Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.field00-4];
 AptValue *v5=Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.field00-5];
 AptValue *v6=Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.field00-6];
 int key=v2->toInteger();
 float x=v3->toNumber(); float y=v4->toNumber();
 float width=v5->toNumber(); float height=v6->toNumber();
 Rva8CD130String text; v->getName(&text);
 Node008AE7C0 *node=(Node008AE7C0*)Rva008C5D70Alloc(0x40);
 node->m_f0=2; node->m_f8=0; node->m_fC=0;
 node->m_f10=width; node->m_f14=height;
 node->m_f1C=0; node->m_f20=0; node->m_f24=12.0f;
 node->m_f28=0; node->m_f2C=0; node->m_f30=0;
 node->m_f34=(char*)Rva008C5D70Alloc(1); node->m_f38=(char*)Rva008C5D70Alloc(1);
 *node->m_f34=0; *node->m_f38=0; node->m_f18=-1;
 { Link008AE7C0 *link=self->m_f50->m_fC;
 node->m_f4=link->m_f4; }
 State008AE7C0 *loopState=self->m_f50;
 Array008AE7C0 *array=loopState->m_fC->m_f4->array();
 for(int i=0;i<array->m_fC;++i) { if(array->m_f10[i]->m_f0==3) { node->m_f18=i; break; } }
 int index=key+0x4000;
 ((BfmeSubmitter1283*)&self->state()->m_f24)->bfmeSubmit1283(0,index,(int)node,(int)&text,(int)self,1,-1,0,0,0,0,0);
 Owner008AE7C0 *result=0; void *previous=0;
 State008AE7C0 *state=self->m_f50;
 state->m_f24->bfmeQuery1279((void*)index,(int)&text,&previous,(void**)&result);
 if(result->m_type==0xf && !((unsigned char)~(result->m_flags>>15)&1)) {
  State008AE7C0 *s=result->m_f50;
  s->m_f74=(s->m_f74&~6)|1;
  s->m_f34=0xff000000; s->m_f30=-1;
  s->m_f5C=node->m_f14; s->m_f50=node->m_f8; s->m_f58=node->m_f10; s->m_f54=node->m_fC;
  s->m_f44=0; s->m_f48=0; s->m_f24=0; s->m_f60=12.0f;
  s->m_f3C=node->m_f1C; s->m_f64=node->m_f18; s->m_f6C=6;
  ((BfmeSlotState1289*)result)->bfmeSetAxis1289(0,x,0);
  ((BfmeSlotState1289*)result)->bfmeSetAxis1289(1,y,0);
  if(g_bfmeDispatchEnabled1281 && flag0133781D) {
   ((BfmePtrTable64_008A4B20*)((char *)g_bfmeHolderBU+0x924))->add((BfmeRef008A4B20*)result);
   ((Rva008ACFC0PointerRegistry*)((char *)g_bfmeHolderBU+0xa28))->add((Rva008ACFC0RegisteredObject*)result);
  }
 }
 return g_bfmeFallbackDB;
}
