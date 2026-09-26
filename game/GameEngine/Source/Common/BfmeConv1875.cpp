class BfmeSubZH
{
public:
	virtual void bfmeV0ZH();
	virtual void bfmeV1ZH();
	virtual void bfmeV2ZH();
	virtual void bfmeFinishZH();

	void bfmeTakeZH(void *value);
	void bfmeStepZH();
};

class BfmeArgZH
{
public:
	unsigned char m_bfmeHeadZH[4];
	int m_bfmeKindZH;
	unsigned char m_bfmePadZH[4];
	void *m_bfmeValueZH;
};

class BfmeOwnerZH
{
public:
	char bfmeSetZH(BfmeArgZH *arg, void *value);

	unsigned char m_bfmeHeadZH[0x16c];
	BfmeSubZH m_bfmeSubZH;
};

char BfmeOwnerZH::bfmeSetZH(BfmeArgZH *arg, void *value)
{
	arg->m_bfmeValueZH = value;

	if (arg->m_bfmeKindZH == 5)
		m_bfmeSubZH.bfmeTakeZH(value);

	m_bfmeSubZH.bfmeStepZH();
	m_bfmeSubZH.bfmeFinishZH();

	return 1;
}
