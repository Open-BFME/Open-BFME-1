class BfmeThingBW;
class BfmeAgentBW;
class BfmeInfoBW;

class BfmeThingBW
{
public:
	void bfmeTakeBW(void *at);
};

class BfmeSubBW
{
public:
	void bfmeSetBW(float level);
	void bfmeAddBW(void *extra);
	void bfmeBonusBW(void *extra);
};

class BfmeAgentBW
{
public:
	virtual void bfmeSlot00BW();
	virtual void bfmeSlot01BW();
	virtual void bfmeSlot02BW();
	virtual void bfmeSlot03BW();
	virtual void bfmeSlot04BW();
	virtual void bfmeSlot05BW();
	virtual void bfmeSlot06BW();
	virtual void bfmeSlot07BW();
	virtual void bfmeSlot08BW();
	virtual void bfmeSlot09BW();
	virtual BfmeThingBW *bfmeGetBW();

	unsigned char m_bfmeHeadBW[0x20c];
	BfmeSubBW *m_bfmeSubBW;
};

class BfmeInfoBW
{
public:
	unsigned char m_bfmeHeadBW[0x10];
	int m_bfmeLevelBW;
	unsigned char m_bfmeMidBW[0x64];
	unsigned char m_bfmeAtBW[4];
	unsigned char m_bfmeTailBW[0x50];
	void *m_bfmeExtraBW;
};

class ExperienceLevelSystem
{
public:
	void bfmeAwardBW(BfmeInfoBW *info, BfmeAgentBW *agent, void *extra, char bonus);
	void bfmeGrantBW(BfmeInfoBW *info, BfmeAgentBW *agent, void *extra);
};

void ExperienceLevelSystem::bfmeAwardBW(BfmeInfoBW *info, BfmeAgentBW *agent, void *extra, char bonus)
{
	if (agent == 0)
		return;

	bfmeGrantBW(info, agent, extra);

	BfmeThingBW *t = agent->bfmeGetBW();

	if (t != 0)
		t->bfmeTakeBW(info->m_bfmeAtBW);

	agent->m_bfmeSubBW->bfmeSetBW((float)info->m_bfmeLevelBW);
	agent->m_bfmeSubBW->bfmeAddBW(info->m_bfmeExtraBW);

	if (bonus != 0)
		agent->m_bfmeSubBW->bfmeBonusBW(info->m_bfmeExtraBW);
}
