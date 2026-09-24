// Windows XP firewall: add this program to the authorized applications
// (retail RVA 0x00690CB0, 518 bytes). Same 0x14-byte owner as
// BfmeThingTTDAppIsEnabled.cpp; the address-derived names are kept.
typedef unsigned short *BSTR;

extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(
	const void *rclsid, void *pUnkOuter, unsigned long dwClsContext,
	const void *riid, void **ppv);
extern "C" __declspec(dllimport) BSTR __stdcall SysAllocString(const unsigned short *value);
extern "C" __declspec(dllimport) unsigned int __stdcall SysStringLen(BSTR value);
extern "C" __declspec(dllimport) void __stdcall SysFreeString(BSTR value);

// Retail VA 0x0111B91C: CLSID_NetFwAuthorizedApplication (first CoCreateInstance argument).
extern const unsigned char g_rva00690cb0Riid[16] = {
	0xb3, 0x46, 0x98, 0xec, 0x62, 0x27, 0x6b, 0x4a,
	0xa2, 0x14, 0x6a, 0xcb, 0x60, 0x34, 0x62, 0xd2
};
// Retail VA 0x0111B930: IID_INetFwAuthorizedApplication (fourth CoCreateInstance argument).
extern const unsigned char g_rva00690cb0Rclsid[16] = {
	0xfa, 0x4f, 0xe6, 0xb5, 0xc5, 0xc2, 0x4e, 0x44,
	0xa3, 0x01, 0xfb, 0x5e, 0x00, 0x01, 0x80, 0x50
};

struct Rva00690CB0Unk;

struct Rva00690CB0Vtbl
{
	void *v0;
	void *v1;
	long (__stdcall *release)(Rva00690CB0Unk *self);
	void *v3, *v4, *v5, *v6, *v7;
	long (__stdcall *callA)(Rva00690CB0Unk *self, void *arg);   // put_Name / Add, +0x20
	void *v9;
	long (__stdcall *callB)(Rva00690CB0Unk *self, void *arg);   // put_ProcessImageFileName, +0x28
	void *v11, *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v19;
	long (__stdcall *create)(Rva00690CB0Unk *self, Rva00690CB0Unk **out); // get_AuthorizedApplications, +0x50
};

struct Rva00690CB0Unk
{
	Rva00690CB0Vtbl *vtable;
};

class Rva00690CB0Owner
{
public:
	bool init();

private:
	const unsigned short *m_00;
	const unsigned short *m_04;
	char m_pad08;
	char m_flag;
	char m_pad0A[2];
	int m_comInitialized;
	Rva00690CB0Unk *m_unknown;
};

bool Rva00690CB0Owner::init()
{
	BSTR h2 = 0;
	BSTR h = 0;
	Rva00690CB0Unk *outB = 0;
	Rva00690CB0Unk *outA = 0;

	if (!m_flag)
	{
		long hr = m_unknown->vtable->create(m_unknown, &outA);
		if (hr < 0)
		{
			if (outA) outA->vtable->release(outA);
			return false;
		}

		hr = CoCreateInstance(g_rva00690cb0Riid, 0, 1, g_rva00690cb0Rclsid, (void **)&outB);
		if (hr < 0)
		{
			if (outA) outA->vtable->release(outA);
			if (outB) outB->vtable->release(outB);
			return false;
		}

		h = SysAllocString(m_04);
		if (SysStringLen(h) == 0)
		{
			if (outA) outA->vtable->release(outA);
			if (outB) outB->vtable->release(outB);
			return false;
		}

		hr = outB->vtable->callB(outB, h);
		if (hr < 0)
		{
			if (outA) outA->vtable->release(outA);
			if (outB) outB->vtable->release(outB);
			return false;
		}

		h2 = SysAllocString(m_00);
		if (SysStringLen(h2) == 0)
		{
			SysFreeString(h);
			if (outA) outA->vtable->release(outA);
			if (outB) outB->vtable->release(outB);
			return false;
		}

		hr = outB->vtable->callA(outB, h2);
		if (hr < 0)
		{
			SysFreeString(h);
			SysFreeString(h2);
			if (outA) outA->vtable->release(outA);
			if (outB) outB->vtable->release(outB);
			return false;
		}

		hr = outA->vtable->callA(outA, outB);
		if (hr < 0)
		{
			SysFreeString(h);
			SysFreeString(h2);
			if (outA) outA->vtable->release(outA);
			if (outB) outB->vtable->release(outB);
			return false;
		}
	}

	SysFreeString(h2);
	SysFreeString(h);
	if (outB) outB->vtable->release(outB);
	if (outA) outA->vtable->release(outA);
	m_flag = 1;
	return true;
}
