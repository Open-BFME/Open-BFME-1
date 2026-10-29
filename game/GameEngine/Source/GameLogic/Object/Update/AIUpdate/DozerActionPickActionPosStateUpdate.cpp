// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
// DozerActionPickActionPosState::update (retail 0x002B8E10, 372 B). Zero Hour's
// DozerAIUpdate.cpp body on BFME layouts: virtual StateMachine::setGoalObject
// (slot 0x38), free findPositionAround, and a
// second ignoreObstacle before the move order.
// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp

#include "Lib/Coord2D.h"
#include "Lib/Coord3D.h"
#include "../../../command_source_type.h"

typedef float Real;
typedef int ObjectID;
typedef int DozerTask;

enum StateReturnType
{
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct FindPositionOptions
{
	FindPositionOptions()
	{
		flags = 0;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;							// RANDOM_START_ANGLE
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}
	unsigned int flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

bool findPositionAround( const Coord3D *center, const FindPositionOptions *options, Coord3D *result );

// TU-local adapter for Coord2D::toAngle, pinned at ILT 0x00046E52.
class BfmeStructureToppleCoord2DCall
{
public:
	Real toAngle() const;
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic TheGameLogic

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual ObjectID getTaskTarget( DozerTask task );
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void internalTaskCompleteOrCancelled( DozerTask task );
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual const Coord3D *getDockPoint( DozerTask task, int point );
};

class AICommandInterface
{
public:
	void aiMoveToPosition( const Coord3D *pos, CommandSourceType cmdSource );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
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
	virtual DozerAIInterface *getDozerAIInterface();

	void ignoreObstacle( Object *obj );

	char m_unmodelled04[0x1C];
	AICommandInterface m_commandInterface;
};

class Object
{
public:
	char m_unmodelled00[0x38];
	Coord3D m_position;
	char m_unmodelled44[0x7C];
	Real m_boundingCircleRadius;
	char m_unmodelledC4[0x140];
	AIUpdateInterface *m_ai;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject( const Object *obj );

	void setGoalPosition( const Coord3D *pos );

	char m_unmodelled04[0xC];
	Object *m_owner;
};

class State
{
public:
	virtual StateReturnType update();

	char m_unmodelled04[0x18];
	StateMachine *m_machine;
};

class DozerActionPickActionPosState : public State
{
public:
	virtual StateReturnType update();

	int m_unmodelled20;
	DozerTask m_task;
};

StateReturnType DozerActionPickActionPosState::update()
{
	StateMachine *machine = m_machine;
	Object *dozer = machine->m_owner;
	AIUpdateInterface *ai = dozer->m_ai;
	if( ai == 0 )
		return STATE_FAILURE;

	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if( dozerAI == 0 )
		return STATE_FAILURE;

	Object *goalObject = TheBfmeGameLogic->findObjectByID( dozerAI->getTaskTarget( m_task ) );
	if( goalObject == 0 )
	{
		m_machine->setGoalObject( 0 );
		dozerAI->internalTaskCompleteOrCancelled( m_task );
		return STATE_FAILURE;
	}

	Coord3D goalPos;
	const Coord3D *dockPos = dozerAI->getDockPoint( m_task, 0 );
	if( dockPos )
	{
		goalPos = *dockPos;
	}
	else
	{
		FindPositionOptions fpOptions;
		Coord2D v;
		v.x = dozer->m_position.x - goalObject->m_position.x;
		v.y = dozer->m_position.y - goalObject->m_position.y;
		Real radius = goalObject->m_boundingCircleRadius;
		fpOptions.minRadius = radius;
		fpOptions.maxRadius = radius;
		fpOptions.startAngle = ( (const BfmeStructureToppleCoord2DCall *)&v )->toAngle();
		if( !findPositionAround( &goalObject->m_position, &fpOptions, &goalPos ) )
			goalPos = goalObject->m_position;
		ai->ignoreObstacle( goalObject );
	}

	machine->setGoalObject( goalObject );
	machine->setGoalPosition( &goalPos );
	ai->ignoreObstacle( goalObject );
	ai->m_commandInterface.aiMoveToPosition( &goalPos, CMD_FROM_AI );
	return STATE_SUCCESS;
}
