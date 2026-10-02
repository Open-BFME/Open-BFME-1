// Open-BFME5 conversions.

extern void *g_bfmeVftUUA[];
extern char g_bfmeFileUUA[];
extern char g_bfmeMsgAUUA[];
extern char g_bfmeMsgBUUA[];
extern char g_bfmeMsgCUUA[];

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get(void);

class BfmeThingUUA
{
public:
	void bfmeGoUUA();
	void *m_bfmeVft;
	char m_bfmePad[4];
	void *m_bfmeRef;
	void *m_bfmeQueue;
	int m_bfmePending;
};

void BfmeThingUUA::bfmeGoUUA()
{
	m_bfmeVft = g_bfmeVftUUA;
	if (m_bfmeRef)
		Rva007EB810Get()->fail(g_bfmeMsgAUUA, g_bfmeFileUUA, 0x45);
	if (m_bfmeQueue)
		Rva007EB810Get()->fail(g_bfmeMsgBUUA, g_bfmeFileUUA, 0x46);
	if (m_bfmePending)
		Rva007EB810Get()->fail(g_bfmeMsgCUUA, g_bfmeFileUUA, 0x47);
}
