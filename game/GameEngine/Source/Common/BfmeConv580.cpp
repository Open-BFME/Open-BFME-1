struct BfmeThingCDB
{
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeVal;
	unsigned char m_bfmeGap[0x28];
	void *m_bfmeCur;
};

void bfmeApplyCDB(void *value, void *what);

void __stdcall bfmeGoCDB(BfmeThingCDB *thing, void *what)
{
	if (what != thing->m_bfmeCur)
	{
		bfmeApplyCDB(thing->m_bfmeVal, what);
		thing->m_bfmeCur = what;
	}
}
