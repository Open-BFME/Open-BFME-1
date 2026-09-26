// Open-BFME5 conversion of the FESL gamebrowser request at 0x007F5B80.

class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	~BfmeMsgVJH() throw();
	char m_pad[0x1c];
	int m_error;
	char m_tail[0x14];
};

class BfmeAVJP
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void send(BfmeMsgVJH *msg, int a1, int a2, bool a3, int a4,
		int a5, int a6, int a7, int a8, int a9, int a10, int a11,
		int a12, int a13, int a14) throw();
};

void __stdcall BfmeGameBrowserVJPCallback();

class BfmeBVJP
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void send(BfmeMsgVJH *msg, void (__stdcall *callback)(),
		void *owner, int value) throw();
};

class BfmeThingVJP
{
public:
	void bfmeGoVJP(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		bool flag, int a9, int a10, int a11, int a12, int a13) throw();

	char m_pad00[0x10];
	BfmeAVJP *m_bfme10;
	BfmeBVJP *m_bfme14;
	char m_pad18[0x10];
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	char m_bfme34;
	char m_bfme35;
	bool m_bfme36;
	char m_pad37[0x2a5];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJP::bfmeGoVJP(int a1, int a2, int a3, int a4, int a5,
	int a6, int a7, bool flag, int a9, int a10, int a11, int a12, int a13) throw()
{
	m_bfme36 = flag;
	BfmeMsgVJH msg(m_bfmeBuf, 0x400);
	int selected = m_bfme2c;
	if (selected == 0)
		selected = m_bfme28;
	m_bfme10->send(&msg, a1, a2, m_bfme36, a3, selected, a7, a4,
		a5, a6, a9, a10, a11, a12, a13);
	m_bfme14->send(&msg, BfmeGameBrowserVJPCallback, this, m_bfme6dc);
}
