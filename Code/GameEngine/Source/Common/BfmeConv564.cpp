class BfmeRefCAD
{
public:
	void bfmeDtorCAD();
	unsigned char m_bfmeHead[0x10];
	int m_bfmeCount;
};

class BfmeThingCAD
{
public:
	void bfmeGoCAD();
	BfmeRefCAD *m_bfmeRef;
};

void bfmeFreeCAD(void *what);

void BfmeThingCAD::bfmeGoCAD()
{
	--m_bfmeRef->m_bfmeCount;
	BfmeRefCAD *ref = m_bfmeRef;
	if (ref->m_bfmeCount == 0)
	{
		if (m_bfmeRef != 0)
		{
			ref->bfmeDtorCAD();
			bfmeFreeCAD(ref);
		}
	}
}
