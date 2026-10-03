// ?d_00156c60@@YAXXZ
// partial score=0.3326 date=2026-10-03
// cl: /D__PLACEMENT_VEC_NEW_INLINE /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/bfmeobject /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// BANK ONLY: not byte exact and not linked. Retail RVA 0x00156C60, 3172 bytes.
// Reconstructed from native bytes and the GeneralsMD AIGroup movement twin;
// no real method identity is asserted. Native RET8 at +0xC61, padding +0xC64.
// Native differs from the twin: 3/5 columns, threshold 16, spacings 21/22,
// no player-type map clamps, no iterator holder lifetimes, and an early bit46 exit.
// Canonical BaseType/Object/ObjectIter/Overridable headers are retained.
// Address-qualified views describe only observed offsets and dispatch ABIs.
// The unbound APIs below are hypotheses for the witnessed native calls, not pins:
// getCenter -> 00151E50 (visible donor separately probes exact 222B);
// Template::ask -> 00087A80; Path dtor -> 003FEB80;
// Pathfinder removeGoal/adjustDestination/updateGoal -> 003E3D20/003F6090/003E9720;
// Terrain getLayerForDestination -> 001A7C20; Commands followPath -> 00153120.
// Canonical SimpleObjectIterator ctor/insert/clear/sort names bind the observed
// 001DDF90/001DDCB0/001DDD60/001DDDC0 calls; no production pin changes made.
// Score is conservative positional-byte similarity, NOT instruction shape.
// Measured 3221B versus3172, 2019 non-reloc differences, shape0.959, frameA8/A0.
// An alternative nontrivial coordinate copy form has frameA0 and3157B but2253
// differences; centroid visibility alone changes A8->A0 in that alternative.
// All constants and the literal derive from the native instruction operands.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>
#include "Lib/BaseType.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectIter.h"
#include "Common/Overridable.h"

struct Rva00156C60Node {
 char prefix[8]; Rva00156C60Node *next; Coord3D position;
 const Coord3D *getPosition() const {return &position;}
 Rva00156C60Node *getNextOptimized() {return next;}
};
struct Rva00156C60Path {
 char prefix[4]; Rva00156C60Node *first, *last;
 ~Rva00156C60Path();
 Rva00156C60Node *getFirstNode() {return first;}
 Rva00156C60Node *getLastNode() {return last;}
};
struct Rva00156C60Commands {
 void aiBfmeCommand9FollowPath(const std::vector<Coord3D>*,Object*,int);
};
struct Rva00156C60Update {
 char prefix[0x21c]; int tmp;
 void setTmpValue(int v) {tmp=v;}
 int getTmpValue() {return tmp;}
 void *getLocomotorSet() {return (char*)this+0x1a8;}
 Rva00156C60Commands *commands() {return (Rva00156C60Commands*)((char*)this+0x20);}
};
struct Rva00156C60Template {
 const Rva00156C60Template *ask() const;
 const Rva00156C60Template *getFinal() const {
  const Rva00156C60Template *p=this;
  if(p && *(Overridable* const*)((char*)p+4)) p=(*(const Rva00156C60Template* const*)((char*)p+4))->ask();
  return p;
 }
 unsigned flag8() const {return (*(const unsigned*)((char*)this+0xc8)&0x100);}
 unsigned flag46() const {return (*(const unsigned*)((char*)this+0xcc)&0x4000);}
};
struct Rva00156C60Object {
 char prefix[4]; Rva00156C60Template *templ; char pad08[0x38-8]; Coord3D position;
 char pad44[0x1a4-0x44]; unsigned char disabled; char pad1a5[0x204-0x1a5]; Rva00156C60Update *ai;
 bool isMobile() const;
 bool held() const {return (disabled&8)!=0;}
 unsigned flag8() const {return templ->getFinal()->flag8();}
 unsigned flag46() const {return templ->getFinal()->flag46();}
 const Coord3D *getPosition() const {return &position;}
 Rva00156C60Update *getAI() {return ai;}
};
static Rva00156C60Object *view(Object*p) {return (Rva00156C60Object*)p;}
struct Rva00156C60Pathfinder {
 void removeGoal(Object*);
 bool adjustDestination(Object*,const void*,Coord3D*,const Coord3D*);
 void updateGoal(Object*,const Coord3D*,int,const char*,int);
};
extern char *TheAI;
static Rva00156C60Pathfinder *pathfinder() {return *(Rva00156C60Pathfinder**)(TheAI+0xc);}
struct Rva00156C60Terrain {
 virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc();
 virtual void s10(); virtual void s14(); virtual void s18();
 virtual float getLayerHeight(float,float,int,Coord3D*,bool);
 int getLayerForDestination(Object*,const Coord3D*);
};
extern Rva00156C60Terrain *TheTerrainLogic;
static Rva00156C60Terrain *terrain() {return TheTerrainLogic;}
struct Rva00156C60Iterator {
 virtual ~Rva00156C60Iterator();
 virtual Object *first();
 virtual Object *next();
 void destroy() {delete this;}
};
struct Rva00156C60Group {
 char prefix[4]; std::list<Object*> m_memberList; char pad08[0x18-8]; Rva00156C60Path *m_rva00156C60_18;
 bool getCenter(Coord3D*);
 bool method(const Coord3D*,int);
};
__declspec(noinline) bool Rva00156C60Group::getCenter(Coord3D *center)
{
 int count=0;
 center->x=0.0f; center->y=0.0f; center->z=0.0f;
 std::list<Object*>::iterator i;
 for(i=m_memberList.begin();i!=m_memberList.end();++i) {
  if(view(*i)->held()) continue;
  if(!view(*i)->isMobile()) continue;
  Rva00156C60Update *ai=view(*i)->getAI();
  if(ai) {
   const Coord3D *p=view(*i)->getPosition();
   center->x+=p->x;center->y+=p->y;center->z+=p->z;++count;
  }
 }
 if(count==0 && !m_memberList.empty()) {
  for(i=m_memberList.begin();i!=m_memberList.end();++i) {
   if(view(*i)->held())continue;
   const Coord3D *p=view(*i)->getPosition();
   center->x+=p->x;center->y+=p->y;center->z+=p->z;++count;
  }
 }
 center->x/=count;center->y/=count;center->z/=count;
 return count>0;
}

Bool Rva00156C60Group::method( const Coord3D *pos, int cmdSource )

{

	if (m_rva00156C60_18==NULL) return false;

	Real dx, dy;
	Coord3D center;
	if (!getCenter( &center )) return false;



	Int numColumns = 3;



	Coord3D startPoint; startPoint.set(m_rva00156C60_18->getFirstNode()->getPosition());
	Real farEnoughSqr = sqr(40.0f);
	Rva00156C60Node *startNode = NULL;
	Rva00156C60Node *node;
	for (node = m_rva00156C60_18->getFirstNode(); node; node=node->getNextOptimized()) {
		Real dx = node->getPosition()->x - startPoint.x;
		Real dy = node->getPosition()->y - startPoint.y;
		if (dx*dx+dy*dy>farEnoughSqr) {
			startNode = node;
			break;
		}
	}
	Coord3D endPoint; endPoint.set(m_rva00156C60_18->getLastNode()->getPosition());
	Rva00156C60Node *endNode = NULL;
	for (node = m_rva00156C60_18->getFirstNode(); node; node=node->getNextOptimized()) {
		Real dx = node->getPosition()->x - endPoint.x;
		Real dy = node->getPosition()->y - endPoint.y;
		if (dx*dx+dy*dy>farEnoughSqr) {
			endNode = node;
		}
	}

	if (startNode==NULL || endNode==NULL) {
		delete m_rva00156C60_18;
		m_rva00156C60_18 = NULL;
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

	Bool useEndVector = false;
	Int unitsToPath = 0;


	SimpleObjectIterator *iter = ::new SimpleObjectIterator;


	SimpleObjectIterator *iter2 = ::new SimpleObjectIterator;


	std::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
        Rva00156C60Object *obj = view(*i);
		if (obj->held() )
		{
			continue;
		}
		if( !obj->flag8() )
		{
			continue;
		}
		if( obj->getAI()==NULL )
		{
			continue;
		}
		if (obj->flag46()) return false;
		Coord3D unitPos; unitPos.set((obj->getPosition()));
		pathfinder()->removeGoal(*i);
		Real dx, dy;
		dx = unitPos.x - center.x;
		dy = unitPos.y - center.y;

		iter->insert((*i), dx*startVectorNormal.x+dy*startVectorNormal.y);
		unitsToPath++;


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

		startVector = endVector;
		startVectorNormal =	endVectorNormal;
		for (theUnit = ((Rva00156C60Iterator*)iter)->first(); theUnit; theUnit = ((Rva00156C60Iterator*)iter)->next()) iter2->insert(theUnit);
		iter->makeEmpty();
		for (theUnit = ((Rva00156C60Iterator*)iter2)->first(); theUnit; theUnit = ((Rva00156C60Iterator*)iter2)->next())
		{
			Coord3D unitPos; unitPos.set((view(theUnit)->getPosition()));
			dx = unitPos.x - center.x;
			dy = unitPos.y - center.y;

			iter->insert(theUnit, dx*startVectorNormal.x+dy*startVectorNormal.y);
		}
		iter2->makeEmpty();
	}

	iter->sort(ITER_SORTED_FAR_TO_NEAR);
	Int curIndex = 0;
	for (theUnit = ((Rva00156C60Iterator*)iter)->first(); theUnit; theUnit = ((Rva00156C60Iterator*)iter)->next())
	{
		Rva00156C60Update *ai = view(theUnit)->getAI();
		Int divisor = ((unitsToPath+1)/numColumns);
		if (divisor<1) divisor=1;
		Int columnDelta = 1-(curIndex/divisor);
		if (columnDelta<-1) columnDelta=-1;
		divisor = ((unitsToPath+3)/5);
		if (divisor<1) divisor=1;
		Int threeColumnDelta = (curIndex/divisor);
		threeColumnDelta = 2-threeColumnDelta;
		if (threeColumnDelta<-2) threeColumnDelta=-2;
		if (unitsToPath<16) {
			threeColumnDelta = columnDelta;
		}

		ai->setTmpValue( (threeColumnDelta<<16)|(columnDelta&0x00ffff));

		Real dx, dy;
		dx = view(theUnit)->getPosition()->x - center.x;
		dy = view(theUnit)->getPosition()->y - center.y;

		iter2->insert(theUnit, dx*startVector.x + dy*startVector.y);
		curIndex++;

	}

	iter2->sort(ITER_SORTED_FAR_TO_NEAR);


	Int column2[3] = {0,0,0};
	Int column3[5] = {0,0,0,0,0};
	{
		for (theUnit = ((Rva00156C60Iterator*)iter2)->first(); theUnit; theUnit = ((Rva00156C60Iterator*)iter2)->next())
		{
			Rva00156C60Update *ai = view(theUnit)->getAI();
			Int tmp = ai->getTmpValue();

			Int threeColumnDelta = tmp>>16;
			Int columnDelta = (Short)(tmp & 0xFFFF);

			Int i;
			Int min2 = 10000;
			Int min3 = 10000;
			for (i=0; i<3; i++) if (column2[i]<min2) min2 = column2[i];
			for (i=0; i<5; i++) if (column3[i]<min3) min3 = column3[i];
			Int delta = 10000;
			Int best = -1;
			for (i=0; i<3; i++) {
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
			for (i=0; i<5; i++) {
				if (column3[i]==min3) {
					Int dx = (2+threeColumnDelta)-i;
					if (dx<0) dx = -dx;
					if (dx<delta) {
						delta = dx;
						best = i;
					}
				}
			}
			if (best >= 0) {
				column3[best]++;
				threeColumnDelta = best-2;
			}

			if (unitsToPath<16) {
				threeColumnDelta = columnDelta;
			}
			ai->setTmpValue( (threeColumnDelta<<16)|(columnDelta&0x00ffff));
		}
	}




	curIndex = 0;
	Int columnFactor[5] = {0,0,0,0,0};
	int layer = terrain()->getLayerForDestination(0,pos);
	for (theUnit = ((Rva00156C60Iterator*)iter2)->first(); theUnit; theUnit = ((Rva00156C60Iterator*)iter2)->next())
	{
		Rva00156C60Update *ai = view(theUnit)->getAI();
		Int tmp = ai->getTmpValue();
		Int threeColumnDelta = tmp>>16;
		Int columnDelta = (Short)(tmp & 0xFFFF);
 		Int factor = columnFactor[threeColumnDelta+2];
		columnFactor[threeColumnDelta+2] = factor+1;

		std::vector<Coord3D> path;
		Rva00156C60Node *node = startNode;
		Rva00156C60Node *previousNode = m_rva00156C60_18->getFirstNode();
		Coord3D prevPos; prevPos.set(view(theUnit)->getPosition());
		while (node) {
			Coord3D dest; dest.set(node->getPosition());
			Rva00156C60Node *tmpNode;
			Rva00156C60Node *nextNode=NULL;
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

			Real offset = 21.0f;
			dest.x += offset * columnDelta * cornerVectorNormal.x;
			dest.y += offset * columnDelta * cornerVectorNormal.y;
 			if (factor&1) {
				dest.x += 5.0f * cornerVectorNormal.x;
				dest.y += 5.0f * cornerVectorNormal.y;
			} else {
				dest.x -= 5.0f * cornerVectorNormal.x;
				dest.y -= 5.0f * cornerVectorNormal.y;
			}

			Coord2D curVector;
			curVector.x = dest.x-prevPos.x;
			curVector.y = dest.y-prevPos.y;


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
		if (threeColumnDelta<-2) threeColumnDelta=-2;
		if (threeColumnDelta>2) threeColumnDelta=2;
		Real offset = 22.0f;
		dest.x += offset * threeColumnDelta * endVectorNormal.x;
		dest.y += offset * threeColumnDelta * endVectorNormal.y;
		if (factor&1) {
			dest.x += 10.0f * endVectorNormal.x;
			dest.y += 10.0f * endVectorNormal.y;
		}

		dest.x -= factor*offset*endVector.x;
		dest.y -= factor*offset*endVector.y;
		dest.z = terrain()->getLayerHeight( dest.x, dest.y, layer, 0, true );

		while (path.size()>0) {
			Coord2D curVector;
			prevPos = path[path.size()-1];
			curVector.x = dest.x-prevPos.x;
			curVector.y = dest.y-prevPos.y;


			if (endVector.x*curVector.x + endVector.y*curVector.y <= 0) {
				path.pop_back();
			}	else {
				break;
			}
		}

		pathfinder()->adjustDestination(theUnit, ai->getLocomotorSet(), &dest, NULL);
		pathfinder()->updateGoal(theUnit, &dest, 1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGroup.cpp", 0x413);
		path.push_back(dest);
		ai->commands()->aiBfmeCommand9FollowPath( &path, NULL, cmdSource );
	}
	((Rva00156C60Iterator*)iter)->destroy();
	((Rva00156C60Iterator*)iter2)->destroy();
	return true;
}

