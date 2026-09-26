// Open-BFME5 conversion of the guarded FESL gamebrowser requests.

class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	~BfmeMsgVJH() throw();
	char m_pad[0x34];
};

class Rva007E8810Message
{
public:
	void setError(int code) throw();
};

class BfmeAsk992
{
public:
	char bfmeHas992C() throw();
	int bfmeGet992C() throw();
};

class BfmeAVJQ
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
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void v38() throw();
	virtual void v3c() throw();
	virtual void v40() throw();
	virtual void v44() throw();
	virtual void v48() throw();
	virtual void v4c() throw();
	virtual void v50() throw();
	virtual void v54() throw();
	virtual void sendFour(void *msg, int a1, int a2, int a3,
		int a4) throw();
	virtual void sendOne(BfmeMsgVJH *msg, int a) throw();
};

extern void __stdcall BfmeGameBrowserVJQCallback();

class BfmeBVJQ
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void send(void *msg, void (__stdcall *callback)(),
		void *owner, int value) throw();
};

class BfmeSinkErrorVJQ
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
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void v38() throw();
	virtual void v3c() throw();
	virtual void v40() throw();
	virtual void v44() throw();
	virtual int sendError(int value) throw();
	virtual void send19(int value) throw();
};

class BfmeSinkZeroVJQ
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
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void v38() throw();
	virtual void v3c() throw();
	virtual void v40() throw();
	virtual void v44() throw();
	virtual void v48() throw();
	virtual void send19(int value) throw();
};

class BfmeThingVJQ
{
public:
	void bfmeGoVJQ(int a) throw();

	char m_pad00[0x10];
	BfmeAVJQ *m_bfme10;
	BfmeBVJQ *m_bfme14;
	char m_pad18[4];
	union
	{
		BfmeSinkErrorVJQ * volatile m_bfme1cError;
		BfmeSinkZeroVJQ *m_bfme1cZero;
	};
	char m_pad20[8];
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	char m_bfme34;
	char m_bfme35;
	char m_pad36[0x2a6];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJQ::bfmeGoVJQ(int a) throw()
{
	BfmeMsgVJH msg(m_bfmeBuf, 0x400);
	if (m_bfme34 && m_bfme30 >= 3)
	{
		m_bfme10->sendOne(&msg, a);
		m_bfme14->send(&msg, BfmeGameBrowserVJQCallback, this, m_bfme6dc);
		return;
	}
	if (m_bfme35)
	{
		Rva007E8810Message *view = (Rva007E8810Message *)&msg;
		BfmeAsk992 *ask = (BfmeAsk992 *)&msg;
		view->setError(-0x70);
		if (ask->bfmeHas992C())
		{
			int error = ask->bfmeGet992C();
			BfmeSinkErrorVJQ *sink = m_bfme1cError;
			sink->send19(error);
			return;
		}
		else
		{
			BfmeSinkZeroVJQ *sink = m_bfme1cZero;
			sink->send19(0);
			return;
		}
	}
}
