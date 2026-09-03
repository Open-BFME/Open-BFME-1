// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class Object;
class ScriptActionParameter;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Object *resolveUnit(ScriptActionParameter *) = 0;
};

class ExperienceLevelSystem
{
public:
	void gainLevel(Object *, Bool);
};

extern ScriptEngine *TheScriptEngine;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doUnitGainLevel(ScriptActionParameter *, Bool);
};

// ?doUnitGainLevel@ScriptActions@@IAEXPAVScriptActionParameter@@_N@Z
void ScriptActions::doUnitGainLevel(
	ScriptActionParameter *parameter, Bool showExperienceFX)
{
	Object *object = TheScriptEngine->resolveUnit(parameter);
	if (object) {
		TheExperienceLevelSystem->gainLevel(object, showExperienceFX);
	}
}
