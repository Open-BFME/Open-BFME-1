// ?d_000a1510@@YAXXZ
// partial score=1.0 date=2026-10-04
// Instruction-exact research bank for native StateMachine serialization.
// RVA 000A1510, complete 640-byte RET4 body; no production claim.
// Identity/ABI evidence: identity_evidence/000a1510-state-machine-xfer-bank.md.
// The existing address-qualified handle symbol is retained for its callers.
// Rva0010C3C0Transfer and rva000A1310 are deliberately UNPINNED prototype
// declarations: their selected providers currently expose incorrect contracts.
// Do not promote by adding aliases. Repair the real providers and caller ABI
// declarations coherently, then run add_match and the whole-source/caller gates.
// This layout view emits no StateMachine vtable and is not the shared native
// class integration. The real native class/map/lifetime migration remains open.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/GameLogic/Object
// stlport
#include "xfer.h"
#include "coord3d.h"
#include <map>
#include "GameLogicObjectLookup.h"
#include "object.h"

struct Rva000A1510Version : Xfer::Version {
 Rva000A1510Version(unsigned char earliest, unsigned char current) {data[0]=earliest;data[1]=current;}
};

class XferException {
public:
 XferException(int tag, const char *format, ...);
 XferException(const XferException &);
 ~XferException();
 char *text;
 int tag;
};
struct Rva000A1510State {
 void *vptr;
 unsigned id;
 unsigned getID() const { return id; }
};
// Prototype only: literal "ObjectID", width 4, virtual +90; native Xfer
// slot+90 implementation restores EAX=this. Source/provider repair is pending.
extern Xfer &Rva0010C3C0Transfer(Xfer *, ObjectID *);
extern GameLogic *TheGameLogic;
class FlagPairTarget;
class Gen000A1510 {
public:
 void *vptr;
 _STL::map<unsigned, Rva000A1510State *> m_stateMap;
 Object *m_owner;
 unsigned m_sleepTill;
 unsigned m_defaultStateID;
 Rva000A1510State *m_currentState;
 ObjectID m_goalObjectID;
 Coord3DBase m_goalPosition;
 ObjectID m_slot30;
 Coord3DBase m_slot34;
 bool m_locked, m_defaultStateInited, m_slot42;
 Rva000A1510State *rva000A1310(unsigned);
 void handle(FlagPairTarget *);
};
typedef char checkSize[sizeof(Gen000A1510)==0x44 ? 1 : -1];
void Gen000A1510::handle(FlagPairTarget *target) {
 Xfer *xfer = reinterpret_cast<Xfer *>(target);
 if(xfer->IsLightCRC()) return;
 ObjectID id;
 Rva000A1510Version version(1,2);
 *xfer == version == m_sleepTill == m_defaultStateID;
 unsigned curStateID = m_currentState ? m_currentState->getID() : 999999;
 *xfer == curStateID;
 if(version.data[1]>=2 && curStateID==999999) return;
 if(xfer->IsLoading()) m_currentState=rva000A1310(curStateID);
 bool snapshotAllStates = false;
 *xfer == snapshotAllStates;
 if(snapshotAllStates) {
  _STL::map<unsigned, Rva000A1510State *>::iterator i;
  int count=0;
  for(i=m_stateMap.begin();i!=m_stateMap.end();++i) ++count;
  int saveCount=count;
  *xfer == saveCount;
  if(saveCount!=count) throw XferException(5,0);
  for(i=m_stateMap.begin();i!=m_stateMap.end();++i) {
   Rva000A1510State *state=(*i).second;
   unsigned id=state->getID();
   *xfer == id;
   if(id!=state->getID()) throw XferException(5,0);
   *xfer == *reinterpret_cast<Snapshot *>(state);
  }
 } else {
  if(m_currentState==0) {
   m_currentState=rva000A1310(m_defaultStateID);
   if(m_currentState==0) throw XferException(5,0);
  }
  *xfer == *reinterpret_cast<Snapshot *>(m_currentState);
 }
 Rva0010C3C0Transfer(&(Rva0010C3C0Transfer(xfer,&m_goalObjectID) == m_goalPosition),&m_slot30) == m_slot34 == m_locked == m_defaultStateInited;
 *xfer == m_slot42;
 id=0;
 if(xfer->IsLoading()) {
  Rva0010C3C0Transfer(xfer,&id);
  if(TheGameLogic) m_owner=TheGameLogic->findObjectByID(id);
 } else {
  if(m_owner) id=m_owner->m_id;
  Rva0010C3C0Transfer(xfer,&id);
 }
}
