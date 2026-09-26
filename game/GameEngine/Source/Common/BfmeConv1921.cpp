class BfmeResBX
{
public:
	unsigned char m_bfmeHeadBX[0xb0];
	int m_bfmeValueBX;
};

class BfmeOwnerBX
{
public:
	virtual void bfmeSlot00BX();
	virtual void bfmeSlot01BX();
	virtual void bfmeSlot02BX();
	virtual void bfmeSlot03BX();
	virtual void bfmeSlot04BX();
	virtual void bfmeSlot05BX();
	virtual void bfmeSlot06BX();
	virtual void bfmeSlot07BX();
	virtual void bfmeSlot08BX();
	virtual void bfmeSlot09BX();
	virtual BfmeResBX *bfmeGetBX();

	void bfmeAimBX(void *at);
	void bfmeIdleBX(int mode, int flag);
};

class BfmeObjBX
{
public:
	unsigned char m_bfmeHeadBX[0x38];
	int m_bfmeAtBX;
	unsigned char m_bfmeMidBX[0x308];
	unsigned char m_bfmeFlagsBX;
};

struct Rva00367E30Logic
{
	BfmeObjBX *bfmeFindBX(int id);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeCfgBX
{
public:
	unsigned char m_bfmeHeadBX[0x34];
	unsigned char m_bfmeOnBX;
};

class BfmeSubBX
{
public:
	bool bfmeQueryBX(int *first, int *second);

	int m_bfme00BX;
	float m_bfme04BX;
	float m_bfme08BX;
	unsigned int m_bfme0cBX;
	unsigned int m_bfme10BX;
	int m_bfme14BX;
	int m_bfme18BX;
	unsigned int m_bfme1cBX;
	int m_bfme20BX;
	int m_bfme24BX;
};

extern float g_bfmeDefaultBU;
extern float g_bfmeUint32Scale;
extern const float BfmeZeroRange;

bool BfmeSubBX::bfmeQueryBX(int *first, int *second)
{
	(void)first;

	switch (m_bfme24BX)
	{
	case 0:
		if (m_bfme0cBX++ >= m_bfme10BX)
		{
			m_bfme24BX = 1;
			m_bfme0cBX = 0;
			*(volatile int *)second = m_bfme00BX;
		}
		*second = 0;
		return true;

	case 1:
		{
			float phase = (float)(unsigned int)m_bfme14BX;
			float value = (m_bfme04BX - *(float *)&m_bfme00BX) /
				(g_bfmeDefaultBU > phase ? g_bfmeDefaultBU : phase);
			value += *(float *)second;
			*(float *)second = value;
			if (*(float *)second >= m_bfme04BX)
			{
				*(int *)second = *(int *)&m_bfme04BX;
				m_bfme24BX = 2;
			}
			return true;
		}

	case 2:
		{
			float phase = (float)(unsigned int)m_bfme18BX;
			float value = (m_bfme04BX - m_bfme08BX) /
				(g_bfmeDefaultBU > phase ? g_bfmeDefaultBU : phase);
			value = *(float *)second - value;
			*(float *)second = value;
			if (*(float *)second <= m_bfme08BX)
			{
				*(int *)second = *(int *)&m_bfme08BX;
				m_bfme24BX = 3;
				m_bfme0cBX = 0;
			}
			return true;
		}

	case 3:
		if (m_bfme0cBX++ >= m_bfme1cBX)
			m_bfme24BX = 4;
		*(int *)second = *(int *)&m_bfme08BX;
		return true;

	case 4:
		{
			float phase = (float)(unsigned int)m_bfme20BX;
			float value = m_bfme08BX /
				(g_bfmeDefaultBU > phase ? g_bfmeDefaultBU : phase);
			value = *(float *)second - value;
			*(float *)second = value;
			if (*(float *)second <= BfmeZeroRange)
			{
				*(int *)second = 0;
				m_bfme24BX = 5;
				m_bfme0cBX = 0;
			}
			return true;
		}

	default:
		*second = 0;
		return false;
	}
}

class BfmeHostBX
{
public:
	int bfmeStartBX();

	unsigned char m_bfmeHeadBX[0x10];
	int m_bfmeIdBX;
	int m_bfmeAtBX;
	BfmeSubBX m_bfmeSubBX;
};

int BfmeHostBX::bfmeStartBX()
{
	BfmeOwnerBX *owner = *(BfmeOwnerBX **)((char *)this - 8);

	if ((*(BfmeCfgBX **)((char *)this - 0xc))->m_bfmeOnBX != 0)
	{
		BfmeObjBX *o = 0;

		if (m_bfmeIdBX != 0)
			o = TheBfmeGameLogic->bfmeFindBX(m_bfmeIdBX);

		if (o != 0 && (o->m_bfmeFlagsBX & 1) == 0)
			owner->bfmeAimBX(&o->m_bfmeAtBX);
		else
			owner->bfmeIdleBX(8, 0);
	}

	BfmeResBX *r = owner->bfmeGetBX();

	if (r != 0)
	{
		m_bfmeSubBX.bfmeQueryBX(&m_bfmeAtBX, &m_bfmeAtBX);
		r->m_bfmeValueBX = m_bfmeAtBX;
	}

	return 1;
}
