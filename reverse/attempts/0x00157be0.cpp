// ?sendSpecial@AIGroup@@QAEXPBUCoord3D@@HHHH@Z
// partial score=0.3718079673135853 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
// AIGroup::sendSpecial, 00157BE0: caller tryGroupSpecial -> ILT 0001A6B3.
// Stack args: command source, mode, low-byte snap flag, low-byte formation flag.
#define _STLP_NO_EXCEPTIONS 1
#include "Lib/BaseType.h"
#include <list>
#include <vector>
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };
enum PathfindLayerEnum { LAYER_GROUND = 1 };
enum IterOrderType { ITER_FASTEST, ITER_SORTED_NEAR_TO_FAR, ITER_SORTED_FAR_TO_NEAR };
enum KindOfType { KINDOF_VEHICLE = 9 };
enum { DISABLED_HELD = 3 };
const Real PATHFIND_CELL_SIZE_F = 10.0f;
const Int PATH_DIAMETER_IN_CELLS = 4;

class Object;
class LocomotorSet {};
class Team; class Waypoint; class PolygonTrigger; class CommandButton; class Path;
enum AICommandType
{
	AICMD_FOLLOW_WAYPOINT_PATH			= 0x06,
	AICMD_FOLLOW_WAYPOINT_PATH_AS_TEAM	= 0x07,
	AICMD_BFME_9						= 0x09,
	AICMD_FOLLOW_EXITPRODUCTION_PATH	= 0x0A,
	AICMD_BFME_36						= 0x24,
	AICMD_BFME_37						= 0x25,
	AICMD_FOLLOW_WAYPOINT_PATH_EXACT	= 0x32,
	AICMD_BFME_33						= 0x33
};



// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	char m_bfme_body[0x5C];					// sizeof(DamageInfo)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
	AICommandType						m_cmd;			// +0x00
	CommandSourceType				m_cmdSource;		// +0x04
	Coord3D									m_pos;			// +0x08
	Object									*m_obj;			// +0x14
	Object									*m_otherObj;		// +0x18
	const Team							*m_team;		// +0x1C
	_STL::vector<Coord3D>		m_coords;			// +0x20
	const Waypoint					*m_waypoint;		// +0x2C
	const PolygonTrigger		*m_polygon;			// +0x30
	Int											m_intValue;		// +0x34
	DamageInfo							m_damage;		// +0x38
	const CommandButton			*m_commandButton;	// +0x94
	Path										*m_path;		// +0x98

	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);	// ILT 0x00030EA4
};


class AICommandInterface {
public:
 virtual void aiDoCommand(const AICommandParms *);
 void aiBfmeCommand36FollowPath(const std::vector<Coord3D> *, Object *, Object *, CommandSourceType);
 void aiBfmeCommand37FollowPath(const std::vector<Coord3D> *, Object *, Object *, CommandSourceType);
 void aiAttackMoveToPosition(const Coord3D *,Int,CommandSourceType);
 void aiMoveToPosition(const Coord3D *,CommandSourceType);
};
template<int N> class RvaSlots: public RvaSlots<N-1> { public: virtual void rvaSlot(char (*)[N])=0; };
template<> class RvaSlots<0> {};
class ThingTemplate;
class Rva00158499 { public: char rva000[4]; ThingTemplate *rva004; const ThingTemplate *getRva004() const; };
class AIUpdateInterface: public RvaSlots<123> {
public:
 virtual Bool isDoingGroundMovement() const=0;
 char rva004[0x20-4];
 AICommandInterface commands;
 char rva024[0x1a8-0x24];
 LocomotorSet locomotor;
 char rva1a9[0x1b8-0x1a9];
 Int rva1b8;
 char rva1bc[0x1cc-0x1bc];
 Rva00158499 *rva1cc;
 char rva1d0[0x21c-0x1d0];
 Int m_tmpValue;
 void setTmpValue(Int x) { m_tmpValue=x; }
 Int getTmpValue() const { return m_tmpValue; }
 LocomotorSet *getLocomotorSet() { return &locomotor; }

};
class Overridable {
public:
 const Overridable *getFinalOverride() const { if(m_nextOverride) return m_nextOverride->getFinalOverride(); return this; }
 char rva000[4];
 Overridable *m_nextOverride;
};
class ThingTemplate: public Overridable {
public:
 char rva008[0x74-8]; Int rva074; char rva078[0xc8-0x78];
 Int getRva43c() const {return rva43c;}
 unsigned int m_kindof[3];
 char rva0d4[0x43c-0xd4]; Int rva43c;
};
const ThingTemplate *Rva00158499::getRva004() const { if(!rva004)return 0; return (const ThingTemplate*)rva004->getFinalOverride(); }
class Object {
public:
 Bool isMobile() const;
 Bool bfmeGetRecentDamageSource(unsigned int *,unsigned int) const;
 Int getLayer() const;
 Bool isAbleToAttack() const;
 char rva000[4];
 ThingTemplate *m_template;
 char rva008[0x38-8];
 Coord3D m_position;
 char rva044[0x1a4-0x44];
 unsigned char m_disabledMask;
 char rva1a8[0x204-0x1a5];
 AIUpdateInterface *m_ai;
 char rva208[0x320-0x208]; Coord2D m_formationOffset;
 void getFormationOffset(Coord2D *offset) const {*offset=m_formationOffset;}
 const Coord3D *getPosition() const { return &m_position; }
 Bool isDisabledByType(Int type) const { return (m_disabledMask & (1<<type))!=0; }
 const ThingTemplate *getTemplate() const {
  const ThingTemplate *t=m_template; if(t==0) return 0;
  return (const ThingTemplate *)t->getFinalOverride();
 }
 unsigned int isKindOf(KindOfType type) const { return (getTemplate()->m_kindof[0] & (1<<type)); }
 AIUpdateInterface *getAI() { return m_ai; }
 AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
};
class PathNode {
public:
 char rva000[8];
 PathNode *m_nextOptimized;
 Coord3D m_position;
 PathNode *getNextOptimized() { return m_nextOptimized; }
 const Coord3D *getPosition() const { return &m_position; }
};
class Path {
protected:
 virtual ~Path();
public:
 PathNode *m_first;
 PathNode *m_last;
 PathNode *getFirstNode() { return m_first; }
 PathNode *getLastNode() { return m_last; }
 void deleteInstance() { this->Path::~Path(); ::operator delete(this); }
};
class SimpleObjectIterator {
public:
 virtual ~SimpleObjectIterator();
 virtual Object *first();
 virtual Object *next();
 char rva004[12];
 SimpleObjectIterator();
 void insert(Object *,Real=0.0f);
 void makeEmpty();
 void sort(IterOrderType);
};
class Pathfinder {
public:
 int lineBlocked(Object *,int,PathfindLayerEnum,const Coord3D *,const Coord3D *);
 void snapLine(const Coord3D *,Coord3D *);
 Bool adjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
 void updateGoal(Object *,const Coord3D *,Int,const char *,Int);
};
class RvaAIData { public: char rva000[0xa4]; Real rva0a4; char rva0a8[4]; Real rva0ac; };
class AI {
public:
 char rva000[0xc]; Pathfinder *m_pathfinder; char rva010[4]; RvaAIData *rva014;
 Pathfinder *pathfinder() { return m_pathfinder; }
};
class TerrainLogic: public RvaSlots<8> {
public:
 virtual void getExtent(Region3D *) const=0;
 virtual void rvaSlot024();
 virtual void rvaSlot028();
 virtual void rvaSlot02C();
 virtual void rvaSlot030();
 virtual void rvaSlot034();
 virtual void rvaSlot038();
 virtual void rvaSlot03C();
 virtual void rvaSlot040();
 virtual void rvaSlot044();
 virtual void rvaSlot048();
 virtual void rvaSlot04C();
 virtual void rvaSlot050();
 virtual void rvaSlot054();
 virtual void rvaSlot058();
 virtual void rvaSlot05C();
 virtual void rvaSlot060();
 virtual void rvaSlot064();
 virtual void rvaSlot068();
 virtual void rvaSlot06C();
 virtual void rvaSlot070();
 virtual void rvaSlot074();
 virtual void rvaSlot078();
 virtual void rvaSlot07C();
 virtual void rvaSlot080();
 virtual void rvaSlot084();
 virtual void rvaSlot088();
 virtual void rvaSlot08C();
 virtual void rvaSlot090();
 virtual void rvaSlot094();
 virtual void rvaSlot098();
 virtual void rvaSlot09C();
 virtual void rvaSlot0A0();
 virtual void rvaSlot0A4();
 virtual void rvaSlot0A8();
 virtual void rvaSlot0AC();
 virtual void rvaSlot0B0();
 virtual void rvaSlot0B4();
 virtual void rvaSlot0B8();
 virtual Bool rvaSlot0BC(const Coord3D *) const=0;
};
extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;
class AIGroup {
public:
 Bool getCenter(Coord3D *);
 char rva000[4];
 std::list<Object *> m_memberList;
 char rva008[0x18-8];
 Path *m_groundPath;
void sendSpecial(const Coord3D *,Int,Int,Int,Int);
};

#include "Lib/trig.h"
extern void j_0003d104(void);
__forceinline void Rva00150100(const Coord3D *from,const Coord3D *to,Coord2D *offset) {
 typedef void (__cdecl *Call)(const Coord3D*,const Coord3D*,Coord2D*);
 ((Call)j_0003d104)(from,to,offset);
}
inline Object *rvaFloatBits(Real f) { union { Real f; Object *p; } x; x.f=f; return x.p; }
template<class T> inline const T &RvaMax(const T&a,const T&b){return a>b?a:b;}
inline void RvaScale(Coord2D *o,Real s){o->x*=s;o->y*=s;}
void AIGroup::sendSpecial(const Coord3D *pos,Int source,Int mode,Int snap,Int flag)
{
 Real dx,dy;
 Coord3D center;
 if(!getCenter(&center))return;
 PathNode *startNode=0,*endNode=0;
 Coord3D destination;destination.set(pos);
 Coord3D startPosition=center;
 Coord3D intermediate=center;
 Bool haveIntermediate=false;
 Real minDistance=TheAI->rva014->rva0a4*4.0f;
 Real endThreshold=TheAI->rva014->rva0a4*2.0f;
 if(m_memberList.empty())return;
 Real distance=0.0f;
 Bool recent=false;
 std::list<Object*>::iterator it;
 for(it=m_memberList.begin();it!=m_memberList.end();++it) {
  Object *obj=*it;
  Coord2D offset;obj->getFormationOffset(&offset);
  Real candidate=(Real)obj->getTemplate()->getRva43c()*TheAI->rva014->rva0a4-offset.x;
  distance=RvaMax(distance,candidate);
  unsigned int id;
  if(obj->bfmeGetRecentDamageSource(&id,4))recent=true;
 }
 distance+=TheAI->rva014->rva0a4*0.5f;
 distance=RvaMax(minDistance,distance);
 if(recent)distance*=2.0f;
 if(m_groundPath) {
  startPosition=*m_groundPath->getFirstNode()->getPosition();
  center=startPosition;
  PathNode *node;
  for(node=m_groundPath->getFirstNode();node;node=node->getNextOptimized()) {
   Coord3D delta=*node->getPosition();
   delta.sub(&center);delta.z=0;
   
   dx=delta.x*delta.x;dy=delta.y*delta.y;
   if(distance*distance<dx+dy) {
    haveIntermediate=true;
    startNode=node;
    delta.normalize();
    delta.scale(distance);
    intermediate=center;
    intermediate.add(&delta);
    break;
   }
   center.set(node->getPosition());
   distance-=sqrt(dx+dy);
  }
  const Coord3D *lastPos=m_groundPath->getLastNode()->getPosition();
  destination=*lastPos;
  Coord3D delta=*lastPos;
  delta.sub(&intermediate);
  endThreshold*=endThreshold;
  if(delta.lengthSqr()<endThreshold)haveIntermediate=false;
  for(node=m_groundPath->getFirstNode();node;node=node->getNextOptimized()) {
   Coord3D delta=*node->getPosition();
   delta.x-=destination.x;delta.y-=destination.y;
   if(sqr(delta.x)+sqr(delta.y)>endThreshold)endNode=node;
  }
  for(node=endNode;node;node=node->getNextOptimized())if(node==startNode)endNode=0;
  if(!startNode||!endNode) {
   m_groundPath->deleteInstance();m_groundPath=0;startNode=0;endNode=0;
  }
 }
 center=startPosition;
 if(endNode)center=*endNode->getPosition();
 Coord3D dir;
 dir.x=destination.x-center.x;dir.y=destination.y-center.y;dir.z=destination.z-center.z;
 dir.normalize();
 Real angle=ACos(dir.x);
 if(dir.y<0.0f)angle=-angle;
 for(it=m_memberList.begin();it!=m_memberList.end();++it) {
  Object *obj=*it;
  if(obj->isDisabledByType(DISABLED_HELD))continue;
  AIUpdateInterface *ai=obj->getAI();
  if(!ai)continue;
  Coord2D originalOffset;obj->getFormationOffset(&originalOffset);
  Int surfaces=ai->rva1b8;
  Bool usePath=true;
  if((unsigned char)TheAI->pathfinder()->lineBlocked(obj,surfaces,(PathfindLayerEnum)obj->getLayer(),obj->getPosition(),&startPosition)) {
   usePath=false;
   if(haveIntermediate) {
    Int surfaces=obj->getAI()->rva1b8;
    if(!(unsigned char)TheAI->pathfinder()->lineBlocked(obj,surfaces,(PathfindLayerEnum)obj->getLayer(),obj->getPosition(),&intermediate))usePath=true;
   }
  }
  std::vector<Coord3D> path;
  center=startPosition;
  if(haveIntermediate&&usePath) {
   Coord2D offset;offset.x=originalOffset.x;offset.y=originalOffset.y;
   Rva00150100(&center,&intermediate,&offset);
   Coord3D dest;
   dest.x=intermediate.x+offset.x;dest.y=intermediate.y+offset.y;dest.z=intermediate.z;
   center=intermediate;
   if((unsigned char)snap==1)TheAI->pathfinder()->snapLine(&intermediate,&dest);
   path.push_back(dest);
  }
  if(startNode&&usePath) {
   for(PathNode *node=startNode;node;node=node->getNextOptimized()) {
    Coord3D dest;dest.set(node->getPosition());
    Coord2D offset;offset.x=originalOffset.x;offset.y=originalOffset.y;
    Rva00150100(&center,&dest,&offset);
    if(TheTerrainLogic->rvaSlot0BC(&dest)) {
     RvaScale(&offset,TheAI->rva014->rva0ac);
    }
    dest.x+=offset.x;dest.y+=offset.y;
    if((unsigned char)snap==1)TheAI->pathfinder()->snapLine(node->getPosition(),&dest);
    path.push_back(dest);
    if(node==endNode)break;
    center=dest;
   }
  }
  Coord2D offset;offset.x=originalOffset.x;offset.y=originalOffset.y;
  Rva00150100(&center,&destination,&offset);
  if(TheTerrainLogic->rvaSlot0BC(&destination)) {
   RvaScale(&offset,TheAI->rva014->rva0ac);
  }
  if(ai->rva1cc && !ai->rva1cc->getRva004()->rva074 && !(unsigned char)flag) {
   offset.x*=0.0f;offset.y*=0.0f;
  }
  Coord3D dest;
  dest.x=destination.x+offset.x;dest.y=destination.y+offset.y;dest.z=destination.z;
  if((unsigned char)snap==1)TheAI->pathfinder()->snapLine(&destination,&dest);
  if(!TheAI->pathfinder()->adjustDestination(obj,*ai->getLocomotorSet(),&dest,0)) {
   Region3D extent;TheTerrainLogic->getExtent(&extent);
   if(!extent.isInRegionNoZ(&dest)) {
    dest=destination;
    TheAI->pathfinder()->adjustDestination(obj,*ai->getLocomotorSet(),&dest,0);
   }
  }
  TheAI->pathfinder()->updateGoal(obj,&dest,1,(const char*)0x01095f44,0x541);
  path.push_back(dest);
  if(mode==1 && obj->isAbleToAttack()) {
   if(!ai->isDoingGroundMovement())ai->commands.aiAttackMoveToPosition(&dest,0x7fffffff,(CommandSourceType)source);
   else ai->commands.aiBfmeCommand37FollowPath(&path,0,rvaFloatBits(angle),(CommandSourceType)source);
  } else {
   if(!ai->isDoingGroundMovement())ai->commands.aiMoveToPosition(&dest,(CommandSourceType)source);
   else ai->commands.aiBfmeCommand36FollowPath(&path,0,rvaFloatBits(angle),(CommandSourceType)source);
  }
 }
}
bool AIGroup::getCenter( Coord3D *center )
{
	int count = 0;
	center->x = 0.0f;
	center->y = 0.0f;
	center->z = 0.0f;

	std::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{													 
		if( (*i)->isDisabledByType( 3) ) 
		{
			continue; // don't bother counting riders in the center calculation.
		}
		if (!(*i)->isMobile()) continue;
 AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
		if (ai)
		{
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	if (count == 0 && !m_memberList.empty())
	{
		/*
			if there are no AIs (eg, the team consists of a faction bldg), we can get here.

			This was originally used to offset the centers of objects moving (still used for that) and non-ais can't move.  
			So if you have a mix of ai's & not ai's, you want just the ais.
			But it seems reasonable that if there are no ai's, it returns the center of the other stuff.  Cause they won't be moving anyway.
		*/
		for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
		{
			if( (*i)->isDisabledByType( 3) ) 
			{
				continue; // don't bother counting riders in the center calculation.
			}
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	center->x /= count;
	center->y /= count;
	center->z /= count;

	return count > 0;
}


void AICommandInterface::aiBfmeCommand36FollowPath( const _STL::vector<Coord3D> *path, Object *obj, Object *otherObj, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_BFME_36, cmdSource);
	parms.m_coords = *path;
	parms.m_obj = obj;
	*(Object **)&parms.m_pos.x = otherObj;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand37FollowPath( const _STL::vector<Coord3D> *path, Object *obj, Object *otherObj, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_BFME_37, cmdSource);
	parms.m_coords = *path;
	parms.m_obj = obj;
	*(Object **)&parms.m_pos.x = otherObj;
	aiDoCommand(&parms);
}



