// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the TransportContain::isSpecificRiderFreeToExit naked dump to clean C++.
//
// Zero Hour's TransportContain.cpp body, unchanged. The one thing that reads
// wrong at first is the tail: retail pushes the position and the locomotor,
// then calls a method on `me`, then pushes its result and calls a method on the
// pathfinder. That looks like two calls with the arguments split between them,
// but 0x005BEC20 takes no arguments at all -- it is Object::getLayer, ending in
// a bare ret -- so those two pushes are simply the last two arguments of
// validMovementTerrain, evaluated before its first.
//
// Retail pins the layout: the contained object is at this+0x08, the AI update
// interface at object+0x204, the position at object+0x38, the current locomotor
// at ai+0x1CC, and the pathfinder at TheAI+0x0C. getAiFreeToExit is the virtual
// at vtable +0x170 and FREE_TO_EXIT is zero, which is why the comparison is a
// plain test against the returned value.
//
// The failure paths share one `xor al,al` epilogue while the two success paths
// each set al and return, so the body is ZH's chain of early returns.

typedef int Int;
typedef bool Bool;

enum { FREE_TO_EXIT = 0 };

class Object;
class Locomotor;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual void unused72();
	virtual void unused73();
	virtual void unused74();
	virtual void unused75();
	virtual void unused76();
	virtual void unused77();
	virtual void unused78();
	virtual void unused79();
	virtual void unused80();
	virtual void unused81();
	virtual void unused82();
	virtual void unused83();
	virtual void unused84();
	virtual void unused85();
	virtual void unused86();
	virtual void unused87();
	virtual void unused88();
	virtual void unused89();
	virtual void unused90();
	virtual void unused91();

	virtual Int getAiFreeToExit(Object *obj) const;		///< vtable +0x170

	const Locomotor *getCurLocomotor(void) const { return m_curLocomotor; }

private:
	unsigned char m_unreconstructed_04[0x1CC - 4];
	Locomotor *m_curLocomotor;							///< retail this+0x1CC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isUsingAirborneLocomotor(void) const;			///< ILT thunk at 0x0000A001
	Int getLayer(void) const;							///< ILT thunk at 0x0003A391

	const Coord3D *getPosition(void) const { return &m_position; }
	const AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }

private:
	unsigned char m_unreconstructed_00[0x38];
	Coord3D m_position;									///< retail this+0x38
	unsigned char m_unreconstructed_44[0x204 - 0x44];
	AIUpdateInterface *m_ai;							///< retail this+0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool validMovementTerrain(Int layer, const Locomotor *loco, const Coord3D *pos);	///< ILT thunk at 0x0001B405
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	unsigned char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;							///< retail this+0x0C
};

extern AI *TheAI;										///< retail [0x012EF214]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportContain.h
class TransportContain
{
protected:
	virtual Bool isSpecificRiderFreeToExit(Object *specificObject);

	Object *getObject(void) const { return m_object; }

private:
	// the vtable pointer occupies +0x00
	unsigned char m_unreconstructed_04[8 - 4];
	Object *m_object;									///< retail this+0x08
};

// ?isSpecificRiderFreeToExit@TransportContain@@MAE_NPAVObject@@@Z
Bool TransportContain::isSpecificRiderFreeToExit(Object* specificObject)
{
	if( specificObject == 0 )
		return true;	// I can, in general, exit people.

	// This is a override, not an extend.  I will check for game legality for
	// okaying the call to exitObjectViaDoor.
	const Object* me = getObject();

	// this is present solely for some transports to override, so that they can land before
	// allowing people to exit...
	const AIUpdateInterface* ai = me->getAIUpdateInterface();
	if (ai && ai->getAiFreeToExit(specificObject) != FREE_TO_EXIT)
		return false;

	// I can always kick people out if I am in the air, I know what I'm doing
	if (me->isUsingAirborneLocomotor())
		return true;

	const Coord3D *myPosition = me->getPosition();
	if (!specificObject->getAIUpdateInterface())
		return false;

	const Locomotor *hisLocomotor = specificObject->getAIUpdateInterface()->getCurLocomotor();
	if( hisLocomotor == 0 )
		return false;

	// He can't get to this spot naturally, so I can't force him there.  (amphib transport)
	if (!TheAI->pathfinder()->validMovementTerrain(me->getLayer(), hisLocomotor, myPosition))
		return false;

	return true;
}
