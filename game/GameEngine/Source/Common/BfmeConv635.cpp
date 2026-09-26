struct BfmeXCRB
{
	unsigned char m_bfmeHead[0xb0];
	float m_bfmeVal;
};

class BfmeSubCRB
{
public:
	virtual void bfmeSpareCRB0();
	virtual void bfmeSpareCRB1();
	virtual void bfmeSpareCRB2();
	virtual void bfmeSpareCRB3();
	virtual void bfmeSpareCRB4();
	virtual void bfmeSpareCRB5();
	virtual void bfmeSpareCRB6();
	virtual void bfmeSpareCRB7();
	virtual void bfmeSpareCRB8();
	virtual void bfmeSpareCRB9();
	virtual BfmeXCRB *bfmeGetCRB();
};

class BfmeThingCRB
{
public:
	void bfmeOneCRB(void *one, void *two);
	void bfmeGoCRB(void *one, void *two);
	unsigned char m_bfmeHead[8];
	BfmeSubCRB *m_bfmeSub;
};

void BfmeThingCRB::bfmeGoCRB(void *one, void *two)
{
	bfmeOneCRB(one, two);
	if (m_bfmeSub->bfmeGetCRB() != 0)
		m_bfmeSub->bfmeGetCRB()->m_bfmeVal = 1.0f;
}
