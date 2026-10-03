// ?bfmeClearEVG@BfmeHostEVG@@QAEXXZ
// partial score=0.9869 date=2026-10-03
class TextureEVG
{
public:
	void bfmeReleaseRefEVG();
 void bfmeAddRefEVG();
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

	BfmeRefEVG &operator=(const BfmeRefEVG &other) {
 if(other.m_bfmePtrEVG) other.m_bfmePtrEVG->bfmeAddRefEVG();
  if(m_bfmePtrEVG) m_bfmePtrEVG->bfmeReleaseRefEVG();
  m_bfmePtrEVG=other.m_bfmePtrEVG;
 return *this;
}
operator TextureEVG*() const {return m_bfmePtrEVG;}
TextureEVG *m_bfmePtrEVG;
};

class Render2DEVG
{
public:
	void bfmeResetEVG();
void set(const BfmeRefEVG &t) {
 if(m_bfmeTexEVG.m_bfmePtrEVG != t.m_bfmePtrEVG) {
 m_bfmeTexEVG=t;
 m_bfmeFlagEVG = m_bfmeTexEVG ? -1 : 0;
 }
}

	unsigned char m_bfmeHeadEVG[0x4c];
	BfmeRefEVG m_bfmeTexEVG;
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
 m_bfmeR2DEVG->set(BfmeRefEVG());

	m_bfmeR2DEVG->bfmeResetEVG();

	for (BfmeItemEVG **p = m_bfmeBeginEVG; p != m_bfmeEndEVG; p++)
		(*p)->bfmeReleaseEVG();
}
