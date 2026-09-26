// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/shims/stringinline /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// BridgeBehavior::createScaffolding at 0x001F3F10, 2122 bytes.
// The Zero Hour BridgeBehavior.cpp twin and the BridgeBehaviorInterface vtable
// identify the virtual body. Constructor 0x1F3390 installs 0x010A2674 at
// complete-object+0x20; slot 2 is ILT 0x3A733 -> this body. ECX is the interface at complete-object+0x20:
// ObjectModule's owner is this-0x18, the flag is this+0x45d, the list this+0x460.
// The 296-byte setScaffoldData body is compiled alongside it: its visible
// argument accesses let VC7.1 recover retail's local-slot reuse. Coordinates
// share support storage between left and right; the first center copy uses set().
//
// GeometryInfo's BFME multi-shape layout is larger than geometry.h's older ZH
// definition. This view retains the witnessed embedded template+0x60 geometry
// and major radius+0x10 used by retail; the two extent methods remain out of line.
// Three string getter calls return owning strings through a hidden result:
// ILT 0x4a83b -> 0x1f22a0 reads Bridge+8; ILT 0x6064 -> 0x1f28b0 reads
// TerrainRoadType+0x20; ILT 0x280bf -> 0x1f28e0 reads TerrainRoadType+0x24.
// Each independently decoded 32-byte callee copy-constructs StringBase<char>,
// returns the hidden result and ret 4; TerrainLogic.h/TerrainRoads.h supply names.
// The existing basetype.h supplies the x87 float-to-integer helper; BFME uses
// CRT ceil rather than the reference fast_float_ceil bit trick.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>
#include <math.h>
#include "basetype.h"
#include "StringInline.h"

#define DEBUG_ASSERTCRASH(x,y) ((void)0)
#define DEBUG_CRASH(x) ((void)0)
#define TRUE true
#define FALSE false
#undef REAL_TO_INT_CEIL
#define REAL_TO_INT_CEIL(x) fast_float2long_round((float)ceil(x))
#define INT_TO_REAL(x) ((float)(x))

enum ObjectID { INVALID_ID=0 };
enum PathfindLayerEnum {};
class Team; class Object;
class GeometryInfo {
public:
    float getMaxHeightBelowPosition() const;
    float getMaxHeightAbovePosition() const;
    float getMajorRadius() const { return m_majorRadius; }
    char m_00[0x10]; float m_majorRadius;
};
class Overridable { public: void *m_vtable; Overridable *m_nextOverride; };
class ThingTemplate : public Overridable {
public:
    const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
    char m_unreconstructed08[0x58]; GeometryInfo m_geometryInfo;
};
class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions(const Coord3D *sunkenPosition,
		const Coord3D *risePosition, const Coord3D *buildPosition);
	virtual void setMotion(int motion);
	virtual int getCurrentMotion() const;
	virtual void reverseMotion();
	virtual void setLateralSpeed(Real speed);
	virtual void setVerticalSpeed(Real speed);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h
class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};


class Thing { public: void setOrientation(Real); };
class Object {
public:
    void setPosition(const Coord3D *);
    const Coord3D *getPosition() const { return &m_cachedPos; }
    Team *getTeam() const { return m_team; }
    ObjectID getID() const { return m_id; }
    void *m_vtable; ThingTemplate *m_template;
    char m_unreconstructed08[0x30]; Coord3D m_cachedPos;
    char m_unreconstructed44[0x30]; ObjectID m_id;
    char m_unreconstructed78[0x1c4]; Team *m_team;
};
template<int N> class BitFlags { std::bitset<N> m_bits; };
typedef BitFlags<86> ObjectStatusMaskType;
class ThingFactory { public:
    const ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *,Team *,const ObjectStatusMaskType & =ObjectStatusMaskType(),unsigned int=0);
};
extern ThingFactory *TheThingFactory;
struct BridgeInfo {
    BridgeInfo();
    Coord3D from,to;
    float bridgeWidth;
    Coord3D fromLeft,fromRight,toLeft,toRight;
    int bridgeIndex,curDamageState;
    ObjectID bridgeObjectID,towerObjectID[4];
    bool damageStateChanged;
};
class Bridge { public:
    AsciiString getBridgeTemplateName();
    void getBridgeInfo(BridgeInfo *info) const { *info=m_bridgeInfo; }
    PathfindLayerEnum getLayer() const { return m_layer; }
    char m_00[0xc]; BridgeInfo m_bridgeInfo;
    char m_78[0x10]; PathfindLayerEnum m_layer;
};
class TerrainRoadType { public:
    AsciiString getScaffoldObjectName();
    AsciiString getScaffoldSupportObjectName();
};
class TerrainRoadCollection { public: TerrainRoadType *findBridge(AsciiString); };
extern TerrainRoadCollection *TheTerrainRoads;
class TerrainLogic
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05(); virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17(); virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21(); virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25(); virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29(); virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33(); virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37();
	virtual Bridge *findBridgeAt(const Coord3D *position);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void changeBridgeState(PathfindLayerEnum layer, bool open);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

private:
	unsigned char m_unreconstructed00[0x0C];
	Pathfinder *m_pathfinder;
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class UpdateModule {
public:
    virtual void updateAnchor();
    char m_04[4]; Object *m_object; char m_0c[0x14];
    Object *getObject() const { return m_object; }
};
class BridgeBehaviorInterface { public:
    virtual void setTower(int,Object *)=0;
    virtual ObjectID getTowerID(int)=0;
    virtual void createScaffolding()=0;
};
void __stlp_deallocate_small(void *node, UnsignedInt bytes);
namespace _STL { void *nodeAllocate(UnsignedInt bytes); }

template <class T>
class BridgeScaffoldAllocator : public _STL::allocator<T>
{
public:
	template <class U> struct rebind { typedef BridgeScaffoldAllocator<U> other; };

	BridgeScaffoldAllocator() {}
	template <class U> BridgeScaffoldAllocator(const BridgeScaffoldAllocator<U> &) {}

	T *allocate(UnsignedInt count, const void * = 0) const
	{
		return (T *)_STL::nodeAllocate(count * sizeof(T));
	}

	void deallocate(T *node, UnsignedInt count) const
	{
		__stlp_deallocate_small(node, count * sizeof(T));
	}
};

template <class T, class U>
BridgeScaffoldAllocator<U> &__stl_alloc_rebind(
	BridgeScaffoldAllocator<T> &allocator, const U *)
{
	return (BridgeScaffoldAllocator<U> &)allocator;
}

typedef _STL::list<ObjectID, BridgeScaffoldAllocator<ObjectID> > BridgeScaffoldList;


class BridgeBehavior : public UpdateModule, public BridgeBehaviorInterface {
public:
    virtual void createScaffolding();
protected:
    void setScaffoldData(Object *,float *,float *,const Coord3D *,const Coord3D *,const Coord3D *);
public:
    char m_24[0x459]; bool m_scaffoldPresent;
    BridgeScaffoldList m_scaffoldObjectIDList;
};
void BridgeBehavior::createScaffolding( void )
{

	// if we have scaffolding up already do nothing
	if( m_scaffoldPresent == TRUE )
		return;

	// get the bridge world object
	Object *us = getObject();
	const Coord3D *center = us->getPosition();

	// get our bridge object
	Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

	// get the bridge template
	AsciiString bridgeTemplateName = bridge->getBridgeTemplateName();
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );
	DEBUG_ASSERTCRASH( bridgeTemplate, ("Unable to find bridge template to create scaffolding\n") );

	// get the thing template for the scaffold object we're going to use
	AsciiString scaffoldObjectName = bridgeTemplate->getScaffoldObjectName();
	const ThingTemplate *scaffoldTemplate = TheThingFactory->findTemplate( scaffoldObjectName );
	if( scaffoldTemplate == NULL )
	{

		DEBUG_CRASH(( "Unable to find bridge scaffold template\n" ));
		return;

	}  // end if

	// get thing template for scaffold support object
	AsciiString scaffoldSupportObjectName = bridgeTemplate->getScaffoldSupportObjectName();
	const ThingTemplate *scaffoldSupportTemplate = TheThingFactory->findTemplate( scaffoldSupportObjectName );
	if( scaffoldSupportTemplate == NULL )
	{

		DEBUG_CRASH(( "Unable to find bridge support scaffold template\n" ));
		return;

	}  // end if

	// how much space is going to be between each of the scaffold objects at their final positions
	Real spacing = scaffoldTemplate->getTemplateGeometryInfo().getMajorRadius() * 2.0f;

	// how tall are the scaffold objects
	Real scaffoldHeight = scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition() +
												scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition();
	Real scaffoldSupportHeight = scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition() +
															 scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition();

	// get the bridge info
	BridgeInfo bridgeInfo;
	bridge->getBridgeInfo( &bridgeInfo );

	//
	// given the area of the bridge, figure out what the start and end points are to create
	// all the scaffold objects at (just in the 2D bridge plane, not thinking about
	// rising the objects up through the ground yet)
	//
	Coord3D leftStart;
	leftStart.x = ((bridgeInfo.fromLeft.x - bridgeInfo.fromRight.x) / 2.0f) + bridgeInfo.fromRight.x;
	leftStart.y = ((bridgeInfo.fromLeft.y - bridgeInfo.fromRight.y) / 2.0f) + bridgeInfo.fromRight.y;
	leftStart.z = ((bridgeInfo.fromLeft.z - bridgeInfo.fromRight.z) / 2.0f) + bridgeInfo.fromRight.z;

	Coord3D rightStart;
	rightStart.x = ((bridgeInfo.toLeft.x - bridgeInfo.toRight.x) / 2.0f) + bridgeInfo.toRight.x;
	rightStart.y = ((bridgeInfo.toLeft.y - bridgeInfo.toRight.y) / 2.0f) + bridgeInfo.toRight.y;
	rightStart.z = ((bridgeInfo.toLeft.z - bridgeInfo.toRight.z) / 2.0f) + bridgeInfo.toRight.z;

	//
	// now that we have the left and right start points, we will compute two angles to
	// use for all the objects that we will create ... objects on the left side of the
	// bridge will be given a 'leftAngle' pointing from 'leftStart' to 'rightStart' and
	// the opposite will be given to objects on the right side of the bridge
	//
	Coord2D angleV;
	angleV.x = rightStart.x - leftStart.x;
	angleV.y = rightStart.y - leftStart.y;
	Real leftAngle = angleV.toAngle();
	Real rightAngle = leftAngle + TWO_PI;

	// compute vector from left to right across bridge and the reverse
	Coord3D leftVector;
	leftVector.x = rightStart.x - leftStart.x;
	leftVector.y = rightStart.y - leftStart.y;
	leftVector.z = rightStart.z - leftStart.z;
	Coord3D rightVector;
	rightVector.x = leftStart.x - rightStart.x;
	rightVector.y = leftStart.y - rightStart.y;
	rightVector.z = leftStart.z - rightStart.z;

	//
	// how many of these scaffold objects will take to tile from each of the endpoints 
	// to the center area of the bridge
	//
	Real tileDistance = leftVector.length();
	Int numObjects = REAL_TO_INT_CEIL( tileDistance / spacing ) + 1;

	//
	// given the number of objects that we need to tile across the whole bridge, we will
	// go through the creation loop ceil( numObjects / 2.0f ) times, and each
	// time through the loop we'll create an object to move from each side of the
	// bridge, except the last object if the number of objects is odd is dead in the
	// center
	//
	Int numIterations = REAL_TO_INT_CEIL( INT_TO_REAL( numObjects ) / 2.0f );

	//
	// normalize left and right vectors as it is a vector that goes from our left start 
	// position to the destination right start position ... we will multiply this vector by a
	// spacing amount and add to the left start position to find a destination position
	// for a particular scaffold object along the bridge surface
	//
	leftVector.normalize();
	rightVector.normalize();

	// create the scaffold objects for now
	Int scaffoldObjectsCreated = 0;
	Coord3D destinationPos, *riseToPos;
	Real *angle;
	Object *obj;
	for( Int i = 0; i < numIterations; ++i )
	{

		// sanity
		DEBUG_ASSERTCRASH( scaffoldObjectsCreated < numObjects, 
											 ("Creating too many scaffold objects\n") );

		// create object
		obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam() );

		// this object is from the "left" side of the bridge
		riseToPos = &leftStart;
		angle = &leftAngle;

		//
		// compute position for object moving from the left side, we're adding 0.1 here
		// so that all scaffold objects *have* to move some distance ... that way we
		// can just assign the speeds so they line up perfectly and not have to worry
		// about any object reaching a destination before any other object
		//
		destinationPos.x = leftVector.x * (spacing * i) + riseToPos->x + 0.1f;
		destinationPos.y = leftVector.y * (spacing * i) + riseToPos->y;
		destinationPos.z = leftVector.z * (spacing * i) + riseToPos->z;

		//
		// now that they key positions are calculated, set the rest of the position data
		// and movement speeds for the object
		//
		setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );

		// keeping track of objects created
		scaffoldObjectsCreated++;
		m_scaffoldObjectIDList.push_back( obj->getID() );

		//
		// create support object layers under the scaffold object, this object mirrors the scaffold
		// object except is on a lower layer
		//
		Real offset = riseToPos->z;
		Coord3D supportRiseToPos = *riseToPos;
		Coord3D supportDestinationPos = destinationPos;
		Coord3D supportBridgeCenter; supportBridgeCenter.set(center);
		while( offset >= 0.0f )
		{

			supportRiseToPos.z -= scaffoldSupportHeight;
			supportDestinationPos.z -= scaffoldSupportHeight;
			supportBridgeCenter.z -= scaffoldSupportHeight;
			obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam() );
			setScaffoldData( obj, 
											 angle, 
											 &scaffoldSupportHeight,
											 &supportRiseToPos, 
											 &supportDestinationPos, 
											 &supportBridgeCenter );
			m_scaffoldObjectIDList.push_back( obj->getID() );


			// off to the next layer
			offset -= scaffoldSupportHeight;

		}  // end while

		//
		// now create the object from the "right" side of the bridge ... but note that
		// we don't do this on the last iteration through this loop when we have an odd
		// number of objects we're tiling because all the space is already perfectly used up)
		//
		if( scaffoldObjectsCreated < numObjects )
		{

			// sanity
			DEBUG_ASSERTCRASH( scaffoldObjectsCreated < numObjects, 
												 ("Creating too many scaffold objects\n") );

			// create new object
			obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam() );

			// this object is on the "right" side of the bridge
			riseToPos = &rightStart;
			angle = &rightAngle;

			//
			// compute position for object moving from the left side, we're adding 0.1 here
			// so that all scaffold objects *have* to move some distance ... that way we
			// can just assign the speeds so they line up perfectly and not have to worry
			// about any object reaching a destination before any other object
			//
			destinationPos.x = rightVector.x * (spacing * i) + riseToPos->x + 0.1f;
			destinationPos.y = rightVector.y * (spacing * i) + riseToPos->y;
			destinationPos.z = rightVector.z * (spacing * i) + riseToPos->z;

			// set the rest scaffold data again
			setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );

			// keeping track of objects created
			scaffoldObjectsCreated++;
			m_scaffoldObjectIDList.push_back( obj->getID() );

			//
			// create support object layers under the scaffold object, this object mirrors the scaffold
			// object except is on a lower layer
			//
			offset = riseToPos->z;
			supportRiseToPos = *riseToPos;
			supportDestinationPos = destinationPos;
			supportBridgeCenter = *center;
			while( offset >= 0.0f )
			{

				supportRiseToPos.z -= scaffoldSupportHeight;
				supportDestinationPos.z -= scaffoldSupportHeight;
				supportBridgeCenter.z -= scaffoldSupportHeight;
				obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam() );
				setScaffoldData( obj, 
												 angle, 
												 &scaffoldSupportHeight,
												 &supportRiseToPos, 
												 &supportDestinationPos, 
												 &supportBridgeCenter );
				m_scaffoldObjectIDList.push_back( obj->getID() );


				// off to the next layer
				offset -= scaffoldSupportHeight;

			}  // end while

		}  // end if

	}  // end for i	

	// scaffolding is now present
	m_scaffoldPresent = TRUE;

	// when scaffolding is present, a bridge cannot be used
	TheAI->pathfinder()->changeBridgeState( bridge->getLayer(), FALSE );

}  // end createScaffolding
void BridgeBehavior::setScaffoldData(Object *object, Real *angle, Real *sunkenHeight,
	const Coord3D *risePosition, const Coord3D *buildPosition,
	const Coord3D *bridgeCenter)
{
	if (object == 0 || angle == 0 || risePosition == 0 || buildPosition == 0)
		return;

	const unsigned char *moduleData = *(const unsigned char **)
		((const unsigned char *)this + 0x04);
	BridgeScaffoldBehaviorInterface *scaffold =
		BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);

	Real fudge = 8.0f;
	Coord3D sunkenPosition;
	sunkenPosition.x = risePosition->x;
	sunkenPosition.y = risePosition->y;
	sunkenPosition.z = risePosition->z - *sunkenHeight - fudge;
	object->setPosition(&sunkenPosition);
	scaffold->setPositions(&sunkenPosition, risePosition, buildPosition);
	scaffold->setMotion(1);
	((Thing *)object)->setOrientation(*angle);

	Real lateralSpeed = *(const Real *)(moduleData + 0x08);
	Coord3D buildToCenter;
	Coord3D riseToCenter;
	buildToCenter.x = buildPosition->x - risePosition->x;
	buildToCenter.y = buildPosition->y - risePosition->y;
	buildToCenter.z = buildPosition->z - risePosition->z;
	riseToCenter.x = bridgeCenter->x - risePosition->x;
	riseToCenter.y = bridgeCenter->y - risePosition->y;
	riseToCenter.z = bridgeCenter->z - risePosition->z;
	Real buildDistance = buildToCenter.length();
	Real riseDistance = riseToCenter.length();
	scaffold->setLateralSpeed(
		lateralSpeed * (buildDistance / riseDistance));
	Real verticalSpeed = *(const Real *)(moduleData + 0x0C);
	scaffold->setVerticalSpeed(verticalSpeed);
}
