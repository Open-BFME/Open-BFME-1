// Open-BFME5 conversions.

class BfmeStrVSI
{
public:
	int bfmeProbeVSI(BfmeStrVSI *out);
	void bfmeAssignVSI(const BfmeStrVSI &other);
	void bfmeSetVSI(const char *text, int length);
	char *m_bfme00;
};

class BfmeArgVSI
{
public:
	char m_bfmePad00[0xc];
	BfmeStrVSI m_bfme0c;
	char m_bfmePad10[0x148];
	char m_bfme158;
};

class BfmeOwnVSI
{
public:
	void bfmeApplyVSI(BfmeArgVSI *arg);
	void bfmeNotifyVSI(int value, int flags);
	char m_bfmePad00[8];
	int m_bfme08;
	char m_bfmePad0c[0x14];
	BfmeStrVSI m_bfme20;
};

void BfmeOwnVSI::bfmeApplyVSI(BfmeArgVSI *arg)
{
	if (arg != 0 && arg->m_bfme158 != 0 && arg->m_bfme0c.bfmeProbeVSI(&m_bfme20) != 0)
	{
		m_bfme20.bfmeAssignVSI(arg->m_bfme0c);
		bfmeNotifyVSI(m_bfme08, 1);
	}
	else
	{
		m_bfme20.bfmeSetVSI("", 0);
		bfmeNotifyVSI(m_bfme08, 0x3fffffff);
	}
}
