// ?scan@Rva0023FED0MemberScanBase@@QAEXPAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@00@Z
// partial score=0.9525316456 date=2026-09-28
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport
//
// Opaque member-list scan: walks an _STL::list<Object *> embedded at this-0xAC
// (a secondary-base this-pointer; no witnessed offset ties this to Object or Team,
// so identity stays address-derived) and buckets each member's Object::m_id
// (witnessed Object+0x74, confidence 1.00) into one of three caller-supplied
// _STL::vector<ObjectID> outputs, based on the still-unresolved comparison
// helper at retail 0x003FD7D0 (called only for byte-shape/ABI; its own body
// remains a dump) and Path::bfmeHasMissingWaypoint (matched,
// PathHasMissingWaypoint.cpp) plus TheTerrainLogic::getWaypointByID (vtable
// slot 0x80, same TerrainLogic shape as PathHasMissingWaypoint.cpp).
//
// Derived from python3 tools/dis_retail.py 0x0023FED0 316.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <list>

enum ObjectID { INVALID_OBJECT_ID = 0 };

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WaypointID;
static const WaypointID INVALID_WAYPOINT_ID = 0x7fffffff;

class TerrainLogic
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot01();
	virtual void bfmeSlot02();
	virtual void bfmeSlot03();
	virtual void bfmeSlot04();
	virtual void bfmeSlot05();
	virtual void bfmeSlot06();
	virtual void bfmeSlot07();
	virtual void bfmeSlot08();
	virtual void bfmeSlot09();
	virtual void bfmeSlot10();
	virtual void bfmeSlot11();
	virtual void bfmeSlot12();
	virtual void bfmeSlot13();
	virtual void bfmeSlot14();
	virtual void bfmeSlot15();
	virtual void bfmeSlot16();
	virtual void bfmeSlot17();
	virtual void bfmeSlot18();
	virtual void bfmeSlot19();
	virtual void bfmeSlot20();
	virtual void bfmeSlot21();
	virtual void bfmeSlot22();
	virtual void bfmeSlot23();
	virtual void bfmeSlot24();
	virtual void bfmeSlot25();
	virtual void bfmeSlot26();
	virtual void bfmeSlot27();
	virtual void bfmeSlot28();
	virtual void bfmeSlot29();
	virtual void bfmeSlot30();
	virtual void bfmeSlot31();
	virtual void *getWaypointByID(WaypointID waypointID);
};

extern TerrainLogic *TheTerrainLogic;

class Object;

// Output of the unresolved comparison helper at 0x003FD7D0. Only the fields this
// body reads are given real names; the two unread dwords keep the buffer's proven
// 36-byte size (frame slots esp+0x14..esp+0x37 in the retail disassembly).
struct Rva0023FED0CompareOut
{
	UnsignedInt m_unused0;
	float m_posA[3];
	float m_posB[3];
	UnsignedInt m_unused2;
	WaypointID m_waypointId;
};

class Path
{
public:
	Bool bfmeHasMissingWaypoint(void) const;
	// retail 0x003FD7D0, still an unresolved dump; called here only for its
	// proven __thiscall(Path*, Object*, void*, CompareOut*, int) shape.
	void rva0023fed0Compare(Object *member, void *goalField, Rva0023FED0CompareOut *out, int zero) const;
};

#define BFME_HAVE_OBJECTID 1
#define OBJECT_TU_MEMBERS ObjectID getID() const { return m_id; }
#include "object.h"

// STLport's list<T> header node: {next, prev, data}; the list object itself
// doubles as the sentinel, so list.end() is the list object's own address.
struct Rva0023FED0Node
{
	Rva0023FED0Node *m_next;
	Rva0023FED0Node *m_prev;
	Object *m_data;
};

class Rva0023FED0MemberScanBase
{
public:
	void scan(_STL::vector<ObjectID> *needRepath, _STL::vector<ObjectID> *lookupFailed, _STL::vector<ObjectID> *ok);

private:
	unsigned char m_pad[4];
};

static Rva0023FED0Node *sentinelOf(Rva0023FED0MemberScanBase *self)
{
	return *reinterpret_cast<Rva0023FED0Node **>(reinterpret_cast<char *>(self) - 0xAC);
}

extern void j_00008a9e();
extern void j_000169cd();
struct Route0023FED0 {};
static void compare0023FED0(Path *path, Object *obj, void *locomotor, Rva0023FED0CompareOut *out) {
 typedef void (Route0023FED0::*Fn)(Object*, void*, Rva0023FED0CompareOut*, bool);
 union { void (*raw)(); Fn call; } route={j_00008a9e};
 (((Route0023FED0*)path)->*route.call)(obj,locomotor,out,false);
}
// The existing generated callee owns this address-derived element type.
// Its pointer-triple layout and 4-byte append are proven by 0x00152780.
struct Gen_t_00152780_p4pod { int a[1]; };
namespace _STL { template<> void vector<Gen_t_00152780_p4pod>::push_back(const Gen_t_00152780_p4pod&); }
static void append0023FED0(_STL::vector<ObjectID> *vec,const ObjectID &id) {
 ((_STL::vector<Gen_t_00152780_p4pod>*)vec)->push_back((const Gen_t_00152780_p4pod&)id);
}
void Rva0023FED0MemberScanBase::scan(_STL::vector<ObjectID> *needRepath, _STL::vector<ObjectID> *lookupFailed, _STL::vector<ObjectID> *ok)
{
 for (_STL::list<Object*>::iterator it=((_STL::list<Object*>*)((char*)this-0xac))->begin();
      it!=((_STL::list<Object*>*)((char*)this-0xac))->end();++it) {
  Object *member=*it;
  if(!member) continue;
  char *upd=(char*)member->m_ai;
  if(!upd) continue;
  Path *path=*(Path**)(upd+0x140);
  Rva0023FED0CompareOut out;
  bool equal=true;
  if(path) {
   compare0023FED0(path,member,*(void**)(upd+0x1cc),&out);
   equal=(out.m_posA[0]==out.m_posB[0] && out.m_posA[1]==out.m_posB[1] && out.m_posA[2]==out.m_posB[2]);
  }
  if(equal) {
   ok->push_back(member->getID());
  } else {
   WaypointID id=out.m_waypointId;
   if(id!=INVALID_WAYPOINT_ID && !TheTerrainLogic->getWaypointByID(id)) {
    append0023FED0(lookupFailed,member->getID());
   } else if(path->bfmeHasMissingWaypoint()) {
    append0023FED0(needRepath,member->getID());
   } else {
    append0023FED0(ok,member->getID());
   }
  }
 }
}
