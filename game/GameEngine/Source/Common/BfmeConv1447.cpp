// Open-BFME5 conversions.

// Retail 0x009A3200 frees every node through the global
// ?Release_Ref@...-free allocator at 0x00881EB0, which is the game's
// operator delete(void *) defined in game/Libraries/Source/WWVegas/WWLib/
// mem_ops.cpp, so the call is spelled with the real operator.

struct BfmeNodeVMN
{
	char m_bfmePad00[0x30];
	BfmeNodeVMN *m_bfme30;
};

class BfmeTableVMN
{
public:
	void bfmeClearVMN();
	BfmeNodeVMN *m_bfme00[0x2b7b];
	BfmeNodeVMN *m_bfmeadec;
};

void BfmeTableVMN::bfmeClearVMN()
{
	unsigned i;
	BfmeNodeVMN *p;

	for (i = 0; i < 0x2b7b; ++i)
	{
		p = m_bfme00[i];
		while (p != 0)
		{
			BfmeNodeVMN *n = p->m_bfme30;

			::operator delete(p);
			p = n;
		}
	}

	p = m_bfmeadec;
	while (p != 0)
	{
		BfmeNodeVMN *n = p->m_bfme30;

		::operator delete(p);
		p = n;
	}
}
