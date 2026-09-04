// EA FESL gamebrowser host-state request at retail 0x007F5C30.

class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	~BfmeMsgVJH() throw();
	char m_pad[0x34];
};

struct Rva007EB810Diag
{
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva00800290Buffer
{
public:
	void append(const char *text);
};

class Rva007F5C30HostedPlayer
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual int getState();
};

class Rva007F5C30HostLookup
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual Rva007F5C30HostedPlayer *find(int id);
};

class Rva007F5C30Sender
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void send(BfmeMsgVJH *msg, int request, int id, int state);
};

class Rva007F5C30Notifier
{
public:
	virtual void v00();
	virtual void v04();
	virtual void send(BfmeMsgVJH *msg, void (__stdcall *callback)(),
		void *owner, int value);
};

class Rva00802290Owner
{
public:
	void reset();
};

class Rva008022A0Owner
{
public:
	void setHpState(int state);
};

class BfmeThingVJS
{
public:
	void bfmeGoVJS(int id, int requesting, int state) throw();

	char m_pad00[0x10];
	Rva007F5C30Sender *m_bfme10;
	Rva007F5C30Notifier *m_bfme14;
	char m_pad18[0x2c0];
	Rva007F5C30HostLookup *m_bfme2d8;
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJS::bfmeGoVJS(int id, int requesting, int state) throw()
{
	Rva007F5C30HostedPlayer *hp = m_bfme2d8->find(id);
	if (hp == 0)
	{
		Rva007EB810Get()->fail("hp",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x3f9);
		return;
	}
	if (hp->getState() != 1)
	{
		Rva007EB810Get()->fail(
			"hp->GetState() == HostedPlayerStateRequestingApproval",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x3fd);
	}
	if ((unsigned char)requesting)
		((Rva008022A0Owner *)hp)->setHpState(2);
	else
		((Rva00802290Owner *)hp)->reset();

	BfmeMsgVJH msg(m_bfmeBuf, 0x400);
	m_bfme10->send(&msg, requesting, id, state);
	m_bfme14->send(&msg, 0, this, m_bfme6dc);
}
