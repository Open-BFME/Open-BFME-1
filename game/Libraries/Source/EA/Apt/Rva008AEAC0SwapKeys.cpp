// cl: /DNDEBUG /MD /EHsc
// Actual first body is 511 bytes; the old 649-byte dump crosses INT3 and a second entry.
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
class BfmeNestedBE;
class BfmeNodeEA;
void __cdecl bfmeUnlink(BfmeNodeEA *);
class BfmeQuery1279 { public: void bfmeQuery1279(void*,int,void**,void**); BfmeNestedBE *bfmeInsert1279(int,BfmeNestedBE*); };
struct State008AEAC0 { int m_f0,m_f4; char pad08[0x1c]; BfmeQuery1279 *m_f24; };
struct Value008AEAC0 {
 virtual void slot00(); virtual void slot04();
 union { unsigned m_flags; struct { unsigned m_type:6; unsigned rest:26; }; };
 int m_f8; char pad0C[0x40]; Value008AEAC0 *m_f4C; State008AEAC0 *m_f50;
 bool validRange() { int t=m_flags&0x3f; return t>=0xc && t<=0x13 && !((unsigned char)~(m_flags>>15)&1); }
};
struct Rva008AE770Stack
{
	int field00;
	int m_rva0133874C;
	Value008AEAC0** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;
AptValue *aptSwapKeys008AEAC0(Value008AEAC0 *self,int argc) {
 if(argc!=1 && self->validRange()) goto done;
 {
 Rva008AE770Stack& stk = Rva008AE770TheStack;
 Value008AEAC0** args = stk.m_rva01338750;
 Value008AEAC0 *v=args[stk.field00-1];
 Value008AEAC0 *other=0; void *previous=0;
 unsigned bits=v->m_flags; int type=bits&0x3f;
 if(type>=0xc && type<=0x13 && !((unsigned char)~(bits>>15)&1)) other=v;
 else if((type==1 || type==0x2a) && !((unsigned char)~(bits>>15)&1)) {
  Rva8CD130String name;
  ((Rva8CD130Value*)v)->getName(&name);
  State008AEAC0 *state=self->m_f4C->m_f50;
  state->m_f24->bfmeQuery1279(0,(int)&name,&previous,(void**)&other);
 } else if(type==7 && !((unsigned char)~(bits>>15)&1)) {
  State008AEAC0 *state=self->m_f4C->m_f50;
  state->m_f24->bfmeQuery1279((void*)((AptValue*)v)->toInteger(),0,&previous,(void**)&other);
 } else goto integer_case;
 if(other && (other->m_flags&0x8000)) {
  int key=other->m_f8; other->m_f8=self->m_f8; self->m_f8=key;
  bfmeUnlink((BfmeNodeEA*)other); bfmeUnlink((BfmeNodeEA*)self);
  self->m_f4C->m_f50->m_f24->bfmeInsert1279(self->m_f8,(BfmeNestedBE*)self);
  self->m_f4C->m_f50->m_f24->bfmeInsert1279(other->m_f8,(BfmeNestedBE*)other);
  self->slot04(); other->slot04();
 } else {
integer_case:
  if(v->m_type==7 && !((unsigned char)~(v->m_flags>>15)&1)) {
   bfmeUnlink((BfmeNodeEA*)self);
   State008AEAC0 *state=self->m_f4C->m_f50;
   state->m_f24->bfmeInsert1279(((AptValue*)v)->toInteger(),(BfmeNestedBE*)self);
   self->slot04();
  }
 }
 }
done:
 return g_bfmeFallbackDB;
}


AptValue *aptSetNextKey008AECC0(Value008AEAC0 *self,int argc) {
 if(argc!=1 && self->validRange()) goto done;
 {
 Rva008AE770Stack& stk = Rva008AE770TheStack;
 Value008AEAC0** args = stk.m_rva01338750;
 Value008AEAC0 *v=args[stk.field00-1];
 if(v->validRange()) {
  if(v->m_flags&0x8000) {
   int key=v->m_f8;
   v->m_f8=self->m_f8;
   self->m_f50->m_f4=key+1;
  }
 } else if((AptValue*)v==g_bfmeFallbackDB) self->m_f50->m_f4=-1;
 }
done:
 return g_bfmeFallbackDB;
}
