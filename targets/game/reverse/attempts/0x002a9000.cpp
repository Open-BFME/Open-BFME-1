// ?approachTarget@SpecialAbilityUpdate@@UAEEXZ
// partial score=0.915966 date=2026-09-28
// cl: /DNDEBUG /MD
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
struct Coord3D { float x,y,z; Coord3D() {} Coord3D(float a,float b,float c):x(a),y(b),z(c) {}
 Coord3D(const Coord3D& p) {x=p.x;y=p.y;z=p.z;} ~Coord3D() {} void set(const Coord3D* p) {*this=*p;}
 void sub(const Coord3D* p) {x-=p->x;y-=p->y;z-=p->z;}
 float length() const {return (float)sqrt(x*x+y*y+z*z);}
};
struct ContactString002A9000 { struct Data {int refs;unsigned short length,capacity;char text[1];}; Data* data;
 bool empty() const {return !data || !data->length;} const char* str() const {return data?data->text:"";}
};
class Object;
enum KindOfType { DummyKind002A9000 };
enum CommandSourceType { DummyCommand002A9000 };
class Thing {public:bool isKindOf(KindOfType) const;};
class AICommandInterface {public:void aiFacePosition(const Coord3D*,CommandSourceType);void aiMoveToObject(Object*,CommandSourceType);};
class AIUpdateInterface {public:void ignoreObstacle(const Object*); AICommandInterface* command(){return (AICommandInterface*)((char*)this+0x20);}};
class Gen_001BEC20 {public:int bfmeScale() const;};
class Object {public:
 const Coord3D* getPosition() const {return &position;}
 bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;
 char pad000[0x38]; Coord3D position;
 char pad044[0x30]; int id; char pad078[0x18c]; AIUpdateInterface* ai;
 char pad208[0xc]; Object* field214; char pad218[0x188]; int field3a0;
};
class GameLogic {public:Object* findObjectByID(int);}; extern GameLogic* TheGameLogic;
class Overridable {public:virtual ~Overridable();Overridable* friend_getFinalOverride();Overridable* next;};
class SpecialPowerTemplate:public Overridable {public:
 char pad008[0xc]; int powerType;
 int getType() const {const SpecialPowerTemplate* self=this;Overridable* p=next;
 if(p) {if(p->next)p=p->next->friend_getFinalOverride();self=(const SpecialPowerTemplate*)p;}return self->powerType;}
};
class SpecialAbilityUpdateModuleData {public:
 char pad000[0x1d8];SpecialPowerTemplate* m_specialPowerTemplate;
 char pad1dc[0x10];float m_startAbilityRange;
 char pad1f0[0x60];ContactString002A9000 field250;
};
struct Rva002A5FB0 { unsigned char method(Coord3D*,float); };
class SpecialAbilityUpdate {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void onExit(bool,bool);

 virtual unsigned char approachTarget();
 SpecialAbilityUpdateModuleData* data;Object* object;
 SpecialAbilityUpdateModuleData* getSpecialAbilityUpdateModuleData() const { return data; }
 Object* getObject() const { return object; }
 char pad00c[0xa0];int targetID;Coord3D targetPos;Coord3D lastPosition;
 char pad0c8[0x15];bool field0dd;char pad0de[7];bool field0e5;
};
unsigned char SpecialAbilityUpdate::approachTarget() {
 Object* self=getObject();
 const SpecialAbilityUpdateModuleData* d=getSpecialAbilityUpdateModuleData();
 if(!field0dd) {
  Coord3D pos=targetPos;
  Object* target=TheGameLogic->findObjectByID(targetID);
  if(target) pos.set(target->getPosition());
  Coord3D delta=lastPosition;
  delta.sub(&pos);
  if(delta.length()<5.0f) {onExit(false,true);return false;}
 }
 lastPosition.set(&targetPos);
 field0dd=false;
 if(targetID) {
  Object* target=TheGameLogic->findObjectByID(targetID);
  if(target) {
   lastPosition.set(target->getPosition());
   SpecialPowerTemplate* power=d->m_specialPowerTemplate;
   bool ranged=d->m_startAbilityRange>50.0f;
   if(power->getType()==39) {
    Object* parent=target->field214;
    if(parent && ((Thing*)parent)->isKindOf((KindOfType)108)) self->field3a0=parent->id;
    else self->field3a0=targetID;
   }
   AIUpdateInterface* ai=self->ai;
   if(ai) {
    if(!d->field250.empty()) {
     Coord3D pos(0,0,0);
     if(target->getWorldspaceBestContactPoint(&pos,&self->position,d->field250.str(),0,42,true)) {
      ai->command()->aiFacePosition(&pos,(CommandSourceType)2);return true;
     }
    }
    ai->ignoreObstacle(target);
    if(!((Thing*)target)->isKindOf((KindOfType)7) && ((Gen_001BEC20*)target)->bfmeScale()!=1 && ranged) {
     Coord3D pos=*target->getPosition();
     ((Rva002A5FB0*)this)->method(&pos,d->m_startAbilityRange);
     ai->command()->aiFacePosition(&pos,(CommandSourceType)2);return true;
    }
    ai->command()->aiMoveToObject(target,(CommandSourceType)2);return true;
   }
  }
 } else if(targetPos.x || targetPos.y || targetPos.z) {
  AIUpdateInterface* ai=self->ai;
  if(ai) {
   ai->command()->aiFacePosition(&targetPos,(CommandSourceType)2);
   if(d->m_specialPowerTemplate->getType()==43) field0e5=true;
   return true;
  }
 }
 return false;
}
