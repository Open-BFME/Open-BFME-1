// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008AF0B0: byte-verified callback; local layouts retain address-derived identities.
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
class AptValue { public: int toInteger() const; };
class Rva8CD130Value { public: void getName(Rva8CD130String *); };
class BfmeSubmitter1283 { public: void bfmeSubmit1283(int,int,int,int,int,int,int,float*,int,int,int,int); };
class BfmeQuery1279 { public: void bfmeQuery1279(void*,int,void**,void**); };
struct Node008AF0B0 { int m_f0,m_f4,m_f8,m_fC,m_f10; char pad14[0x2c]; };
struct Array008AF0B0 {
 char pad00[0x10]; int *m_f10;
};
struct Data008AF0B0 { char pad00[8]; Array008AF0B0 m_f8;
 Array008AF0B0 *array() { return &m_f8; }
};
struct Link008AF0B0 { int m_f0; Data008AF0B0 *m_f4; };
struct State008AF0B0 { char pad00[0xc]; Link008AF0B0 *m_fC; char pad10[0x14]; BfmeQuery1279 *m_f24; int m_f28,m_f2C; };
struct Owner008AF0B0 {
 State008AF0B0 *state() { return m_f50; } int m_f0; unsigned m_flags; char pad08[0x48]; State008AF0B0 *m_f50; };
extern AptValue **g_bfmeArr1233;
extern int g_stack01338748;
extern AptValue *g_bfmeFallbackDB;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
AptValue *aptCreateNode008AF0B0(Owner008AF0B0 *self,int argc) {
 if(argc!=2) return g_bfmeFallbackDB;
 Rva8CD130Value *v=(Rva8CD130Value*)g_bfmeArr1233[g_stack01338748-1];
 int key=g_bfmeArr1233[g_stack01338748-2]->toInteger();
 Node008AF0B0 *node=(Node008AF0B0*)Rva008C5D70Alloc(0x40);
 node->m_f0=5;
 node->m_f8=0; node->m_fC=0; node->m_f10=0;
 Link008AF0B0 *link=self->m_f50->m_fC;
 Array008AF0B0 *array=link->m_f4->array();
 node->m_f4=array->m_f10[0];
 Rva8CD130String text;
 v->getName(&text);
 int index=key+0x4000;
 ((BfmeSubmitter1283*)&self->state()->m_f24)->bfmeSubmit1283(0,index,(int)node,(int)&text,(int)self,1,-1,0,0,0,0,0);
 Owner008AF0B0 *result=0; void *previous=0;
 State008AF0B0 *state=self->m_f50;
 state->m_f24->bfmeQuery1279((void*)index,(int)&text,&previous,(void**)&result);
 unsigned bits=result->m_flags;
 int type=bits&0x3f;
 if(type>=0xc && type<=0x13 && !((unsigned char)~(bits>>15)&1)) { State008AF0B0 *s=result->m_f50; s->m_f2C=1; }
 return g_bfmeFallbackDB;
}
