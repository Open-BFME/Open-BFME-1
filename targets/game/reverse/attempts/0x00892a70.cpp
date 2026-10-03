// ?rva00892A70@@YAHI@Z
// partial score=0.5891 date=2026-10-03
// cl: /DNDEBUG /MD /O2
// RVA 00892A70: native private EAX input, plain RET at 00892B71.
// Complete nonmatching candidate: 260B versus258B, normalized shape1.000.
// The native MOV EDI,EAX prologue is recovered by updating the elapsed
// parameter itself; a separate remaining local gave a stack parameter.
// Retail direct callers 0089457D (EAX=1) and008946F2 (EAX=frame delta)
// independently prove this private input ABI. Neither call pushes an argument.
// Residue starts at counter update +8A: compiler uses EDX, retail EAX.
// This costs two bytes (absolute EAX load/store short forms), shifts later
// relocations, and is NOT an exact bank. Receiver copies, argument rotation,
// counter temporaries, member accessors, and volatile/nonvolatile alternatives
// did not remove the scratch-register residue. No assembly is used.
// Tick008A15F0 and tracker00896710 bindings remain provisional/unpinned.
// All other calls reuse the existing matched callees. No production rows change.
struct Rva00892A70Rate { char gap[0x24]; unsigned step; };
struct Rva00892A70Data { char gap[0xC]; Rva00892A70Rate *rate; char gap10[0x20]; unsigned remainder; };
struct Rva00892A70Value {
 void *vptr; unsigned flags; char gap[0x48]; Rva00892A70Data *data;
 bool valid()const { unsigned f=flags; return (f&0x3f)==0x12 && !((unsigned char)(~(f>>15))&1); }
};
struct Rva00892A70Head { char gap[0x58]; Rva00892A70Value *value; };
struct BfmePickWorld1284 { char gap[0x122C]; Rva00892A70Head **head; };
extern BfmePickWorld1284 *g_bfmeHolderBU;
class BfmeFilterWalk1236 { public: void bfmeFilterWalk1236(); };
class Rva008A1940Queue { public: void flush(); };
class BfmeSlotDispatcher1281 { public: void bfmeFlushSlots1289(); };
class BfmeTracker4310 { public: void Rva00896710(); };
extern BfmeTracker4310 *g_bfmeTracker4310;
// Pending opaque binding, callees.py: thiscall ret4, receiver is holder.
class Rva008A15F0Owner { public: void method(unsigned); };
extern int g_rva00891FA0Value;
extern int g_rva00891FA0Ready;
static int rva00892A70(unsigned elapsed) {
 BfmePickWorld1284 *owner=g_bfmeHolderBU;
 Rva00892A70Value *value=(*owner->head)->value;
 int result=0;
 if(!value->valid())return 0;
 elapsed+=value->data->remainder;
 unsigned step=value->data->rate->step;
 if(elapsed>=step) {
  result=1;
  do {
   ((Rva008A15F0Owner *)owner)->method(step);
   ((BfmeFilterWalk1236 *)&g_bfmeHolderBU->head)->bfmeFilterWalk1236();
   ((Rva008A1940Queue *)g_bfmeHolderBU)->flush();
   ((BfmeSlotDispatcher1281 *)g_bfmeHolderBU)->bfmeFlushSlots1289();
   g_bfmeTracker4310->Rva00896710();
   int total=g_rva00891FA0Value;
   owner=g_bfmeHolderBU;
   g_rva00891FA0Value=total+step;
   value=(*owner->head)->value;
   elapsed-=step;
   if(!value->valid())return 1;
  }while(!g_rva00891FA0Ready && elapsed>=step);
 }
 value=(*owner->head)->value;
 if(value->valid())value->data->remainder=elapsed;
 return result;
}
// Absent-from-retail emission wrapper allows MSVC's private static ABI.
int Rva00892A70Emission(unsigned elapsed) { return rva00892A70(elapsed); }
