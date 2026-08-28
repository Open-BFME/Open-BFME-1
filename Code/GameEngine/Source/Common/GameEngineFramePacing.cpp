// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void liteupdate(int phase) = 0;
	virtual void update(int phase) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual int getFrameAdvanceCount(void) = 0;
	virtual int getFramePacingStatus(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual bool isPacketRouter(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void beginUpdate(void) = 0;
	virtual void endUpdate(void) = 0;
};

extern NetworkInterface *TheNetwork;
#define LogicTimeScale (*(float *)0x012A72A4)
#define One (*(const float *)0x01075334)

class BfmeGameLogicPause
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void update(int phase) = 0;
	bool isGamePaused(void);

	char m_gap04[0x108];
	int m_gameMode;
};

#define TheGameLogic (*(BfmeGameLogicPause **)0x012F0898)
#define TheGameClient (*(unsigned char **)0x012F1464)

void j_00014e25(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void _bfme_updateNetworkAndLogic(int phase);
	virtual void _bfme_updateClientSubsystems(void);

private:
	bool _bfme_shouldSkipClientFrame(void);
	bool _bfme_shouldSkipClientFrameCall(void);
	void _bfme_updateClientFrameRatio(void);

	char m_head[0x2c];
	int m_clientFramePeriod;
	int m_clientFrameCounter;
	float m_clientFrameRatio;
	char m_gap3C[4];
	float m_clientFrameLimit;
};

class ClientSubsystem
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void update(void);
};

struct ClientSubsystemVtable
{
	void *m_slots00[5];
	void (__fastcall *update)(ClientSubsystem *subsystem, ClientSubsystemVtable *vtable);
};

struct ClientSubsystemVtableEax
{
	void *m_slots00[5];
	void (__fastcall *update)(ClientSubsystem *subsystem);
};

struct NetworkDispatchVtable
{
	void *m_slots00[9];
	void (__fastcall *liteupdate)(NetworkInterface *network, NetworkDispatchVtable *vtable, int phase);
};

class ClientFrameSubsystem
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void update(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void setFrame(int frame) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual int getFrame(void) = 0;

	char m_gap04[0xc0];
	bool m_advanceFrame;
};

class RadarSubsystem
{
public:
	char m_gap00[4];
	ClientSubsystem m_update;
};

class GameLogicClientUpdate
{
public:
	void deleteLoadScreen(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class MessageStream
{
public:
	void propagateMessages(void);
};

class BFMEDesyncCheck
{
public:
	BFMEDesyncCheck();
	~BFMEDesyncCheck() { writeReportIfMismatched(); }
	void writeReportIfMismatched(void);
};

class BfmeInGameUI_setInputEnabled
{
public:
	void setEngineInputEnabled(bool enabled);
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

unsigned int _bfme_updateTimedOps(void);

#define GameLogicClient (*(GameLogicClientUpdate **)0x012F0898)
extern ClientFrameSubsystem *TheGameClientClientUpdate;
#define GameClientSubsystem TheGameClientClientUpdate
#define WindowManagerSubsystem (*(ClientSubsystem **)0x012F19E8)
extern RadarSubsystem *TheRadarClientUpdate;
#define Radar TheRadarClientUpdate
#define MessageStreamSubsystem (*(MessageStream **)0x012ED5EC)
#define InputLockSubsystem (*(ClientSubsystem **)0x012F4C50)
#define InGameUISubsystem (*(BfmeInGameUI_setInputEnabled **)0x012F148C)
#define MouseSubsystem (*(Mouse **)0x012F4C5C)
extern ClientSubsystem *TheAudioClientUpdate;
#define AudioSubsystem TheAudioClientUpdate
#define AuxiliarySubsystem (*(ClientSubsystem **)0x012ED84C)
extern int BfmeSavedClientFrame;
extern int BfmeSkippedClientFrames;
#define SavedClientFrame BfmeSavedClientFrame
#define SkippedClientFrames BfmeSkippedClientFrames
extern int BfmeTimedOpInputLocked;
#define TimedOpInputLocked BfmeTimedOpInputLocked

void GameEngine::_bfme_updateClientFrameRatio(void)
{
	float ratio = (float)m_clientFramePeriod / (float)m_clientFrameCounter;
	m_clientFrameRatio = ratio;
	if (ratio < 0.0f)
		m_clientFrameRatio = 0.0f;
	else if (ratio > 1.0f)
		m_clientFrameRatio = 1.0f;
	else
		m_clientFrameRatio = ratio;
}

bool GameEngine::_bfme_shouldSkipClientFrame(void)
{
	NetworkInterface *network = TheNetwork;
	if (network != 0)
	{
		if (!(LogicTimeScale < One))
		{
			if (m_clientFramePeriod != 1)
			{
				if (m_clientFramePeriod > m_clientFrameCounter)
				{
					if (network->getFramePacingStatus() > 1)
						return true;

					++m_clientFrameCounter;
					if ((float)m_clientFrameCounter > m_clientFrameLimit)
						m_clientFrameLimit = (float)m_clientFrameCounter;
					return false;
				}
				else if (network->getFramePacingStatus() > 3)
				{
					if ((float)m_clientFramePeriod < m_clientFrameLimit)
						m_clientFrameLimit = (float)m_clientFramePeriod;
					return true;
				}
			}
		}
	}

	return false;
}

void GameEngine::_bfme_updateNetworkAndLogic(int phase)
{
	BfmeGameLogicPause *logic = TheGameLogic;
	bool ready = true;
	if (phase == 1)
	{
		ready = !logic->isGamePaused();
		if (TheNetwork != 0)
		{
			if (TheNetwork->getFrameAdvanceCount() > 0)
			{
				TheNetwork->beginUpdate();
				TheNetwork->update(phase);
				TheNetwork->endUpdate();
				ready = true;
				if (!TheNetwork->isPacketRouter())
					TheNetwork->getFramePacingStatus();
			}
			else
			{
				ready = false;
			}
		}

		logic = TheGameLogic;
		if (logic != 0 && logic->m_gameMode == 5)
		{
			j_00014e25();
			logic = TheGameLogic;
		}

	}

	if (ready)
		logic->update(phase);
	else
		TheGameClient[0xc4] = 0;
}

void GameEngine::_bfme_updateClientSubsystems(void)
{
	GameLogicClient->deleteLoadScreen();

	if (GameClientSubsystem->m_advanceFrame)
	{
		GameClientSubsystem->setFrame(GameClientSubsystem->getFrame() + 1);
	}

	WindowManagerSubsystem->update();
	if (**(int **)0x012A7244 == 0 && _bfme_shouldSkipClientFrameCall())
	{
		int skippedClientFrames = SkippedClientFrames;
		ClientFrameSubsystem *client = GameClientSubsystem;
		SkippedClientFrames = skippedClientFrames + 1;
		SavedClientFrame = client->getFrame();
		return;
	}

	BFMEDesyncCheck desyncCheck;
	Radar->m_update.update();
	GameClientSubsystem->update();
	MessageStreamSubsystem->propagateMessages();

	unsigned int timedOps = _bfme_updateTimedOps();
	int inputLocked = timedOps & 1;
	if (inputLocked)
		InputLockSubsystem->update();

	if (inputLocked != TimedOpInputLocked)
	{
		if (inputLocked)
		{
			InGameUISubsystem->setEngineInputEnabled(false);
			MouseSubsystem->_bfme_setEngineVisibility(false);
		}
		else
		{
			InGameUISubsystem->setEngineInputEnabled(true);
			if ((timedOps & 4) == 0)
				MouseSubsystem->_bfme_setEngineVisibility(true);
		}
	}

	ClientSubsystem *audio = AudioSubsystem;
	ClientSubsystemVtable *audioVtable = *(ClientSubsystemVtable **)audio;
	TimedOpInputLocked = inputLocked;
	audioVtable->update(audio, audioVtable);
	ClientSubsystem *auxiliary = AuxiliarySubsystem;
	ClientSubsystemVtableEax *auxiliaryVtable = *(ClientSubsystemVtableEax **)auxiliary;
	auxiliaryVtable->update(auxiliary);
	if (TheNetwork != 0)
	{
		NetworkInterface *network = TheNetwork;
		NetworkDispatchVtable *networkVtable = *(NetworkDispatchVtable **)network;
		networkVtable->liteupdate(network, networkVtable, 0);
	}
}
