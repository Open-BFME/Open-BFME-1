class BfmeObsZS
{
public:
	virtual void bfmeV0ZS();
	virtual void bfmeV1ZS();
	virtual void bfmeV2ZS();
	virtual void bfmeV3ZS();
	virtual void bfmeEventZS(void *owner, void *a, void *b, void *c);
};

class BfmeOwnerZS
{
public:
	int bfmeNotifyZS(void *a, void *b, void *c);

	void bfmeSelfZS(void *a, void *b, void *c);

	unsigned char m_bfmeHeadZS[0x25c];
	BfmeObsZS **m_bfmeBeginZS;
	BfmeObsZS **m_bfmeEndZS;
};

int BfmeOwnerZS::bfmeNotifyZS(void *a, void *b, void *c)
{
	bfmeSelfZS(a, b, c);

	for (BfmeObsZS **p = m_bfmeBeginZS; p != m_bfmeEndZS; p++)
		(*p)->bfmeEventZS(this, a, b, c);

	return 1;
}
