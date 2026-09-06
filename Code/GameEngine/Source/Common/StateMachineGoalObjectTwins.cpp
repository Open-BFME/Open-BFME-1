// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: the goal-object setters of two BFME state machines whose
// layouts differ from StateMachine.cpp's (found by the near-miss object
// scan: StateMachine.cpp compiles the same bodies with the goal id at +0x24,
// the goal position at +0x28 and the lock byte at +0x34).  Machine A keeps
// the goal id at +0x20 and the position at +0x24; machine B at +0x30/+0x34;
// both have the lock byte at +0x40.  Same include set as StateMachine.cpp so
// Object::getID and Thing::getPosition inline identically.
//   0x000A0800 (51) internalSetGoalObject A   0x000A0C40 (58) setGoalObject A
//   0x000A0840 (51) internalSetGoalObject B   0x000A0C90 (58) setGoalObject B
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/StateMachine.h"
#include "GameLogic/Object.h"

class Rva000A0800Machine
{
public:
	void setGoalObject( const Object *obj );
private:
	void internalSetGoalObject( const Object *obj );
	void internalSetGoalPosition( const Coord3D *pos ) { if (pos) m_goalPosition = *pos; }

	char m_unmodelled00[ 0x20 ];
	ObjectID m_goalObjectID;			// +0x20
	Coord3D m_goalPosition;				// +0x24
	char m_unmodelled30[ 0x10 ];
	Bool m_locked;						// +0x40
};

class Rva000A0840Machine
{
public:
	void setGoalObject( const Object *obj );
private:
	void internalSetGoalObject( const Object *obj );
	void internalSetGoalPosition( const Coord3D *pos ) { if (pos) m_goalPosition = *pos; }

	char m_unmodelled00[ 0x30 ];
	ObjectID m_goalObjectID;			// +0x30
	Coord3D m_goalPosition;				// +0x34
	Bool m_locked;						// +0x40
};

void Rva000A0800Machine::internalSetGoalObject( const Object *obj )
{
	if (obj) {
		m_goalObjectID = obj->getID();
		internalSetGoalPosition(obj->getPosition());
	}
	else {
		m_goalObjectID = INVALID_ID;
	}
}

void Rva000A0840Machine::internalSetGoalObject( const Object *obj )
{
	if (obj) {
		m_goalObjectID = obj->getID();
		internalSetGoalPosition(obj->getPosition());
	}
	else {
		m_goalObjectID = INVALID_ID;
	}
}

void Rva000A0800Machine::setGoalObject( const Object *obj )
{
	if (m_locked)
		return;

	internalSetGoalObject( obj );
}

void Rva000A0840Machine::setGoalObject( const Object *obj )
{
	if (m_locked)
		return;

	internalSetGoalObject( obj );
}
