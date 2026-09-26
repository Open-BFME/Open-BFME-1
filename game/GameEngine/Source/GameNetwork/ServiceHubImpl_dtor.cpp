// cl: /O2
// 0x007EA6F0: ServiceHubImpl destructor. Stamp the derived vptr, assert each
// service pointer is already null (servicehub.cpp 0x6D..0x7D), then run the
// three 0x007E86C0 member vptr stores and the base vptr.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get();

struct Gen_007e86c0
{
	void m();
};

extern int vftable_01129CB0;
extern int vftable_01129AF4;

class ServiceHubImpl
{
public:
	~ServiceHubImpl();

private:
	char m_pad00[0x0C];
	void *m_0C;
	char m_pad10[0x224];
	void *m_234;
	void *m_238;
	void *m_23C;
	void *m_240;
	void *m_244;
	char m_pad248[8];
	void *m_250;
	void *m_254;
	Gen_007e86c0 m_258;
	char m_pad25C[0x0C];
	void *m_268;
	void *m_26C;
	Gen_007e86c0 m_270;
	char m_pad274[0x0C];
	void *m_280;
	void *m_284;
	void *m_288;
	Gen_007e86c0 m_28C;
	char m_pad290[0x0C];
	void *m_29C;
	void *m_2A0;
	void *m_2A4;
	void *m_2A8;
};

ServiceHubImpl::~ServiceHubImpl()
{
	void *p = m_2A4;
	*(int *)this = (int)&vftable_01129CB0;
	if (p)
		Rva007EB810Get()->fail("mGameBrowser == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x6D);
	if (m_2A8)
		Rva007EB810Get()->fail("mDemangler == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x6E);
	if (m_29C)
		Rva007EB810Get()->fail("mTheaterService == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x6F);
	if (m_280)
		Rva007EB810Get()->fail("mMessengerService == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x70);
	if (m_240)
		Rva007EB810Get()->fail("mClubService == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x71);
	if (m_23C)
		Rva007EB810Get()->fail("mRecordService == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x72);
	if (m_238)
		Rva007EB810Get()->fail("mRankingService == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x73);
	if (m_234)
		Rva007EB810Get()->fail("mAccountService == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x74);
	if (m_244)
		Rva007EB810Get()->fail("mConnectService == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x75);
	if (m_254)
		Rva007EB810Get()->fail("mFeslConnTransactor == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x76);
	if (m_26C)
		Rva007EB810Get()->fail("mMessengerConnTransactor == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x77);
	if (m_288)
		Rva007EB810Get()->fail("mTheaterConnTransactor == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x78);
	if (m_2A0)
		Rva007EB810Get()->fail("mSharedConn == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x79);
	if (m_284)
		Rva007EB810Get()->fail("mTheaterConn == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x7A);
	if (m_268)
		Rva007EB810Get()->fail("mMessengerConn == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x7B);
	if (m_250)
		Rva007EB810Get()->fail("mFeslConn == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x7C);
	if (m_0C)
		Rva007EB810Get()->fail("mFeslNaming == 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp", 0x7D);
	m_28C.m();
	m_270.m();
	m_258.m();
	*(int *)this = (int)&vftable_01129AF4;
}
