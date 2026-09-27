// ?d_008be760@@YAXXZ
// partial score=0.92 date=2026-09-27
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <string.h>
extern void *(*Rva008C5D70Alloc)(unsigned);
extern "C" void (*TheBfmeFree)(void *,unsigned);
struct Alloc008BE760 {
 static void *operator new(unsigned n) {return Rva008C5D70Alloc(n);}
 static void operator delete(void *p,unsigned n) {TheBfmeFree(p,n);}
};
class Gen_008AC620 : public Alloc008BE760 {public: Gen_008AC620(); virtual ~Gen_008AC620(); unsigned fields[11];};
class Detail008BE760 : public Gen_008AC620 {public: __forceinline Detail008BE760() {} virtual ~Detail008BE760();};
class BfmeDerived1283 : public Alloc008BE760 {public: BfmeDerived1283(); unsigned fields[9];};
class Rva008BE450SizedDeleting : public Alloc008BE760 {public: Rva008BE450SizedDeleting() throw(); unsigned fields[30];};
class Rva008BD2D0 : public Alloc008BE760 {public: Rva008BD2D0() throw(); unsigned fields[6];};
class Rva008BD2F0 : public Alloc008BE760 {public: Rva008BD2F0() throw(); unsigned fields[6];};
class Rva008BD310 : public Alloc008BE760 {public: Rva008BD310() throw(); unsigned fields[7];};
struct BfmeHdrVKI {unsigned short m_bfme00,m_bfme02,m_bfme04,m_bfme06;};
struct BfmeStringPool3AF0 {void *field00; void (__cdecl *free)(void *);};
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern BfmeHdrVKI g_bfmeDefaultString1284;
class BfmeStrVKI {public:
 BfmeHdrVKI *m_bfme00;
 void bfmeSetVKI(const char *);
 __forceinline BfmeStrVKI(const char *text) {bfmeSetVKI(text);}
 __forceinline ~BfmeStrVKI() {BfmeHdrVKI *p=m_bfme00; if(--p->m_bfme00==0) g_bfmeStringPool1284->free(p);}
 __forceinline BfmeStrVKI &operator=(const BfmeStrVKI &other) {
  ++other.m_bfme00->m_bfme00;
  BfmeHdrVKI *p=m_bfme00;
  if(--p->m_bfme00==0) g_bfmeStringPool1284->free(p);
  m_bfme00=other.m_bfme00;
  return *this;
 }
};
class Rva8CD130Value;
class Rva008AD530StringBinding {public: void resolve(Rva8CD130Value *);};
class BfmeNestedBE;
class BfmeNodeEA;
class BfmeQuery1279 {public:
 void bfmeQuery1279(void *,int,void **,void **);
 BfmeNestedBE *bfmeCreate1284(void *,int,int);
 BfmeNestedBE *bfmeInsert1279(int,BfmeNestedBE *);
};
class BfmeWrapper1279 {public: void bfmeProcess1279(void *);};
void bfmeUnlink(BfmeNodeEA *);
class BfmeTab1024 {public: void bfmeAdd1024(int,int);};
class BfmeNode1285 {public: void bfmeSetState1285(int);};
class Node008BE760 {public:
 virtual void retain(); virtual void release();
 unsigned flags; int field08; BfmeStrVKI field0c; unsigned field10[15]; Node008BE760 *field4c; unsigned *field50; unsigned field54,field58; int field5c;
 __forceinline bool container() const {return ((flags&63)==13 && !((unsigned char)~(flags>>15)&1)) || ((flags&63)==18 && !((unsigned char)~(flags>>15)&1));}
};
extern char *Rva008A5380Holder;
class Rva008BE760 {public:
 BfmeQuery1279 *field00;
 void create(int key,int *descriptor,BfmeStrVKI *name,Node008BE760 *parent,int replace,int arg6,Node008BE760 **output,int *created);
};
void Rva008BE760::create(int key,int *descriptor,BfmeStrVKI *name,Node008BE760 *parent,int replace,int arg6,Node008BE760 **output,int *created)
{
 Node008BE760 *node=0;
 bool isNew;
 { Node008BE760 *found;
 void *previous; field00->bfmeQuery1279((void *)key,(int)name,&previous,(void **)&found);
 if(found) {
  if(replace) ((BfmeWrapper1279 *)this)->bfmeProcess1279(found);
  else {
   if(!((unsigned char)~(found->flags>>15)&1)) {node=found; isNew=false; goto done;}
   if(name) {
    BfmeHdrVKI *a=name->m_bfme00;
    BfmeHdrVKI *b=found->field0c.m_bfme00;
    unsigned n=a->m_bfme02;
    if(n==b->m_bfme02 && (a==b || !memcmp((char *)a+8,(char *)b+8,n))) {
     found->flags|=0x8000;
     node=found;
    }
   }
  }
 }
 }
 {
 unsigned *detail=0;
 int kind=13;
 isNew=true;
 if(*descriptor==5) {
  detail=(unsigned *)new Detail008BE760;
  detail[6]=-1;
  detail[7]|=0x3000000;
  kind=13;
 } else if(*descriptor==4) {
  detail=(unsigned *)new BfmeDerived1283;
  detail[7]=0;
  kind=14;
 } else if(*descriptor==2) {
  detail=(unsigned *)new Rva008BE450SizedDeleting;
  detail[3]=(unsigned)descriptor;
  detail[9]=descriptor[8]; detail[24]=descriptor[9]; detail[15]=descriptor[7]; detail[25]=descriptor[6]; detail[23]=descriptor[5]; detail[20]=descriptor[2]; detail[22]=descriptor[4]; detail[21]=descriptor[3];
  kind=15;
 } else if(*descriptor==10) {detail=(unsigned *)new Rva008BD2D0;kind=16;}
 else if(*descriptor==1) {detail=(unsigned *)new Rva008BD2F0;kind=12;}
 else if(*descriptor==8) {detail=(unsigned *)new Rva008BD310;kind=17;}
 if(parent->container()) detail[2]=parent->field50[6]; else detail[2]=-1;
 if(!node) node=(Node008BE760 *)field00->bfmeCreate1284((void *)key,kind,(int)detail);
 else {
  if(key!=node->field08) {
   bfmeUnlink((BfmeNodeEA *)node);
   field00->bfmeInsert1279(key,(BfmeNestedBE *)node);
   node->release();
  }
  node->field50=detail;
 }
 if(parent->container()) node->field5c=detail[2]; else node->field5c=-1;
 if(kind==13 || kind==14) {
  ((Node008BE760 **) *(unsigned *)(Rva008A5380Holder+12))[*(int *)(Rva008A5380Holder+16)]=node;
  ++*(int *)(Rva008A5380Holder+16);
  node->retain();
 } else if(kind==15) {
  unsigned *d=node->field50;
  *(BfmeStrVKI *)(d+6)=BfmeStrVKI(*(const char **)(d[3]+0x34));
  *(BfmeStrVKI *)(d+7)=BfmeStrVKI(*(const char **)(d[3]+0x38));
  ((Rva008AD530StringBinding *)d)->resolve((Rva8CD130Value *)parent);
  d[27]=6;
 }
 if(name) {
  node->field0c=*name;
  if(name->m_bfme00!=&g_bfmeDefaultString1284) ((BfmeTab1024 *)parent->field50[4])->bfmeAdd1024((int)name,(int)node);
 }
 }
done:
 parent->retain();
 if(node->field4c) node->field4c->release();
 node->field4c=parent;
 node->field50[3]=(unsigned)descriptor;
 node->field50[1]=arg6;
 if(*descriptor==4) ((BfmeNode1285 *)node)->bfmeSetState1285(1);
 *output=node;
 *created=isNew;
}
