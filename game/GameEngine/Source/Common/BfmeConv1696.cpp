void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

class BfmeScopedFM
{
public:
	BfmeScopedFM(void) {}
	~BfmeScopedFM(void) { bfmeUnlock1179(); }

	int m_bfmePadFM;
};

struct BfmeD3DFM;

struct BfmeD3DVtFM
{
	void (__stdcall *m_bfmeSlot0FM)(BfmeD3DFM *self);
	void (__stdcall *m_bfmeSlot1FM)(BfmeD3DFM *self);
	void (__stdcall *m_bfmeReleaseFM)(BfmeD3DFM *self);
};

struct BfmeD3DFM
{
	BfmeD3DVtFM *m_bfmeVtFM;
};

class BfmeTexFM
{
public:
	void bfmeReleaseRefFM(void);
};

class BfmeSurfaceFM
{
public:
	void bfmeUnlockFM(void);

	BfmeD3DFM *m_bfmeD3DFM;
};

class BfmeRadarFM
{
public:
	void bfmeCloseFM(void);

	unsigned char m_bfmeHeadFM[0x34];
	BfmeTexFM *m_bfmeTexFM;
	BfmeSurfaceFM m_bfmeSurfaceFM;
	int m_bfmeFlagsFM;
	unsigned char m_bfmeMidFM[0xa];
	char m_bfmeLockedFM;
};

void BfmeRadarFM::bfmeCloseFM(void)
{
	W3DRadarResetLock();

	BfmeScopedFM scope;

	if ((m_bfmeFlagsFM & 1) != 0)
	{
		m_bfmeSurfaceFM.bfmeUnlockFM();
		m_bfmeFlagsFM &= ~1;
	}

	if (m_bfmeTexFM != 0)
	{
		m_bfmeTexFM->bfmeReleaseRefFM();
		m_bfmeTexFM = 0;
	}

	BfmeD3DFM *surface = m_bfmeSurfaceFM.m_bfmeD3DFM;
	if (surface != 0)
	{
		surface->m_bfmeVtFM->m_bfmeReleaseFM(surface);
		m_bfmeSurfaceFM.m_bfmeD3DFM = 0;
	}

	m_bfmeLockedFM = 0;
}
