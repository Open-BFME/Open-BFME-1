// cl: /O2
// 0x007EAE30: ServiceHubImpl constructor. Three Snapshot-shaped members,
// bounded copies from fesl/internal/util.h, then NetConn init.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get();

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" char *__cdecl strncpy(char *dest, const char *source, unsigned int count);

#pragma intrinsic(strlen)

class Rva7F4CC0Child
{
public:
	Rva7F4CC0Child();
	virtual void v0();

private:
	int m_04;
};

extern int vftable_01129CB0;
extern int vftable_011296B0;

class HubSub : public Rva7F4CC0Child
{
public:
	HubSub()
	{
		*(int *)this = (int)&vftable_011296B0;
		m_08 = 0;
		m_0C = 0;
		*(int *)((char *)this + 4) = 0;
	}
	virtual void v0();
	void *m_08;
	void *m_0C;
};

class ServiceHubImpl
{
public:
	ServiceHubImpl(void *a, void *b, void *c, void *d, void *e, void *f) throw();
	virtual void v0();
	void init();

private:
	void *m_04;
	void *m_08;
	void *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30[0x20];
	char m_50[0x20];
	char m_70[0x10];
	char m_80[0x10];
	char m_90;
	char m_pad91[0x0F];
	char m_A0;
	char m_padA1[0x40];
	char m_E1;
	char m_padE2[0x1F];
	char m_101;
	char m_pad102[0x40];
	char m_142;
	char m_pad143[0x40];
	char m_183;
	char m_pad184[0x5F];
	char m_1E3;
	char m_pad1E4[0x1F];
	char m_203[0x20];
	char m_pad223[1];
	int m_224;
	int m_228;
	int m_22C;
	char m_230;
	char m_pad231[3];
	void *m_234;
	void *m_238;
	void *m_23C;
	void *m_240;
	void *m_244;
	int m_248;
	int m_24C;
	void *m_250;
	void *m_254;
	HubSub m_258;
	void *m_268;
	void *m_26C;
	HubSub m_270;
	void *m_280;
	void *m_284;
	void *m_288;
	HubSub m_28C;
	void *m_29C;
	void *m_2A0;
	void *m_2A4;
	void *m_2A8;
	char m_2AC;
};

ServiceHubImpl::ServiceHubImpl(void *a, void *b, void *c, void *d, void *e, void *f) throw()
{
	m_04 = this;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_08 = e;
	if (!a)
		Rva007EB810Get()->fail("src",
			"..\\..\\source\\include\\fesl/internal/util.h", 33);
	if (!(strlen((const char *)a) < 0x20))
		Rva007EB810Get()->fail("strlen(src) < dstSize",
			"..\\..\\source\\include\\fesl/internal/util.h", 34);
	strncpy(m_30, (const char *)a, 0x20);
	if (!b)
		Rva007EB810Get()->fail("src",
			"..\\..\\source\\include\\fesl/internal/util.h", 33);
	if (!(strlen((const char *)b) < 0x20))
		Rva007EB810Get()->fail("strlen(src) < dstSize",
			"..\\..\\source\\include\\fesl/internal/util.h", 34);
	strncpy(m_50, (const char *)b, 0x20);
	if (!c)
		Rva007EB810Get()->fail("src",
			"..\\..\\source\\include\\fesl/internal/util.h", 33);
	if (!(strlen((const char *)c) < 0x10))
		Rva007EB810Get()->fail("strlen(src) < dstSize",
			"..\\..\\source\\include\\fesl/internal/util.h", 34);
	strncpy(m_70, (const char *)c, 0x10);
	if (!d)
		Rva007EB810Get()->fail("src",
			"..\\..\\source\\include\\fesl/internal/util.h", 33);
	if (!(strlen((const char *)d) < 0x10))
		Rva007EB810Get()->fail("strlen(src) < dstSize",
			"..\\..\\source\\include\\fesl/internal/util.h", 34);
	strncpy(m_80, (const char *)d, 0x10);
	if (f)
	{
		if (!(strlen((const char *)f) < 0x20))
			Rva007EB810Get()->fail("strlen(src) < dstSize",
				"..\\..\\source\\include\\fesl/internal/util.h", 34);
		strncpy(m_203, (const char *)f, 0x20);
	}
	else
		m_203[0] = 0;
	m_90 = 0;
	m_A0 = 0;
	m_E1 = 0;
	m_101 = 0;
	m_142 = 0;
	m_183 = 0;
	m_1E3 = 0;
	m_234 = 0;
	m_248 = 0;
	m_238 = 0;
	m_23C = 0;
	m_240 = 0;
	m_244 = 0;
	m_280 = 0;
	m_29C = 0;
	m_2A4 = 0;
	m_2A8 = 0;
	m_254 = 0;
	m_26C = 0;
	m_288 = 0;
	m_250 = 0;
	m_268 = 0;
	m_284 = 0;
	m_2A0 = 0;
	m_0C = 0;
	m_224 = 0;
	m_228 = 0;
	m_22C = 0;
	m_24C = 0;
	m_230 = 1;
	m_2AC = 0;
	init();
}
