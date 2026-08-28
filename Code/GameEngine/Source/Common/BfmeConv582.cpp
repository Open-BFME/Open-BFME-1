class BfmeThingCDD
{
public:
	void bfmeOneCDD(void *one, void *two);
	void bfmeTwoCDD(void *value);
	void bfmeGoCDD(void *one, void *two);
	unsigned char m_bfmeHead[0x4da8];
	void *m_bfmeVal;
};

void BfmeThingCDD::bfmeGoCDD(void *one, void *two)
{
	bfmeOneCDD(one, two);
	bfmeTwoCDD(m_bfmeVal);
}
