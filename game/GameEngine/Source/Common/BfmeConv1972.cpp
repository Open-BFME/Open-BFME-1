class BfmeDictESI
{
public:
	void *bfmeGetESI(const char *key, void *fallback);
};

class BfmeStateESI
{
public:
	virtual void bfmeSlot00ESI();
	virtual void bfmeSlot01ESI();
	virtual void bfmeSlot02ESI();
	virtual void bfmeSlot03ESI();
	virtual void bfmeSlot04ESI();
	virtual void bfmeSlot05ESI();
	virtual void bfmeSlot06ESI();
	virtual void bfmeSlot07ESI();
	virtual void bfmeSlot08ESI();
	virtual void bfmeSlot09ESI();
	virtual void bfmeSlot10ESI();
	virtual void bfmeSlot11ESI();
	virtual void bfmeSlot12ESI();
	virtual int bfmeSlot13ESI(void *pid);
	void bfmeSetESI(int value);
};

class BfmeLogESI
{
public:
	virtual void bfmeLog00ESI();
	virtual void bfmeLog01ESI();
	virtual void bfmeLog02ESI();
	virtual void bfmeLog03ESI(const char *what, const char *file, int line);
};

BfmeLogESI *bfmeLogGetESI();

class BfmeSinkESI
{
public:
	virtual void bfmeSink00ESI();
	virtual void bfmeSink01ESI();
	virtual void bfmeSink02ESI();
	virtual void bfmeSink03ESI();
	virtual void bfmeSink04ESI();
	virtual void bfmeSink05ESI();
	virtual void bfmeSink06ESI();
	virtual void bfmeSink07ESI();
	virtual void bfmeSink08ESI();
	virtual void bfmeSink09ESI();
	virtual void bfmeSink10ESI();
	virtual void bfmeSink11ESI();
	virtual void bfmeSink12ESI();
	virtual void bfmeSink13ESI();
	virtual void bfmeSink14ESI();
	virtual void bfmeSink15ESI();
	virtual void bfmeSink16ESI();
	virtual void bfmeSink17ESI(void *pid);
};

class BfmeHostESI
{
public:
	void bfmeApplyESI(BfmeDictESI *dict);

	unsigned char m_bfmeHeadESI[0x1c];
	BfmeSinkESI *m_bfme1cESI;
	unsigned char m_bfmeMidESI[0x2b8];
	BfmeStateESI *m_bfme2d8ESI;
};

void BfmeHostESI::bfmeApplyESI(BfmeDictESI *dict)
{
	if (m_bfme2d8ESI == 0)
		return;

	void *pid = dict->bfmeGetESI("PID", 0);

	int value = m_bfme2d8ESI->bfmeSlot13ESI(pid);

	if (value == 0)
	{
		BfmeLogESI *log = bfmeLogGetESI();

		log->bfmeLog03ESI("hp", "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp", 0x5f6);

		return;
	}

	m_bfme2d8ESI->bfmeSetESI(value);

	m_bfme1cESI->bfmeSink17ESI(pid);
}
