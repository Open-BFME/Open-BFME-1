struct BfmeThingCHG
{
	unsigned char m_bfmeHead[0x9c];
	unsigned char m_bfmeA[4];
	unsigned char m_bfmeB[0xc];
	unsigned char m_bfmeC[4];
};

void bfmeTailCHG(void *one, void *two, void *three, void *four);

void bfmeGoCHG(void *one, BfmeThingCHG *thing, void *three, void *four)
{
	if (thing == 0)
		return;
	bfmeTailCHG(one, thing->m_bfmeB, thing->m_bfmeC, thing->m_bfmeA);
}
