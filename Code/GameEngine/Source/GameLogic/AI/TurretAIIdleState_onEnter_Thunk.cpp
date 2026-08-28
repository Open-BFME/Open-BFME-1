// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@TurretAIIdleState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// Open-BFME5: retail-layout C++ conversion of TurretAIIdleState::onEnter.

enum StateReturnType
{
	STATE_RETURN_ZERO = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
private:
	char Pad0[0x1F0];

public:
	int TurretSync;
	char Pad1[8];
	unsigned int NextIdleMoodTargetFrame;

	void resetNextMoodCheckTime();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	char Pad[0x204];

public:
	AIUpdateInterface *AIUpdate;
};

class TurretModuleData
{
private:
	char Pad[0x48];

public:
	int MinIdleScanInterval;
	int MaxIdleScanInterval;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAI
{
private:
	char Pad0[8];

public:
	TurretModuleData *ModuleData;
	int WhichTurret;
	Object *Owner;

	int getMinIdleScanInterval() const { return ModuleData->MinIdleScanInterval; }
	int getMaxIdleScanInterval() const { return ModuleData->MaxIdleScanInterval; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretStateMachine
{
private:
	char Pad0[0x10];

public:
	Object *Owner;
	char Pad1[0x30];
	TurretAI *Turret;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
private:
	char Pad[0x3C];

public:
	unsigned int Frame;

	unsigned int getFrame() const { return Frame; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAIIdleState
{
public:
	virtual StateReturnType onEnter();

private:
	char Pad0[0x18];
	TurretStateMachine *Machine;
	char Pad1[4];
	unsigned int NextIdleScan;

	TurretAI *getTurretAI() const { return Machine->Turret; }
};

extern GameLogic *TheGameLogic;
extern char TurretAIFileName[];
int GetGameLogicRandomValue(int, int, char *, int);

StateReturnType TurretAIIdleState::onEnter()
{
	AIUpdateInterface *ai = Machine->Owner->AIUpdate;
	if (ai != 0) {
		ai->resetNextMoodCheckTime();
		if (ai->TurretSync == Machine->Turret->WhichTurret) {
			ai->TurretSync = -1;
		}
	}

	unsigned int now = TheGameLogic->getFrame();
	int delay = GetGameLogicRandomValue(
		getTurretAI()->getMinIdleScanInterval(),
		getTurretAI()->getMaxIdleScanInterval(),
		TurretAIFileName, 0x4FE);
	NextIdleScan = now + delay;

	TurretAI *turret = Machine->Turret;
	AIUpdateInterface *turret_ai = turret->Owner->AIUpdate;
	unsigned int wake_frame = turret_ai != 0
		? turret_ai->NextIdleMoodTargetFrame
		: TheGameLogic->Frame;

	if (wake_frame > NextIdleScan) {
		wake_frame = NextIdleScan;
	}
	if (wake_frame > 0x3FFFFFFF) {
		wake_frame = 0x3FFFFFFF;
	}
	now = TheGameLogic->Frame;
	if (wake_frame > now) {
		return (StateReturnType)(wake_frame - now);
	}
	return STATE_RETURN_ZERO;
}
