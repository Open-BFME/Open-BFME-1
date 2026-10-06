// cl: /Igame/GameEngine/Source/GameLogic/Object /GX
// Retail 0x00373220, 621 bytes: CastleBehavior::registerOwnedObject.
// Identity: the landed CastleBehaviorCreateOwnedObject.cpp calls this through
// ILT 0x0003ACD8; its existing registration pin targets this body. The literal
// CastleMemberBehavior independently anchors the member-module lookup.
// The local static key produces retail's one-state EH initialization frame.
// All four ID append branches share one temporary: separate branch locals
// put the +0xC4-vector argument in the dead module-data slot instead of the
// incoming argument slot (the only two byte differences in the initial draft).
// Address-derived ABI adapters below preserve existing unresolved identities:
// 169CD -> vector append 152780; 23678 -> 2BA240 (one unsigned argument);
// 1DA34 -> filter 3A04A0 (Object*, Player*, bool result);
// 3A279 -> logic thunk 383930 (Object*, int). No new pins are required.
// clearStatus uses the corrected 00162CD0 identity, not its old model-condition
// alias. CastleBehavior and Object+0x258 have no witnessed member names.
enum NameKeyType { NAMEKEY_INVALID=0 };
enum KindOfType { KINDOF_00373220_98=0x98, KINDOF_00373220_67=0x67, KINDOF_00373220_95=0x95 };
enum ObjectStatusTypes { OBJECT_STATUS_00373220_5=5 };
class Player;
class Module;
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
// Retail's Object::findModule (0x001BEE60) is a protected member, so the mangled
// call name carries that access; only the friend may call it here.
#define OBJECT_TU_MEMBERS void setStatusBit(int,bool); Player* getControllingPlayer() const; void clearStatus(ObjectStatusTypes); \
	protected: Module* findModule(NameKeyType) const; friend class CastleBehavior;
#include "object.h"
template<class T> inline T& field373220(void* p,int n) { return *(T*)((char*)p+n); }
class Overridable {
public:
 void* field00;
 Overridable* m_nextOverride;
 const Overridable* getFinalOverride() const;
};
class ThingTemplate : public Overridable {};
inline ThingTemplate* finalTemplate373220(Object* object) {
 ThingTemplate* t=object->m_template;
 if(!t) return 0;
 if(t->m_nextOverride) return (ThingTemplate*)t->m_nextOverride->getFinalOverride();
 return t;
}
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;
class GameLogic { public: void destroyObject(Object*); };
extern GameLogic* TheGameLogic;
extern void j_000169cd();
extern void j_00023678();
extern void j_0001da34();
extern void j_0003a279();
struct ObjectIDs00373220 {
 void append(const int& id) { union { void* p; void (ObjectIDs00373220::*f)(const int&); } u; u.p=(void*)j_000169cd; (this->*u.f)(id); }
};
struct Filter00373220 {
 bool accepts(Object* object,Player* player) { union { void* p; bool (Filter00373220::*f)(Object*,Player*); } u; u.p=(void*)j_0001da34; return (this->*u.f)(object,player); }
};
struct Logic00373220 {
 void notify(Object* object,int value) { union { void* p; void (Logic00373220::*f)(Object*,int); } u; u.p=(void*)j_0003a279; (this->*u.f)(object,value); }
};
class CastleBehavior {
public:
 void registerOwnedObject(Object* object);
 void prepareOwnedObjectForUnpack(Object* object);
 void notify(unsigned id) { union { void* p; void (CastleBehavior::*f)(unsigned); } u; u.p=(void*)j_00023678; (this->*u.f)(id); }
};
void CastleBehavior::registerOwnedObject(Object* object) {
 void* data=field373220<void*>(this,4);
 Object* owner=field373220<Object*>(this,8);
 if(!object) return;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
 Module* member=object->findModule(key);
 int id;
 if(member) field373220<int>(member,0x18)=owner->m_id;
 if(field373220<unsigned>(finalTemplate373220(object),0xdc)&0x10000) object->setStatusBit(0x4e,true);
 if(field373220<unsigned>(finalTemplate373220(object),0xc8)&0x10000000) {
  if(!field373220<int>(this,0xa0)) {
   field373220<int>(this,0xa0)=object->m_id;
   if(field373220<float>(object,0x258)==0.0f && field373220<float>(this,0xb4)!=0.0f) {
    field373220<float>(object,0x258)=field373220<float>(this,0xb4);
    field373220<float>(this,0xb4)=0.0f;
   }
   if(member) { field373220<bool>(member,0x24)=true; field373220<int>(member,0x14)=field373220<int>(this,0xa0); }
   notify(field373220<unsigned>(this,0xa0));
  } else TheGameLogic->destroyObject(object);
 } else if(object->isKindOf(KINDOF_00373220_98)) {
  id=object->m_id; ((ObjectIDs00373220*)((char*)this+0xdc))->append(id);
 } else if(object->isKindOf(KINDOF_00373220_67) || object->isKindOf(KINDOF_00373220_95)) {
  id=object->m_id; ((ObjectIDs00373220*)((char*)this+0xb8))->append(id);
  if(object->isKindOf(KINDOF_00373220_95)) object->clearStatus(OBJECT_STATUS_00373220_5);
 } else if(((Filter00373220*)((char*)data+0x40))->accepts(object,owner->getControllingPlayer()) && ((Filter00373220*)((char*)data+0x3c))->accepts(object,owner->getControllingPlayer())) {
  id=object->m_id; ((ObjectIDs00373220*)((char*)this+0xd0))->append(id);
  prepareOwnedObjectForUnpack(object);
 } else {
  id=object->m_id; ((ObjectIDs00373220*)((char*)this+0xc4))->append(id);
 }
 ((Logic00373220*)TheGameLogic)->notify(object,field373220<int>(this,0x104));
}
