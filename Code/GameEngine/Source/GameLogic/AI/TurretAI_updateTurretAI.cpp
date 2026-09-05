// cl: /DNDEBUG /MD /EHsc
// Retail 0x0018D710: TurretAI::updateTurretAI. ZH twin in
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// Field offsets from the landed isTryingToAimAtTarget body and the turretai shim.

typedef unsigned int UnsignedInt;
typedef int Int;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum StateReturnType
{
	STATE_CONTINUE = 0
};

enum TurretStateType
{
	TURRETAI_IDLE = 0,
	TURRETAI_IDLESCAN = 1,
	TURRETAI_AIM = 2,
	TURRETAI_FIRE = 3,
	TURRETAI_RECENTER = 4
};

#define IS_STATE_SLEEP(ret) ((Int)(ret) > 0)
#define GET_STATE_SLEEP_FRAMES(ret) ((UnsignedInt)(ret))
#define UPDATE_SLEEP(numFrames) ((UpdateSleepTime)(numFrames))

class GameLogic
{
	unsigned char m_pad[0x3c];
public:
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class BfmeCurrentState
{
public:
	unsigned char m_pad00[4];
	UnsignedInt m_id;
};

class TurretStateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual StateReturnType updateStateMachine() = 0;

	unsigned char m_pad04[0x1c - 4];
	BfmeCurrentState *m_currentState;

	UnsignedInt getCurrentStateID() const
	{
		return m_currentState ? m_currentState->m_id : 0xffffffff;
	}
};

class TurretAI
{
public:
	UpdateSleepTime updateTurretAI();

private:
	void startRotOrPitchSound();
	void stopRotOrPitchSound();

	unsigned char m_pad00[0x14];
	TurretStateMachine *m_turretStateMachine;
	unsigned char m_pad18[0x90 - 0x18];
	UnsignedInt m_enableSweepUntil;
	unsigned char m_pad94[0x9c - 0x94];
	UnsignedInt m_continuousFireExpirationFrame;
	UnsignedInt m_sleepUntil;
	bool m_playRotSound;
	bool m_playPitchSound;
	unsigned char m_positiveSweep;
	bool m_didFire;
	bool m_enabled;
	bool m_firesWhileTurning;
};

// ?updateTurretAI@TurretAI@@QAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime TurretAI::updateTurretAI()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_sleepUntil != 0 && now < m_sleepUntil)
		return UPDATE_SLEEP(m_sleepUntil - now);

	UpdateSleepTime subMachineSleep = UPDATE_SLEEP_FOREVER;

	if ((!m_firesWhileTurning) || (m_continuousFireExpirationFrame <= now))
	{
		m_playRotSound = false;
		m_playPitchSound = false;
	}

	if (m_enabled || m_turretStateMachine->getCurrentStateID() == TURRETAI_RECENTER)
	{
		m_didFire = false;
		StateReturnType stRet = m_turretStateMachine->updateStateMachine();

		if (m_turretStateMachine == 0)
			return UPDATE_SLEEP_NONE;

		if (m_didFire)
		{
			const int ENABLE_SWEEP_FRAME_COUNT = 3;
			m_enableSweepUntil = now + ENABLE_SWEEP_FRAME_COUNT;
			m_continuousFireExpirationFrame = now + ENABLE_SWEEP_FRAME_COUNT;
		}

		if (m_playRotSound || m_playPitchSound)
			startRotOrPitchSound();
		else
			stopRotOrPitchSound();

		if (IS_STATE_SLEEP(stRet))
		{
			Int frames = GET_STATE_SLEEP_FRAMES(stRet);
			if (frames < subMachineSleep)
				subMachineSleep = UPDATE_SLEEP(frames);
		}
		else
		{
			subMachineSleep = UPDATE_SLEEP_NONE;
		}
	}

	m_sleepUntil = now + subMachineSleep;
	return subMachineSleep;
}
