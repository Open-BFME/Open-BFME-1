// ?bfmeUpdateYF@BfmeHostYF@@QAEXUBfmeHandleYF@@@Z
// partial score=0.95 date=2026-09-09
class BfmeObjYF
{
public:
	unsigned char m_bfmeHeadYF[0x10];
	int m_bfme10YF;
	unsigned char m_bfmeMidYF[0x24 - 0x14];
	int m_bfme24YF;
	int m_bfme28YF;
	unsigned char m_bfmeMid2YF[0x30 - 0x2c];
	int m_bfme30YF;
	unsigned char m_bfmeMid3YF[0x3c - 0x34];
	int m_bfme3CYF;
};

struct BfmeHandleYF
{
	__forceinline BfmeHandleYF(const BfmeHandleYF &o) { m_bfmePtrYF = o.m_bfmePtrYF; }

	BfmeObjYF *m_bfmePtrYF;
};

int bfmeCalcYF(int a, int b, int *p, int *q);
void bfmeApplyYF(int a, int b);

class BfmeHostYF
{
public:
	void bfmeUpdateYF(BfmeHandleYF h);
	void bfmeNoteYF(BfmeHandleYF h);
};

void BfmeHostYF::bfmeUpdateYF(BfmeHandleYF h)
{
	BfmeObjYF *o = h.m_bfmePtrYF;

	bfmeNoteYF(h);

	int n = o->m_bfme28YF;
	int v = 0;

	if (bfmeCalcYF(o->m_bfme24YF, n, &v, &v) != n)
	{
		if (o->m_bfme3CYF != 2)
		{
			bfmeApplyYF(o->m_bfme10YF, 2);
			o->m_bfme3CYF = 2;
		}

		o->m_bfme30YF = 2;
	}
}
