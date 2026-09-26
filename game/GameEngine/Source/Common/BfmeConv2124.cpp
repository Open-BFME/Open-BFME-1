class Rva005A00B0Transition
{
public:
	bool bfmeReadyAAW();
};

extern Rva005A00B0Transition *TheTransitionHandler;

extern const float g_bfmeDeltaAAW;
extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

class BfmeHostAAW
{
public:
	virtual void bfmeSlot0AAW();
	virtual void bfmeSlot1AAW();
	virtual void bfmeSlot2AAW();
	virtual void bfmeSlot3AAW();
	virtual void bfmeStopAAW(int a);
	virtual void bfmeSlot5AAW();
	virtual void bfmeSlot6AAW();
	virtual void bfmeSlot7AAW();
	virtual void bfmeSlot8AAW();
	virtual void bfmeSlot9AAW();
	virtual void bfmeSlot10AAW();
	virtual void bfmeSlot11AAW();
	virtual void bfmeFadeAAW(int a, int b);
	virtual void bfmeSlot13AAW();
	virtual void bfmeSlot14AAW();
	virtual void bfmeSlot15AAW();
	virtual void bfmeSlot16AAW();
	virtual void bfmeSlot17AAW();
	virtual void bfmeDoneAAW();
	virtual void bfmeExpireAAW();

	void bfmeUpdateAAW();
	void bfmeTickAAW();

	int m_bfme04AAW;
	unsigned char m_bfmeGapAAW[0x144 - 8];
	float m_bfme144AAW;
};

void BfmeHostAAW::bfmeUpdateAAW()
{
	bfmeTickAAW();

	switch (m_bfme04AAW)
	{
		case 2:
		{
			if (m_bfme144AAW <= g_bfmeDefaultBU)
				m_bfme144AAW = g_bfmeDeltaAAW + m_bfme144AAW;

			if (m_bfme144AAW > g_bfmeDefaultBU && TheTransitionHandler->bfmeReadyAAW())
			{
				bfmeFadeAAW(1, 1);
				m_bfme144AAW = 0;
				bfmeStopAAW(0);
				bfmeDoneAAW();
			}

			break;
		}

		case 3:
		{
			float f = m_bfme144AAW - g_bfmeDeltaAAW;

			m_bfme144AAW = f;

			if (f < BfmeZeroRange)
			{
				m_bfme144AAW = 0;
				bfmeExpireAAW();
			}

			break;
		}
	}
}
