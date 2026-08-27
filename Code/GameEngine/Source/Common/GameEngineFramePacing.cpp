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
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual int getFramePacingStatus(void) = 0;
};

#define TheNetwork (*(NetworkInterface **)0x012F7714)
#define LogicTimeScale (*(float *)0x012A72A4)
#define One (*(const float *)0x01075334)

class GameEngine
{
private:
	bool _bfme_shouldSkipClientFrame(void);

	char m_head[0x30];
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
