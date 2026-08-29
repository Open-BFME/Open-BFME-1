// Open-BFME5 conversions.

class BfmeHub993
{
public:
	virtual void bfmeVH0993();
	virtual void bfmeVH1993();
	virtual void bfmeVH2993();
	virtual void bfmeVH3993();
	virtual void bfmeVH4993();
	virtual void bfmeVH5993();
	virtual void bfmeVH6993();
	virtual void bfmeVH7993();
	virtual void bfmeVH8993();
	virtual void bfmeVH9993();
	virtual void bfmeVH10993();
	virtual void bfmeVH11993();
	virtual void bfmeVH12993();
	virtual void bfmeVH13993();
	virtual void bfmeVH14993();
	virtual void bfmeVH15993();
	virtual void bfmeVH16993();
	virtual void bfmeVH17993();
	virtual void bfmeVH18993();
	virtual void bfmeVH19993();
	virtual void bfmeVH20993();
	virtual void bfmeVH21993();
	virtual void bfmeVH22993();
	virtual void bfmeVH23993();
	virtual void bfmeVH24993();
	virtual void bfmeVH25993();
	virtual void bfmeVH26993();
	virtual void bfmeVH27993();
	virtual void bfmeVH28993();
	virtual void bfmeVH29993();
	virtual void bfmeVH30993();
	virtual void bfmeVH31993();
	virtual void bfmeVH32993();
	virtual void bfmeVH33993();
	virtual void bfmeVH34993();
	virtual void bfmeVH35993();
	virtual void bfmeVH36993();
	virtual void bfmeVH37993();
	virtual void bfmeVH38993();
	virtual void bfmeVH39993();
	virtual void bfmeVH40993();
	virtual void bfmeVH41993();
	virtual void bfmeVH42993();
	virtual void bfmeVH43993();
	virtual void bfmeVH44993();
	virtual void bfmeVH45993();
	virtual void bfmeFix993(int r);
	virtual void bfmeVH47993();
	virtual void bfmeEnd993(int a, int b);
	virtual void bfmeVH49993();
	virtual void bfmeVH50993();
	virtual void bfmeVH51993();
	virtual void bfmeVH52993();
	virtual void bfmeVH53993();
	virtual void bfmeVH54993();
	virtual void bfmeVH55993();
	virtual void bfmeVH56993();
	virtual void bfmeVH57993();
	virtual void bfmeVH58993();
	virtual void bfmeVH59993();
	virtual int bfmeAsk993();
};

extern BfmeHub993 *g_bfmeHub993;

class BfmeA993
{
public:
	void bfmeGo993A(int unused);

	char m_bfmePad[0x24];
	char m_bfmeOn;
};

void BfmeA993::bfmeGo993A(int unused)
{
	m_bfmeOn = 1;

	int r = g_bfmeHub993->bfmeAsk993();

	if (!r)
		g_bfmeHub993->bfmeFix993(r);

	g_bfmeHub993->bfmeEnd993(0, 0);
}

class BfmeAskB993
{
public:
	char bfmeAsk993B();
};

class BfmeLog993
{
public:
	void bfmeLog993B(int a, char *fmt, int n, char *s, int p, int q, int r, int t);
};

extern BfmeAskB993 *g_bfmeAskB993;
extern BfmeLog993 *g_bfmeLog993;
extern int g_bfmeVal993B;
extern char g_bfmeStrA993B[];
extern char g_bfmeStrB993B[];
extern char g_bfmeFmt993B[];

void bfmeGo993B(void)
{
	char *s = g_bfmeAskB993->bfmeAsk993B() ? g_bfmeStrA993B : g_bfmeStrB993B;

	g_bfmeLog993->bfmeLog993B(g_bfmeVal993B, g_bfmeFmt993B, 1, s, 0, 0, 0, 0);
}
