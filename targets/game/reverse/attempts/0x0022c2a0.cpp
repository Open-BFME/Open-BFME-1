// ?transfer@Rva0022C2A0@@QAEXPAVBfmeSeedTarget@@@Z
// partial score=0.9874776386 date=2026-09-28
// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
struct BfmeSeedPair { unsigned char first,second; BfmeSeedPair(unsigned char n):first(n),second(n) {} };
class BfmeSeedTarget { public:
virtual void slot0();
virtual void slot1();
virtual bool saving();
virtual void slot3();
virtual bool checksum();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void version(BfmeSeedPair*);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void uintValue(unsigned*);
virtual void intValue(int*);
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void boolValue(bool*);
};
class Gen_0022CD40 { public: void bfmeSeed(BfmeSeedTarget*); };
class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver*,void*);
static void transferID(BfmeSeedTarget* target,void* id) { Rva0010C3C0((MidVirtualSlot90Receiver*)target,id); }
class Object { public: char pad[0x74]; unsigned m_id; };
class GameLogic { public: void destroyObject(Object*); };
extern GameLogic* TheBfmeGameLogic;
class Rva0022C2A0 { public:
 void transfer(BfmeSeedTarget*);
 char pad000[0xe4]; std::list<Object*> field0e4; unsigned field0e8; bool field0ec; char pad0ed[3]; std::map<int,int> field0f0; std::list<int> field0fc;
};
void Rva0022C2A0::transfer(BfmeSeedTarget* target) {
 ((Gen_0022CD40*)this)->bfmeSeed(target);
 if(target->checksum()) return;
 BfmeSeedPair version(1); target->version(&version);
 { int id;
 if(target->saving()) {
  target->uintValue(&field0e8);
  for(std::list<Object*>::iterator it=field0e4.begin();it!=field0e4.end();++it) {
   id=(*it)->m_id; transferID(target,&id);
  }
 } else {
  if(!field0e4.empty()) {
   field0e8=0;
   for(std::list<Object*>::iterator it=field0e4.begin();it!=field0e4.end();) {
    Object* object=*it; it=field0e4.erase(it); TheBfmeGameLogic->destroyObject(object);
   }
   field0e4.clear();
  }
  target->uintValue(&field0e8);
  for(unsigned i=0;i<field0e8;++i) {
   transferID(target,&id); field0fc.push_back(id);
  }
 }
 }
 target->boolValue(&field0ec);
 { int count;
 if(target->saving()) {
  count=field0f0.size(); target->intValue(&count);
  for(std::map<int,int>::iterator it=field0f0.begin();it!=field0f0.end();++it) {
   std::pair<int,int> value=*it;
   transferID(target,&value.first); target->intValue(&value.second);
  }
 } else {
  target->intValue(&count);
  for(int i=0;i<count;++i) {
   int id; int value; transferID(target,&id); target->intValue(&value); field0f0[id]=value;
  }
 }
}
}
