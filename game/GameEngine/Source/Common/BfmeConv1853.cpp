class BfmeShownXU
{
public:
	void bfmeShowXU();
};

class BfmeMakerXU
{
public:
	BfmeShownXU *bfmeMakeXU(int what);
};

class BfmeSrcXU
{
public:
	virtual void bfmeS00XU();
	virtual void bfmeS01XU();
	virtual void bfmeS02XU();
	virtual void bfmeS03XU();
	virtual void bfmeS04XU();
	virtual void bfmeS05XU();
	virtual void bfmeS06XU();
	virtual void bfmeS07XU();
	virtual void bfmeS08XU();
	virtual void bfmeS09XU();
	virtual void bfmeS10XU();
	virtual void bfmeS11XU();
	virtual void bfmeS12XU();
	virtual void bfmeS13XU();
	virtual void bfmeS14XU();
	virtual int bfmeGetXU();
};

class BfmeOwnerXU
{
public:
	void bfmeSetXU(int mode);

	unsigned char m_bfmeHeadXU[4];
	BfmeMakerXU *m_bfmeAXU;
	BfmeSrcXU *m_bfmeBXU;
	unsigned char m_bfmePadXU[4];
	int m_bfmeModeXU;
};

void BfmeOwnerXU::bfmeSetXU(int mode)
{
	m_bfmeModeXU = mode;

	if (mode == 1)
	{
		if (m_bfmeAXU != 0)
			m_bfmeAXU->bfmeMakeXU(0)->bfmeShowXU();
	}

	if (m_bfmeModeXU == 3 || m_bfmeModeXU == 2)
	{
		if (m_bfmeAXU != 0)
			m_bfmeAXU->bfmeMakeXU(m_bfmeBXU->bfmeGetXU())->bfmeShowXU();
	}
}
