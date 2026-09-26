class BfmeBufERR;

class BfmeAudioERR
{
public:
	virtual void bfmeSlot00ERR();
	virtual void bfmeSlot01ERR();
	virtual void bfmeSlot02ERR();
	virtual void bfmeSlot03ERR();
	virtual void bfmeSlot04ERR();
	virtual void bfmeSlot05ERR();
	virtual void bfmeSlot06ERR();
	virtual void bfmeSlot07ERR();
	virtual void bfmeSlot08ERR();
	virtual void bfmeSlot09ERR();
	virtual void bfmeSlot10ERR();
	virtual void bfmeSlot11ERR();
	virtual void bfmeSlot12ERR();
	virtual void bfmeSlot13ERR();
	virtual void bfmeSlot14ERR();
	virtual void bfmeSlot15ERR();
	virtual void bfmeSlot16ERR();
	virtual int bfmeSlot17ERR(BfmeBufERR *buf);
	virtual void bfmeSlot18ERR();
	virtual void bfmeSlot19ERR(int handle);
};

extern BfmeAudioERR *g_bfmeAudioERR;

class BfmeBufERR
{
public:
	BfmeBufERR(void *first, void *second);
	~BfmeBufERR();

	unsigned char m_bfmeBodyERR[0x70];
};

class BfmeXERR
{
public:
	unsigned char m_bfmeHeadERR[0x74];
	void *m_bfmeValueERR;
};

class BfmeYERR
{
public:
	void bfmeDoERR(BfmeXERR *owner, unsigned int count);
};

class BfmeNodeERR
{
public:
	unsigned char m_bfmeHeadERR[8];
	unsigned char m_bfmePayloadERR[4];
	unsigned int m_bfmeCountERR;
};

class BfmeHostERR
{
public:
	void bfmeUpdateERR();

	unsigned char m_bfmeHeadERR[0xc];
	int m_bfmeHandleERR;
};

void BfmeHostERR::bfmeUpdateERR()
{
	BfmeAudioERR *audio = g_bfmeAudioERR;
	BfmeNodeERR *node = *(BfmeNodeERR **)((char *)this - 0x1c);

	if (audio != 0)
	{
		int handle = m_bfmeHandleERR;

		if (handle != 1)
			audio->bfmeSlot19ERR(handle);

		BfmeXERR *owner = *(BfmeXERR **)((char *)this - 0x18);
		void *value = owner->m_bfmeValueERR;
		BfmeBufERR buf(node->m_bfmePayloadERR, value);
		BfmeBufERR *arg = &buf;

		m_bfmeHandleERR = g_bfmeAudioERR->bfmeSlot17ERR(arg);
	}

	if (node->m_bfmeCountERR > 0)
		((BfmeYERR *)((char *)this - 0x20))->bfmeDoERR(
			*(BfmeXERR **)((char *)this - 0x18), node->m_bfmeCountERR);
}
