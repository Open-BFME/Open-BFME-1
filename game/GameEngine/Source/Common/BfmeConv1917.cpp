class BfmeThingBS;
class BfmeAgentBS;
class BfmeInfoBS;

class BfmeThingBS
{
public:
	void bfmeTakeBS(void *at);
};

class BfmeSubBS
{
public:
	void bfmeSetBS(float level);
	void bfmeAddBS(void *extra);
};

class BfmeAgentBS
{
public:
	virtual void bfmeSlot00BS();
	virtual void bfmeSlot01BS();
	virtual void bfmeSlot02BS();
	virtual void bfmeSlot03BS();
	virtual void bfmeSlot04BS();
	virtual void bfmeSlot05BS();
	virtual void bfmeSlot06BS();
	virtual void bfmeSlot07BS();
	virtual void bfmeSlot08BS();
	virtual void bfmeSlot09BS();
	virtual BfmeThingBS *bfmeGetBS();

	unsigned char m_bfmeHeadBS[0x20c];
	BfmeSubBS *m_bfmeSubBS;
};

class BfmeInfoBS
{
public:
	unsigned char m_bfmeHeadBS[0x10];
	int m_bfmeLevelBS;
	unsigned char m_bfmeMidBS[0x64];
	unsigned char m_bfmeAtBS[4];
	unsigned char m_bfmeTailBS[0x50];
	void *m_bfmeExtraBS;
};

class ExperienceLevelSystem
{
public:
	void bfmeGrantBS(BfmeInfoBS *info, BfmeAgentBS *agent, int mode);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

int __cdecl bfmeApplyBS(BfmeAgentBS *a, BfmeInfoBS *b)
{
	if (a != 0)
	{
		TheExperienceLevelSystem->bfmeGrantBS(b, a, 1);

		BfmeThingBS *t = a->bfmeGetBS();

		if (t != 0)
			t->bfmeTakeBS(b->m_bfmeAtBS);

		a->m_bfmeSubBS->bfmeSetBS((float)b->m_bfmeLevelBS);
		a->m_bfmeSubBS->bfmeAddBS(b->m_bfmeExtraBS);
	}

	return 1;
}
