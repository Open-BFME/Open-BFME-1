// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@TurretAIIdleState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// readable body of ?setTurretTargetObject@TurretAI@@QAEXPAVObject@@_N@Z: Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// readable body of ?startRotOrPitchSound@TurretAI@@AAEXXZ: Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
//
// The three TurretAI bodies that reach out through the turret -- to the owning
// Object and its AI module, and to the turret's own state machine:
//
//   TurretAIIdleState::onEnter    schedule the next idle scan off the owner's AI
//   TurretAI::setTurretTargetObject  retarget through the machine
//   TurretAI::startRotOrPitchSound   the owner's per-unit turret loop sound
//
// They sat in three files, and each described TurretAI, Object and the machine
// only as far as its own body reached. Side by side the three descriptions
// agree and complete each other, which is the point of merging them:
//
//   TurretAI       +0x08 module data, +0x0C which turret, +0x10 owner,
//                  +0x14 machine, +0x20 the rot/pitch sound, +0x94 the
//                  victim's initial team, +0x98 has-target
//   Object         +0x74 id, +0x204 AI module, +0x23C team, +0x344 status
//   StateMachine   +0x10 owner, +0x1C current state, and the turret machine's
//                  own back-pointer to the turret at +0x44
//
// Nothing here is inferred from the union: every field is one the file it came
// from already had at that offset. What the merge adds is that they are one
// object -- the idle state's "Machine->Owner" and the retarget body's
// "Machine->CurrentState" are the same machine, two fields apart.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_RETURN_ZERO = 0
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

// An enum, not an integer typedef: AudioEventRTS::setObjectID is an external
// call, so its parameter type is part of the symbol this TU links against.
enum ObjectID {
	INVALID_OBJECT_ID = 0
};

typedef unsigned int AudioHandle;

class Weapon;
class TurretAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString {
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS {
public:
	AudioEventRTS &operator=(const AudioEventRTS &that);
	void setPlayingHandle(AudioHandle handle);
	void setObjectID(ObjectID id);
	Bool isCurrentlyPlaying() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate {
public:
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;
};

#define TEN_VIRTUALS(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); \
	virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); \
	virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9()

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	TEN_VIRTUALS(a);
	TEN_VIRTUALS(b);
	TEN_VIRTUALS(c);
	TEN_VIRTUALS(d);
	TEN_VIRTUALS(e);
	TEN_VIRTUALS(f);
	TEN_VIRTUALS(g);
	TEN_VIRTUALS(h);
	TEN_VIRTUALS(i);
	TEN_VIRTUALS(j);
	TEN_VIRTUALS(k);
	virtual void l0();
	virtual void l1();
	virtual void l2();
	virtual void l3();
	virtual void l4();
	virtual void removeTargeter(ObjectID, Bool);

	void resetNextMoodCheckTime();

	char Pad0[0x1F0 - 4];
	int TurretSync;						// +0x1F0
	char Pad1[8];
	UnsignedInt NextIdleMoodTargetFrame;			// +0x1FC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
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
	virtual const ThingTemplate *getTemplate() const = 0;

	char Pad0[0x3C - 4];
	UnsignedInt KindOf;					// +0x3C
	char Pad1[0x34];
	ObjectID ID;						// +0x74
	char Pad2[0x18C];
	AIUpdateInterface *AI;					// +0x204
	char Pad3[0x34];
	void *Team;						// +0x23C
	char Pad4[0x104];
	unsigned char Status;					// +0x344

	Weapon *getCurrentWeapon(WeaponSlotType *slot);

	__forceinline ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const unsigned char *>(this) + 0x74);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager {
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
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual void slot0D() = 0;
	virtual void slot0E() = 0;
	virtual void slot0F() = 0;
	virtual void slot10() = 0;
	virtual AudioHandle addAudioEvent(AudioEventRTS *event) = 0;
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
struct TurretAIData
{
	char Pad0[0x3C];
	UnsignedInt ControlledWeaponSlots;			// +0x3C
	char Pad1[0x48 - 0x40];
	int MinIdleScanInterval;				// +0x48
	int MaxIdleScanInterval;				// +0x4C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
struct State
{
	void *VTable;
	int ID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void d7();
	virtual void setState(int);
	virtual void d9();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void setGoalObject(Object *);

	char Pad0[0x10 - 4];
	Object *Owner;						// +0x10
	char Pad1[0x1C - 0x14];
	State *CurrentState;					// +0x1C

	Object *getGoalObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretStateMachine : public StateMachine
{
public:
	char Pad2[0x44 - 0x20];
	TurretAI *Turret;					// +0x44
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char Pad[0x3C];
	UnsignedInt Frame;					// +0x3C

	UnsignedInt getFrame() const { return Frame; }
};

extern GameLogic *TheGameLogic;
extern char TurretAIFileName[];
int GetGameLogicRandomValue(int, int, char *, int);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAI
{
public:
	void setTurretTargetObject(Object *victim, Bool forceAttacking);

	int getMinIdleScanInterval() const { return Data->MinIdleScanInterval; }
	int getMaxIdleScanInterval() const { return Data->MaxIdleScanInterval; }

private:
	void startRotOrPitchSound();

public:
	char Pad0[8];
	const TurretAIData *Data;				// +0x08
	int WhichTurret;					// +0x0C
	Object *Owner;						// +0x10
	TurretStateMachine *Machine;				// +0x14
	char Pad1[0x20 - 0x18];
	AudioEventRTS m_turretRotOrPitchSound;			// +0x20
	char Pad2[0x94 - 0x21];
	void *VictimInitialTeam;				// +0x94
	int Target;						// +0x98
	char Pad3[0x0E];
	unsigned char ForceAttacking;				// +0xAA
	unsigned char TargetWasSetByIdleMood;			// +0xAB
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAIIdleState
{
public:
	virtual StateReturnType onEnter();

private:
	char Pad0[0x18];
	TurretStateMachine *Machine;				// +0x1C
	char Pad1[4];
	UnsignedInt NextIdleScan;				// +0x24

	TurretAI *getTurretAI() const { return Machine->Turret; }
};

// ?onEnter@TurretAIIdleState@@UAE?AW4StateReturnType@@XZ
StateReturnType TurretAIIdleState::onEnter()
{
	AIUpdateInterface *ai = Machine->Owner->AI;
	if (ai != 0) {
		ai->resetNextMoodCheckTime();
		if (ai->TurretSync == Machine->Turret->WhichTurret) {
			ai->TurretSync = -1;
		}
	}

	UnsignedInt now = TheGameLogic->getFrame();
	int delay = GetGameLogicRandomValue(
		getTurretAI()->getMinIdleScanInterval(),
		getTurretAI()->getMaxIdleScanInterval(),
		TurretAIFileName, 0x4FE);
	NextIdleScan = now + delay;

	TurretAI *turret = Machine->Turret;
	AIUpdateInterface *turret_ai = turret->Owner->AI;
	UnsignedInt wake_frame = turret_ai != 0
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

// ?setTurretTargetObject@TurretAI@@QAEXPAVObject@@_N@Z
void TurretAI::setTurretTargetObject(Object *victim, Bool forceAttacking)
{
	WeaponSlotType slot;
	if (victim == 0 || (victim->Status & 1) != 0 ||
		Owner->getCurrentWeapon(&slot) == 0 ||
		(Data->ControlledWeaponSlots & (1u << slot)) == 0) {
		victim = 0;
	}

	if (victim == 0 && Target == 1 && Machine != 0) {
		Object *self = Owner;
		Object *target = Machine->getGoalObject();
		if (self != 0 && target != 0) {
			AIUpdateInterface *targetAI = target->AI;
			if (targetAI != 0) {
				targetAI->removeTargeter(self->ID, false);
			}
		}
	}

	Machine->setGoalObject(victim);
	Target = victim != 0;
	TargetWasSetByIdleMood = 0;
	ForceAttacking = (unsigned char)forceAttacking;

	int stateID = Machine->CurrentState != 0 ? Machine->CurrentState->ID : 999999;
	if (victim != 0) {
		if (stateID != 2 && stateID != 3) {
			Machine->setState(2);
		}
		VictimInitialTeam = victim->Team;
	} else {
		if (stateID == 2 || stateID == 3) {
			Machine->setState(5);
		}
		VictimInitialTeam = 0;
	}
}

// ?startRotOrPitchSound@TurretAI@@AAEXXZ
void TurretAI::startRotOrPitchSound()
{
	if (!m_turretRotOrPitchSound.isCurrentlyPlaying())
	{
		const ThingTemplate *thingTemplate = Owner->getTemplate();
		if (thingTemplate)
		{
			{
				AsciiString soundName("TurretMoveLoop");
				m_turretRotOrPitchSound = *thingTemplate->getPerUnitSound(soundName);
			}
			m_turretRotOrPitchSound.setObjectID(Owner->getID());
			m_turretRotOrPitchSound.setPlayingHandle(TheAudio->addAudioEvent(&m_turretRotOrPitchSound));
		}
	}
}
