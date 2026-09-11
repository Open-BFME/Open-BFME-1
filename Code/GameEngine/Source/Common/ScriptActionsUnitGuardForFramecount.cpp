// cl: /DNDEBUG /MD /O2 /EHsc
typedef bool Bool;
typedef int Int;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum GuardMode { GUARDMODE_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

struct Coord3D { int x; int y; int z; };
class AsciiString { char *m_data; };

class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *, GuardMode, CommandSourceType);
};

class AIUpdateInterface
{
	unsigned char m_pad[0x20];
public:
	AICommandInterface m_command;
};

class Object
{
public:
	unsigned char m_beforePosition[0x38];
	Coord3D m_position;
	unsigned char m_beforeAI[0x204 - 0x44];
	AIUpdateInterface *m_ai;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
};

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
	void setSequentialTimer(Object *, Int);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doUnitGuardForFramecount(const AsciiString &, Int, Bool);
};

void ScriptActions::doUnitGuardForFramecount(const AsciiString &unitName,
	Int framecount, Bool seconds)
{
	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (!object)
		return;
	AIUpdateInterface *ai = object->getAIUpdateInterface();
	if (!ai)
		return;

	int x = object->m_position.x;
	int y = object->m_position.y;
	_ReadWriteBarrier();
	Coord3D position;
	position.x = x;
	position.z = object->m_position.z;
	position.y = y;
	ai->m_command.aiGuardPosition(&position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);

	if (seconds)
		TheScriptEngine->setSequentialTimer(object, framecount * 5);
	else
		TheScriptEngine->setSequentialTimer(object, framecount);
}
