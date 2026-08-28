class BfmeMakerAWB
{
public:
	virtual void bfmeSpareAWB0();
	virtual void bfmeSpareAWB1();
	virtual void bfmeSpareAWB2();
	virtual void bfmeSpareAWB3();
	virtual void bfmeSpareAWB4();
	virtual void bfmeSpareAWB5();
	virtual void bfmeSpareAWB6();
	virtual void bfmeSpareAWB7();
	virtual void bfmeSpareAWB8();
	virtual void *bfmeMakeAWB();
};

extern BfmeMakerAWB *g_bfmeMakerAWB;

struct BfmeNodeAWB
{
	unsigned char m_bfmeHead[0x28];
	bool m_bfmeFlag;
	unsigned char m_bfmePad[3];
	int m_bfmeZero;
	void *m_bfmeWhat;
};

class BfmeKeyAWB
{
public:
	BfmeNodeAWB *bfmeFindAWB();
};

void bfmeGoAWB(BfmeKeyAWB *key)
{
	if (key == 0)
		return;
	BfmeNodeAWB *node = key->bfmeFindAWB();
	if (node == 0)
		return;
	void *have = node->m_bfmeWhat;
	node->m_bfmeFlag = true;
	node->m_bfmeZero = 0;
	if (have == 0)
		node->m_bfmeWhat = g_bfmeMakerAWB->bfmeMakeAWB();
}
