// Open-BFME5 conversions.

class BfmeSubTNC
{
public:
	virtual void bfmeV0TNC() = 0;
	virtual void bfmeV1TNC() = 0;
	virtual void bfmeV2TNC() = 0;
	virtual void bfmeV3TNC() = 0;
	virtual int bfmeRunTNC() = 0;
};

struct BfmeGuardTNC
{
	char m_bfmePad[0x40];
	char m_bfmeBusy;
};

class BfmeThingTNC
{
public:
	int bfmeGoTNC();
	char m_bfmePad[0x1c];
	BfmeGuardTNC *m_bfmeGuard;
	char m_bfmePad2[4];
	BfmeSubTNC *m_bfmeSub;
};

int BfmeThingTNC::bfmeGoTNC()
{
	if (!m_bfmeSub)
		return 0;
	m_bfmeGuard->m_bfmeBusy = 1;
	int r = m_bfmeSub->bfmeRunTNC();
	m_bfmeGuard->m_bfmeBusy = 0;
	return r > 0 ? 0 : r;
}

class BfmeSubTND
{
public:
	virtual void bfmeV0TND() = 0;
	virtual void bfmeV1TND() = 0;
	virtual void bfmeV2TND() = 0;
	virtual void bfmeV3TND() = 0;
	virtual int bfmeCountTND() = 0;
};

class BfmeThingTND
{
public:
	void bfmeGoTND();
	char m_bfmePad[0xdc];
	BfmeSubTND *m_bfmeSub;
	float m_bfmeValue;
	float m_bfmePrev;
};

void BfmeThingTND::bfmeGoTND()
{
	BfmeSubTND *s = m_bfmeSub;
	if (s) {
		m_bfmePrev = m_bfmeValue;
		m_bfmeValue = (float)(s->bfmeCountTND() - 1);
	}
}
