// Open-BFME5 conversions.

extern void *g_bfmeVftUUA[];
extern char g_bfmeFileUUA[];
extern char g_bfmeMsgAUUA[];
extern char g_bfmeMsgBUUA[];
extern char g_bfmeMsgCUUA[];

class BfmeLogUUA
{
public:
	virtual void bfmeV0UUA() = 0;
	virtual void bfmeV1UUA() = 0;
	virtual void bfmeV2UUA() = 0;
	virtual void bfmeWarnUUA(const char *msg, const char *file, int line) = 0;
};

BfmeLogUUA *bfmeGetLogUUA(void);

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
		bfmeGetLogUUA()->bfmeWarnUUA(g_bfmeMsgAUUA, g_bfmeFileUUA, 0x45);
	if (m_bfmeQueue)
		bfmeGetLogUUA()->bfmeWarnUUA(g_bfmeMsgBUUA, g_bfmeFileUUA, 0x46);
	if (m_bfmePending)
		bfmeGetLogUUA()->bfmeWarnUUA(g_bfmeMsgCUUA, g_bfmeFileUUA, 0x47);
}
