struct BfmeThingBHG
{
	unsigned char m_bfmeHead[0x259];
	bool m_bfmeFlag;
};

extern BfmeThingBHG *g_bfmeThingBHG;

void bfmeTailBHG();

void bfmeGoBHG()
{
	if (g_bfmeThingBHG != 0)
		g_bfmeThingBHG->m_bfmeFlag = false;
	bfmeTailBHG();
}
