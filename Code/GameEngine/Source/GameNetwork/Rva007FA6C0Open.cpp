// cl: /O2
// 0x007FA6C0: open the FESL record at +8 against fesl.ea.com. Returns -202
// if that record is missing. Optional teardown if the flag byte is set.

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual int v2();
};

Rva007E9B70Obj *Rva007E9B70Get();

struct Rva00806580Record;

int Rva00806710(Rva00806580Record *record, const char *host, unsigned a, unsigned b);
void Rva00806A70(Rva00806580Record *record, int flag);

struct Rva007FA6C0Arg
{
	char m_pad[8];
	unsigned m_08;
	unsigned m_0C;
};

class Rva007FA6C0
{
public:
	int openHost(Rva007FA6C0Arg *arg, unsigned char flag);

private:
	char m_pad[8];
	Rva00806580Record *m_08;
	int m_0C;
};

int Rva007FA6C0::openHost(Rva007FA6C0Arg *arg, unsigned char flag)
{
	if (!m_08)
		return -202;
	m_0C = Rva007E9B70Get()->v2();
	unsigned b = arg->m_0C;
	unsigned a = arg->m_08;
	int r = Rva00806710(m_08, "fesl.ea.com", a, b);
	if (flag)
		Rva00806A70(m_08, 1);
	return r;
}
