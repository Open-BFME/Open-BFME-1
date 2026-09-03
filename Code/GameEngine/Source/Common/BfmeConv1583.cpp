// Open-BFME5 conversions.

class BfmeStrVSJ
{
public:
	int bfmeProbeVSJ(BfmeStrVSJ *out);
	void bfmeAssignVSJ(const BfmeStrVSJ &other);
	void bfmeSetVSJ(const char *text, int length);
	char *m_bfme00;
};

class BfmeArgVSJ
{
public:
	char m_bfmePad00[0xc];
	BfmeStrVSJ m_bfme0c;
};

class BfmeOwnVSJ
{
public:
	void bfmeApplyVSJ(BfmeArgVSJ *arg, char force);
	void bfmeNotifyVSJ(int value, int flags);
	char m_bfmePad00[8];
	int m_bfme08;
	char m_bfmePad0c[0x14];
	BfmeStrVSJ m_bfme20;
};

void BfmeOwnVSJ::bfmeApplyVSJ(BfmeArgVSJ *arg, char force)
{
	if (arg != 0 && arg->m_bfme0c.bfmeProbeVSJ(&m_bfme20) == 0 && force == 0)
	{
		m_bfme20.bfmeSetVSJ("", 0);
		bfmeNotifyVSJ(m_bfme08, 0x3fffffff);
	}
	else
	{
		m_bfme20.bfmeAssignVSJ(arg->m_bfme0c);
		bfmeNotifyVSJ(m_bfme08, 1);
	}
}
