// ?doUnitGuardForFramecount@ScriptActions@@IAEXABVAsciiString@@H_N@Z
// partial score=0.95 date=2026-09-11
typedef bool Bool;
typedef int Int;

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

struct Coord3D
{
	int x;
	int y;
	int z;
};

class AsciiString
{
	char *m_data;
};

class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *position, GuardMode guardMode,
		CommandSourceType commandSource);
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
	int m_positionX;
	int m_positionY;
	int m_positionZ;
	unsigned char m_beforeAI[0x204 - 0x44];
	AIUpdateInterface *m_ai;

};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;

	void setSequentialTimer(Object *object, Int frames);
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

	AIUpdateInterface *ai = object->m_ai;
	if (!ai)
		return;

	int x = object->m_positionX;
	int y = object->m_positionY;
	Coord3D position;
	position.y = y;
	position.x = x;
	position.z = object->m_positionZ;
	ai->m_command.aiGuardPosition(&position, GUARDMODE_NORMAL,
		CMD_FROM_SCRIPT);

	if (seconds)
		TheScriptEngine->setSequentialTimer(object, framecount * 5);
	else
		TheScriptEngine->setSequentialTimer(object, framecount);
}
