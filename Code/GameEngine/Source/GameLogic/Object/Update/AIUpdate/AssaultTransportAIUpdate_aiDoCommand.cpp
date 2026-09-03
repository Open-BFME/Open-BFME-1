// cl: /DNDEBUG /MD /EHsc
// readable body of ?aiDoCommand@AssaultTransportAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp
// Open-BFME: AssaultTransportAIUpdate::aiDoCommand, retail 0x002B4AB0.
//
// The command values for this small transport-specific router are 5 (idle),
// 0x0b/0x39 (attack object), and 0x0f (attack move).  The implementation is
// entered through AICommandInterface's secondary subobject at +0x20; the
// local layout consequently makes the derived transport fields appear at the
// retail offsets used by the body.

typedef bool Bool;
typedef int Int;
typedef int ObjectID;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
public:
	Int m_cmd;
	Int m_cmdSource;
	Coord3D m_pos;
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum AICommandType
{
	AICMD_IDLE = 5,
	AICMD_ATTACK_OBJECT = 0x0b,
	AICMD_ATTACKMOVE_TO_POSITION = 0x0f
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void updateModuleAnchor() = 0;

private:
	char m_pad04[0x1c];
};

class AssaultTransportAIUpdateBase
    : public UpdateModule, public AICommandInterface
{

protected:
	void call_0002105d();

private:
	char m_pad24[0x340 - 0x24];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public AssaultTransportAIUpdateBase
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssaultTransportAIUpdate.h
class AssaultTransportAIInterface
{
public:
	virtual void beginAssault(const Object *object) const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssaultTransportAIUpdate.h
class AssaultTransportAIUpdate : public AIUpdateInterface,
	public AssaultTransportAIInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void retrieveMembers();

private:
	ObjectID m_memberIDs[10];
	Bool m_memberHealing[10];
	Bool m_newMember[10];
	Coord3D m_attackMoveGoalPos;
	ObjectID m_designatedTarget;
	Int m_state;
	Int m_framesRemaining;
	Int m_currentMembers;
	Bool m_isAttackMove;
	Bool m_isAttackObject;
	Bool m_newOccupantsAreNewMembers;
};

// ?aiDoCommand@AssaultTransportAIUpdate@@UAEXPBUAICommandParms@@@Z
void AssaultTransportAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	if (parms->m_cmdSource != CMD_FROM_AI)
	{
		switch (parms->m_cmd)
		{
		case AICMD_ATTACKMOVE_TO_POSITION:
			call_0002105d();
			m_attackMoveGoalPos = parms->m_pos;
			m_isAttackMove = true;
			break;

		case AICMD_ATTACK_OBJECT:
		case 0x39:
			call_0002105d();
			m_isAttackObject = true;
			break;

		case AICMD_IDLE:
			{
				m_designatedTarget = 0;
				retrieveMembers();
				call_0002105d();
			}
			break;

		default:
			call_0002105d();
			break;
		}
	}

	AIUpdateInterface::aiDoCommand(parms);
}
