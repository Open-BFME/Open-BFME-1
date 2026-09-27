// ?d_008bebf0@@YAXXZ
// partial score=0.993 date=2026-09-27
// Caller-backed identity: BfmeSubmitColors1283 and the 0x008BEE50 wrapper.
// Field offsets and flags below are witnessed by retail 0x008BEBF0.
#include <string.h>
struct BfmeIterator1285 { void *m_data; unsigned m_extra; };
class BfmeIteratorList1285 { public: BfmeIterator1285 *bfmeFirst1285(); BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *); };
class Rva008CF3C0String;
class Rva008A9B00;
class Rva008CF3C0State { public: void append(void *,void *,Rva008CF3C0String *,Rva008A9B00 *,int,int,int); };
struct Rva008AE770Stack {};
extern Rva008AE770Stack Rva008AE770TheStack;
struct Words008BEBF0Six { unsigned words[6]; };
struct Words008BEBF0Eight { unsigned words[8]; };
class BfmeNodeDX { public:
 void *vptr; union {unsigned flags; struct {unsigned kindBits:6; unsigned spareBits:9; unsigned validBit:1; unsigned highBits:16;};}; unsigned field08[2]; Words008BEBF0Six field10; Words008BEBF0Eight field28; unsigned field48; unsigned field4c; char *field50;
 void finish008B06C0();
};
class Value008BEBF0 { public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual BfmeIteratorList1285 *list();
 union {unsigned flags; struct {unsigned lowBits:15; unsigned validBit:1; unsigned highBits:16;};};
};
class BfmeSubmitter1283 { public:
 void bfmeSubmit1283(int,int,int,int,int,int,int,float *,int,int,int,int);
 __forceinline void submitImpl(BfmeNodeDX *,int,void *,int,int,int,int,float *,int,int,int,int);
 void create008BE760(int,void *,int,int,int,int,BfmeNodeDX **,int *);
 void bfmeRouteNode1282(BfmeNodeDX *,int);
};
#pragma comment(linker, "/alternatename:?create008BE760@BfmeSubmitter1283@@QAEXHPAXHHHHPAPAVBfmeNodeDX@@PAH@Z=?d_008be760@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish008B06C0@BfmeNodeDX@@QAEXXZ=?d_008b06c0@@YAXXZ")
__forceinline void BfmeSubmitter1283::submitImpl(BfmeNodeDX *a1,int a2,void *a3,int a4,int a5,int a6,int a7,float *colors,int a9,int a10,int a11,int a12)
{
 int created=0;
 void *input=a3;
 BfmeNodeDX *node=(BfmeNodeDX *)a1;
 if(input) { if(!node) { create008BE760(a2,input,a4,a5,a6,a7,&a1,&created); node=(BfmeNodeDX *)a1; } }
 if(!node) return;
 if(!node->field48) {
  if(colors) node->field28=*(Words008BEBF0Eight *)colors;
  if(a9) node->field10=*(Words008BEBF0Six *)a9;
 }
 if(a10) *(int *)(node->field50+0x20)=a10;
 if(node->kindBits==17 && !((unsigned char)~(node->flags>>15)&1)) *(int *)(node->field50+0x18)=a11;
 if(created) bfmeRouteNode1282(node,1);
 if(((node->flags&63)==13 && !((unsigned char)~(node->flags>>15)&1)) || ((node->flags&63)==18 && !((unsigned char)~(node->flags>>15)&1))) {
  Value008BEBF0 *value=(Value008BEBF0 *)a12;
  if(value && value->validBit) {
   a1=(BfmeNodeDX *)value->list();
   for(BfmeIterator1285 *it=((BfmeIteratorList1285 *)a1)->bfmeFirst1285();it;it=((BfmeIteratorList1285 *)a1)->bfmeNext1285(it)) {
    if(strcmp((char *)it->m_data+8,"__proto__") && strcmp((char *)it->m_data+8,"prototype"))
     ((Rva008CF3C0State *)&Rva008AE770TheStack)->append(node,0,(Rva008CF3C0String *)it,(Rva008A9B00 *)(it->m_extra&~1),1,1,0);
   }
  }
  node->finish008B06C0();
 }
}

void BfmeSubmitter1283::bfmeSubmit1283(int a1,int a2,int a3,int a4,int a5,int a6,int a7,float *a8,int a9,int a10,int a11,int a12) {
 submitImpl((BfmeNodeDX *)a1,a2,(void *)a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
}
