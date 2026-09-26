// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;
class Player;
class AIUpdateInterface002B9970;
class DozerAIInterface002B9970;

class StateMachine002B9970
{
public:
	virtual void slot000();
	unsigned char m_beforeOwner[0xc];
	Object *m_owner;
};

class State002B9970
{
public:
	virtual StateReturnType update() = 0;

	Object *getMachineOwner()
	{
		return m_machine->m_owner;
	}

protected:
	unsigned char m_beforeMachine[0x18];
	StateMachine002B9970 *m_machine;
	unsigned char m_afterMachine[4];
};

class Player
{
public:
	virtual void slot000();
	unsigned char m_beforePlayerIndex[0x20];
	int m_playerIndex;

	int getPlayerIndex() const
	{
		return m_playerIndex;
	}
};

class Object
{
public:
	virtual void slot000();

	AIUpdateInterface002B9970 *getAIUpdateInterface() const
	{
		return m_ai;
	}

	Player *getControllingPlayer() const;

	bool isEffectivelyDead() const
	{
		return (m_privateStatus & 1) != 0;
	}

	unsigned char m_beforeAI[0x200];
	AIUpdateInterface002B9970 *m_ai;
	unsigned char m_beforePrivateStatus[0x13c];
	unsigned char m_privateStatus;
};

// ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

class AICommandInterface
{
public:
	virtual void aiDoCommand() = 0;
	void aiRepair(Object *object, CommandSourceType source);
};

// ?aiRepair@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z
#pragma comment(linker, "/alternatename:?aiRepair@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z=?j_00029c08@@YAXXZ")

class DozerAIInterface002B9970
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual float getBoredTime() const;
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual bool isAnyTaskPending() const;
};

class AIUpdatePrimary002B9970
{
public:
	virtual void slot000();
	unsigned char m_afterVtable[0x1c];
};

class AIUpdateInterface002B9970 : public AIUpdatePrimary002B9970, public AICommandInterface
{
public:
	virtual void slot004(); virtual void slot008();
	virtual void slot00c(); virtual void slot010();
	virtual void slot014(); virtual void slot018();
	virtual void slot01c(); virtual void slot020();
	virtual void slot024(); virtual void slot028();
	virtual void slot02c(); virtual void slot030();
	virtual void slot034(); virtual void slot038();
	virtual void slot03c(); virtual void slot040();
	virtual void slot044(); virtual void slot048();
	virtual void slot04c(); virtual void slot050();
	virtual void slot054(); virtual void slot058();
	virtual void slot05c(); virtual void slot060();
	virtual void slot064(); virtual void slot068();
	virtual void slot06c(); virtual void slot070();
	virtual void slot074(); virtual void slot078();
	virtual void slot07c(); virtual void slot080();
	virtual void slot084(); virtual void slot088();
	virtual void slot08c(); virtual void slot090();
	virtual void slot094(); virtual void slot098();
	virtual void slot09c(); virtual void slot0a0();
	virtual void slot0a4(); virtual void slot0a8();
	virtual void slot0ac(); virtual void slot0b0();
	virtual void slot0b4(); virtual void slot0b8();
	virtual void slot0bc(); virtual void slot0c0();
	virtual void slot0c4(); virtual void slot0c8();
	virtual void slot0cc(); virtual void slot0d0();
	virtual void slot0d4(); virtual void slot0d8();
	virtual void slot0dc(); virtual void slot0e0();
	virtual void slot0e4(); virtual void slot0e8();
	virtual void slot0ec(); virtual void slot0f0();
	virtual void slot0f4(); virtual void slot0f8();
	virtual void slot0fc(); virtual void slot100();
	virtual void slot104(); virtual void slot108();
	virtual void slot10c(); virtual void slot110();
	virtual void slot114(); virtual void slot118();
	virtual void slot11c(); virtual void slot120();
	virtual void slot124(); virtual void slot128();
	virtual void slot12c(); virtual void slot130();
	virtual void slot134(); virtual void slot138();
	virtual DozerAIInterface002B9970 *getDozerAIInterface();
	virtual void slot13c(); virtual void slot140();
	virtual void slot144(); virtual void slot148();
	virtual void slot14c(); virtual void slot150();
	virtual void slot154(); virtual void slot158();
	virtual void slot15c(); virtual void slot160();
	virtual void slot164(); virtual void slot168();
	virtual void slot16c(); virtual void slot170();
	virtual void slot174(); virtual void slot178();
	virtual bool isIdle() const;
};

class GameLogic
{
public:
	virtual void slot000();
	unsigned char m_beforeFrame[0x38];
	unsigned int m_frame;

	unsigned int getFrame() const
	{
		return m_frame;
	}
};

class InGameUI
{
public:
	virtual void slot000(); virtual void slot004();
	virtual void slot008(); virtual void slot00c();
	virtual void slot010(); virtual void slot014();
	virtual void slot018(); virtual void slot01c();
	virtual void slot020(); virtual void slot024();
	virtual void slot028(); virtual void slot02c();
	virtual void slot030(); virtual void slot034();
	virtual void slot038(); virtual void slot03c();
	virtual void slot040(); virtual void slot044();
	virtual void slot048(); virtual void slot04c();
	virtual void slot050(); virtual void slot054();
	virtual void slot058(); virtual void slot05c();
	virtual void slot060(); virtual void slot064();
	virtual void slot068(); virtual void slot06c();
	virtual void slot070(); virtual void slot074();
	virtual void slot078(); virtual void slot07c();
	virtual void slot080(); virtual void slot084();
	virtual void slot088(); virtual void slot08c();
	virtual void slot090(); virtual void slot094();
	virtual void slot098(); virtual void slot09c();
	virtual void slot0a0(); virtual void slot0a4();
	virtual void slot0a8(); virtual void slot0ac();
	virtual void slot0b0(); virtual void slot0b4();
	virtual void slot0b8(); virtual void slot0bc();
	virtual void slot0c0(); virtual void slot0c4();
	virtual void slot0c8(); virtual void slot0cc();
	virtual void slot0d0(); virtual void slot0d4();
	virtual void slot0d8(); virtual void slot0dc();
	virtual void slot0e0(); virtual void slot0e4();
	virtual void slot0e8(); virtual void slot0ec();
	virtual void slot0f0(); virtual void slot0f4();
	virtual void slot0f8(); virtual void slot0fc();
	virtual void slot100(); virtual void slot104();
	virtual void slot108(); virtual void slot10c();
	virtual void slot110(); virtual void slot114();
	virtual void slot118(); virtual void slot11c();
	virtual void slot120(); virtual void slot124();
	virtual void slot128(); virtual void slot12c();
	virtual void slot130(); virtual void slot134();
	virtual void slot138(); virtual void slot13c();
	virtual void slot140(); virtual void slot144();
	virtual void slot148(); virtual void slot14c();
	virtual void slot150(); virtual void slot154();
	virtual void slot158(); virtual void slot15c();
	virtual void slot160(); virtual void slot164();
	virtual void slot168(); virtual void slot16c();
	virtual void slot170(); virtual void slot174();
	virtual void slot178(); virtual void addIdleWorker(Object *object);
	virtual void removeIdleWorker(Object *object, int playerNumber);
};

extern GameLogic *TheGameLogic;
extern InGameUI *TheInGameUI;
extern float g_bfmeUint32Scale;
extern Object *findObjectToRepair(Object *object);

class Rva002B9970DozerPrimaryIdleState : public State002B9970
{
public:
	// ?update@DozerPrimaryIdleState@@UAE?AW4StateReturnType@@XZ
	virtual StateReturnType update();

	unsigned int m_idleTooLongTimestamp;
	int m_idlePlayerNumber;
	bool m_isMarkedAsIdle;
};

// ?update@DozerPrimaryIdleState@@UAE?AW4StateReturnType@@XZ
StateReturnType Rva002B9970DozerPrimaryIdleState::update()
{
	DozerAIInterface002B9970 *dozerAI;
	Object *dozer = getMachineOwner();
	AIUpdateInterface002B9970 *ai = dozer->getAIUpdateInterface();
	if (!ai)
		return STATE_FAILURE;

	dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
		return STATE_FAILURE;

	if (ai->isIdle() && !m_isMarkedAsIdle && !dozer->isEffectivelyDead())
	{
		m_idlePlayerNumber = dozer->getControllingPlayer()->getPlayerIndex();
		TheInGameUI->addIdleWorker(getMachineOwner());
		m_isMarkedAsIdle = true;
	}

	if (m_isMarkedAsIdle && (!ai->isIdle() || dozer->isEffectivelyDead()))
	{
		TheInGameUI->removeIdleWorker(getMachineOwner(), m_idlePlayerNumber);
		m_idlePlayerNumber = -1;
		m_isMarkedAsIdle = false;
	}

	if (!ai->isIdle())
		m_idleTooLongTimestamp = TheGameLogic->getFrame();

	if (TheGameLogic->getFrame() - m_idleTooLongTimestamp > dozerAI->getBoredTime() &&
		dozerAI->isAnyTaskPending() == false)
	{
		m_idleTooLongTimestamp = TheGameLogic->getFrame();
		Object *repairTarget =
			(reinterpret_cast<Object *(__cdecl *)(void)>(findObjectToRepair))();
		if (repairTarget)
			ai->aiRepair(repairTarget, CMD_FROM_AI);
	}

	return STATE_CONTINUE;
}
