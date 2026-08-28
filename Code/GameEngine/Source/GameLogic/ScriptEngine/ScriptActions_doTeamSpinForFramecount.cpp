// cl: /DNDEBUG /MD /EHsc
// readable body of ?doTeamSpinForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME: ScriptActions::doTeamSpinForFramecount, retail 0x002F11E0, 38
// bytes.
//
// The reference's three lines, with `this` unused in both -- but over TWO
// globals, not one. The team comes from TheScriptEngine (0x00EF076C) through
// vtable slot 0x68; the second call goes to a different global entirely,
// 0x00EF0888, which is TheExperienceLevelSystem: GameEngine::init pushes the
// literal "TheExperienceLevelSystem" immediately before pushing that address,
// and the tail target 0x00381050 sits inside the same TU as the subsystem's
// constructor at 0x00381480.
//
// That is why an earlier landing of this body was retracted: it wrote
// TheScriptEngine for both calls, and the byte gate masks DIR32 sites so the
// wrong global went unnoticed. Writing the two globals separately is what makes
// the row honest. The member's own name is not recovered, so it is
// address-anchored on the class the evidence names.
//
// The pairing is also what makes the tail a jump: the team replaces the name in
// the incoming frame and the call reuses it.

typedef int Int;

class AsciiString;
class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual Team *getTeamNamed(const AsciiString &name) = 0;	// slot 26, vtable+0x68
};

extern ScriptEngine *TheScriptEngine;

class ExperienceLevelSystem
{
public:
	// The 139-byte body at 0x00381050, reached through the ILT at 0x00027237.
	void rva00381050(Team *team, Int frames);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamSpinForFramecount(const AsciiString &teamName, Int waitForFrames);
};

void ScriptActions::doTeamSpinForFramecount(const AsciiString &teamName, Int waitForFrames)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	TheExperienceLevelSystem->rva00381050(team, waitForFrames);
}
