class BfmeModuleERH
{
public:
	int bfmeStateERH();
};

class BfmeLocalERH
{
public:
	int bfmeRelERH(int team);
};

class BfmePlayersERH
{
public:
	char bfmeBusyERH();

	unsigned char m_bfmeHeadERH[0xc];
	BfmeLocalERH *m_bfmeLocalERH;
};

extern BfmePlayersERH *g_bfmePlayersERH;

class BfmeKeyGenERH
{
public:
	int bfmeNameToKeyERH(const char *name);
};

extern BfmeKeyGenERH *g_bfmeKeyGenERH;

class BfmeHostERH
{
public:
	int bfmeGoERH();
	BfmeModuleERH *bfmeFindERH(int key);

	unsigned char m_bfmeHeadERH[0x130];
	int m_bfmeFlagsERH;
	unsigned char m_bfmeMidERH[0x108];
	int m_bfmeTeamERH;
};

int BfmeHostERH::bfmeGoERH()
{
	if ((m_bfmeFlagsERH & 0x800) == 0)
		return 0;

	if (g_bfmePlayersERH->bfmeBusyERH())
		return 0;

	if (g_bfmePlayersERH->m_bfmeLocalERH->bfmeRelERH(m_bfmeTeamERH) != 0)
		return 0;

	static int s_bfmeKeyERH =
		g_bfmeKeyGenERH->bfmeNameToKeyERH("SpecialDisguiseUpdate");

	BfmeModuleERH *mod = bfmeFindERH(s_bfmeKeyERH);

	if (mod != 0)
		return mod->bfmeStateERH();

	return 0;
}
