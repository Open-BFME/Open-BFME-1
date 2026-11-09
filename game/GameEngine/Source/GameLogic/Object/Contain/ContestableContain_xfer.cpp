// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common /Igame/GameEngine/Include/Precompiled
// RVA 0x0021C080 xfer, 603 bytes (ret 4 at
// +0x258 then INT3). Identity: the matched constructor 0x0021BEE0
// (??0ContestableContain) installs vftable 0x010AB3C0 and slot 3 reaches
// this body through thunk 0x0042230E; that slot is BFME Snapshot xfer slot 3
// (GarrisonContain vftable 0x010AB818 slot 3 ILT 0x0000EAA7; Squad vftable
// 0x01083E78 slot 3). The body seeds the base transfer through ILT
// 0x00007658 (0x00248BE0 ?bfmeSeed@Gen_00248BE0), skips the light CRC,
// then round-trips a two-byte version record, an ObjectID list, an ObjectID
// map and a pair list. ObjectIDs cross through helper ILT 0x0000C9B4
// (0x0010C3C0). ThrowInfo 0x011DFE5C is XferException.
// Witnessed slots: hoisted ObjectID -24, hoisted loop counter -20,
// branch-scoped counts sharing the version record -16, owner spill -12,
// 8-byte pair item -8. The hoisted counter is what puts retail s -20/-16
// split into place.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
#include "xfer.h"
enum ObjectID { INVALID_ID = 0 };
struct XferVersion : public Xfer::Version {
	XferVersion(unsigned char version, unsigned char currentVersion) { data[0]=version; data[1]=currentVersion; }
};
class BfmeSeedTarget;
class Gen_00248BE0 { public: void bfmeSeed(BfmeSeedTarget*); };
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver*,void*);
class XferException {
public:
	XferException(int,const char*,...);
	XferException(const XferException&);
	~XferException();
	char *text; int tag;
};
struct Rva0021C080Object { unsigned char pad[0x74]; ObjectID m_id; };
struct Rva0021C080Entry { Rva0021C080Object *field0; unsigned char count; unsigned char pad[3]; };
typedef std::pair<ObjectID,ObjectID> Rva0021C080Pair;
namespace _STL { template<> void _Construct(Rva0021C080Pair*,const Rva0021C080Pair&); }
class BfmeContestableXferView {
public:
	unsigned char pad[0x9bc];
	std::list<Rva0021C080Object*> field9bc;
	std::list<ObjectID> field9c0;
	std::map<Rva0021C080Object*,Rva0021C080Entry> field9c4;
	std::list<Rva0021C080Pair> field9d0;
	unsigned int field9d4;
	bool field9d8;
};
class Rva0021C080Contestable {
protected:
	virtual void xfer(Xfer *xfer);
};
void Rva0021C080Contestable::xfer(Xfer *xfer) {
	((Gen_00248BE0*)this)->bfmeSeed((BfmeSeedTarget*)xfer);
	if(xfer->IsLightCRC()) return;
	BfmeContestableXferView *self = (BfmeContestableXferView*)this;
	{
		XferVersion version(1,1);
		*xfer==version;
	}
	*xfer==self->field9d4; *xfer==self->field9d8;
	ObjectID id;
	int i;
	if(xfer->IsStoring()) {
		int count=self->field9bc.size(); *xfer==count;
		for(std::list<Rva0021C080Object*>::iterator j=self->field9bc.begin();j!=self->field9bc.end();++j) {
			id=(*j)->m_id; Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id);
		}
		count=self->field9c4.size(); *xfer==count;
		for(std::map<Rva0021C080Object*,Rva0021C080Entry>::iterator j=self->field9c4.begin();j!=self->field9c4.end();++j) {
			id=j->first->m_id; Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id);
			if(j->second.field0==0) id=INVALID_ID;
			else id=j->second.field0->m_id;
			Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id);
		}
	} else {
		if(!self->field9bc.empty()) throw XferException(5,0);
		int count;
		*xfer==count;
		for(i=0;i<count;++i) {
			Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&id); self->field9c0.push_back(id);
		}
		*xfer==count;
		for(i=0;i<count;++i) {
			Rva0021C080Pair item;
			Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&item.first);
			Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&item.second);
			self->field9d0.push_back(item);
		}
	}
}
