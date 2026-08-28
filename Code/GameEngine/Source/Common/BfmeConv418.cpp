extern "C" unsigned char bfmeVftARDa[];
extern "C" unsigned char bfmeVftARDb[];
extern "C" unsigned char bfmeVftARDc[];

class BfmeThingARD
{
public:
	void bfmeBaseARD(void *one, void *two);
	BfmeThingARD *bfmeInitARD(void *one, void *two);
	void *m_bfmeVftA;
	unsigned char m_bfmeGap[8];
	void *m_bfmeVftB;
	void *m_bfmeVftC;
};

BfmeThingARD *BfmeThingARD::bfmeInitARD(void *one, void *two)
{
	bfmeBaseARD(one, two);
	m_bfmeVftA = bfmeVftARDa;
	m_bfmeVftB = bfmeVftARDb;
	m_bfmeVftC = bfmeVftARDc;
	return this;
}
