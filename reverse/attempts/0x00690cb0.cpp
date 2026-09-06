// ?init@Rva00690CB0Owner@@QAE_NXZ
// partial score=0.55 date=2026-09-05
// Open-BFME5: clean C++ conversion of the COM device initializer paired with
// Rva00690B40ComReset.cpp (::reset()). Same field layout: m_unknown at +0x10.
// Two globals at +0x00/+0x04 feed an unidentified pair of "acquire/probe"
// imports; two more unidentified imports back a COM-style interface shared by
// m_unknown, the object returned via its create() slot and the object
// returned by CoCreateInstance.

extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(
	const void *rclsid, void *pUnkOuter, unsigned long dwClsContext,
	const void *riid, void **ppv);
extern "C" __declspec(dllimport) void __stdcall bfmeReleaseTVB(void *h);
extern "C" __declspec(dllimport) void *__stdcall bfmeAcquireTVB(void *param);
extern "C" __declspec(dllimport) long __stdcall bfmeProbeTVB(void *handle);

extern const unsigned char g_rva00690cb0Rclsid[16];
extern const unsigned char g_rva00690cb0Riid[16];

struct Rva00690CB0Unk;

struct Rva00690CB0Vtbl
{
	void *v0;
	void *v1;
	long (__stdcall *release)(Rva00690CB0Unk *self);
	void *v3, *v4, *v5, *v6, *v7;
	long (__stdcall *callA)(Rva00690CB0Unk *self, void *arg);
	void *v9;
	long (__stdcall *callB)(Rva00690CB0Unk *self, void *arg);
	void *v11, *v12, *v13, *v14, *v15, *v16, *v17, *v18, *v19;
	long (__stdcall *create)(Rva00690CB0Unk *self, Rva00690CB0Unk **out);
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
	void *m_00;
	void *m_04;
	char m_pad08;
	char m_flag;
	char m_pad0A[2];
	int m_comInitialized;
	Rva00690CB0Unk *m_unknown;
};

bool Rva00690CB0Owner::init()
{
	Rva00690CB0Unk *outB = 0;
	Rva00690CB0Unk *outA = 0;
	void *h = 0;
	void *h2 = 0;

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

		h = bfmeAcquireTVB(m_04);
		if (bfmeProbeTVB(h))
		{
			long rc = outB->vtable->callB(outB, h);
			if (rc < 0)
			{
				if (outA) outA->vtable->release(outA);
				if (outB) outB->vtable->release(outB);
				return false;
			}

			h2 = bfmeAcquireTVB(m_00);
			if (bfmeProbeTVB(h2))
			{
				rc = outB->vtable->callA(outB, h2);
				if (rc < 0)
				{
					bfmeReleaseTVB(h);
					bfmeReleaseTVB(h2);
					if (outA) outA->vtable->release(outA);
					if (outB) outB->vtable->release(outB);
					return false;
				}

				rc = outA->vtable->callA(outA, outB);
				if (rc < 0)
				{
					bfmeReleaseTVB(h);
					bfmeReleaseTVB(h2);
					if (outA) outA->vtable->release(outA);
					if (outB) outB->vtable->release(outB);
					return false;
				}
			}
			else
			{
				bfmeReleaseTVB(h);
				if (outA) outA->vtable->release(outA);
				if (outB) outB->vtable->release(outB);
				return false;
			}
		}
		else
		{
			if (outA) outA->vtable->release(outA);
			if (outB) outB->vtable->release(outB);
			return false;
		}
	}

	bfmeReleaseTVB(h2);
	bfmeReleaseTVB(h);
	if (outB) outB->vtable->release(outB);
	if (outA) outA->vtable->release(outA);
	m_flag = 1;
	return true;
}
