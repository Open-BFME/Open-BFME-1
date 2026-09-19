// cl: /DNDEBUG /MD /EHsc
// readable body of ?onStructureConstructionComplete@Player@@QAEXPAVObject@@0_N@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?buildSpecificTeam@Player@@QAEXPAVTeamPrototype@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?setPlayerType@Player@@QAEXW4PlayerType@@_N@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

// The player's AIPlayer at Player+0x220: the method that makes it, and the
// three that call into it through its vtable.
//
//   0x000C9240  setPlayerType                    makes it, or destroys it
//   0x000C9600  onStructureConstructionComplete  onStructureProduced   slot 8
//   0x000C9740  buildSpecificTeam                buildSpecificAITeam   slot 9
//   0x000C9790  recruitSpecificTeam              recruitSpecificAITeam slot 10
//
// They sat in three files, and each one declared AIPlayer's vtable cut off
// immediately after the slot it happened to call: eight slots then
// onStructureProduced, nine then buildSpecificAITeam, ten then
// recruitSpecificAITeam. Three files, three different pictures of one vtable,
// none of them wrong and none of them able to say so. Declared once, the three
// slots line up and the numbering checks itself: what the recruit file called
// its slot 9 is the build file's buildSpecificAITeam, and what the build file
// called its slot 8 is the construction file's onStructureProduced.
//
// The AI pointer had drifted only in spelling -- m_ai in three files and
// PlayerAI in the fourth, at the same +0x220 -- and the padding before it was
// spelled four ways for the same 0x220 bytes. Only setPlayerType named
// anything inside that run: the player type at +0x2C.
//
// AIPlayer itself was modelled twice and disjointly, which is the second thing
// this file fixes. The three callers gave it a vtable and no size; setPlayerType,
// which is the one that news it, gave it 0x78 opaque bytes and no vtable, and
// typed the member as an unrelated "BfmeOwnedAI" carrying just a virtual
// destructor so that its delete would dispatch. Neither half is wrong and
// together they say the whole thing: AIPlayer is a 0x78-byte object whose first
// four bytes are the vptr, whose slot 0 is the destructor setPlayerType deletes
// through, and whose slots 8 to 10 are what the other three call. The body below
// is therefore 0x78 minus the pointer, and BfmeOwnedAI is gone.
//
// AISkirmishPlayer stays 0xa0 opaque bytes. It is constructed and immediately
// cast, and nothing here proves it shares AIPlayer's vtable, so nothing claims
// it does.
//
// notifyOfObjectCreationOrDestruction is not a Player method and does not
// belong to this family; it rides along because it is the callee that
// onStructureConstructionComplete opens with, exactly as it did in that
// method's own file. It stays __declspec(noinline) because retail calls it.
//
// On flags, the four disagreed and the probe went both ways: the two forwarders
// byte-verify unchanged under /DNDEBUG /MD /EHsc, and the other two byte-verify
// unchanged under /O2 /Ob0 ... -- except setPlayerType, which does NOT survive
// /Ob0. It needs getAiData() inlined. So the /EHsc line is the one all four
// share, and it is the one this file carries.

typedef bool Bool;
typedef float Real;

struct Coord3D;
class Object;
class TeamPrototype;
class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
enum PlayerType
{
	PLAYER_COMPUTER = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	AIPlayer(Player *player);
	virtual ~AIPlayer();							// slot 0, the deleting destructor
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void onStructureProduced(Object *, Object *);				// slot 8, vtable+0x20
	virtual void buildSpecificAITeam(TeamPrototype *, Bool);			// slot 9, vtable+0x24
	virtual void recruitSpecificAITeam(TeamPrototype *, Real, const Coord3D *);	// slot 10, vtable+0x28

private:
	unsigned char m_bfmeBody[0x78 - 4];					// with the vptr, retail's 0x78
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AISkirmishPlayer.h
class AISkirmishPlayer
{
public:
	AISkirmishPlayer(Player *player);

private:
	unsigned char m_bfmeBody[0xa0];
};

struct BfmeAIData
{
	unsigned char m_bfmeBeforeForceSkirmishAI[0x65];
	bool m_forceSkirmishAI;
};

struct BfmeAI
{
	const BfmeAIData *getAiData() { return m_data; }

	unsigned char m_bfmeBeforeData[0x14];
	BfmeAIData *m_data;
};

extern "C" BfmeAI *TheAIParseDefinitionAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	__declspec(noinline) void notifyOfObjectCreationOrDestruction();

private:
	char Pad[0x170D8];
	unsigned int FrameObjectCountChanged;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
private:
	char Pad[0x3C];

public:
	unsigned int Frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *);
	void addObjectToPathfindMap(Object *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
private:
	char Pad[0x0C];

public:
	Pathfinder *PathfinderInstance;
};

class StructureCompletionInterface
{
public:
	virtual void Slot0();
	virtual void Slot1();
	virtual void Slot2();
	virtual void onConstructionComplete(Object *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void friend_adjustPowerForPlayer(bool);
	StructureCompletionInterface *getStructureCompletionInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
private:
	char Pad[0x24];

public:
	bool UIDirty;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	unsigned char m_bfmeBeforeType[0x2c];
	PlayerType m_playerType;						// this+0x2C
	unsigned char m_bfmeBeforeAI[0x220 - 0x30];
	AIPlayer *m_ai;								// this+0x220

public:
	void setPlayerType(PlayerType type, bool skirmish);
	void onStructureConstructionComplete(Object *, Object *, bool);
	void buildSpecificTeam(TeamPrototype *);
	void recruitSpecificTeam(TeamPrototype *, Real, const Coord3D *);
};

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern ControlBar *TheControlBar;

// ?notifyOfObjectCreationOrDestruction@ScriptEngine@@QAEXXZ
__declspec(noinline) void ScriptEngine::notifyOfObjectCreationOrDestruction()
{
	FrameObjectCountChanged = TheGameLogic->Frame;
}

// ?setPlayerType@Player@@QAEXW4PlayerType@@_N@Z
void Player::setPlayerType(PlayerType type, bool skirmish)
{
	m_playerType = type;

	delete m_ai;
	m_ai = 0;

	if (type == PLAYER_COMPUTER)
	{
		if (skirmish || TheAIParseDefinitionAI->getAiData()->m_forceSkirmishAI)
			m_ai = reinterpret_cast<AIPlayer *>(new AISkirmishPlayer(this));
		else
			m_ai = new AIPlayer(this);
	}
}

// ?onStructureConstructionComplete@Player@@QAEXPAVObject@@0_N@Z
void Player::onStructureConstructionComplete(Object *builder, Object *structure, bool)
{
	TheScriptEngine->notifyOfObjectCreationOrDestruction();
	TheAI->PathfinderInstance->removeObjectFromPathfindMap(structure);
	TheAI->PathfinderInstance->addObjectToPathfindMap(structure);
	structure->friend_adjustPowerForPlayer(true);

	if (m_ai != 0) {
		m_ai->onStructureProduced(builder, structure);
	}

	if (TheControlBar != 0) {
		TheControlBar->UIDirty = true;
	}

	if (structure->getStructureCompletionInterface() != 0) {
		structure->getStructureCompletionInterface()->onConstructionComplete(builder);
	}
}

// ?buildSpecificTeam@Player@@QAEXPAVTeamPrototype@@@Z
void Player::buildSpecificTeam(TeamPrototype *teamPrototype)
{
	if (m_ai) {
		m_ai->buildSpecificAITeam(teamPrototype, true);
	}
}

// ?recruitSpecificTeam@Player@@QAEXPAVTeamPrototype@@MPBUCoord3D@@@Z
void Player::recruitSpecificTeam(
	TeamPrototype *teamPrototype, Real recruitRadius, const Coord3D *position)
{
	if (m_ai) {
		m_ai->recruitSpecificAITeam(teamPrototype, recruitRadius, position);
	}
}
