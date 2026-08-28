extern "C" unsigned char bfmeVftAGBa[];
extern "C" unsigned char bfmeVftAGBb[];
extern "C" unsigned char bfmeVftAGBc[];
extern "C" unsigned char bfmeVftAGBd[];
extern "C" unsigned char bfmeVftAGBe[];

class BfmeThingAGB
{
public:
	void bfmeBaseAGB(void *one, void *two);
	BfmeThingAGB *bfmeInitAGB(void *one, void *two);
	void *volatile m_bfmeVftA;
	unsigned char m_bfmeGap[8];
	void *volatile m_bfmeVftB;
	void *volatile m_bfmeVftC;
	bool m_bfmeFlag;
};

BfmeThingAGB *BfmeThingAGB::bfmeInitAGB(void *one, void *two)
{
	bfmeBaseAGB(one, two);
	m_bfmeVftB = bfmeVftAGBa;
	m_bfmeVftC = bfmeVftAGBb;
	m_bfmeVftA = bfmeVftAGBc;
	m_bfmeVftB = bfmeVftAGBd;
	m_bfmeVftC = bfmeVftAGBe;
	m_bfmeFlag = true;
	return this;
}
