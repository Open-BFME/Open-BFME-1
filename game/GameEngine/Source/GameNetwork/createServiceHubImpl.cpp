// cl: /O2
// 0x007EB1C0: FESL hubsingle.cpp ServiceHubImpl singleton factory.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

void *Gen007F0130(unsigned int size);

class ServiceHubImpl
{
public:
	ServiceHubImpl(void *a, void *b, void *c, void *d, void *e, void *f) throw();

	char m_pad[0x2B0];
};

inline void *operator new(unsigned int, void *p)
{
	return p;
}

void *bfmeGo929C(void);
void Rva007F0120(void *a, void *b);
Rva007EB810Diag *Rva007EB810Get();
void Rva007EBAA0(void);

extern ServiceHubImpl *g_Va0130A588;
extern unsigned char g_Va0130A58C;
extern unsigned char g_Va0130A58D;

ServiceHubImpl *createServiceHubImpl(void *a, void *b, void *c, void *d, void *e, void *f)
{
	void *p = bfmeGo929C();
	if (p == 0)
	{
		Rva007F0120(p, p);
		g_Va0130A58C = 1;
	}
	if (Rva007EB810Get() == 0)
	{
		Rva007EBAA0();
		g_Va0130A58D = 1;
	}
	if (g_Va0130A588)
		Rva007EB810Get()->fail(
			"!ServiceHubImpl::gInstance",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\hubsingle.cpp",
			0x35);
	void *raw = Gen007F0130(0x2B0);
	if (raw)
	{
		g_Va0130A588 = new (raw) ServiceHubImpl(a, b, c, d, e, f);
		return g_Va0130A588;
	}
	g_Va0130A588 = 0;
}
