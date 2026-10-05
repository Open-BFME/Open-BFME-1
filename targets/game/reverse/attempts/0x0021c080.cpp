// ?method@Rva0021C080@@QAEXPAVXfer@@@Z
// partial score=0.9751 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common /Igame/GameEngine/Include/Precompiled

// The 603-byte body uses a name derived from its RVA, Rva0021C080::method.
// The matched constructor at 0x0021BEE0 installs vtable 0x010AB3C0. Slot 3
// reaches this body through thunk 0x0042230E. No source name is proven.

// The body calls the matched base transfer at 0x00248BE0 through incremental
// link thunk (ILT) 0x00007658. It calls Xfer slots 4, 10, 29, 35, 2, and 30.
// It sends ObjectID values through helper 0x0010C3C0, reached through ILT
// 0x0000C9B4.

// The fields at +0x9BC, +0x9C0, +0x9C4, +0x9D0, +0x9D4, and +0x9D8 hold two
// lists, a 12-byte STLport map, a pair list, a count, and a boolean. Each
// object stores its ObjectID at +0x74. The node sizes and the call through
// ILT 0x000267F6 to 0x000952A0 support the pair list. That call constructs a
// pair of ObjectIDs.

// ThrowInfo 0x011DFE5C names XferException. Its copy ILT 0x0004A26E and
// destructor ILT 0x00040804 match the existing pins. The throw keeps both
// callbacks and the constructor bytes.

// The frame size is 0x1C bytes. The source differs in 15 bytes outside
// relocation operands. The version and count share +0x18 in both bodies.
// Branch-local IDs put the load-side ID in the retail slot. The store-side
// ID still uses +0x0C where retail uses +0x10. The loop counter still uses
// +0x10 where retail uses +0x14. The saved owner uses +0x14 where retail
// uses +0x1C. No exact link check has passed.
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
 if(xfer->IsStoring()) {
  ObjectID id;
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
  ObjectID id;
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
