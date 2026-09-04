// ?d_00271630@@YAXXZ
// partial score=0.92 date=2026-09-04
class BfmeHostHA
{
public:
	virtual void bfmeSpare00HA(void) = 0;
	virtual void bfmeSpare01HA(void) = 0;
	virtual void bfmeSpare02HA(void) = 0;
	virtual void bfmeSpare03HA(void) = 0;
	virtual void bfmeSpare04HA(void) = 0;
	virtual void bfmePrepHA(void) = 0;          // +0x14 slot 5
	virtual void bfmeSpare06HA(void) = 0;
	virtual void bfmeSpare07HA(void) = 0;
	virtual void bfmePulseHA(int code) = 0;     // +0x20 slot 8
	virtual void bfmeSpare09HA(void) = 0;
	virtual void bfmeSpare10HA(void) = 0;
	virtual void bfmeSpare11HA(void) = 0;
	virtual void bfmeSpare12HA(void) = 0;
	virtual void bfmeSpare13HA(void) = 0;
	virtual void bfmeAimHA(void *who) = 0;      // +0x38 slot 14
};

class BfmeGlobHA
{
public:
	unsigned char bfmeAskHA(void *obj, void *a, void *b);
};

extern BfmeGlobHA *g_bfmeGlobHA;

class BfmeThingHA
{
public:
	void bfmeGoHA(void *a, void *b);
	static BfmeGlobHA *globHA(void) { return g_bfmeGlobHA; }

private:
	unsigned char m_bfmePad00[8];
	void *m_bfmeObject;                 // +0x08
	unsigned char m_bfmePad0C[0x24];    // +0x0C
	BfmeHostHA *m_bfmeHost;
	unsigned char m_bfmePad34[0x14];    // +0x34
	void *m_bfmeSaved;                  // +0x48
};

void BfmeThingHA::bfmeGoHA(void *a, void *b)
{
	if (!globHA()->bfmeAskHA(m_bfmeObject, a, b))
		return;
	m_bfmeHost->bfmePrepHA();
	m_bfmeHost->bfmeAimHA(a);
	m_bfmeSaved = b;
	m_bfmeHost->bfmePulseHA(0x3c);
}
