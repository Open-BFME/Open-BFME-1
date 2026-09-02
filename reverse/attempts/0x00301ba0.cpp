// ?doNamedGuard@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD
// ScriptActions::doNamedGuard. ZH also calls chooseLocomotorSet; retail
// does not. AIUpdateInterface's AICommandInterface subobject is at +0x20.
// Object position at +0x38, m_ai at +0x204.

typedef float Real;
typedef int Int;

struct Coord3D { Real x, y, z; };

enum GuardMode { GUARDMODE_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AsciiString
{
	char *m_data;
};

class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource);
};

class AIPad20
{
	unsigned char m_pad[0x20];
};

class AIUpdateInterface : public AIPad20, public AICommandInterface
{
};

class Object
{
public:
	void leaveGroup();
	unsigned char m_beforePos[0x38];
	Coord3D m_pos;
	unsigned char m_betweenPosAndAI[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual void _se_17() = 0;
	virtual void _se_18() = 0;
	virtual void _se_19() = 0;
	virtual void _se_20() = 0;
	virtual void _se_21() = 0;
	virtual void _se_22() = 0;
	virtual void _se_23() = 0;
	virtual void _se_24() = 0;
	virtual void _se_25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doNamedGuard(const AsciiString& unitName);
};

void ScriptActions::doNamedGuard(const AsciiString& unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit) {
		return;
	}
	AIUpdateInterface *aiUpdate = theUnit->m_ai;
	if (!aiUpdate) {
		return;
	}
	theUnit->leaveGroup();
	Int z = *(Int *)&theUnit->m_pos.z;
	Int x = *(Int *)&theUnit->m_pos.x;
	Int y = *(Int *)&theUnit->m_pos.y;
	Coord3D position;
	*(Int *)&position.x = x;
	*(Int *)&position.y = y;
	*(Int *)&position.z = z;
	aiUpdate->aiGuardPosition(&position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
}
