// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// readable body of ?doTeamUseCommandButtonAbility@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The three readable command-button actions:
//
//   0x002F4A20  doTeamUseCommandButtonAbility  arm 245, TEAM_USE_COMMANDBUTTON_ABILITY
//   0x002F54C0  doTeamUseCommandButtonOnNamed  the same, aimed at a named unit
//   0x002F6D70  doNamedSetAutoAbility          NAME_SET_AUTO_ABILITY
//
// The first two resolve the team at slot 17, ask ControlBar for the button by
// name, and hand it to the team's AIGroup. The on-named form does more first: it
// works out which member of the group is the source -- by special-power id when
// the button has a template, by command type otherwise -- and asks the button
// whether it is valid to use on the target before issuing the order.
//
// doNamedSetAutoAbility takes the third route to the same ControlBar: it finds
// the unit's AutoAbilityBehavior module by name key, then walks the unit's own
// command set looking for the button before toggling it, which is why it is the
// only one here that needs findCommandSet.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class AIGroup;
class CommandButton;
class Object;
class Team;
struct Coord3D;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

// Slot 27 takes the unit name by value through this wrapper, where slot 26
// takes it by reference.
class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride) {
			return m_nextOverride->friend_getFinalOverride();
		}
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride) {
			return m_nextOverride->friend_getFinalOverride();
		}
		return this;
	}

private:
	void *m_memoryPoolVTable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	UnsignedInt getID() const
	{
		return getFinalOverride()->m_id;
	}

private:
	const SpecialPowerTemplate *getFinalOverride() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}
	AsciiString m_name;
	UnsignedInt m_id;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	Bool isValidToUseOn(const Object *, const Object *, const Coord3D *, CommandSourceType) const;

private:
	unsigned char m_beforeCommand[0x10];
	GUICommandType m_command;
	unsigned char m_beforeSpecialPower[0x20];
	const SpecialPowerTemplate *m_specialPower;
};

class Module
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Module *findModule(NameKeyType key) const;
	const AsciiString &getCommandSetString() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class AutoAbilityBehavior
{
};

class BfmeArgVSJ
{
};

class BfmeOwnVSJ
{
public:
	void bfmeApplyVSJ(BfmeArgVSJ *commandButton, char enabled);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

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
	virtual Object *getUnitNamed(const AsciiString &) = 0;
	virtual Object *getUnitNamedByValue(BfmeAsciiStringArg name) = 0;
};

// The name doNamedSetAutoAbility's file gave this same vtable when all it
// needed was slot 27.
typedef ScriptEngine ScriptEngineByValue;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupDoCommandButton(const CommandButton *button, CommandSourceType cmd);
	void groupDoCommandButtonAtObject(const CommandButton *, Object *, CommandSourceType);
	Object *getSpecialPowerSourceObject(UnsignedInt);
	Object *getCommandButtonSourceObject(GUICommandType);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern AI *TheAI;
extern ControlBar *TheControlBar;
extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamUseCommandButtonAbility(const AsciiString &team,
		const AsciiString &ability);
	void doTeamUseCommandButtonOnNamed(
		const AsciiString &, const AsciiString &, const AsciiString &);
	void doNamedSetAutoAbility(const AsciiString &unitName,
		const AsciiString &commandButtonName, Bool enabled);
};

void ScriptActions::doTeamUseCommandButtonAbility(const AsciiString &team,
	const AsciiString &ability)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (theTeam)
	{
		const CommandButton *commandButton = TheControlBar->findCommandButton(ability);
		if (commandButton)
		{
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				theTeam->getTeamAsAIGroup(theGroup);
				theGroup->groupDoCommandButton(commandButton, CMD_FROM_SCRIPT);
			}
		}
	}
}

// ?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doTeamUseCommandButtonOnNamed(
	const AsciiString &teamName, const AsciiString &commandAbility, const AsciiString &unitName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton) {
		return;
	}

	Object *srcObj = 0;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(
			commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if (!srcObj) {
		return;
	}

	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	if (commandButton->isValidToUseOn(srcObj, obj, 0, CMD_FROM_SCRIPT)) {
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}

// ?doNamedSetAutoAbility@ScriptActions@@IAEXABVAsciiString@@0_N@Z
void ScriptActions::doNamedSetAutoAbility(
	const AsciiString &unitName, const AsciiString &commandButtonName, Bool enabled )
{
	Object *object = TheScriptEngine->getUnitNamedByValue( unitName );
	if ( object )
	{
		static NameKeyType autoAbilityBehaviorKey =
			TheNameKeyGenerator->nameToKey( "AutoAbilityBehavior" );
		AutoAbilityBehavior *behavior = (AutoAbilityBehavior *)
			object->findModule( autoAbilityBehaviorKey );
		if ( behavior )
		{
			const CommandButton *commandButton =
				TheControlBar->findCommandButton( commandButtonName );
			if ( commandButton &&
				*(const unsigned char *)((const char *)commandButton + 0x158) )
			{
				const CommandSet *commandSet =
					TheControlBar->findCommandSet( object->getCommandSetString() );
				if ( commandSet )
				{
					for ( Int i = 0; i < 20; ++i )
					{
						if ( commandButton == commandSet->getCommandButton( i ) )
						{
							((BfmeOwnVSJ *)behavior)->bfmeApplyVSJ(
								(BfmeArgVSJ *)commandButton, enabled );
						}
					}
				}
			}
		}
	}
}
