// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008B9F30: type-22 array native that copies the range [start,end) into a new array.
// Registered as a callback by the array property dispatcher at 0x008BA0B0.
class AptValue { public:
 virtual void retain(); virtual void release(); virtual void slot08(); virtual void slot0c(); virtual void slot10(); virtual unsigned char slot14();
 int toInteger() const;
 union {unsigned flags; struct {unsigned kindBits:6; unsigned otherBits:26;};};
 unsigned kind() const { return kindBits; }
 bool invalid() const {return ((unsigned char)~(flags>>15)&1)!=0;}
};
class BfmeE1242;
class BfmeN1242 { public:
 void bfmeReserve1242(int);
 void bfmePut1242(int i, BfmeE1242 *e);
 __forceinline void set(int index,AptValue *item) {
    if(index>=0) {
     bfmeReserve1242(index+1);
     bfmePut1242(index,(BfmeE1242 *)item);
     field28=index+1>field28?index+1:field28;
    }
 }
 char field00[0x20]; unsigned *field20; int field24; int field28;
};
void *Rva008A90F0(unsigned bytes);
// The constructor at 0x008B9C60 is pinned under this ABI view; new calls the landed 0x008A90F0.
// The unwind funclet deletes through 0x008A9120, landed as Rva008A9120HeaderedDelete's operator.
class ArrayValue008B9C60 : public AptValue { public:
 ArrayValue008B9C60();
 char m_unmodelled08[0x24];
 static void *operator new(unsigned n) { return Rva008A90F0(n); }
 static void operator delete(void *p, unsigned n);
};
#pragma comment(linker, "/alternatename:??3ArrayValue008B9C60@@SAXPAXI@Z=??3Rva008A9120HeaderedDelete@@SAXPAXI@Z")
extern AptValue **g_bfmeArr1233;
extern AptValue *g_bfmeFallbackDB;
struct Rva008AE770Stack { int field00; };
extern Rva008AE770Stack Rva008AE770TheStack;
AptValue *slice008B9F30(AptValue *value,int argc)
{
 if(value->kind()==22 && !value->invalid()) {
  BfmeN1242 *array=(BfmeN1242 *)value;
  int start=0;
  int end=array->field28;
  if(argc>0) {
   start=g_bfmeArr1233[Rva008AE770TheStack.field00-1]->toInteger();
   if(start<0) start+=array->field28;
  }
  if(argc>1) {
   end=g_bfmeArr1233[Rva008AE770TheStack.field00-2]->toInteger();
   if(end<0) end+=array->field28;
   else if(end>array->field28) end=array->field28;
  }
  if(start>end || start<0 || end<0) return g_bfmeFallbackDB;
  BfmeN1242 *out=(BfmeN1242 *)new ArrayValue008B9C60;
  for(int i=start;i<end;++i)
   out->set(out->field28,(AptValue *)(array->field20[i]&~1));
  return (AptValue *)out;
 }
 return g_bfmeFallbackDB;
}
