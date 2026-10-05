// Open-BFME5 conversions.

extern void *g_bfmeVftUUA[];

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
		Rva007EB810Get()->fail("mProtoPingRef == 0", "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp", 0x45);
	if (m_bfmeQueue)
		Rva007EB810Get()->fail("mPendingQueue == 0", "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp", 0x46);
	if (m_bfmePending)
		Rva007EB810Get()->fail("mNumPendingRequests == 0", "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp", 0x47);
}
