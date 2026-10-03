class BfmeObsZS
{
public:
	virtual void bfmeV0ZS();
	virtual void bfmeV1ZS();
	virtual void bfmeV2ZS();
	virtual void bfmeV3ZS();
	virtual void bfmeEventZS(void *owner, void *a, void *b, void *c);
};

class BfmeMsgHandler
{
public:
	int defaultHandler(int msg, void *p2, void *p3);
	int checkMsg(int msg, void *p2, void *p3);
};

class BfmeOwnerZS
{
public:
	int bfmeNotifyZS(void *a, void *b, void *c);

	unsigned char m_bfmeHeadZS[0x25c];
	BfmeObsZS **m_bfmeBeginZS;
	BfmeObsZS **m_bfmeEndZS;
};

int BfmeOwnerZS::bfmeNotifyZS(void *a, void *b, void *c)
{
	((BfmeMsgHandler *)this)->defaultHandler((int)a, b, c);

	for (BfmeObsZS **p = m_bfmeBeginZS; p != m_bfmeEndZS; p++)
		(*p)->bfmeEventZS(this, a, b, c);

	return 1;
}
