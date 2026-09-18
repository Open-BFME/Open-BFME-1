// Open-BFME5 conversions.

struct BfmeRec1039
{
	int m_bfmeKind;
	char m_bfmePad[4];
	int m_bfmeVal;
	char m_bfmePad2[4];
};

struct BfmeQ1039
{
	BfmeRec1039 *m_bfmeCur;
	char m_bfmePad[4];
	BfmeRec1039 *m_bfmeEnd;
};

void bfmeGrow1039(BfmeQ1039 *q, int n);

void bfmeGo1039E(BfmeQ1039 *q, int v)
{
	q->m_bfmeCur->m_bfmeKind = 6;
	q->m_bfmeCur->m_bfmeVal = v;

	if (q->m_bfmeCur == q->m_bfmeEnd)
		bfmeGrow1039(q, 1);

	q->m_bfmeCur++;
}
