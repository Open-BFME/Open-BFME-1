// cl: /O2
// 0x007EAC30: strncpy MAC into +0x1E3, lazy-make +0x244, then send through
// the +0xA0 flag or the +0x30/+0x70/+0x90 triple.

class Rva007EAC30Iface
{
public:
	virtual void v0();
	virtual void sendFlag(char *flag, int n, int tag, void *self);
	virtual void sendTriple(char *a, char *b, char *c, int n, int tag, void *self);
};

class Rva007EAC30Inner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot2(int a, void *arg);
};

class Rva007EAC30Nested
{
public:
	char m_pad[0x6A8];
	Rva007EAC30Inner *m_inner;
};

struct Bfme5Obj70
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void run();
};

class Rva007EAC30Peer
{
public:
	char m_pad00[0x0C];
	Rva007EAC30Iface *m_iface;
	char m_pad10[0x90];
	char m_flag;
};

extern "C" char *strncpy(char *dest, const char *src, unsigned int n);
char *Rva007F89F0(void);
Bfme5Obj70 *bfme5MakeObj70(int arg);

class Rva007EAC30Owner
{
public:
	void send(int arg);

private:
	char m_pad00[4];
	Rva007EAC30Peer *m_04;
	char m_pad08[4];
	Rva007EAC30Iface *m_0C;
	char m_pad10[0x20];
	char m_buf30[0x40];
	char m_buf70[0x20];
	char m_buf90[0x10];
	char m_bufA0[0x143];
	char m_name[0x1F];
	char m_pad202[0x22];
	int m_224;
	char m_pad228[0x1C];
	Bfme5Obj70 *m_244;
	char m_pad248[0x0C];
	Rva007EAC30Nested *m_254;
	char m_pad258[0x54];
	char m_2AC;
};

void Rva007EAC30Owner::send(int arg)
{
	char *mac = Rva007F89F0();
	strncpy(m_name, mac, 0x1F);
	if (!m_244)
		m_244 = bfme5MakeObj70((int)this);
	m_244->run();
	m_254->m_inner->slot2(1, 0);
	m_2AC = 0;
	if (m_04->m_flag)
	{
		int n = m_224;
		m_04->m_iface->sendFlag(m_bufA0, n > 0 ? n : arg, 0x00BEAC10, this);
	}
	else
	{
		int n = m_224;
		if (n <= 0)
			n = arg;
		m_0C->sendTriple(m_buf30, m_buf70, m_buf90, n, 0x00BEAC10, this);
	}
}
