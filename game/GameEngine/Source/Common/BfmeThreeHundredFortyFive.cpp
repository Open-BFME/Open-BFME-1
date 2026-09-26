extern "C" unsigned char bfmeVftTF[];

class BfmeThingTF
{
public:
	void bfmeBaseTF(int what);
	BfmeThingTF *bfmeInitTF(void *what);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x4c];
	void *m_bfmeWhat;
};

BfmeThingTF *BfmeThingTF::bfmeInitTF(void *what)
{
	bfmeBaseTF(0);
	m_bfmeWhat = what;
	m_bfmeVft = bfmeVftTF;
	return this;
}
