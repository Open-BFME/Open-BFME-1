extern "C" unsigned char bfmeVftTC[];

class BfmeThingTC
{
public:
	void bfmeBaseTC();
	BfmeThingTC *bfmeInitTC(void *what);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeWhat;
};

BfmeThingTC *BfmeThingTC::bfmeInitTC(void *what)
{
	bfmeBaseTC();
	m_bfmeWhat = what;
	m_bfmeVft = bfmeVftTC;
	return this;
}
