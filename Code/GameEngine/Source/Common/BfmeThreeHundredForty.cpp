extern "C" unsigned char bfmeVftTA[];

class BfmeThingTA
{
public:
	void bfmeBaseTA();
	BfmeThingTA *bfmeInitTA();
	void *m_bfmeVft;
};

BfmeThingTA *BfmeThingTA::bfmeInitTA()
{
	m_bfmeVft = bfmeVftTA;
	bfmeBaseTA();
	return this;
}
