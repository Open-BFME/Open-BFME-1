// cl: /DNDEBUG /MD /EHsc
// BFME AIUpdateInterface::blockedBy, RVA 0x00274630, 1052 bytes.
// AIUpdate.cpp supplies the goal-cell / priority / relative-angle algorithm;
// retail additionally tests BFME kinds, locomotor speeds, special path nodes,
// and formation ordering. Every direct callee is decoded from this boundary.
//
// Keep the authentic coordinate copy constructor and the visible non-inlined
// Thing angle helper below. The helper is independently byte-exact (214 B at
// 0x00150510): its read-only use proves local coordinate addresses do not escape.
// An opaque declaration adds 16 frame bytes and changes local copy scheduling.
#include <math.h>
struct Coord3D{Coord3D(){} Coord3D(const Coord3D&c):x(c.x),y(c.y),z(c.z){}float x,y,z;};
struct Coord2D{float x,y;};
struct ICoord2D{int x,y;};
enum CrushSquishTestType{TEST_CRUSH_OR_SQUISH=2};
// Numeric BFME-only kinds retain their decoded ordinals pending the name table.
enum KindOfType{INFANTRY=8, BFME108=108,BFME115=115,BFME124=124};
extern void j_00021017();
extern void j_0002760b();
class Object; class AIUpdateInterface;
class BfmeSub1CC_EC3 {
public: // Called through existing ILT 0x000230AB; receiver is Object AI+0x1CC.
float query(void *); bool isMovingBackwards()const{return (flags>>7)&1;}
char prefix[0x40];unsigned flags;
};
class Thing{
public:
const Coord3D* getPosition() const{return &position;}
const Coord3D* getUnitDirectionVector2D() const;
bool isKindOf(KindOfType) const;
__declspec(noinline) float bfmeRelativeAngleTo(const Coord3D*) const;
char prefix[0x38];Coord3D position;
};
class Object:public Thing{
public:
bool crushPolicy(Object*,CrushSquishTestType)const;
__forceinline BfmeSub1CC_EC3* bfmeLocomotor()const{
 typedef BfmeSub1CC_EC3* (Object::*Call)()const;
 union {void(*address)();Call member;} route={j_00021017};
 return (this->*route.member)();
}
char pad44[0x9c-0x44];ICoord2D goalCell;
char pada4[0x204-0xa4];AIUpdateInterface* ai;
char pad208[0x31c-0x208];void *group;Coord2D formationPosition;
};
class Path{public:__forceinline bool bfmeHasSpecialNode(){
 typedef bool (Path::*Call)();
 union {void(*address)();Call member;} route={j_0002760b};
 return (this->*route.member)();
}};
class AIStateMachine{public:const Coord3D*getGoalPosition()const{return &goal;} char prefix[0x24];Coord3D goal;};
class AIUpdateInterface{
public:
bool blockedBy(Object*);
bool hasHigherPathPriority(AIUpdateInterface*)const;
virtual void slot000();
virtual void slot004();
virtual void slot008();
virtual void slot00C();
virtual void slot010();
virtual void slot014();
virtual void slot018();
virtual void slot01C();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02C();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03C();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04C();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05C();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06C();
virtual void slot070();
virtual void slot074();
virtual void slot078();
virtual void slot07C();
virtual void slot080();
virtual void slot084();
virtual void slot088();
virtual void slot08C();
virtual void slot090();
virtual void slot094();
virtual void slot098();
virtual void slot09C();
virtual void slot0A0();
virtual void slot0A4();
virtual void slot0A8();
virtual void slot0AC();
virtual void slot0B0();
virtual void slot0B4();
virtual void slot0B8();
virtual void slot0BC();
virtual void slot0C0();
virtual void slot0C4();
virtual void slot0C8();
virtual void slot0CC();
virtual void slot0D0();
virtual void slot0D4();
virtual void slot0D8();
virtual void slot0DC();
virtual void slot0E0();
virtual void slot0E4();
virtual void slot0E8();
virtual void slot0EC();
virtual void slot0F0();
virtual void slot0F4();
virtual void slot0F8();
virtual void slot0FC();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void slot10C();
virtual void slot110();
virtual void slot114();
virtual void slot118();
virtual void slot11C();
virtual void slot120();
virtual void slot124();
virtual void slot128();
virtual void slot12C();
virtual void slot130();
virtual void slot134();
virtual void slot138();
virtual void slot13C();
virtual void slot140();
virtual void slot144();
virtual void slot148();
virtual void slot14C();
virtual void slot150();
virtual void slot154();
virtual void slot158();
virtual void slot15C();
virtual void slot160();
virtual void slot164();
virtual void slot168();
virtual void slot16C();
virtual void slot170();
virtual void slot174();
virtual void slot178();
virtual void slot17C();
virtual void slot180();
virtual void slot184();
virtual void slot188();
virtual void slot18C();
virtual void slot190();
virtual void slot194();
virtual void slot198();
virtual void slot19C();
virtual void slot1A0();
virtual void slot1A4();
virtual void slot1A8();
virtual void slot1AC();
virtual void slot1B0();
virtual void slot1B4();
virtual void slot1B8();
virtual void slot1BC();
virtual void slot1C0();
virtual void slot1C4();
virtual void slot1C8();
virtual void slot1CC();
virtual void slot1D0();
virtual void slot1D4();
virtual void slot1D8();
virtual void slot1DC();
virtual void slot1E0();
virtual void slot1E4();
virtual void slot1E8();
virtual bool isDoingGroundMovement()const;
Object*getObject()const{return object;}
AIStateMachine*getStateMachine()const{return state;}
const ICoord2D*getPathfindGoalCell()const{return &object->goalCell;}
BfmeSub1CC_EC3*getCurLocomotor()const{return locomotor;}
bool isAiInDeadState()const{return dead;}
int getNumFramesBlocked()const{return framesBlocked;}
char pad04[4];Object*object;char pad0c[0x30-12];AIStateMachine*state;
char pad34[0x140-0x34];Path*path;char pad144[0x16c-0x144];int framesBlocked;
char pad170[0x1cc-0x170];BfmeSub1CC_EC3*locomotor;char pad1d0[8];int goalType;
char pad1dc[0x32b-0x1dc];bool dead;
};
bool AIUpdateInterface::blockedBy(Object*other)
{
 Coord3D goalPos=*getStateMachine()->getGoalPosition();
 Object*obj=getObject();Coord3D pos=*obj->getPosition();
 ICoord2D goalCell=*getPathfindGoalCell();
 if(goalCell.x>0&&goalCell.y>0){float dx=fabs(goalPos.x-pos.x),dy=fabs(goalPos.y-pos.y);if(dx<10.0f&&dy<10.0f)return false;}
 bool canCrush=obj->crushPolicy(other,TEST_CRUSH_OR_SQUISH);if(canCrush)return false;
 AIUpdateInterface*aiOther=other->ai;
 if(!aiOther->isDoingGroundMovement())return false;
 if(getCurLocomotor()&&getCurLocomotor()->isMovingBackwards())return false;
 bool otherMoving=aiOther->goalType!=0;
 Coord3D otherPos=*other->getPosition();
 float dx=pos.x-otherPos.x,dy=pos.y-otherPos.y;
 float curDSqr=dx*dx+dy*dy;
 if(obj->isKindOf(BFME115)&&other->isKindOf(BFME108))return false;
 if(other->isKindOf(BFME115)&&obj->isKindOf(BFME108))return false;
 if(other->isKindOf(BFME115)&&obj->isKindOf(BFME115))return false;
 if(obj->isKindOf(BFME124)&&other->isKindOf(INFANTRY))return false;
 if(obj->isKindOf(BFME115)&&other->isKindOf(BFME115))return false;
 if(obj->bfmeLocomotor()&&other->bfmeLocomotor()){
  float ourSpeed=obj->bfmeLocomotor()->query(obj);
  float otherSpeed=other->bfmeLocomotor()->query(other);
  if(ourSpeed-otherSpeed>ourSpeed*0.1f)return false;
 }
 if(path&&path->bfmeHasSpecialNode())return false;
 if(curDSqr<0.01f)return hasHigherPathPriority(aiOther);
 Coord3D ourDir=*obj->getUnitDirectionVector2D();
 Coord3D theirDir=*other->getUnitDirectionVector2D();
 float dotProduct=ourDir.x*theirDir.x+ourDir.y*theirDir.y;
 if(getNumFramesBlocked()>5){if(dotProduct<=0.0f)return false;}
 float collisionAngle=obj->bfmeRelativeAngleTo(&otherPos);
 float otherAngle=other->bfmeRelativeAngleTo(&pos);
 float angleLimit=0.7853981852531433f;
 if(collisionAngle>1.5707963705062866f||collisionAngle< -1.5707963705062866f)return false;
 if(obj->group==other->group&&obj->group){
  Coord2D ours=getObject()->formationPosition;
  Coord2D theirs=other->formationPosition;
  if(theirs.x<ours.x)return false;
  if(ours.x<theirs.x)return true;
 }
 if(!otherMoving)angleLimit*=0.75f;
 if(collisionAngle>angleLimit||collisionAngle< -angleLimit){
  if(dotProduct<=0.0f)return false;
  if(otherMoving&&(otherAngle>angleLimit||otherAngle< -angleLimit)){
   dx+=ourDir.x-theirDir.x;dy+=ourDir.y-theirDir.y;
   if(curDSqr>dx*dx+dy*dy){if(hasHigherPathPriority(aiOther))return false;}
   else return false;
  }else return false;
 }
 if(!aiOther->isAiInDeadState())return true;
 return false;
}

extern float ACos(float);
#define BFME_ZERO_RANGE (*(const float *)0x01075350)
#define BFME_DEFAULT_BU (*(const float *)0x01075334)
#define BFME_MINUS_ONE (*(const double *)0x01095f18)
#define BFME_ONE (*(const double *)0x0107c640)

// ?bfmeRelativeAngleTo@Thing@@QBEMPBUCoord3D@@@Z
float Thing::bfmeRelativeAngleTo(const Coord3D *point) const
{
	// This arithmetic temporary is trivial; no owning coordinate is copied.
	struct {float x,y,z;} delta;
	delta.x = point->x - position.x;
	delta.y = point->y - position.y;
	float distance = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance == BFME_ZERO_RANGE)
		return BFME_ZERO_RANGE;

	float scale = BFME_DEFAULT_BU / distance;
	delta.x *= scale;
	delta.y *= scale;
	const Coord3D *direction = getUnitDirectionVector2D();
	float cosine = delta.y * direction->y + delta.x * direction->x;
	if (cosine < BFME_MINUS_ONE)
		cosine = -1.0f;
	else if (cosine > BFME_ONE)
		cosine = 1.0f;

	float angle = ACos(cosine);
	if (direction->x * delta.y - direction->y * delta.x < BFME_ZERO_RANGE)
		angle = -angle;
	return angle;
}
