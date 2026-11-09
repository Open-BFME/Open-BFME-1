class BfmeRefCAD
{
public:
	void bfmeDtorCAD();
	unsigned char m_bfmeHead[0x10];
	int m_bfmeCount;
};

// bfmeDtorCAD is reached through ILT 0x00030841, which the ledger defines as j_00030841.
extern void j_00030841();

class BfmeThingCAD
{
public:
	void bfmeGoCAD();
	BfmeRefCAD *m_bfmeRef;
};


void BfmeThingCAD::bfmeGoCAD()
{
	--m_bfmeRef->m_bfmeCount;
	BfmeRefCAD *ref = m_bfmeRef;
	if (ref->m_bfmeCount == 0)
	{
		if (m_bfmeRef != 0)
		{
			typedef void (BfmeRefCAD::*DtorCall)();
			union { void (*raw)(); DtorCall member; } dtor;
			dtor.raw = j_00030841;
			(ref->*dtor.member)();
			::operator delete(ref);
		}
	}
}
