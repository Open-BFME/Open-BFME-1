class GameLogic
{
public:
	unsigned char m_bfmeHeadIS[0x3c];
	int m_bfmeFrameIS;
};

extern GameLogic *TheBfmeGameLogic;

class BfmeWakeIS
{
public:
	void bfmeSetWakeIS(void *obj, int sleep);

	int m_bfmeWakeDataIS;
};

class BfmeDataIS
{
public:
	unsigned char m_bfmeHeadIS[0xc];
	float m_bfmeDelayIS;
};

class BfmeUpdIS
{
public:
	void bfmeSleepIS(void);

	unsigned char m_bfmeHeadIS[8];
	BfmeWakeIS m_bfmeWakeIS;
	BfmeDataIS *m_bfmeDataIS;
	void *m_bfmeObjIS;
	unsigned char m_bfmeMidIS[0x14];
	int m_bfmeFrameIS;
	char m_bfmeDoneIS;
};

void BfmeUpdIS::bfmeSleepIS(void)
{
	if (m_bfmeDoneIS)
		return;

	m_bfmeFrameIS = TheBfmeGameLogic->m_bfmeFrameIS - (int)(m_bfmeDataIS->m_bfmeDelayIS * -5.0f);
	m_bfmeDoneIS = 1;
	m_bfmeWakeIS.bfmeSetWakeIS(m_bfmeObjIS, 1);
}
