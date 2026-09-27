// cl: /DNDEBUG /MD /EHsc
// Retail 0x002A79B0, 696 bytes. ZH isWithinStartAbilityRange control-flow twin:
// target ID lookup, positional distance, squared start range and LOS filter.
// BFME additionally uses a named contact point, oriented geometry contact and
// a special-power-specific distance adjustment. It clears stale target IDs.
// Bool is byte-valued here; unsigned char preserves the retail normalizations.
// Module-data startAbilityRange/approachRequiresLOS offsets are witnessed;
// fields 0x24F and 0x250 remain address-labelled. The string view describes
// the observed allocation header without redeclaring AsciiString.
// BfmeObjEQT is the existing 12-byte LOS filter view from BfmeConv1946.cpp.
// Its vtable is 0x010956B0; unrelated DistLOD names on that table are not evidence
// for changing this game-logic identity. Keep the override receiver mutable:
// a separate getType temporary changes MSVC receiver allocation.
struct Coord3D { float x,y,z; };
struct ContactString002A79B0 { struct Data {int refs;unsigned short length,capacity;char text[1];}; Data* data;
 bool empty() const {return !data || !data->length;} const char* str() const {return data?data->text:"";}
};
class Object;
struct BfmePt951;
class BfmeGap951 { public: float bfmeGapB951(const BfmePt951*) const; };
class Gen_000ED3B0 { public: float bfmeGapSq(const Gen_000ED3B0*) const; };
class BfmeThingEQT;
class BfmeBaseEQT { public: BfmeBaseEQT():zero(0) {} int zero; };
class BfmeObjEQT:public BfmeBaseEQT { public:
 BfmeObjEQT(BfmeThingEQT* p):owner(p) {} virtual ~BfmeObjEQT() {}
 char bfmeRunEQT(void*); BfmeThingEQT* owner;
};
class BfmeVec3HN;
class BfmeCheckHN { public: bool bfmeTestHN(BfmeVec3HN*); };
enum KindOfType { DummyKind002A79B0 };
class Thing { public: bool isKindOf(KindOfType) const; };
class BfmeSubYR { public: char bfmeDoYR(void*,void*,void*,void*,int); };
class Object { public:
 bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;
 float bfmeBoundaryDistanceSquared2D(const Object*) const;
 char pad000[0x38]; Coord3D position; float angle; char pad048[0x64]; BfmeSubYR geometry;
};
class GameLogic { public: Object* findObjectByID(int); };
extern GameLogic* TheGameLogic;
enum SpecialPowerType { DummyPower002A79B0 };
class Overridable { public: virtual ~Overridable(); Overridable* friend_getFinalOverride(); Overridable* next; };
class SpecialPowerTemplate:public Overridable { public:
 SpecialPowerType getSpecialPowerType() const;
 char pad008[0xc]; int powerType;
 int getType() const { const SpecialPowerTemplate* self=this; Overridable* p=next;
  if(p) {if(p->next) p=p->next->friend_getFinalOverride();self=(const SpecialPowerTemplate*)p;}
  return self->powerType;
 }
};
class SpecialAbilityUpdateModuleData { public:
 char pad000[0x1d8]; SpecialPowerTemplate* m_specialPowerTemplate;
 char pad1dc[0x10]; float m_startAbilityRange;
 char pad1f0[0x59]; bool m_approachRequiresLOS;
 char pad24a[5]; bool field24f; ContactString002A79B0 field250;
};
class SpecialAbilityUpdate { public:
 unsigned char isWithinStartAbilityRange();
 void* vptr; SpecialAbilityUpdateModuleData* data; Object* object;
 char pad00c[0xa0]; int targetID; Coord3D targetPos;
 char pad0bc[0x26]; bool withinRange;
};
unsigned char SpecialAbilityUpdate::isWithinStartAbilityRange() {
 const SpecialAbilityUpdateModuleData* d=data;
 SpecialPowerTemplate* power=d->m_specialPowerTemplate;
 Object* self=object;
 if(withinRange) return true;
 float distance=0;
 Object* target=0;
 if(targetID) {
  target=TheGameLogic->findObjectByID(targetID);
  if(target) {
  bool contact=false;
  if(!d->field250.empty()) {
   Coord3D p={0,0,0};
   if(target->getWorldspaceBestContactPoint(&p,&self->position,d->field250.str(),0,42,true)) {
    distance=((BfmeGap951*)self)->bfmeGapB951((const BfmePt951*)&p);
    contact=true;
   }
  }
  if(!contact) {
   if(((Thing*)target)->isKindOf((KindOfType)131)) distance=target->bfmeBoundaryDistanceSquared2D(self);
   else distance=((Gen_000ED3B0*)target)->bfmeGapSq((Gen_000ED3B0*)self);
  }
  } else { targetID=0; return false; }
 } else if(targetPos.x || targetPos.y || targetPos.z) {
  distance=((BfmeGap951*)self)->bfmeGapB951((const BfmePt951*)&targetPos);
  Overridable* next=power->next;
  if(next) { if(next->next) next=next->next->friend_getFinalOverride(); power=(SpecialPowerTemplate*)next; }
  if(power->powerType==39) distance-=400.0f;
 } else { if(power->getSpecialPowerType()==110) return false; return true; }
 float range=d->m_startAbilityRange*d->m_startAbilityRange;
 if(distance<=range) {
  if(distance==0 && targetID && d->field24f) {
   float angle=target->angle;
   return self->geometry.bfmeDoYR(&self->position,0,&target->geometry,&target->position,*(int*)&angle)!=0;
  }
  if(d->m_approachRequiresLOS) {
   BfmeObjEQT filter((BfmeThingEQT*)self);
   if(target) { if(filter.bfmeRunEQT(target)) return true; }
   else { if(((BfmeCheckHN*)&filter)->bfmeTestHN((BfmeVec3HN*)&targetPos)) return true; }
   return false;
  }
  return true;
 }
 return false;
}
