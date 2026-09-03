// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: SpecialAbilityUpdate::startFacing, retail 0x002AA850, 154 bytes.
// The BFME AI command base is adjusted by 0x20 from the AI update object.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef Int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiFaceObject(Object *target, CommandSourceType cmdSource);
	void aiFacePosition(const Coord3D *pos, int cmdSource);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	AICommandInterface *getCommandInterface(void)
	{
		return reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI(void) const
	{
		return m_ai;
	}

private:
	unsigned char m_unreconstructed_000[0x204];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
	virtual void specialAbilityAnchor() = 0;
	void startFacing();

private:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_unreconstructed_00C[0xA0];
	ObjectID m_targetID;
	Coord3D m_targetPos;
	unsigned char m_unreconstructed_0BC[0x24];
	Bool m_facingInitiated;
};

// ?startFacing@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::startFacing()
{
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	Object *object = m_object;
	AIUpdateInterface *ai = object->getAI();
	if (!ai)
		return;

	AICommandInterface *commands = ai->getCommandInterface();
	commands->aiIdle(CMD_FROM_AI);
	m_facingInitiated = true;
	if (target)
	{
		commands->aiFaceObject(target, CMD_FROM_AI);
	}
	else if (m_targetPos.x || m_targetPos.y || m_targetPos.z)
	{
		commands->aiFacePosition(&m_targetPos, CMD_FROM_AI);
	}
}
