// cl: /DNDEBUG /MD /EHsc

#include "../../../Include/Common/ScalarTypes.h"


#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

class ScriptActionParameter
{
	friend class ScriptActions;

private:
	unsigned char m_unmodelled[0x10];
	AsciiString m_string;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Int getId() const { return m_id; }

private:
	unsigned char m_unmodelled[0x74];
	Int m_id;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
};

// The gate setter is reached through ILT 0x0000E6B5, the ledger's 5-byte row
// ?j_0000e6b5@@YAXXZ (symbols.csv pins ?bfmeSetNeedsGateOpenRaw@Team@@QAEXHH@Z
// there and nothing defines it), through a raw pointer bridge that keeps the
// thiscall shape.
void j_0000e6b5();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
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

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamNeedsOpenGate(
		ScriptActionParameter *, ScriptActionParameter *, Bool);
};

// ?doTeamNeedsOpenGate@ScriptActions@@IAEXPAVScriptActionParameter@@0_N@Z
void ScriptActions::doTeamNeedsOpenGate(ScriptActionParameter *teamParameter,
	ScriptActionParameter *gateParameter, Bool needsOpen)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParameter->m_string, false);
	if (!team) {
		return;
	}

	Object *gate = TheScriptEngine->resolveUnit(gateParameter);
	if (!gate) {
		return;
	}

	union { void (*raw)(void); void (Team::*typed)(Int, Int); } setNeedsGateOpen;
	setNeedsGateOpen.raw = &j_0000e6b5;
	(team->*setNeedsGateOpen.typed)(gate->getId(), *(const Int *)&needsOpen);
}
