extern "C" void *bfmeVftSJ[];

class BfmeThingSJ
{
public:
	void bfmeBaseSJ(int mode);
	void bfmeReleaseSJ();

	__forceinline BfmeThingSJ()
	{
		bfmeBaseSJ(0);

		m_bfmeVftSJ = bfmeVftSJ;
	}

	void *volatile m_bfmeVftSJ;
	unsigned short m_bfmeRefSJ;
	unsigned char m_bfmeBodySJ[0x36];
};

class BfmeObjSJ
{
public:
	virtual void bfmeSlot00SJ();
	virtual void bfmeSlot01SJ();
	virtual void bfmeSlot02SJ();
	virtual void bfmeSlot03SJ();
	virtual void bfmeSlot04SJ();
	virtual void bfmeSlot05SJ();
	virtual void bfmeSlot06SJ();
	virtual void bfmeSlot07SJ();
	virtual void bfmeSlot08SJ();
	virtual void bfmeSlot09SJ();
	virtual void bfmeSlot10SJ();
	virtual void bfmeSlot11SJ();
	virtual void bfmeSlot12SJ();
	virtual int bfmeKindSJ();
};

class BfmeSrcSJ
{
public:
	BfmeObjSJ *m_bfmeObjSJ;
};

class BfmeBaseSJ
{
public:
	__forceinline BfmeBaseSJ() { m_bfmeTexSJ = 0; }
	~BfmeBaseSJ();

	BfmeThingSJ *m_bfmeTexSJ;
};

class BfmeHostSJ : public BfmeBaseSJ
{
public:
	BfmeHostSJ(BfmeSrcSJ *src);
};

BfmeHostSJ::BfmeHostSJ(BfmeSrcSJ *src)
{
	if (src->m_bfmeObjSJ != 0 && src->m_bfmeObjSJ->bfmeKindSJ() == 0x544558)
	{
		BfmeThingSJ *tex = new BfmeThingSJ();

		if (tex != 0)
		{
			tex->m_bfmeRefSJ++;

			if (m_bfmeTexSJ != 0)
				m_bfmeTexSJ->bfmeReleaseSJ();

			m_bfmeTexSJ = tex;
		}
	}
}
