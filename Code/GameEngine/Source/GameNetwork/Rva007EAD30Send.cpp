// cl: /O2
// 0x007EAD30 / 0x007EADC0: after a prepare helper, send either the flag
// string at +0x101/+0x142 or the +0x30/+0x70 pair through this+0xC.

class Rva007EADIface
{
public:
	virtual void v0();
	virtual void sendFlag(char *flag, int n, int tag, void *self);
	virtual void v2();
	virtual void sendPairC(char *a, char *b, int tag, void *self);
	virtual void sendPairD(char *a, char *b, int tag, void *self);
};

class Rva007EAD30Owner
{
public:
	void send();
	void prepare();

private:
	char m_pad00[0x0C];
	Rva007EADIface *m_iface;
	char m_pad10[0x20];
	char m_buf30[0x40];
	char m_buf70[0x91];
	char m_flag;
	char m_pad102[0x126];
	int m_n;
};

class Rva007EADC0Owner
{
public:
	void send();
	void prepare();

private:
	char m_pad00[0x0C];
	Rva007EADIface *m_iface;
	char m_pad10[0x20];
	char m_buf30[0x40];
	char m_buf70[0xD2];
	char m_flag;
	char m_pad143[0xE9];
	int m_n;
};

void Rva007EAD30Owner::send()
{
	prepare();
	char *flag = &m_flag;
	if (m_flag)
	{
		int n = m_n;
		if (n <= 0)
			n = 0x34C1;
		m_iface->sendFlag(flag, n, 0x00BEAD10, this);
	}
	else
	{
		m_iface->sendPairC(m_buf30, m_buf70, 0x00BEAD10, this);
	}
}

void Rva007EADC0Owner::send()
{
	prepare();
	char *flag = &m_flag;
	if (m_flag)
	{
		int n = m_n;
		if (n <= 0)
			n = 0x37DC;
		m_iface->sendFlag(flag, n, 0x00BEADA0, this);
	}
	else
	{
		m_iface->sendPairD(m_buf30, m_buf70, 0x00BEADA0, this);
	}
}
