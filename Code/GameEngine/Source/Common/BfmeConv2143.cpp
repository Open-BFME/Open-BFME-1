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
	virtual void *bfmeV20QR();
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
	void bfmeStoreQR(void *arg, void *val);

	unsigned char m_bfmeHeadQR[0xfc];
	BfmeMidQR *m_bfmeFCQR;
};

void *BfmeHostQR::bfmeApplyQR(void *arg)
{
	BfmeMidQR *p = m_bfmeFCQR;
	void *r = 0;
	void *volatile deadQR = r;

	if (p != r)
		r = p->m_bfme200QR->bfmeV20QR();

	bfmeStoreQR(arg, r);

	return arg;
}
