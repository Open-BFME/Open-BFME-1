// ?d_008b9a40@@YAXXZ
// partial score=0.989 date=2026-09-27
// Retail 0x008B9A40: array range deletion and argument insertion.
class AptValue { public:
 virtual void retain(); virtual void release(); virtual void slot08(); virtual void slot0c(); virtual void slot10(); virtual unsigned char slot14();
 int toInteger() const;
 union {unsigned flags; struct {unsigned kindBits:6; unsigned otherBits:26;};};
 unsigned kind() const { return kindBits; }
 bool invalid() const {return ((unsigned char)~(flags>>15)&1)!=0;}
};
class BfmeN1242 { public:
 void bfmeReserve1242(int);
 __forceinline void set(int index,AptValue *item) {
    if(index>=0) {
     bfmeReserve1242(index+1);
     AptValue *old=(AptValue *)(field20[index]&~1);
     item->retain();
     if(old) old->release();
     if(item->slot14()==1) item=(AptValue *)((unsigned)item|1);
     field20[index]=(unsigned)item;
     field28=index+1>field28?index+1:field28;
    }
 }
 char field00[0x20]; unsigned *field20; int field24; int field28;
};
extern AptValue **g_bfmeArr1233;
extern AptValue *g_bfmeFallbackDB;
struct Rva008AE770Stack { int field00; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern "C" void *bfmeMove1242(void *,const void *,unsigned);
AptValue *splice008B9A40(AptValue *value,int argc)
{
 if(value->kind()==22 && !value->invalid()) {
  if(argc>0) {
  BfmeN1242 *array=(BfmeN1242 *)value;
  int start=g_bfmeArr1233[Rva008AE770TheStack.field00-1]->toInteger();
  if(start<0) start+=array->field28;
  int count=array->field28-start;
  if(argc>1) count=g_bfmeArr1233[Rva008AE770TheStack.field00-2]->toInteger();
  if(count>array->field28-start) count=array->field28-start;
  if(start>=array->field28) count=0;
  for(int i=0;i<count;++i) {
   AptValue *old=(AptValue *)(array->field20[start+i]&~1);
   if(old) old->release();
  }
  bfmeMove1242(array->field20+start,array->field20+start+count,(array->field28-count-start)*4);
  for(int j=0;j<count;++j) array->field20[j-count+array->field28]=0;
  array->field28-=count;
  if(argc>2) {
   int add=argc-2;
   array->bfmeReserve1242(array->field28+add);
   bfmeMove1242(array->field20+start+add,array->field20+start,(array->field28-start)*4);
   array->field28+=add;
   for(int k=0;k<add;++k) {
    array->field20[start+k]=0;
    AptValue *item=g_bfmeArr1233[Rva008AE770TheStack.field00-3-k];
    array->set(start+k,item);
   }
  }
  return value;
  }
  return g_bfmeFallbackDB;
 }
 return g_bfmeFallbackDB;
}
