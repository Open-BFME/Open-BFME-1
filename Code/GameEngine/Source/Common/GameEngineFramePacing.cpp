// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2

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
	virtual void slot09(void) = 0;
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

class GameEngine
{
public:
	virtual void _bfme_updateNetworkAndLogic(int phase);

private:
	bool _bfme_shouldSkipClientFrame(void);

	char m_head[0x2c];
	int m_clientFramePeriod;
	int m_clientFrameCounter;
	char m_gap38[8];
	float m_clientFrameLimit;
};

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
