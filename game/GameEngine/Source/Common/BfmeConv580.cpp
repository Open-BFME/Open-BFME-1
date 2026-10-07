struct BfmeThingCDB
{
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeVal;
	unsigned char m_bfmeGap[0x28];
	void *m_bfmeCur;
};

// ILT 0x0001224C -> 0x0051B130, the matched bfmeGo1064C@@YAXHH@Z.
void bfmeGo1064C(int value, int what);

void __stdcall bfmeGoCDB(BfmeThingCDB *thing, void *what)
{
	if (what != thing->m_bfmeCur)
	{
		bfmeGo1064C((int)thing->m_bfmeVal, (int)what);
		thing->m_bfmeCur = what;
	}
}
