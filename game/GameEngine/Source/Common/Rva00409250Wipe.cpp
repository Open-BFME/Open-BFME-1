// cl: /O2 /G6 /Ob0

extern char g_bfmeVft963[];

struct BfmeNode925
{
	char m_pad[0x14];
	BfmeNode925 *next;
	int extra;
};

class BfmeReg925
{
public:
	void bfmeWipe925();
	void bfmeFinish925();
	char *m_vft;
	char m_pad[4];
	BfmeNode925 *m_08;
	int m_0c;
	BfmeNode925 *m_10;
};

void BfmeReg925::bfmeWipe925()
{
	int z = 0;
	m_vft = g_bfmeVft963;
	int i = z;
	while (i < 2)
	{
		BfmeNode925 *p = i ? m_08 : m_10;
		while (p)
		{
			BfmeNode925 *n = p->next;
			p->next = 0;
			p->extra = z;
			p = n;
		}
		++i;
	}
	bfmeFinish925();
}
