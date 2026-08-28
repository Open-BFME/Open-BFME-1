extern "C" unsigned char bfmeVftTJ[];

class BfmeThingTJ
{
public:
	void bfmeBaseTJ(void *one, void *two);
	BfmeThingTJ *bfmeInitTJ(void *one, void *two);
	void *m_bfmeVft;
};

BfmeThingTJ *BfmeThingTJ::bfmeInitTJ(void *one, void *two)
{
	bfmeBaseTJ(one, two);
	m_bfmeVft = bfmeVftTJ;
	return this;
}
