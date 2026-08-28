struct BfmeThingDBE
{
	void *m_bfmeX;
};

int bfmeTailDBE(BfmeThingDBE *a);

int bfmeGoDBE(BfmeThingDBE *a)
{
	if (a == 0)
		return 0;
	if (a->m_bfmeX == 0)
		return 0;
	return bfmeTailDBE(a);
}
