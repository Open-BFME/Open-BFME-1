// ?friend_moveVehicleToPos@AIGroup@@AAE_NPBUCoord3D@@W4CommandSourceType@@@Z
// partial score=0.5843949044585988 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
// AIGroup 0x00158A40: Zero Hour algorithm with BFME instruction witnesses.
#define _STLP_NO_EXCEPTIONS 1
#include "Lib/BaseType.h"
#include <list>
#include <vector>
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
enum PathfindLayerEnum { LAYER_GROUND = 1 };
enum IterOrderType { ITER_FASTEST, ITER_SORTED_NEAR_TO_FAR, ITER_SORTED_FAR_TO_NEAR };
enum KindOfType { KINDOF_VEHICLE = 9 };
enum { DISABLED_HELD = 3 };
const Real PATHFIND_CELL_SIZE_F = 10.0f;
const Int PATH_DIAMETER_IN_CELLS = 4;
inline Real sqr(Real x) { return x*x; }
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
 void aiBfmeCommand9FollowPath(const std::vector<Coord3D> *, Object *, CommandSourceType);
};
template<int N> class RvaSlots: public RvaSlots<N-1> { public: virtual void rvaSlot(char (*)[N])=0; };
template<> class RvaSlots<0> {};
class AIUpdateInterface: public RvaSlots<123> {
public:
 virtual Bool isDoingGroundMovement() const=0;
 char rva004[0x20-4];
 AICommandInterface commands;
 char rva024[0x1a8-0x24];
 LocomotorSet locomotor;
 char rva1a9[0x21c-0x1a9];
 Int m_tmpValue;
 void setTmpValue(Int x) { m_tmpValue=x; }
 Int getTmpValue() const { return m_tmpValue; }
 LocomotorSet *getLocomotorSet() { return &locomotor; }
 void aiFollowPath(const std::vector<Coord3D> *p,Object *o,CommandSourceType c) { commands.aiBfmeCommand9FollowPath(p,o,c); }
};
class Overridable {
public:
 const Overridable *getFinalOverride() const { if(m_nextOverride) return m_nextOverride->getFinalOverride(); return this; }
 char rva000[4];
 Overridable *m_nextOverride;
};
class ThingTemplate: public Overridable {
public:
 char rva008[0xc8-8];
 unsigned int m_kindof[3];
};
class Object {
public:
 Bool isMobile() const;
 char rva000[4];
 ThingTemplate *m_template;
 char rva008[0x38-8];
 Coord3D m_position;
 char rva044[0x1a4-0x44];
 unsigned char m_disabledMask;
 char rva1a8[0x204-0x1a5];
 AIUpdateInterface *m_ai;
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
 void removeGoal003E3D20(Object *);
 Bool adjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
 void updateGoal(Object *,const Coord3D *,Int,const char *,Int);
};
class AI {
public:
 char rva000[0xc]; Pathfinder *m_pathfinder;
 Pathfinder *pathfinder() { return m_pathfinder; }
};
class TerrainLogic: public RvaSlots<7> {
public:
 virtual Real getLayerHeight(Real,Real,PathfindLayerEnum,Coord3D *,Bool) const=0;
 PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);
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
private:
 Bool friend_moveVehicleToPos(const Coord3D *,CommandSourceType);
};

Bool AIGroup::friend_moveVehicleToPos( const Coord3D *pos, CommandSourceType cmdSource )

{

	if (m_groundPath==NULL) return false;

	Real dx, dy;
	Coord3D center;
	if (!getCenter( &center )) return false;

	if (!m_groundPath) {
		return false;
	}

	Int numColumns = 2;


	// Get the start & end vectors for the path.
	Coord3D startPoint; startPoint.set(m_groundPath->getFirstNode()->getPosition());
	Real farEnoughSqr = sqr(PATH_DIAMETER_IN_CELLS*PATHFIND_CELL_SIZE_F);
	PathNode *startNode = NULL;
	PathNode *node;
	for (node = m_groundPath->getFirstNode(); node; node=node->getNextOptimized()) {
		Real dx = node->getPosition()->x - startPoint.x;	
		Real dy = node->getPosition()->y - startPoint.y;
		if (dx*dx+dy*dy>farEnoughSqr) {
			startNode = node;
			break;
		}
	}
	Coord3D endPoint; endPoint.set(m_groundPath->getLastNode()->getPosition());
	PathNode *endNode = NULL;		
	for (node = m_groundPath->getFirstNode(); node; node=node->getNextOptimized()) {
		Real dx = node->getPosition()->x - endPoint.x;	
		Real dy = node->getPosition()->y - endPoint.y;
		if (dx*dx+dy*dy>farEnoughSqr) {
			endNode = node;
		}
	}
	if (endNode == m_groundPath->getFirstNode()) {
		endNode = NULL;
	}
	if (startNode==NULL || endNode==NULL) {
		m_groundPath->deleteInstance();
		m_groundPath = NULL;
		return false;
	}
	
	Coord2D startVector;
	startVector.x = startNode->getPosition()->x - startPoint.x;
	startVector.y = startNode->getPosition()->y - startPoint.y;
	startVector.normalize();

	Coord2D endVector;
	endVector.x = endPoint.x - endNode->getPosition()->x;
	endVector.y = endPoint.y - endNode->getPosition()->y;
	endVector.normalize();

	Coord2D startVectorNormal;
	startVectorNormal.x = -startVector.y;
	startVectorNormal.y = startVector.x;
	startVectorNormal.normalize();

	Coord2D endVectorNormal;
	endVectorNormal.x = -endVector.y;
	endVectorNormal.y = endVector.x;
	endVectorNormal.normalize();

	Int unitsToPath = 0;
	Bool useEndVector = false;
	// Move.
	SimpleObjectIterator *iter = new SimpleObjectIterator;
	SimpleObjectIterator *iter2 = new SimpleObjectIterator;
	std::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )	
	{
		if ((*i)->isDisabledByType( DISABLED_HELD ) ) 
		{
			continue; // don't bother telling the occupants to move.
		}
		if( !(*i)->isKindOf( KINDOF_VEHICLE ) )
		{	
			continue;
		}
		if( (*i)->getAI()==NULL )
		{	
			continue;
		}
		if( !(*i)->getAI()->isDoingGroundMovement() )
		{	
			continue;
		}	 
		Coord3D unitPos; unitPos.set((*i)->getPosition());
		TheAI->pathfinder()->removeGoal003E3D20(*i);
		Real dx, dy;
		dx = unitPos.x - center.x;
		dy = unitPos.y - center.y;
		// Sort by the dot product of normal.
		iter->insert((*i), dx*startVectorNormal.x+dy*startVectorNormal.y);
		unitsToPath++;

		// If units are closer to the end vector than the start vector, use the end vector.
		Real distToEndSqr;
		Real distToStartSqr;
		dx = unitPos.x - endPoint.x;
		dy = unitPos.y - endPoint.y;
		distToEndSqr = dx*dx + dy*dy;
		dx = unitPos.x - startPoint.x;
		dy = unitPos.y - startPoint.y;
		distToStartSqr = dx*dx + dy*dy;
		if (distToStartSqr>distToEndSqr) {
			useEndVector = true;
		}
	}


	Object *theUnit;
	if (useEndVector) {
		// resort unsing the end vector.
		startVector = endVector;
		startVectorNormal =	endVectorNormal;
		for (theUnit = iter->first(); theUnit; theUnit = iter->next()) iter2->insert(theUnit);
		iter->makeEmpty();
		for (theUnit = iter2->first(); theUnit; theUnit = iter2->next())
		{
			Coord3D unitPos; unitPos.set(theUnit->getPosition());
			dx = unitPos.x - center.x;
			dy = unitPos.y - center.y;
			// Sort by the dot product of normal.
			iter->insert(theUnit, dx*startVectorNormal.x+dy*startVectorNormal.y);
		}
		iter2->makeEmpty();
	}

	iter->sort(ITER_SORTED_FAR_TO_NEAR);
	Int curIndex = 0;
	for (theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
		Int divisor = ((unitsToPath+1)/numColumns);
		if (divisor<1) divisor=1;
		Int columnDelta = 1-(curIndex/divisor);  // 0, 1 from left to right across column. jba.
		if (columnDelta==0) columnDelta=-1;
		divisor = ((unitsToPath+1)/3);
		if (divisor<1) divisor=1;
		Int threeColumnDelta = (curIndex/divisor);  // 0, 1, 2 from left to right across column. jba.
		threeColumnDelta = 1-threeColumnDelta; // 1, 0, -1
		if (threeColumnDelta<-1) threeColumnDelta=-1;
		if (unitsToPath<5) {
			threeColumnDelta = columnDelta;
		}

		ai->setTmpValue( (threeColumnDelta<<16)|(columnDelta&0x00ffff));
		// Sort next pass by the dot product of start vector.
		Real dx, dy;
		dx = theUnit->getPosition()->x - center.x;
		dy = theUnit->getPosition()->y - center.y;
		Int adjust = 0;
		iter2->insert(theUnit, adjust + dx*startVector.x + dy*startVector.y);
		curIndex++;

	}

	iter2->sort(ITER_SORTED_FAR_TO_NEAR);
	// Even out columns by priority.
	Int column2[3] = {0,0,0};	
	Int column3[3] = {0,0,0};	
	{
		for (theUnit = iter2->first(); theUnit; theUnit = iter2->next())
		{
			AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
			Int tmp = ai->getTmpValue();
			Int threeColumnDelta = tmp>>16;
			Int columnDelta = (Short)(tmp & 0xFFFF);

			Int i;
			Int min2 = 10000;
			Int min3 = 10000;
			for (i=0; i<3; i+=2) if (column2[i]<min2) min2 = column2[i];
			i=0; do { if (column3[i]<min3) min3 = column3[i]; } while(++i<3);
			Int delta = 10000;
			Int best = -1;
			for (i=0; i<3; i+=2) {
				if (column2[i]==min2) {
					Int dx = (1+columnDelta)-i;
					if (dx<0) dx = -dx;
					if (dx<delta) {
						delta = dx;
						best = i;
					}
				}
			}
			if (best >= 0) {
				column2[best]++;
				columnDelta = best-1;
			}

			delta = 10000;
			best = -1;
			i=0; do {
				if (column3[i]==min3) {
					Int dx = (1+threeColumnDelta)-i;
					if (dx<0) dx = -dx;
					if (dx<delta) {
						delta = dx;
						best = i;
					}
				}
			} while(++i<3);
			if (best >= 0) {
				column3[best]++;
				threeColumnDelta = best-1;
			}

			if (unitsToPath<5) {
				threeColumnDelta = columnDelta;
			}
			ai->setTmpValue( (threeColumnDelta<<16)|(columnDelta&0x00ffff));
		}
	}




	curIndex = 0;
	Int columnFactor[5] = {0,0,0,0,0};
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0,pos);
	for (theUnit = iter2->first(); theUnit; theUnit = iter2->next())
	{
		AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
		Int tmp = ai->getTmpValue();
		Int threeColumnDelta = tmp>>16;
		Int columnDelta = (Short)(tmp & 0xFFFF);
 		Int factor[2]; factor[0] = columnFactor[threeColumnDelta+2];
		columnFactor[threeColumnDelta+2] = factor[0]+1;

		std::vector<Coord3D> path;
		PathNode *node = startNode;
		PathNode *previousNode = m_groundPath->getFirstNode();
		Coord3D prevPos; prevPos.set(theUnit->getPosition());
		while (node) {
			Coord3D dest; dest.set(node->getPosition());
			PathNode *tmpNode;
			PathNode *nextNode=NULL;
			for (tmpNode = node->getNextOptimized(); tmpNode; tmpNode=tmpNode->getNextOptimized()) {
				Real dx = tmpNode->getPosition()->x - dest.x;	
				Real dy = tmpNode->getPosition()->y - dest.y;
				if (dx*dx+dy*dy>farEnoughSqr) {
					nextNode = tmpNode;
					break;
				}
			}
			if (nextNode==NULL) break;
			Coord2D cornerVectorNormal;
			cornerVectorNormal.y = nextNode->getPosition()->x - previousNode->getPosition()->x;
			cornerVectorNormal.x = -(nextNode->getPosition()->y - previousNode->getPosition()->y);
			cornerVectorNormal.normalize();

			Coord2D cornerVector;
			cornerVector.x = nextNode->getPosition()->x - previousNode->getPosition()->x;
			cornerVector.y = nextNode->getPosition()->y - previousNode->getPosition()->y;

			Real offset = PATHFIND_CELL_SIZE_F*1.5f;
			dest.x += offset * columnDelta * cornerVectorNormal.x;
			dest.y += offset * columnDelta * cornerVectorNormal.y;
 			if (factor[0]&1) {
				dest.x += 0.5f*PATHFIND_CELL_SIZE_F * cornerVectorNormal.x;
				dest.y += 0.5f*PATHFIND_CELL_SIZE_F * cornerVectorNormal.y;
			} else {
				dest.x -= 0.5f*PATHFIND_CELL_SIZE_F * cornerVectorNormal.x;
				dest.y -= 0.5f*PATHFIND_CELL_SIZE_F * cornerVectorNormal.y;
			}

			Coord2D curVector;
			curVector.x = dest.x-prevPos.x;
			curVector.y = dest.y-prevPos.y;
			// Make sure that this dest is going in the same direction as the vector.
			if (cornerVector.x*curVector.x + cornerVector.y*curVector.y > 0) {
				path.push_back( dest );
				prevPos = dest;
			}

			node=node->getNextOptimized();

			for (tmpNode = previousNode->getNextOptimized(); tmpNode && tmpNode!=node; tmpNode=tmpNode->getNextOptimized()) {
				Real dx = tmpNode->getPosition()->x - node->getPosition()->x;	
				Real dy = tmpNode->getPosition()->y - node->getPosition()->y;
				if (dx*dx+dy*dy>farEnoughSqr) {
					previousNode = tmpNode;
				}
			}
		}

		Coord3D dest; dest.set(pos);
		if (threeColumnDelta<-3) threeColumnDelta=-3;
		if (threeColumnDelta>3) threeColumnDelta=3;
		Real offset = PATHFIND_CELL_SIZE_F*3.2f;
		if (unitsToPath<5) {
			offset = PATHFIND_CELL_SIZE_F*1.5f;
		}
		dest.x += offset * threeColumnDelta * endVectorNormal.x;
		dest.y += offset * threeColumnDelta * endVectorNormal.y;
		if (factor[0]&1) {
			dest.x += PATHFIND_CELL_SIZE_F * endVectorNormal.x;
			dest.y += PATHFIND_CELL_SIZE_F * endVectorNormal.y;
		}
		dest.x -= factor[0]*offset*endVector.x;
		dest.y -= factor[0]*offset*endVector.y;
		dest.z = TheTerrainLogic->getLayerHeight( dest.x, dest.y, layer, 0, true );

		while (path.size()>0) {
			Coord2D curVector;
			prevPos = path[path.size()-1];
			curVector.x = dest.x-prevPos.x;
			curVector.y = dest.y-prevPos.y;

			// Make sure that this dest is going in the same direction as the vector.
			if (endVector.x*curVector.x + endVector.y*curVector.y <= 0) {
				path.pop_back();
			}	else {
				break;
			}
		}
		TheAI->pathfinder()->adjustDestination(theUnit, *ai->getLocomotorSet(), &dest, NULL);
		TheAI->pathfinder()->updateGoal(theUnit, &dest, LAYER_GROUND, (const char *)0x01095f44, 0x6b4);
		path.push_back(dest);
		ai->aiFollowPath( &path, NULL, cmdSource );
	}
	delete iter;
	delete iter2;
	return true;
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


void AICommandInterface::aiBfmeCommand9FollowPath( const _STL::vector<Coord3D> *path, Object *ignoreObject, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_BFME_9, cmdSource);
	parms.m_coords = *path;
	parms.m_obj = ignoreObject;
	aiDoCommand(&parms);
}

