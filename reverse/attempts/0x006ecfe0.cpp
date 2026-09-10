// ?d_006ecfe0@@YAXXZ
// partial score=0.92 date=2026-09-08
class TextureEVG
{
public:
	void bfmeReleaseRefEVG();
};

class BfmeRefEVG
{
public:
	__forceinline BfmeRefEVG() { m_bfmePtrEVG = 0; }
	__forceinline ~BfmeRefEVG()
	{
		if (m_bfmePtrEVG != 0)
			m_bfmePtrEVG->bfmeReleaseRefEVG();
	}

	TextureEVG *m_bfmePtrEVG;
};

class Render2DEVG
{
public:
	void bfmeResetEVG();

	unsigned char m_bfmeHeadEVG[0x4c];
	TextureEVG *volatile m_bfmeTexEVG;
	int m_bfmeFlagEVG;
};

class BfmeItemEVG
{
public:
	virtual void bfmeSlot00EVG();
	virtual void bfmeSlot01EVG();
	virtual void bfmeSlot02EVG();
	virtual void bfmeSlot03EVG();
	virtual void bfmeSlot04EVG();
	virtual void bfmeSlot05EVG();
	virtual void bfmeSlot06EVG();
	virtual void bfmeSlot07EVG();
	virtual void bfmeSlot08EVG();
	virtual void bfmeSlot09EVG();
	virtual void bfmeSlot10EVG();
	virtual void bfmeReleaseEVG();
};

class BfmeHostEVG
{
public:
	void bfmeClearEVG();

	unsigned char m_bfmeHeadEVG[0x164];
	Render2DEVG *m_bfmeR2DEVG;
	unsigned char m_bfmePadEVG[0x134];
	BfmeItemEVG **m_bfmeBeginEVG;
	BfmeItemEVG **m_bfmeEndEVG;
};

void BfmeHostEVG::bfmeClearEVG()
{
	BfmeRefEVG ref;
	Render2DEVG *r = m_bfmeR2DEVG;

	if (r->m_bfmeTexEVG != 0)
	{
		TextureEVG *tex = r->m_bfmeTexEVG;

		if (tex != 0)
			tex->bfmeReleaseRefEVG();

		r->m_bfmeTexEVG = 0;
		r->m_bfmeFlagEVG = r->m_bfmeTexEVG != 0 ? -1 : 0;
	}

	m_bfmeR2DEVG->bfmeResetEVG();

	for (BfmeItemEVG **p = m_bfmeBeginEVG; p != m_bfmeEndEVG; p++)
		(*p)->bfmeReleaseEVG();
}
