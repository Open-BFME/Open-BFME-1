// ?create@Rva8D0D80State@@QAEPAVRva8D0D80Result@@PAX00HH@Z
// partial score=0.1949 date=2026-10-03
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Experimental native factory draft. Address views and unpinned constructor adapters require ABI review.
#include <math.h>
#include <string.h>
struct H { unsigned short refs,length,capacity,unknown; };
extern H g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void*);
class BfmeStrVKI { public:
 H *data;
 BfmeStrVKI():data(&g_bfmeDefaultString1284){++data->refs;}
 BfmeStrVKI(const BfmeStrVKI&v):data(v.data){++data->refs;}
 ~BfmeStrVKI(){H*p=data;--p->refs;if(!p->refs)Rva01337A30ReleaseTable[1](p);}
};
class BfmeStrVKK { public:void bfmeTruncVKK(unsigned);};
class AptValue {public: int toInteger() const; float toNumber();};
class Rva8CD130Value {public:void getName(BfmeStrVKI*);};
class Rva8D0D80Result;
struct Rva8D0080Tag;
struct Rva8D0080View { 
 virtual void slot00(); virtual void slot04(); virtual void slot08();virtual void slot0C();virtual void slot10();
 virtual unsigned char slot14();virtual Rva8D0080Tag* slot18();virtual void slot1C();virtual void slot20(int);
 virtual void slot24();virtual void slot28();virtual void slot2C();virtual void slot30();virtual void slot34();virtual void slot38();virtual void slot3C();
 virtual void slot40(void*,int);virtual unsigned* slot44(int*);
 unsigned flags;unsigned field08,field0C,field10,field14,field18,field1C;
};
class Gen_008C5E80 {public:bool bfmeIsKind()const;};
class BfmeTaggedItem;
class Gen_00899320 {public:void bfmeSet(BfmeTaggedItem*);};
struct Rva8D0080Tag {char pad[12];unsigned field0C;};
class BfmeStackBB {public:void bfmePopN(int);};
class Rva00899770;
class Rva008AE770Stack {public:Rva00899770*createString(void*,int,BfmeStrVKI*,int,int,int);};
class Rva008CF740Value;
class Rva008CF740 {public:void run(Rva008CF740Value*,Rva008CF740Value*,int);};
class BfmeTab1024 {public:int bfmeFind1024(int);};
class BfmeN1242;class BfmeE1242;
class BfmeN1242 {public:void rva008B8E10(int,BfmeE1242*);};
extern AptValue *g_bfmeFallbackDB;
extern void *g_rva013387D8;
extern BfmeStrVKI g_rva013386F4;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
class BfmeItemDX;void bfmePush(BfmeItemDX*);
inline void *headerAlloc(unsigned n){unsigned*raw=(unsigned*)Rva008C5D70Alloc(n+8);void*p=raw+2;bfmePush((BfmeItemDX*)p);return p;}
void *Rva008A3130(unsigned);void *Rva008A90F0(unsigned);void *Rva008AB840(unsigned);
void *Rva008C45F0(unsigned);void *Rva008C46B0(unsigned);void *Rva008C4710(unsigned);void *Rva008C4770(unsigned);void *Rva008C47D0(unsigned);void *Rva008C4830(unsigned);
void Rva008C4620(char*,char*);void Rva008C4680(char*,char*);void Rva008C46E0(char*,char*);void Rva008C4740(char*,char*);void Rva008C47A0(char*,char*);void Rva008C4800(char*,char*);void Rva008C4860(char*,char*);
class Rva008A3160HeaderedDelete {public:static void operator delete(void*,unsigned);};
class Rva008A9120HeaderedDelete {public:static void operator delete(void*,unsigned);};
class Rva008AB870HeaderedDelete {public:static void operator delete(void*,unsigned);};
class Rva00897590HeaderedDelete {public:static void operator delete(void*,unsigned);};
#define NEW_FREE(alloc,free) static void*operator new(unsigned n){return alloc(n);} static __forceinline void operator delete(void*p,unsigned n){free((char*)p,(char*)n);}
#define NEW_CLASS(alloc,owner) static void*operator new(unsigned n){return alloc(n);} static __forceinline void operator delete(void*p,unsigned n){owner::operator delete(p,n);}
struct Rva008B5880Arg; class Rva008B5880 {public:char raw[44];NEW_FREE(headerAlloc,Rva008C4680) Rva008B5880(Rva008B5880Arg*);};
// Existing ledger models these three native constructors as pointer-return methods.
// Their address-derived ctor views below are experimental, unpinned, and must be reconciled before landing.
class Rva008B9C60 {public:char raw[44];NEW_CLASS(Rva008A90F0,Rva008A9120HeaderedDelete) Rva008B9C60();};
class Rva008CBA80 {public:char raw[32];NEW_FREE(Rva008C4710,Rva008C4740) Rva008CBA80();};
class Rva008CBB30 {public:char raw[36];NEW_FREE(Rva008C47D0,Rva008C4800) Rva008CBB30();};
class Rva8CB6D0Callback;class Rva8CB6D0Derived {public:char raw[36];NEW_CLASS(Rva008A3130,Rva008A3160HeaderedDelete) Rva8CB6D0Derived(Rva8CB6D0Callback*);};
class Rva8CB8C0Bounds {public:char raw[100];NEW_FREE(Rva008C45F0,Rva008C4620) Rva8CB8C0Bounds(int,int,int,int,int,int,int);};
// Existing 13-int ABI view retained via explicit float bit storage; arg1/arg9 carry pointers.
class Rva8CB820Derived {public:char raw[64];NEW_CLASS(Rva008AB840,Rva008AB870HeaderedDelete) Rva8CB820Derived(int,int,int,int,int,int,int,int,int,int,int,int,int);};
class Rva008B4630Callback;class Rva008B4630 {public:char raw[36];NEW_FREE(Rva008C46B0,Rva008C46E0) Rva008B4630(Rva008B4630Callback*);};
struct Rva008B38F0Input;class Rva008B38D0 {public:char raw[40];NEW_FREE(Rva008C4770,Rva008C47A0) Rva008B38D0(const Rva008B38F0Input*);};
class Rva8CBB80Derived {public:char raw[40];NEW_FREE(Rva008C4830,Rva008C4860) Rva8CBB80Derived();Rva8CBB80Derived(BfmeStrVKI);};
class Rva00899F00Base {public:char raw[32];NEW_CLASS(Rva008A3130,Rva008A3160HeaderedDelete) Rva00899F00Base(unsigned,short);};
class BfmeHeld99CB0;class Rva89ACB0Holder {public:char raw[28];NEW_CLASS(headerAlloc,Rva00897590HeaderedDelete) Rva89ACB0Holder(BfmeHeld99CB0*);};
class Rva008A9B00 {public:
 static void*operator new(unsigned n){return Rva008C5D70Alloc(n);}static void operator delete(void*,unsigned);
 Rva008A9B00();void*vptr;unsigned flags;H*data;Rva008A9B00*next;
};
struct Pool {int capacity,count;Rva008A9B00**items;__forceinline void add(Rva008A9B00*v){int&n=count;if(n>=capacity){v->flags&=0xbfffffff;return;}items[n]=v;++n;}};
extern Pool*g_rva8CD130IdleHook;
extern Rva008A9B00*Rva008C3B60Head;
class Rva8D0D80State {public:
 Rva8D0D80Result*create(void*,void*,void*,int,int);
 int field00,field04;Rva8D0080View**field08;char gap0C[0x24];int field30,field34;Rva8D0080View**field38;
 __forceinline AptValue*at(int n){return (AptValue*)field08[field00-n];}
};
static __forceinline int floatBits(float f){union {float f;int i;}u;u.f=f;return u.i;}
Rva8D0D80Result*Rva8D0D80State::create(void*owner,void*scope,void*key0,int argc,int invoke){
 Rva8D0080View*result=0;
 BfmeStrVKI*key=(BfmeStrVKI*)key0;
 Rva8D0080View*function=(Rva8D0080View*)((Rva008AE770Stack*)this)->createString(owner,(int)scope,key,1,1,0);
 if (!((unsigned char)~(function->flags>>15)&1) && ((Gen_008C5E80*)function)->bfmeIsKind()) {
 if(_strcmpi((char*)key->data+8,"Sound")==0){result=(Rva8D0080View*)new Rva008B5880((Rva008B5880Arg*)owner);}
 else if(_strcmpi((char*)key->data+8,"Array")==0){
  Rva008B9C60*array=new Rva008B9C60;
  if(argc==1 && ((((Rva8D0080View*)at(1))->flags&0x3f)==7 && !((unsigned char)~(((Rva8D0080View*)at(1))->flags>>15)&1) && at(1)->toInteger()>=0 || (((Rva8D0080View*)at(1))->flags&0x3f)==6 && !((unsigned char)~(((Rva8D0080View*)at(1))->flags>>15)&1) && fmod(at(1)->toNumber(),1.0f)==0.0f))
   ((BfmeN1242*)array)->rva008B8E10(at(1)->toInteger()-1,(BfmeE1242*)g_bfmeFallbackDB);
  else for(int i=0;i<argc;++i)((BfmeN1242*)array)->rva008B8E10(i,(BfmeE1242*)at(i+1));
  result=(Rva8D0080View*)array;
 }
 else if(_strcmpi((char*)key->data+8,"String")==0){
  BfmeStrVKI text;
  Rva008A9B00*s=Rva008C3B60Head;
  if(s){Rva008C3B60Head=s->next;g_rva8CD130IdleHook->add(s);if(s->data!=&g_bfmeDefaultString1284)((BfmeStrVKK*)&s->data)->bfmeTruncVKK(0);}
  else s=new Rva008A9B00;
  if(argc==1)((Rva8CD130Value*)at(1))->getName(&text);
  ++text.data->refs;H*old=s->data;--old->refs;if(!old->refs)Rva01337A30ReleaseTable[1](old);s->data=text.data;
  function=(Rva8D0080View*)((BfmeTab1024*)((char*)g_rva013387D8+8))->bfmeFind1024((int)&g_rva013386F4);
  result=(Rva8D0080View*)new Rva8CB6D0Derived((Rva8CB6D0Callback*)s);
 }
 else if(_strcmpi((char*)key->data+8,"Date")==0){result=(Rva8D0080View*)new Rva8CB8C0Bounds(argc>0?at(1)->toInteger():-1,argc>1?at(2)->toInteger():-1,argc>2?at(3)->toInteger():-1,argc>3?at(4)->toInteger():-1,argc>4?at(5)->toInteger():-1,argc>5?at(6)->toInteger():-1,argc>6?at(7)->toInteger():-1);}
 else if(_strcmpi((char*)key->data+8,"TextFormat")==0){result=(Rva8D0080View*)new Rva8CB820Derived(argc>0?(int)at(1):(int)g_bfmeFallbackDB,floatBits(argc>1?at(2)->toNumber():-1.0f),argc>2?at(3)->toInteger():-1,argc>3?at(4)->toInteger():-1,argc>4?at(5)->toInteger():-1,argc>5?at(6)->toInteger():-1,argc>6?at(7)->toInteger():0,argc>7?at(8)->toInteger():0,argc>8?(int)at(9):(int)g_bfmeFallbackDB,argc>9?at(10)->toInteger():-1,argc>10?at(11)->toInteger():-1,argc>11?at(12)->toInteger():-1,argc>12?at(13)->toInteger():-1);}
 else if(_strcmpi((char*)key->data+8,"Color")==0)result=(Rva8D0080View*)new Rva008B4630((Rva008B4630Callback*)at(1));
 else if(_strcmpi((char*)key->data+8,"MovieClip")==0)result=(Rva8D0080View*)new Rva008CBA80;
 else if(_strcmpi((char*)key->data+8,"XML")==0){if(argc==1)result=(Rva8D0080View*)new Rva008B38D0((Rva008B38F0Input*)at(1));else result=(Rva8D0080View*)new Rva008B38D0(0);}
 else if(_strcmpi((char*)key->data+8,"LoadVars")==0)result=(Rva8D0080View*)new Rva008CBB30;
 else if(_strcmpi((char*)key->data+8,"Error")==0){if(argc==1){BfmeStrVKI text;((Rva8CD130Value*)at(1))->getName(&text);result=(Rva8D0080View*)new Rva8CBB80Derived(text);}else result=(Rva8D0080View*)new Rva8CBB80Derived;}
 else result=(Rva8D0080View*)new Rva00899F00Base(0x1b,8);
 result->slot00();
 Rva8D0080Tag*tag=function->slot18();Rva8D0080View*link=(Rva8D0080View*)(tag->field0C&~1u);
 if(!link){link=(Rva8D0080View*)new Rva89ACB0Holder((BfmeHeld99CB0*)function);((Gen_00899320*)tag)->bfmeSet((BfmeTaggedItem*)link);}
 result->slot20(1);result->field1C|=0x200;
 Rva8D0080View*previous=(Rva8D0080View*)(result->field10&~1u);
 if(link)link->slot00();if(previous)previous->slot04();
 if(!link)result->field10=0;else {if(link->slot14()==1)link=(Rva8D0080View*)((unsigned)link|1);result->field10=(unsigned)link;}
 unsigned flags=function->flags;
 if(((flags&0x3f)==0x1b && !((unsigned char)~(flags>>15)&1))||((flags&0x3f)==10 && !((unsigned char)~(flags>>15)&1))){
  int count;unsigned*source=function->slot44(&count);if(count>0){unsigned*copy=(unsigned*)Rva008C5D70Alloc(count*4);memcpy(copy,source,count*4);result->slot40(copy,count);}
 }
 if((unsigned char)invoke){field38[field30++]=result;result->slot00();((Rva008CF740*)this)->run((Rva008CF740Value*)result,(Rva008CF740Value*)function,argc);
  Rva8D0080View*top=field08[field00-1];if(!((unsigned char)(top->flags>>30)&1))top->slot04();--field00;field38[field30-1]->slot04();--field30;
 }
 result->field1C&=~0x200;
 } else ((BfmeStackBB*)this)->bfmePopN(argc);
 return (Rva8D0D80Result*)result;
}
