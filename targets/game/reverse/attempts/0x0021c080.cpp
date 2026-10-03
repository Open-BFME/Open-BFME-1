// ?method@Rva0021C080@@QAEXPAVXfer@@@Z
// partial score=0.9718 date=2026-10-03
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common /Igame/GameEngine/Include/Precompiled
// Retail 0021C080..0021C2DA (603 bytes), final RET4 at0021C2D8 then CC.
// Opaque complete-object view; vtable010AB3C0 slot3 contains0042230E,
// whose ILT reaches this body. Matched ContestableContain ctor0021BEE0
// installs that table. No new semantic method name is claimed.
// Calls the existing base transfer00248BE0 through00007658, then canonical
// Xfer slots4/10/29/35/2/30. ObjectID hand-over uses0010C3C0 through0000C9B4.
// Raw fields: list at9BC, ID list at9C0, 12B STLport map at9C4, pair-ID list
// at9D0, unsigned9D4 and bool9D8. Objects expose canonical ObjectID at74.
// Node allocation sizes12/16 and pair-copy call000267F6->000952A0 establish
// the load containers; _Construct specialization is intentionally out of line.
// Exception ThrowInfo011DFE5C names XferException; copy ILT0004A26E and
// destructor ILT00040804 agree with existing canonical pins. Native throw
// must preserve those callbacks as well as the constructor instruction bytes.
// Current best: 603 bytes, 17 non-relocation differences, all stack offsets.
// Version/count at+18 and pair/exception at+20 match; ID at+C versus retail10,
// loop counter at10 versus14, saved owner14 versus1C remain. Shape1.000 is
// not byte equality. No strict link/data/exception-table acceptance claimed.
// Levers: native ObjectID pair _Construct visibility produces the missing call;
// explicit null branch fixes the store ordering; version/count union shrinks
// frame24 to1C. Pair alignment and grouping index/count/id made placement worse.
// Canonical Xfer/ObjectID headers are included; opaque owner carries its RVA.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
#include "game_type.h"
#include "xfer.h"
class BfmeSeedTarget;
class Gen_00248BE0 { public: void bfmeSeed(BfmeSeedTarget*); };
class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver*,void*);
class XferException {
public:
 XferException(int,const char*,...);
 XferException(const XferException&);
 ~XferException();
 char *text; int tag;
};
struct Rva0021C080Object { unsigned char pad[0x74]; ObjectID field74; };
struct Rva0021C080Entry { Rva0021C080Object *field0; unsigned char count; unsigned char pad[3]; };
typedef std::pair<ObjectID,ObjectID> Rva0021C080Pair;
namespace _STL { template<> void _Construct(Rva0021C080Pair*,const Rva0021C080Pair&); }
struct Rva0021C080 {
 unsigned char pad[0x9bc];
 std::list<Rva0021C080Object*> field9bc;
 std::list<ObjectID> field9c0;
 std::map<Rva0021C080Object*,Rva0021C080Entry> field9c4;
 std::list<Rva0021C080Pair> field9d0;
 unsigned int field9d4;
 bool field9d8;
 void method(Xfer*);
};
void Rva0021C080::method(Xfer *xfer) {
 ((Gen_00248BE0*)this)->bfmeSeed((BfmeSeedTarget*)xfer);
 if(xfer->IsLightCRC()) return;
 __declspec(align(8)) union { Xfer::Version version; int count; } transfer;
 transfer.version.data[0]=1; transfer.version.data[1]=1;
 *xfer==transfer.version;
 *xfer==field9d4; *xfer==field9d8;
 ObjectID id;
 if(xfer->IsStoring()) {
  transfer.count=field9bc.size(); *xfer==transfer.count;
  for(std::list<Rva0021C080Object*>::iterator i=field9bc.begin();i!=field9bc.end();++i) {
   id=(*i)->field74; Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id);
  }
  transfer.count=field9c4.size(); *xfer==transfer.count;
  for(std::map<Rva0021C080Object*,Rva0021C080Entry>::iterator i=field9c4.begin();i!=field9c4.end();++i) {
   id=i->first->field74; Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id);
   if(i->second.field0==0) id=INVALID_ID;
   else id=i->second.field0->field74;
   Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id);
  }
 } else {
  if(!field9bc.empty()) throw XferException(5,0);
  *xfer==transfer.count;
  for(int i=0;i<transfer.count;++i) {
   Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id); field9c0.push_back(id);
  }
  *xfer==transfer.count;
  for(int i=0;i<transfer.count;++i) {
   Rva0021C080Pair item;
   Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&item.first);
   Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&item.second);
   field9d0.push_back(item);
  }
 }
}
