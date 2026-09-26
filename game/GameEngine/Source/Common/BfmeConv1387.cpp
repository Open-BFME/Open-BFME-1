// cl: /GS
// Open-BFME5 conversions.

class BfmeMsgVJJ
{
public:
	void bfmeSetVJJ(const char *k, const char *v) throw();
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class BfmeThingVJJ
{
public:
	void bfmeGoVJJ(BfmeMsgVJJ *out);
	void bfmeFmtVJJ(char *buf, int n) throw();
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

void BfmeThingVJJ::bfmeGoVJJ(BfmeMsgVJJ *out)
{
	char buf[0x20];
	bfmeFmtVJJ(buf, 0x20);
	out->m_bfme04 = m_bfme04;
	out->m_bfme08 = m_bfme08;
	out->m_bfme0c = m_bfme0c;
	out->bfmeSetVJJ("IP", buf);
}
