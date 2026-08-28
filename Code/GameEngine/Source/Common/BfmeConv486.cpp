class BfmeSubBLE
{
public:
	void bfmeTailBLE();
};

class BfmeThingBLE
{
public:
	void bfmeStepBLE();
	void bfmeGoBLE();
	unsigned char m_bfmeHead[0x28c];
	BfmeSubBLE *m_bfmeSub;
};

void BfmeThingBLE::bfmeGoBLE()
{
	bfmeStepBLE();
	BfmeSubBLE *sub = m_bfmeSub;
	if (sub != 0)
		sub->bfmeTailBLE();
}
