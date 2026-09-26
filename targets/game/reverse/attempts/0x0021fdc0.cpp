// ?exitObjectViaDoor@GarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.9 date=2026-09-26
// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport
// ?exitObjectViaDoor@GarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// Retail 0x0021FDC0: 732 bytes; ret 8.
//
// Identity: the GarrisonContain ExitInterface vtable 0x010AB528 (installed by
// the matched constructor 0x0021D820 and destructor 0x0021D9C0) has slot 2
// (+0x08) at ILT 0x0004910C, which jumps to this body; slot 2 of Zero Hour's
// ExitInterface is exitObjectViaDoor(Object *, ExitDoorType), and the body is
// the Generals GarrisonContain::exitObjectViaDoor donor statement for
// statement (removeFromContain, three validMovementTerrain probes stepping
// by the major radius along the owner's orientation, addObjectToPathfindMap,
// adjustToPossibleDestination, a Coord3D exit path, follow-path command and
// updateGoal, then recalcApparentControllingPlayer).  The __FILE__ string
// passed to updateGoal at 0x010AB8F8 names GarrisonContain.cpp.
//
// The incoming receiver is the ExitInterface subobject at module+0x30; the
// contain interface is receiver-0x10 and the owning Object is at
// receiver-0x28 (module+0x08), as in the matched OpenContain sibling.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "Lib/BaseType.h"
#include <vector>

// Retain the native vector append cursor across the placement copy (same
// specialization as the matched OpenContain::exitObjectViaDoor sibling).
namespace _STL {
template <> inline void vector<Coord3D>::push_back(const Coord3D &value) {
	Coord3D *finish = _M_finish;
	if (finish != _M_end_of_storage._M_data) {
		_Construct(finish, value);
		_M_finish = finish + 1;
	} else {
		_M_insert_overflow(finish, value, __false_type(), 1, true);
	}
}
}

enum ExitDoorType
{
	DOOR_1 = 0
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class Object;
class Locomotor;
class LocomotorSet;

// Real Cos(Real) / Real Sin(Real), Common/System/Trig.cpp (0x00873920 / 0x00873910).
Real Cos(Real angle);
Real Sin(Real angle);

// 0x001D0520 through ILT 0x0001621B: the two-argument BFME position setter.
// Its matched ledger row carries this address-bucket name.
class BfmePosTP;
class BfmeHostTP
{
public:
	void bfmeSetPositionTP(const BfmePosTP *position, bool flag);
};

struct AIUpdateInterfaceHead0021FDC0
{
	char m_unmodelled_000[0x20];
};

class AICommandInterface
{
public:
	void aiFollowExitProductionPath(const std::vector<Coord3D> *path,
		Object *ignoreObject, CommandSourceType commandSource);
};

class AIUpdateInterface : public AIUpdateInterfaceHead0021FDC0, public AICommandInterface
{
public:
	Locomotor *getCurLocomotor() const
	{
		return *(Locomotor *const *)((const char *)this + 0x1CC);
	}

	const LocomotorSet &getLocomotorSet() const
	{
		return *(const LocomotorSet *)((const char *)this + 0x1A8);
	}
};

class Thing
{
public:
	void setOrientation(Real angle);
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	Real getOrientation() const
	{
		return *(const Real *)((const char *)this + 0x44);
	}

	Real getMajorRadius() const
	{
		return *(const Real *)((const char *)this + 0xBC);
	}

	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface *const *)((const char *)this + 0x204);
	}

	void setPosition(const Coord3D *position, bool flag)
	{
		((BfmeHostTP *)this)->bfmeSetPositionTP((const BfmePosTP *)position, flag);
	}
};

class Pathfinder
{
public:
	Bool validMovementTerrain(Int layer, const Locomotor *locomotor,
		const Coord3D *position);
	void addObjectToPathfindMap(Object *object);
	Bool adjustToPossibleDestination(Object *object,
		const LocomotorSet &locomotorSet, Coord3D *destination);
	void updateGoal(Object *object, const Coord3D *position,
		PathfindLayerEnum layer, const char *file, Int line);
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	char m_unmodelled_000[0x0C];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;

template <int N>
class Rva0021FDC0ContainSlots : public Rva0021FDC0ContainSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva0021FDC0ContainSlots<0>
{
};

// Contain interface at module+0x20.  Slot +0x40 is recalcApparentControllingPlayer
// (matched 0x0021F9F0 through ILT 0x00010E42 in vtable 0x010AB598); slot +0x90
// is the two-argument removeFromContain the OpenContain sibling calls.  Slots
// +0x144 and +0x14C reach 0x00219AC0 / 0x00219AE0, which both return the
// owner's position pointer (Object+0x38).
class ContainView0021FDC0 : public Rva0021FDC0ContainSlots<16>
{
public:
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void slot44() = 0; virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0; virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0; virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0; virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void removeFromContain(Object *object, Bool exposeStealthUnits) = 0;
	virtual void slot94() = 0; virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0; virtual void slotA4() = 0; virtual void slotA8() = 0; virtual void slotAC() = 0;
	virtual void slotB0() = 0; virtual void slotB4() = 0; virtual void slotB8() = 0; virtual void slotBC() = 0;
	virtual void slotC0() = 0; virtual void slotC4() = 0; virtual void slotC8() = 0; virtual void slotCC() = 0;
	virtual void slotD0() = 0; virtual void slotD4() = 0; virtual void slotD8() = 0; virtual void slotDC() = 0;
	virtual void slotE0() = 0; virtual void slotE4() = 0; virtual void slotE8() = 0; virtual void slotEC() = 0;
	virtual void slotF0() = 0; virtual void slotF4() = 0; virtual void slotF8() = 0; virtual void slotFC() = 0;
	virtual void slot100() = 0; virtual void slot104() = 0; virtual void slot108() = 0; virtual void slot10C() = 0;
	virtual void slot110() = 0; virtual void slot114() = 0; virtual void slot118() = 0; virtual void slot11C() = 0;
	virtual void slot120() = 0; virtual void slot124() = 0; virtual void slot128() = 0; virtual void slot12C() = 0;
	virtual void slot130() = 0; virtual void slot134() = 0; virtual void slot138() = 0; virtual void slot13C() = 0;
	virtual void slot140() = 0;
	virtual const Coord3D *ownerPosition00219AC0() = 0;
	virtual void slot148() = 0;
	virtual const Coord3D *ownerPosition00219AE0() = 0;
};

class GarrisonContain
{
public:
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor);

	ContainView0021FDC0 *contain()
	{
		return (ContainView0021FDC0 *)((char *)this - 0x10);
	}

	void removeFromContain(Object *obj)
	{
		contain()->removeFromContain(obj, false);
	}

	void recalcApparentControllingPlayer()
	{
		contain()->recalcApparentControllingPlayer();
	}

	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 0x28);
	}
};

void GarrisonContain::exitObjectViaDoor( Object *exitObj, ExitDoorType exitDoor )
{
	removeFromContain( exitObj );

	Coord3D startPosition;

	Real exitAngle = getObject()->getOrientation();
	startPosition = *contain()->ownerPosition00219AC0();

	AIUpdateInterface *ai = exitObj->getAI();
	if (ai) {
		Locomotor *loco = ai->getCurLocomotor();
		if (loco && !TheAI->pathfinder()->validMovementTerrain( LAYER_GROUND, loco, &startPosition)) {
			Real offset = getObject()->getMajorRadius();
			startPosition.x -= offset*Cos(exitAngle);
			startPosition.y -= offset*Sin(exitAngle);
			if (!TheAI->pathfinder()->validMovementTerrain(LAYER_GROUND, loco, &startPosition)) {
				startPosition.x += 2*offset*Cos(exitAngle);
				startPosition.y += 2*offset*Sin(exitAngle);
				if (!TheAI->pathfinder()->validMovementTerrain(LAYER_GROUND, loco, &startPosition)) {
					startPosition = *getObject()->getPosition();
				}
			}
		}
	}

	exitObj->setPosition( &startPosition, false );
	exitObj->setOrientation( exitAngle );
	TheAI->pathfinder()->addObjectToPathfindMap( exitObj );
	if( ai )
	{
		Coord3D endPosition = *contain()->ownerPosition00219AE0();
		TheAI->pathfinder()->adjustToPossibleDestination(exitObj, ai->getLocomotorSet(), &endPosition);
		std::vector<Coord3D> exitPath;
		exitPath.push_back(endPosition);
		exitPath.push_back(endPosition);

		ai->aiFollowExitProductionPath( &exitPath, getObject(), CMD_FROM_AI );
		TheAI->pathfinder()->updateGoal(exitObj, &endPosition, TheTerrainLogic->getLayerForDestination(exitObj, &endPosition),
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\GarrisonContain.cpp", 0x58C);
	}

	recalcApparentControllingPlayer();
}
