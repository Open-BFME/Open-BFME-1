class BfmeMgr19E
{
public:
	void bfmeAddAI(void *owner, char *fmt, int argc, char *first, char *second,
		char *third, char *fourth, char *fifth);
};

extern BfmeMgr19E *g_mgr12F19E8;
extern char g_bfmeFmt1057[];
extern char g_bfmeEscAI[];

class BfmeHostAI
{
public:
	unsigned char m_bfmeHeadAI[0x250];
	void *m_bfmeSinkAI;
};

class BfmeOwnAI
{
public:
	int bfmeHandleAI(void *unused, int code, unsigned char kind, int flags);
	void bfmeCloseAI(int reason);

	unsigned char m_bfmeHeadAI[0x34];
	BfmeHostAI *m_bfmeHostAI;
	unsigned char m_bfmeMidAI[4];
	int m_bfmeStateAI;
};

int BfmeOwnAI::bfmeHandleAI(void *unused, int code, unsigned char kind, int flags)
{
	int kindValue = kind;

	if (code != 0x15)
		return 0;

	switch (kindValue)
	{
		case 1:
			break;

		default:
			return 0;
	}

	if ((flags & 1) == 0)
		return 0;

	int state = m_bfmeStateAI;

	if (state == 1)
	{
		g_mgr12F19E8->bfmeAddAI(m_bfmeHostAI->m_bfmeSinkAI, g_bfmeFmt1057, state,
			g_bfmeEscAI, 0, 0, 0, 0);
		bfmeCloseAI(0);

		return 1;
	}

	if (state == 3 || state == 2)
		return 1;

	return 0;
}
