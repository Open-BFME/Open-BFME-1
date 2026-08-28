struct BfmeCsDXB
{
	unsigned char m_bfmeHead[0x18];
};

class BfmeSubDXB
{
public:
	void bfmeCallDXB();
};

extern "C" __declspec(dllimport) void __stdcall bfmeInitDXB(BfmeCsDXB *cs);

struct BfmeThingDXB
{
	void bfmeGoDXB();
	unsigned char m_bfmeHead[0x18];
	BfmeCsDXB m_bfmeCs;
	BfmeSubDXB m_bfmeSub;
};

void BfmeThingDXB::bfmeGoDXB()
{
	bfmeInitDXB(&m_bfmeCs);
	m_bfmeSub.bfmeCallDXB();
}

extern "C" __declspec(dllimport) void __cdecl bfmeFreeDXC(void *what);

struct BfmeThingDXC
{
	void bfmeGoDXC();
	void bfmeTailDXC();
	unsigned char m_bfmeHead[0x48];
	void *m_bfmeP;
};

void BfmeThingDXC::bfmeGoDXC()
{
	bfmeFreeDXC(m_bfmeP);
	bfmeTailDXC();
}

extern "C" __declspec(dllimport) int __stdcall bfmeStatusDXD(void *h);

struct BfmeThingDXD
{
	bool bfmeGoDXD();
	unsigned char m_bfmeHead[4];
	void *m_bfmeH;
};

bool BfmeThingDXD::bfmeGoDXD()
{
	void *h = m_bfmeH;
	if (!h)
		return true;
	return bfmeStatusDXD(h) != 4;
}

extern "C" __declspec(dllimport) int __stdcall bfmeQueryDXE(void *what);
extern unsigned char g_bfmeArgDXE[];
void __stdcall bfmeFailDXE(int code);

void bfmeGoDXE()
{
	int r = bfmeQueryDXE(g_bfmeArgDXE);
	if (r < 0)
		bfmeFailDXE(r);
}

extern "C" __declspec(dllimport) int __stdcall bfmeMaskDXF(void *a);

bool bfmeGoDXF(void *a)
{
	return (bfmeMaskDXF(a) & 0xffff7fff) == 1;
}
