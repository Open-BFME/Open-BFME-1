// cl: /DNDEBUG /MD /EHsc
// readable body of ?doTeamDelete@ScriptActions@@IAEXABVAsciiString@@_N@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamKill@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamStopSequentialScript@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamSpinForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doCreateTeamFromCapturedUnits@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doGuardSupplyCenter@ScriptActions@@IAEXABVAsciiString@@H@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doBuildTeam@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Ten actions that look a team up by name and do one thing to it:
//
//   0x002F3790  doBuildTeam                   build the prototype's team
//   0x002F37E0  doRecruitTeam                 recruit a prototype near a team
//   0x002F3920  doTeamDelete                  Team::deleteTeam
//   0x002F3B60  doTeamKill                    Team::killTeam
//   0x002F4FF0  doTeamStopSequentialScript    drop its sequential scripts
//   0x002F5470  doTeamSpinForFramecount       set its sequential timer
//   0x002F5730  doCreateTeamFromCapturedUnits the lookup and nothing else
//   0x002F5880  doTeamEmoticon                an emoticon over the group
//   0x002F5960  doGuardSupplyCenter           through the controlling player
//   0x002F5B80  doTeamUpgrade                 Team::giveUpgrade
//
// Every one of them was a separate file that spent seventy-odd lines restating
// AsciiString, the by-value string wrapper and the ScriptEngine vtable in order
// to reach a lookup at slot 16 or 17, and then did its one line of work. Written
// once, that preamble is seventy lines instead of seven hundred, and the ten
// one-liners sit next to each other where the family is legible.

typedef bool Bool;
typedef int Int;
typedef float Real;

class AIGroup;
class Player;
class Team;
class TeamPrototype;
class UpgradeTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

private:
	struct Header
	{
		int refCount;
		unsigned short length;
	};
	Header *m_data;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

// Slots 16 and 17 both take the name by value through this wrapper.
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void deleteTeam(Bool);
	void killTeam();
	void giveUpgrade(const UpgradeTemplate *);
	void getTeamAsAIGroup(AIGroup *);
	Player *getControllingPlayer() const;
	Coord3D *getEstimateTeamPosition(Coord3D *) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void guardSupplyCenter(Team *, Int);
	void recruitSpecificTeam(TeamPrototype *, Real, const Coord3D *);
	void buildSpecificTeam(TeamPrototype *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupSetEmoticon(const AsciiString &, Int);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &) const;
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
	virtual TeamPrototype *getTeamPrototypeNamed(BfmeAsciiStringArg) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;

	// Not slots.
	void setSequentialTimer(Team *, Int);
	void removeAllSequentialScripts(Team *);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern UpgradeCenter *TheUpgradeCenter;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doBuildTeam(const AsciiString &);
	void doRecruitTeam(const AsciiString &, Real, const AsciiString &);
	void doTeamDelete(const AsciiString &, Bool);
	void doTeamKill(const AsciiString &);
	void doTeamStopSequentialScript(const AsciiString &);
	void doTeamSpinForFramecount(const AsciiString &, Int);
	void doCreateTeamFromCapturedUnits(const AsciiString &, const AsciiString &);
	void doTeamEmoticon(const AsciiString &, const AsciiString &, Real);
	void doGuardSupplyCenter(const AsciiString &, Int);
	void doTeamUpgrade(const AsciiString &, const AsciiString &);
};

// ?doBuildTeam@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doBuildTeam(const AsciiString &teamName)
{
	TeamPrototype *teamPrototype = TheScriptEngine->getTeamPrototypeNamed(teamName);
	if (teamPrototype) {
		Player *player = teamPrototype->getControllingPlayer();
		if (player) {
			player->buildSpecificTeam(teamPrototype);
		}
	}
}

// ?doRecruitTeam@ScriptActions@@IAEXABVAsciiString@@M0@Z
void ScriptActions::doRecruitTeam(
	const AsciiString &teamName, Real recruitRadius, const AsciiString &recruitAtTeamName)
{
	TeamPrototype *teamPrototype = TheScriptEngine->getTeamPrototypeNamed(teamName);
	if (!teamPrototype) {
		return;
	}

	Player *player = teamPrototype->getControllingPlayer();
	if (!player) {
		return;
	}

	if (!recruitAtTeamName.isEmpty()) {
		Team *recruitAtTeam = TheScriptEngine->getTeamNamed(recruitAtTeamName, false);
		if (!recruitAtTeam) {
			return;
		}

		Coord3D position;
		recruitAtTeam->getEstimateTeamPosition(&position);
		player->recruitSpecificTeam(teamPrototype, recruitRadius, &position);
		return;
	}

	player->recruitSpecificTeam(teamPrototype, recruitRadius, 0);
}

// ?doTeamDelete@ScriptActions@@IAEXABVAsciiString@@_N@Z
void ScriptActions::doTeamDelete(const AsciiString &teamName, Bool ignoreDead)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team) {
		team->deleteTeam(ignoreDead);
	}
}

// ?doTeamKill@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamKill(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team) {
		team->killTeam();
	}
}

// ?doTeamStopSequentialScript@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamStopSequentialScript(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	TheScriptEngine->removeAllSequentialScripts(team);
}

// ?doTeamSpinForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doTeamSpinForFramecount(
	const AsciiString &teamName, Int waitForFrames)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	TheScriptEngine->setSequentialTimer(team, waitForFrames);
}

// ?doCreateTeamFromCapturedUnits@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doCreateTeamFromCapturedUnits(
	const AsciiString &, const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}
}

// ?doTeamEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z
void ScriptActions::doTeamEmoticon(
	const AsciiString &teamName, const AsciiString &emoticonName, Real duration)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	AIGroup *group = TheAI->createGroup();
	if (!group) {
		return;
	}

	team->getTeamAsAIGroup(group);
	Int frames = (Int)(duration * 30.0f);
	group->groupSetEmoticon(emoticonName, frames);
}

// ?doGuardSupplyCenter@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doGuardSupplyCenter(const AsciiString &teamName, Int supplies)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	Player *player = team->getControllingPlayer();
	if (!player) {
		return;
	}

	player->guardSupplyCenter(team, supplies);
}

// ?doTeamUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamUpgrade(
	const AsciiString &teamName, const AsciiString &upgradeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeName);
	if (team && upgrade) {
		team->giveUpgrade(upgrade);
	}
}
