// cl: /DNDEBUG /MD /EHsc
// readable body of ?doTeamGarrisonSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doUnitGarrisonSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class AIGroup;
class AIUpdateInterface;
class Object;
class Player;
class Team;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
	virtual Object *getUnitNamedByValue(AsciiString) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0; virtual void slot65() = 0; virtual void slot66() = 0; virtual void slot67() = 0;
	virtual void slot68() = 0; virtual void slot69() = 0; virtual void slot70() = 0; virtual void slot71() = 0;
	virtual void slot72() = 0; virtual void slot73() = 0; virtual void slot74() = 0; virtual void slot75() = 0;
	virtual PlayerMaskType getPlayerWhoEntered() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	Player *getControllingPlayer() const;
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Bool isKindOf(KindOfType kind) const
	{
		return ((const Thing *)this)->isKindOf(kind);
	}

private:
	unsigned char m_unreconstructed_00[0x1fc];
	ContainModuleInterface *m_contain;
	unsigned char m_unreconstructed_200[4];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	PlayerMaskType getPlayerMask() const { return 1 << m_playerIndex; }

private:
	unsigned char m_unreconstructed_00[0x24];
	int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
	void getTeamAsAIGroup(AIGroup *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupEnter(Object *, CommandSourceType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void slot00() = 0;

private:
	unsigned char m_unreconstructed_04[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiEnter(Object *, CommandSourceType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamGarrisonSpecificBuilding(const AsciiString &, const AsciiString &);
	void doUnitGarrisonSpecificBuilding(const AsciiString &, const AsciiString &);
};

// ?doTeamGarrisonSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamGarrisonSpecificBuilding(
	const AsciiString &teamName, const AsciiString &buildingName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam) {
		return;
	}

	Object *theBuilding = TheScriptEngine->getUnitNamedByValue(buildingName);
	if (!theBuilding) {
		return;
	}

	if (!theBuilding->getContain()) {
		return;
	}
	PlayerMaskType player = theBuilding->getContain()->getPlayerWhoEntered();

	if (!(theBuilding->isKindOf(KINDOF_STRUCTURE) &&
		(player == 0) || (player == theTeam->getControllingPlayer()->getPlayerMask()))) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	theTeam->getTeamAsAIGroup(theGroup);
	theGroup->groupEnter(theBuilding, CMD_FROM_SCRIPT);
}

// ?doUnitGarrisonSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doUnitGarrisonSpecificBuilding(
	const AsciiString &unitName, const AsciiString &buildingName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit) {
		return;
	}

	Object *theBuilding = TheScriptEngine->getUnitNamedByValue(buildingName);
	if (!theBuilding) {
		return;
	}

	ContainModuleInterface *contain = theBuilding->getContain();
	if (!contain) {
		return;
	}

	PlayerMaskType player = contain->getPlayerWhoEntered();
	if (!((theBuilding->isKindOf(KINDOF_STRUCTURE) && (player == 0)) ||
		(player == theUnit->getControllingPlayer()->getPlayerMask()))) {
		return;
	}

	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai) {
		return;
	}

	ai->aiEnter(theBuilding, CMD_FROM_SCRIPT);
}
