class BfmeVirtQR
{
public:
	virtual void bfmeV00QR();
	virtual void bfmeV04QR();
	virtual void bfmeV08QR();
	virtual void bfmeV0CQR();
	virtual void bfmeV10QR();
	virtual void bfmeV14QR();
	virtual void bfmeV18QR();
	virtual void bfmeV1CQR();
	virtual int bfmeV20QR();
};

class BfmeMidQR
{
public:
	unsigned char m_bfmeHeadQR[0x200];
	BfmeVirtQR *m_bfme200QR;
};

class BfmeHostQR
{
public:
	void *bfmeApplyQR(void *arg);
	void Rva00417430AudioSelector(void *out, int selector);

	unsigned char m_bfmeHeadQR[0xfc];
	BfmeMidQR *m_bfmeFCQR;
};

void *BfmeHostQR::bfmeApplyQR(void *arg)
{
	BfmeMidQR *p = m_bfmeFCQR;
	int r = 0;
	int volatile deadQR = r;

	if (p != 0)
		r = p->m_bfme200QR->bfmeV20QR();

	Rva00417430AudioSelector(arg, r);

	return arg;
}
