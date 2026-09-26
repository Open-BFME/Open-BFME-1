class UnicodeString
{
public:
	void set(const UnicodeString &o);
};

class BfmeElemXF
{
public:
	~BfmeElemXF();
};

class BfmeBaseXF
{
public:
	BfmeBaseXF &operator=(const BfmeBaseXF &o);

	unsigned char m_bfmeHeadXF[0xc];
};

class BfmeMapXF : public BfmeBaseXF
{
public:
	void bfmeAssignXF(const BfmeMapXF &o);

	UnicodeString m_bfmeTextXF;
	BfmeElemXF *m_bfmeSlotXF[4];
};

void BfmeMapXF::bfmeAssignXF(const BfmeMapXF &o)
{
	if (&o == this)
		return;

	BfmeElemXF **q = m_bfmeSlotXF;
	int n = 4;

	do
	{
		BfmeElemXF *p = *q;

		if (p)
		{
			delete p;
			*q = 0;
		}

		q++;
	}
	while (--n);

	BfmeBaseXF::operator=(o);
	m_bfmeTextXF.set(o.m_bfmeTextXF);
}
