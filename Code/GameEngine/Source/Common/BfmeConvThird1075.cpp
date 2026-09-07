// Independent reconstruction of the served retail body at 0x0055E120.
// The separate state arms are intentional: merging cases 2 and 3 makes the
// VS2003 compiler replace retail's sub/dec/dec dispatch with a range test.

class BfmeMgr19E
{
public:
	void bfmeAddAJ(void *owner, char *fmt, int argc, char *first, char *second,
		char *third, char *fourth, char *fifth);
};

extern BfmeMgr19E *g_mgr12F19E8;
extern char g_bfmeFmtAJ[];
extern char g_bfmeLitA1072[];
extern char g_bfmeLitB1072[];
extern char g_bfmeD1072;

class BfmeOwnAJ
{
public:
	void bfmeCloseAJ(int reason);
};

class BfmeQ1075
{
public:
	int bfmeGo1075A(int code, unsigned char kind, char flags);

	unsigned char m_bfmeHeadAJ[0x250];
	void *m_bfmeSinkAJ;
	unsigned char m_bfmeMidAJ[4];
	int m_bfmeStateAJ;
};

int BfmeQ1075::bfmeGo1075A(int code, unsigned char kind, char flags)
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
		return 1;

	switch (m_bfmeStateAJ)
	{
		case 4:
			if (g_bfmeD1072)
				g_mgr12F19E8->bfmeAddAJ(m_bfmeSinkAJ, g_bfmeFmtAJ, 1,
					g_bfmeLitA1072, 0, 0, 0, 0);
			else
				g_mgr12F19E8->bfmeAddAJ(m_bfmeSinkAJ, g_bfmeFmtAJ, 1,
					g_bfmeLitB1072, 0, 0, 0, 0);
			((BfmeOwnAJ *)this)->bfmeCloseAJ(0);
			break;

		case 2:
			((BfmeOwnAJ *)this)->bfmeCloseAJ(0);
			break;

		case 3:
			((BfmeOwnAJ *)this)->bfmeCloseAJ(0);
			break;
	}

	return 1;
}
