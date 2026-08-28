struct BfmeThingBHH
{
	unsigned char m_bfmeHead[0x60];
	bool m_bfmeFlag;
};

void bfmeTailBHH(BfmeThingBHH *what);

void bfmeGoBHH(BfmeThingBHH *what)
{
	if (what->m_bfmeFlag)
		bfmeTailBHH(what);
}
