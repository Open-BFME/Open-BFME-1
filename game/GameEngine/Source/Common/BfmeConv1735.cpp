class BfmeMgr19E
{
public:
	void bfmeRunAG(void);
};

extern BfmeMgr19E *g_mgr12F19E8;
extern void *g_bfmeReadyAG;

class BfmeOwnAG
{
public:
	int bfmeHandleAG(int code, unsigned char kind, int flags);

	unsigned char m_bfmeHeadAG[0x258];
	int m_bfmeBusyAG;
};

int BfmeOwnAG::bfmeHandleAG(int code, unsigned char kind, int flags)
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

	if ((flags & 1) && m_bfmeBusyAG == 0 && g_bfmeReadyAG)
		g_mgr12F19E8->bfmeRunAG();

	return 1;
}
